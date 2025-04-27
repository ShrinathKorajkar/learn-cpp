#include <iostream>
#include <ctime>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

/*
    time_t  :-  time since Jan 1, 1970
    clock_t :-  processor time

    funcitions :
        a. time()     :-  current time as time_t value
        b. difftime() :-  diff btwn 2 time_t values in sec
        c. mktime()   :-  convert tm to time_t value
        d. ctime()    :-  convert time_t to string (Day Mon dd hh:mm:ss yyyy)
        e. localtime():-  local time zone fron time_t
        f. gmtime()   :-  convert time_t to universal time zone
        g. strftime() :-  format time represented in tm to specified format
        h. strptime() :-  convert string to tm representation
        i. clock()    :-  return processor time in clock_t value
        j. sleep()    :-  suspend execution
        k. nanosleep  :-  sleep for nanosec
        l. CLOCKS_PER_SEC :-  const for representing no of clock ticks
*/
int main()
{
    time_t now = time(nullptr);
    cout << "Current time : " << now;

    time_t end = time(nullptr);
    double diff = difftime(end, now);
    cout << "\nDiff : " << diff;

    struct tm timeInfo;
    timeInfo.tm_year = 121; // Year 2021
    timeInfo.tm_mon = 6;    // July (months are zero-based)
    timeInfo.tm_mday = 15;  // 15th
    timeInfo.tm_hour = 12;  // 12:00:00
    timeInfo.tm_min = 0;
    timeInfo.tm_sec = 0;

    time_t timestamp = mktime(&timeInfo);
    cout << "\nTimestamp : " << timestamp;

    char *timeStr = ctime(&now);
    cout << "\nCurrent time as string : " << timeStr;

    struct tm *localTime = localtime(&now);
    cout << "\nLocal time : " << asctime(localTime);

    struct tm *gmTime = gmtime(&now);
    cout << "\nUniversal time : " << asctime(gmTime);

    char buffer[80];
    strftime(buffer, sizeof(buffer), "\nFormatted time: %Y-%m-%d %H:%M:%S\n", localTime);
    cout << buffer;

    std::string dateTimeStr = "2023-09-07 03:11:36";
    std::tm tmStruct = {};
    std::istringstream ss(dateTimeStr);

    ss >> std::get_time(&tmStruct, "%Y-%m-%d %H:%M:%S");
    std::time_t timeValue = std::mktime(&tmStruct);
    std::cout << "Converted time_t value: " << timeValue << std::endl;
    return 0;
}