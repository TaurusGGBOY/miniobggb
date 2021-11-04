#include <storage/common/bitmap.h>
#include<cstring>

void Bitmap::set_bit_at_index(const char *bitmap, int index, int is_null, char *buf)
{
    // trx field as the first
    int value = *(int*)(bitmap);
    // printf("set input value:%d, index:%d, isnull:%d\n", value, index, is_null);
    // tostring(bitmap);
    if(is_null){
        value = value | 1 <<index;
    }else{
        value = value & ~(1 <<index);
    }
    memcpy(buf, &value, 4);  
    // printf("set output value:%d\n", *(int*)buf);
    // tostring(buf);
}

void Bitmap::set_bit_at_index_null(const char *bitmap, int index, char *buf)
{
    set_bit_at_index(bitmap, index, 1, buf);
}
void Bitmap::set_bit_at_index_not_null(const char *bitmap, int index, char *buf)
{
    set_bit_at_index(bitmap, index, 0, buf);
}

int Bitmap::get_null_at_index(const char *bitmap, int index)
{
    int value = *(int*)(bitmap);
    // printf("get input value:%d, index:%d\n", value, index);
    // tostring(bitmap);
    return value>>index & 1;
}
void Bitmap::tostring(const char* bitmap){
    char buf[33];
    int value = *(int*)bitmap;
    for(int i = 31;i>=0;i--){
        buf[i] = (value&1)+'0';
        value=value>>1;
    }
    buf[32] = '\0';
    printf("%s\n", buf);
}

bool Bitmap::contain_null(const char *bitmap){
    int value = *(int*)(bitmap);
    int res = 0;
    for(int i =0;i<=31;i++){
        res |= (1&value>>i);
    }
    return res==1;
}