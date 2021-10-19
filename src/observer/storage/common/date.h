#ifndef __OBSERVER_STORAGE_COMMON_DATE_H_
#define __OBSERVER_STORAGE_COMMON_DATE_H_

#include <string>

// TODO if change this util class to others
class Date
{
private:
    Date() {}

public:
    static Date &get_instance()
    {
        static Date instance;
        return instance;
    }
    Date(Date const &) = delete;
    void operator=(Date const &) = delete;

    int date_to_int(const char * date);
    void int_to_date(int day, char* buf);
    bool is_legal(const char* date);
};

#endif // __OBSERVER_STORAGE_COMMON_DATE_H_