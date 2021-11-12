/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its
affiliates. All rights reserved. miniob is licensed under Mulan PSL v2. You can
use this software according to the terms and conditions of the Mulan PSL v2. You
may obtain a copy of Mulan PSL v2 at: http://license.coscl.org.cn/MulanPSL2 THIS
SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Longda on 2021/4/13.
//
#ifndef __OBSERVER_STORAGE_COMMON_PAGE_MANAGER_H_
#define __OBSERVER_STORAGE_COMMON_PAGE_MANAGER_H_

#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>

#include <string.h>
#include <sys/stat.h>
#include <time.h>

#include <vector>

#include "rc.h"
#include <unordered_map>
#include "common/log/log.h"

typedef int PageNum;

//
#define BP_INVALID_PAGE_NUM (-1)
#define BP_PAGE_SIZE (1 << 12)
#define BP_PAGE_DATA_SIZE (BP_PAGE_SIZE - sizeof(PageNum))
#define BP_FILE_SUB_HDR_SIZE (sizeof(BPFileSubHeader))
#define BP_BUFFER_SIZE 50
#define MAX_OPEN_FILE 1024

typedef struct {
    PageNum page_num;
    char data[BP_PAGE_DATA_SIZE];
} Page;
// sizeof(Page) should be equal to BP_PAGE_SIZE

typedef struct {
    PageNum page_count;
    int allocated_pages;
} BPFileSubHeader;

typedef struct Frame{
    bool dirty;
    unsigned int pin_count;
    int file_desc;
    Page page;
    struct Frame* prev;
    struct Frame* next;
} Frame;

typedef struct {
    bool open;
    Frame* frame;
} BPPageHandle;

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Mainly for demonstration purposes, i.e. works but is overly simple
        // In the real world, use sth. like boost.hash_combine
        return h1 ^ h2;  
    }
};

class BPFileHandle {
   public:
    BPFileHandle() { memset(this, 0, sizeof(*this)); }

   public:
    bool bopen;
    const char* file_name;
    int file_desc;
    Frame* hdr_frame;
    Page* hdr_page;
    char* bitmap;
    BPFileSubHeader* file_sub_header;
};

class BPManager {
   public:
    BPManager(int size = BP_BUFFER_SIZE) {
        this->size = size;
        head = new Frame();
        tail = new Frame();
        head->prev = nullptr;
        head->next = tail;
        tail->prev = head;
        tail->next = nullptr;
    }

    ~BPManager() {
        size = 0;
        for(auto iter=frame_map.begin();iter!=frame_map.end();++iter){
            Frame* frame = iter->second;
            frame->prev=nullptr;
            frame->next=nullptr;
            frame=nullptr;
        }
    }

    Frame* alloc() {
        if(frame_map.size()>=size){
            Frame* head_next = head->next;
            if(head_next!=tail){
                delete_frame_in_bpmanager(head_next);
            }else{
                return nullptr;
            }
        }
        Frame* frame = new Frame();
        add_frame_to_tail(frame);
        return frame;
    }

    Frame* get(int file_desc, PageNum page_num) {
        if(frame_map.count({file_desc, page_num})<=0){
            return nullptr;
        }
        Frame* frame = frame_map[{file_desc, page_num}];

        delete_frame_in_chain(frame);
        add_frame_to_tail(frame);
        return frame;
    }

   public:
    int size;
    std::unordered_map<std::pair<int, PageNum>, Frame*, pair_hash> frame_map;
    Frame* head = nullptr;
    Frame* tail = nullptr;

    public:
    void delete_frame_in_chain(Frame* frame){
        if(frame->next==nullptr&&frame->prev==nullptr){
            return;
        }
        Frame* l = frame->prev;
        Frame* r = frame->next;
        l->next = r;
        r->prev = l;
        frame->prev = nullptr;
        frame->next = nullptr;
    }

    void delete_frame_in_map(Frame* frame){
        if(frame==nullptr){
            return;
        }
        frame_map.erase({frame->file_desc, frame->page.page_num});
    }

    void delete_frame_in_bpmanager(Frame* frame) {
        delete_frame_in_chain(frame);
        delete_frame_in_map(frame);
    }

    void add_frame_to_tail(Frame* frame){
        Frame* prev_last = tail->prev;
        prev_last->next = frame;
        tail->prev = frame;
        frame->prev = prev_last;
        frame->next = tail;
    }

    int frame_map_size(){
        return frame_map.size();
    }


    int frame_map_count(int file_desc, PageNum page_num){
        return frame_map.count({file_desc, page_num});
    }

    void print_map(){
        for(auto iter=frame_map.begin();iter!=frame_map.end();++iter){
            printf("file_desc:%d, page num:%d, frame:%p ",iter->first.first, iter->first.second, iter->second);
            for(int i = 0;i<5;i++){
                printf("%d:%d,", i, *(int*)(iter->second->page.data+i*4));
            }
            printf("\n");
        }
    }

    void add_frame_to_map(Frame* frame){
        frame_map[{frame->file_desc,frame->page.page_num}] = frame;
    }
};

class DiskBufferPool {
   public:
    /**
     * 创建一个名称为指定文件名的分页文件
     */
    RC create_file(const char* file_name);

    /**
     * 根据文件名打开一个分页文件，返回文件ID
     * @return
     */
    RC open_file(const char* file_name, int* file_id);

    /**
     * 关闭fileID对应的分页文件
     */
    RC close_file(int file_id);

    /**
     * 根据文件ID和页号获取指定页面到缓冲区，返回页面句柄指针。
     * @return
     */
    RC get_this_page(int file_id, PageNum page_num, BPPageHandle* page_handle);

    /**
     * 在指定文件中分配一个新的页面，并将其放入缓冲区，返回页面句柄指针。
     * 分配页面时，如果文件中有空闲页，就直接分配一个空闲页；
     * 如果文件中没有空闲页，则扩展文件规模来增加新的空闲页。
     */
    RC allocate_page(int file_id, BPPageHandle* page_handle);

    /**
     * 根据页面句柄指针返回对应的页面号
     */
    RC get_page_num(BPPageHandle* page_handle, PageNum* page_num);

    /**
     * 根据页面句柄指针返回对应的数据区指针
     */
    RC get_data(BPPageHandle* page_handle, char** data);

    /**
     * 丢弃文件中编号为pageNum的页面，将其变为空闲页
     */
    RC dispose_page(int file_id, PageNum page_num);

    /**
     * 释放指定文件关联的页的内存， 如果已经脏， 则刷到磁盘，除了pinned page
     * @param file_handle
     * @param page_num 如果不指定page_num 将刷新所有页
     */
    RC force_page(int file_id, PageNum page_num);

    /**
     * 标记指定页面为“脏”页。如果修改了页面的内容，则应调用此函数，
     * 以便该页面被淘汰出缓冲区时系统将新的页面数据写入磁盘文件
     */
    RC mark_dirty(BPPageHandle* page_handle);

    /**
     * 此函数用于解除pageHandle对应页面的驻留缓冲区限制。
     * 在调用GetThisPage或AllocatePage函数将一个页面读入缓冲区后，
     * 该页面被设置为驻留缓冲区状态，以防止其在处理过程中被置换出去，
     * 因此在该页面使用完之后应调用此函数解除该限制，使得该页面此后可以正常地被淘汰出缓冲区
     */
    RC unpin_page(BPPageHandle* page_handle);

    /**
     * 获取文件的总页数
     */
    RC get_page_count(int file_id, int* page_count);

    RC flush_all_pages(int file_id);

   protected:
    RC allocate_block(Frame** buf);
    RC dispose_block(Frame* buf);

    /**
     * 刷新指定文件关联的所有脏页到磁盘，除了pinned page
     * @param file_handle
     * @param page_num 如果不指定page_num 将刷新所有页
     */
    RC force_page(BPFileHandle* file_handle, PageNum page_num);
    RC force_all_pages(BPFileHandle* file_handle);
    RC check_file_id(int file_id);
    RC check_page_num(PageNum page_num, BPFileHandle* file_handle);
    RC load_page(PageNum page_num, BPFileHandle* file_handle, Frame* frame);
    RC flush_block(Frame* frame);

   private:
    BPManager bp_manager_;
    BPFileHandle* open_list_[MAX_OPEN_FILE] = {nullptr};
};

DiskBufferPool* theGlobalDiskBufferPool();

#endif  //__OBSERVER_STORAGE_COMMON_PAGE_MANAGER_H_
