#ifndef __OBSERVER_STORAGE_COMMON_BITMAP_H_
#define __OBSERVER_STORAGE_COMMON_BITMAP_H_

#include <string>

// TODO if change this util class to others
class Bitmap
{
private:
    Bitmap() {}

public:
    static Bitmap &get_instance()
    {
        static Bitmap instance;
        return instance;
    }
    Bitmap(Bitmap const &) = delete;
    void operator=(Bitmap const &) = delete;
    void set_bit_at_index(const char* bitmap, int index, int is_null, char* buf);
    void set_bit_at_index_null(const char* bitmap, int index, char* buf);
    void set_bit_at_index_not_null(const char* bitmap, int index, char* buf);
    int get_null_at_index(const char* bitmap, int index);
    void tostring(const char* bitmap);
    bool contain_null(const char *bitmap);

};

#endif // __OBSERVER_STORAGE_COMMON_BITMAP_H_