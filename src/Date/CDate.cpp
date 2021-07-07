#include "CDate.h"
using namespace std;
const std::string CDate::WEEKDAYS[]={"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
const std::string CDate::MONTHNAMES[]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
const int CDate::DAYSINMONTH[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};



CDate::CDate()
:m_Now(time(nullptr)), m_Date(*localtime(&m_Now)){
}

CDate::CDate(int year, int month, int day) {
    m_Date.tm_year = year - 1900;
    m_Date.tm_mon = month - 1;
    m_Date.tm_mday = day;
    mktime(&m_Date);
}
CDate & CDate::nextMonth() {
    m_Date.tm_mon++;
    mktime(&m_Date);
    return *this;
}

CDate & CDate::prevMonth() {
    m_Date.tm_mon--;
    mktime(&m_Date);
    return *this;
}

CDate & CDate::nextWeek() {
    m_Date.tm_mday+=7;
    mktime(&m_Date);
    return *this;
}

CDate & CDate::prevWeek() {
    m_Date.tm_mday-=7;
    mktime(&m_Date);
    return *this;
}

CDate & CDate::nextDay() {
    m_Date.tm_mday++;
    mktime(&m_Date);
    return *this;
}

CDate & CDate::prevDay() {
    m_Date.tm_mday--;
    mktime(&m_Date);
    return *this;
}

std::ostream & operator<<(ostream &out, const CDate &rhs) {
    return out << rhs.m_Date.tm_mday << ". " << rhs.m_Date.tm_mon + 1 << ". " << rhs.m_Date.tm_year + 1900 ;
}
const std::string & CDate::getWeekDay()const {
    return CDate::WEEKDAYS[getWeekDayIdx()];
}
int CDate::getWeekDayIdx() const {
    return m_Date.tm_wday == 0 ? 6 : m_Date.tm_wday - 1;//by default week starts by sunday - idx 0, we want start by monday at idx 0
}
bool CDate::isLeapYear(int year){
    return year % 4000 == 0 ? false : (year % 400 == 0 ? true : (year % 100 == 0 ? false : (year % 4 == 0 ? true : false)));
}
int CDate::getYear() const {
    return m_Date.tm_year + 1900;
}
int CDate::getMonthIdx() const {
    return m_Date.tm_mon;
}

int CDate::getMonth() const {
    return getMonthIdx() + 1;
}

int CDate::getDay() const {
    return m_Date.tm_mday;
}

int CDate::getDaysInMonth() const {
    return CDate::MonthDays(getYear(), getMonth());
}

CDate CDate::getMonthBegin() const {
    return CDate(getYear(), getMonth(), 1);
}


CDate CDate::getWeekBegin() const {
    CDate weekBegin = *this;
    weekBegin.decDays(getWeekDayIdx());
    return weekBegin;
}

CDate CDate::getWeekEnd() const {
    CDate weekEnd = *this;
    weekEnd.incDays(CDate::DAYSINWEEK - getWeekDayIdx() - 1);
    return weekEnd;
}

int CDate::MonthDays(int year, int month) {
    if(CDate::isLeapYear(year) && month == 2)
        return 29;
    return CDate::DAYSINMONTH[month - 1];
}

bool CDate::isValidDate(int year, int month, int day) {
    if(month > 12 || month < 1 || year < 1900 || day < 1 || day > CDate::MonthDays(year, month))
        return false;
    return true;
}

CDate & CDate::decDays(int count) {
    m_Date.tm_mday -= count;
    mktime(&m_Date);
    return *this;
}

CDate & CDate::incDays(int count) {
    m_Date.tm_mday += count;
    mktime(&m_Date);
    return *this;
}

bool CDate::operator<( const CDate &rhs)const {
    if(m_Date.tm_year != rhs.m_Date.tm_year)
        return m_Date.tm_year < rhs.m_Date.tm_year;
    if(m_Date.tm_mon != rhs.m_Date.tm_mon)
        return m_Date.tm_mon < rhs.m_Date.tm_mon;
    return m_Date.tm_mday < rhs.m_Date.tm_mday;
}

bool CDate::operator==(const CDate &rhs) const {
    return !(*this < rhs) && !(rhs < *this);
}

bool CDate::operator!=(const CDate &rhs) const {
    return !(*this == rhs);
}

CDate CDate::parseDateString(const string &dateString) {
    int day, month, year;
    string datePart;

    stringstream ss (dateString);
    getline(ss, datePart, '.');
    day = stoi(datePart);

    getline(ss, datePart, '.');
    month = stoi(datePart);

    getline(ss, datePart, '.');
    year = stoi(datePart);

    if(!CDate::isValidDate(year, month, day))
        throw range_error("Invalid date range");

    return CDate(year, month, day);
}
