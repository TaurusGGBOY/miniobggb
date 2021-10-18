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

    int date_to_int(std::string date);
    int date_to_int(int date[]);
    std::string int_to_date(int day);
    bool is_legal(std::string date);
    bool is_common_year(int year);
    int *date_to_arr(std::string date);
    int compare(std::string date1, std::string date2);
};

#endif // __OBSERVER_STORAGE_COMMON_DATE_H_