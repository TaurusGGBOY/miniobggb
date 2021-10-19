#include <storage/common/date.h>
#include <regex>
#include <chrono>
#include <ctime>
#include <iomanip>

static const std::regex p("^(?:[0-9]{4}([-/.]?)(?:(?:0?[1-9]|1[0-2])([-/.]?)(?:0?[1-9]|1[0-9]|2[0-8])|(?:0?[13-9]|1[0-2])([-/.]?)(?:29|30)|(?:0?[13578]|1[02])([-/.]?)31)|(?:[0-9]{2}(?:0[48]|[2468][048]|[13579][26])|(?:0[48]|[2468][048]|[13579][26])00)([-/.]?)0?2([-/.]?)29)$");

int Date::date_to_int(const char * date)
{
    if(!is_legal(date)){
        return -1;
    }
    std::tm tm = {};
    strptime(date, "%Y-%m-%d", &tm);
    auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    auto hours = std::chrono::time_point_cast<std::chrono::hours>(tp).time_since_epoch().count();
    return (int)(hours/24);
}

void Date::int_to_date(int day, char* buf)
{
    long long seconds = day * 24 * 60 * 60;
    std::time_t t(seconds);
    struct tm *ptr=localtime(&t);
    strftime(buf,40,"%Y-%m-%d",ptr);
}

bool Date::is_legal(const char* date){
    std::smatch res;
    std::string date_str = std::string(date);
    if (std::regex_match(date_str, res, p))
    {
        return true;
    }
    return false;
}