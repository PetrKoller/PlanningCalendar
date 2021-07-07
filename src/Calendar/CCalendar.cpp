#include "CCalendar.h"
using namespace std;

const CDate &CCalendar::getCurrentDate() const{
    return m_CurrentDate;
}

CDate &CCalendar::getCurrentDate() {
    return m_CurrentDate;
}

void CCalendar::setCalendarExit(bool state) {
    m_EndCalendar = state;
}

CDate &CCalendar::setDate(const CDate &date) {
    return m_CurrentDate = date;
}

const std::map<CDate, std::vector<std::shared_ptr<CEvent>>> &CCalendar::getEvents()const {
    return m_Events;
}

std::map<CDate, std::vector<std::shared_ptr<CEvent>>> &CCalendar::getEvents() {
    return m_Events;
}

bool CCalendar::getCalendarExit() const {
    return m_EndCalendar;
}