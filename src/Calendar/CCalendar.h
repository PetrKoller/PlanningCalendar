#pragma once

#include "../Date/CDate.h"
#include "../Event/CEvent.h"
#include <map>
#include <memory>

class CCalendar {
public:
    CCalendar() = default;
    CCalendar(const CCalendar & rhs) = delete;
    CCalendar & operator=(const CCalendar & rhs) = delete;
    /** @return Reference to CDate object - current date */
    CDate & getCurrentDate();
    /** @return const reference to CDate object - current date */
    const CDate & getCurrentDate()const;
    /** Set the exit state for the calendar
     * @param state Exit state to be set */
    void setCalendarExit(bool state);
    /** Get the exit state from the calendar
     * @return true (Exit calendar), false (do not exit calendar) */
    bool getCalendarExit()const;
    /** Set the current date
     * @param date Date to be set
     * @return reference to CDate*/
    CDate & setDate(const CDate & date);
    /**@return const reference to events*/
    const std::map<CDate, std::vector<std::shared_ptr<CEvent>>>&getEvents()const;
    /**@return reference to events*/
    std::map<CDate, std::vector<std::shared_ptr<CEvent>>>&getEvents();

private:
    bool m_EndCalendar = false;
    CDate m_CurrentDate;
    std::map<CDate, std::vector<std::shared_ptr<CEvent>>>m_Events;
};



