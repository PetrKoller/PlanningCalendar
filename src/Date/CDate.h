#pragma once

#include <ctime>
#include <iostream>
#include <memory>
#include <sstream>

class CDate {
public:

    static const int DAYSINWEEK = 7;
    static const std::string MONTHNAMES[12];
    static const std::string WEEKDAYS[7];
    static const int DAYSINMONTH[12];

    CDate();
    CDate(int year, int month, int day);
    /**Flips CDate to the next month
     * @return reference to CDate object */
    CDate & nextMonth();
    /**Flips CDate to the prev month
     * @return reference to CDate object */
    CDate & prevMonth();
    /**Flips CDate to the next week
     * @return reference to CDate object */
    CDate & nextWeek();
    /**Flips CDate to the prev week
     * @return reference to CDate object */
    CDate & prevWeek();
    /**Flips CDate to the next day
     * @return reference to CDate object */
    CDate & nextDay();
    /**Flips CDate to the prev day
     * @return reference to CDate object */
    CDate & prevDay();
    /** @return id of the weekday (0-6)*/
    int getWeekDayIdx()const;
    /** @return year converted from tm structure */
    int getYear()const;
    /** @return month converted from tm structure */
    int getMonth()const;
    /** @return day converted from tm structure */
    int getDay()const;
    /**Returns days in month of the CDate object
     * @return days in month*/
    int getDaysInMonth()const;
    /**@return month id (0 - 11)*/
    int getMonthIdx()const;
    /**Get begin of the month
     * @return Month begin of the CDate object*/
    CDate getMonthBegin()const;
    /**Get begin of the week
     * @return week begin of the CDate object*/
    CDate getWeekBegin()const;
    /**Get end of the week
     * @return Week end of the CDate object*/
    CDate getWeekEnd()const;
    /** @return name of the weekday */
    const std::string & getWeekDay()const;
    /** @param out
     * @param rhs
     * @return ostream*/
    friend std::ostream &operator << (std::ostream & out, const CDate & rhs);
    /**less than operator
     * @param rhs
     * @return true(*this is less than rhs), false(*this is not less than rhs)*/
    bool operator<(const CDate & rhs)const;
    /**equal operator
     * @param rhs
     * @return true(equal), false(not equal)
     */
    bool operator==(const CDate & rhs)const;
    /**not equal operator
     * @param rhs
     * @return true(not equal), false(equal)
     */
    bool operator!=(const CDate & rhs)const;
    /** Converts string into CDate object, if date is invalid, throws exception
     * @param dateString String to be converted into CDate object
     * @return CDate object corresponding to the given string
     */
    static CDate parseDateString(const std::string & dateString);
    /**Decreases days and converts to corresponding date
     * @param count Count of days to decrease
     * @return Reference to CDate object with decreased days
     */
    CDate & decDays(int count);
    /**Increases days and converts to corresponding date
     * @param count Count of days to increase
     * @return Reference to CDate object with increased days
     */
    CDate & incDays(int count);
private:
    /**Get the number of days of the month
     * @param year important for leaping years
     * @param month
     * @return corresponding number of days
     */
    static int MonthDays(int year, int month);
    /** Checks if the given year is leap
     * @param year year to be checked
     * @return true (leap), false (not leap)
     */
    static bool isLeapYear(int year);
    /** Checks if the given parameters creates valid date
     * @param year
     * @param month
     * @param day
     * @return true (valid), false(not valid)
     */
    static bool isValidDate(int year, int month, int day);
    std::time_t m_Now = 0;
    std::tm m_Date{};

};


