#ifndef DATE_CALCULATOR_H
#define DATE_CALCULATOR_H

#include <string>
#include <sstream>
#include <cstdlib>

/**
 * @class DateCalculator
 * @brief A utility class for simple date manipulations.
 *
 * Provides static methods to add months or years to a date string in "YYYY-MM-DD" format.
 * This is a lightweight implementation to avoid external libraries.
 */
class DateCalculator {
public:
    /**
     * @brief Adds a specified number of years to a date string.
     * @param dateStrParm The date string in "YYYY-MM-DD" format.
     * @param yearsParm The number of years to add.
     * @return The new date string.
     */
    static std::string addYears(const std::string& dateStrParm, int yearsParm) {
        int sYear, sMonth, sDay;
        pParseDate(dateStrParm, sYear, sMonth, sDay);
        sYear += yearsParm;
        return pFormatDate(sYear, sMonth, sDay);
    }

    /**
     * @brief Adds a specified number of months to a date string.
     * @param dateStrParm The date string in "YYYY-MM-DD" format.
     * @param monthsParm The number of months to add.
     * @return The new date string.
     */
    static std::string addMonths(const std::string& dateStrParm, int monthsParm) {
        int sYear, sMonth, sDay;
        pParseDate(dateStrParm, sYear, sMonth, sDay);

        int sTotalMonths = (sYear * 12) + (sMonth - 1) + monthsParm;
        sYear = sTotalMonths / 12;
        sMonth = (sTotalMonths % 12) + 1;
        
        return pFormatDate(sYear, sMonth, sDay);
    }

private:
    /**
     * @brief Parses a "YYYY-MM-DD" string into integer components.
     * @param dateStrParm The date string to parse.
     * @param yearOut The output parameter for the year.
     * @param monthOut The output parameter for the month.
     * @param dayOut The output parameter for the day.
     */
    static void pParseDate(const std::string& dateStrParm, int& yearOut, int& monthOut, int& dayOut) {
        yearOut  = std::atoi(dateStrParm.substr(0, DateYearLength).c_str());
        monthOut = std::atoi(dateStrParm.substr(DateYearLength + DateSeparatorLength, DateMonthLength).c_str());
        dayOut   = std::atoi(dateStrParm.substr(DateYearLength + DateSeparatorLength + DateMonthLength + DateSeparatorLength, DateDayLength).c_str());
    }

    /**
     * @brief Formats integer date components into a "YYYY-MM-DD" string.
     * @param yearParm The year.
     * @param monthParm The month.
     * @param dayParm The day.
     * @return A formatted date string.
     */
    static std::string pFormatDate(int yearParm, int monthParm, int dayParm) {
        std::ostringstream sStream;
        sStream << yearParm << "-" << std::setfill('0') << std::setw(DateMonthLength) << monthParm << "-" << std::setfill('0') << std::setw(DateDayLength) << dayParm;
        return sStream.str();
    }
};

#endif // DATE_CALCULATOR_H
