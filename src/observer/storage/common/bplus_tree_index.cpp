/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its
affiliates. All rights reserved. miniob is licensed under Mulan PSL v2. You can
use this software according to the terms and conditions of the Mulan PSL v2. You
may obtain a copy of Mulan PSL v2 at: http://license.coscl.org.cn/MulanPSL2 THIS
SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by wangyunlai.wyl on 2021/5/19.
//

#include "storage/common/bplus_tree_index.h"
#include "common/log/log.h"
#include <algorithm>

BplusTreeIndex::~BplusTreeIndex() noexcept { close(); }

RC BplusTreeIndex::create(const char *file_name, const IndexMeta &index_meta,
                          const FieldMeta &field_meta) {
  if (inited_) {
    return RC::RECORD_OPENNED;
  }

  RC rc = Index::init(index_meta, field_meta);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  rc = index_handler_.create(file_name, field_meta.type(), field_meta.len());
  if (RC::SUCCESS == rc) {
    inited_ = true;
  }
  return rc;
}

RC BplusTreeIndex::create(const char *file_name, const IndexMeta &index_meta,
                          std::vector<const FieldMeta *> &field_metas) {
  if (inited_) {
    return RC::RECORD_OPENNED;
  }

  RC rc = Index::init(index_meta, field_metas);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  std::vector<AttrType> attr_vec;
  std::vector<int> len_vec;
  std::vector<int> offsets;
  for (auto it : field_metas) {
    attr_vec.push_back(it->type());
    len_vec.push_back(it->len());
    offsets.push_back(it->offset());
  }
  rc = index_handler_.create_by_list(file_name, attr_vec, len_vec, offsets);
  if (RC::SUCCESS == rc) {
    inited_ = true;
  }
  return rc;
}

RC BplusTreeIndex::open(const char *file_name, const IndexMeta &index_meta,
                        const FieldMeta &field_meta) {
  if (inited_) {
    return RC::RECORD_OPENNED;
  }
  RC rc = Index::init(index_meta, field_meta);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  rc = index_handler_.open(file_name);
  if (RC::SUCCESS == rc) {
    inited_ = true;
  }
  return rc;
}

RC BplusTreeIndex::close() {
  if (inited_) {
    index_handler_.close();
    inited_ = false;
  }
  return RC::SUCCESS;
}

RC BplusTreeIndex::insert_entry(const char *record, const RID *rid) {
  if (index_meta_.field_num() == 0) {
    return index_handler_.insert_entry(record + field_meta_.offset(), rid);
  } else {
    std::vector<int> offsets;
    std::vector<AttrType> types;
    std::vector<int> lens;
    for (int i = 0; i < index_meta_.field_num(); i++) {
      offsets.push_back(field_meta_list_[i]->offset());
      types.push_back(field_meta_list_[i]->type());
      lens.push_back(field_meta_list_[i]->len());
    }
    return index_handler_.insert_entry_multi_index(record, rid, offsets, types,
                                                   lens);
  }
}

RC BplusTreeIndex::delete_entry(const char *record, const RID *rid) {
  return index_handler_.delete_entry(record + field_meta_.offset(), rid);
}

RC BplusTreeIndex::delete_entry_multi_index(const char *record,
                                            const RID *rid) {
  std::vector<int> offsets;
  std::vector<AttrType> types;
  std::vector<int> lens;
  for (int i = 0; i < index_meta_.field_num(); i++) {
    offsets.push_back(field_meta_list_[i]->offset());
    types.push_back(field_meta_list_[i]->type());
    lens.push_back(field_meta_list_[i]->len());
  }

  return index_handler_.delete_entry_multi_index(record, rid, offsets, types,
                                                 lens);
}

IndexScanner *BplusTreeIndex::create_scanner(CompOp comp_op,
                                             const char *value) {
  BplusTreeScanner *bplus_tree_scanner = new BplusTreeScanner(index_handler_);
  RC rc = bplus_tree_scanner->open(comp_op, value);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open index scanner. rc=%d:%s", rc, strrc(rc));
    delete bplus_tree_scanner;
    return nullptr;
  }

  BplusTreeIndexScanner *index_scanner =
      new BplusTreeIndexScanner(bplus_tree_scanner);
  return index_scanner;
}

IndexScanner *
BplusTreeIndex::create_scanner_multi_index(std::vector<std::string> value_list,
                                           std::vector<CompOp> comop_list) {
  BplusTreeScanner *bplus_tree_scanner = new BplusTreeScanner(index_handler_);
  RC rc = bplus_tree_scanner->open_multi_index(value_list, comop_list);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open index scanner. rc=%d:%s", rc, strrc(rc));
    delete bplus_tree_scanner;
    return nullptr;
  }

  BplusTreeIndexScanner *index_scanner =
      new BplusTreeIndexScanner(bplus_tree_scanner);
  return index_scanner;
}

RC BplusTreeIndex::sync() { return index_handler_.sync(); }

////////////////////////////////////////////////////////////////////////////////
BplusTreeIndexScanner::BplusTreeIndexScanner(BplusTreeScanner *tree_scanner)
    : tree_scanner_(tree_scanner) {}

BplusTreeIndexScanner::~BplusTreeIndexScanner() noexcept {
  tree_scanner_->close();
  delete tree_scanner_;
}

RC BplusTreeIndexScanner::next_entry(RID *rid) {
  return tree_scanner_->next_entry(rid);
}

RC BplusTreeIndexScanner::destroy() {
  delete this;
  return RC::SUCCESS;
}