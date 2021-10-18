#include <storage/common/date.h>
#include <regex>

static const int EVERY_DAYS[] = {-1, 31, 28, 31, 30, 31, 30, 1, 31, 30, 31, 30, 31};

static const std::regex p("[0-9]{4}-[0-9]{1,2}-[0-9]{1,2}");

static const int DIS_DAYS[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

int Date::date_to_int(std::string date)
{
    // TODO if implement this or not
    return 0;
}

std::string Date::int_to_date(int day)
{
    return "";
}

bool Date::is_legal(std::string date)
{

    std::smatch res;
    int *a = date_to_arr(date);
    if (a != nullptr)
    {
        // TODO no consider overflow
        int year = a[0];
        int month = a[1];
        int day = a[2];
        if (year < 0 || month < 0 || day < 0)
        {
            return false;
        }
        if (month >= 13 || day >= 31)
        {
            return false;
        }
        int standard = EVERY_DAYS[month];
        // if not common year and compare Feb.
        if (month == 2 && !is_common_year(year))
        {
            standard = 29;
        }
        return day <= standard;
    }
    return false;
}

bool Date::is_common_year(int year)
{
    // 400 is not common year
    if (year % 400 == 0)
    {
        return false;
    }
    // 100 is common year
    if (year % 100 == 0)
    {
        return true;
    }
    if (year % 4 == 0)
    {
        return false;
    }
    return true;
}

int *Date::date_to_arr(std::string date)
{
    // TODO if there is memory leakage
    std::smatch res;
    int a[3];
    if (std::regex_match(date, res, p))
    {
        // TODO no consider overflow
        a[0] = atoi(res.str(1).c_str());
        a[1] = atoi(res.str(2).c_str());
        a[2] = atoi(res.str(3).c_str());
        return a;
    }
    return nullptr;
}

int Date::compare(std::string date1, std::string date2)
{
    int *a1 = date_to_arr(date1);
    int *a2 = date_to_arr(date2);
    for (int i = 0; i < 3; i++)
    {
        if (a1[i] != a2[i])
        {
            return a1[i] - a2[i];
        }
    }
    return 0;
}