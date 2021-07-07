#pragma once
#include "../Date/CDate.h"
#include <iomanip>
#include <vector>
#include "../Validator/CValidator.h"
#include "../Prompt/CPrompt.h"
#include <map>
#include <set>

class CEvent {
public:
    CEvent(const std::string & name, const std::string & place, const CDate & date ,const std::pair<int, int>&startTime, const std::pair<int, int>&endTime, const std::vector<std::string>& attendees);
    /**Set the event date to specific date
     * @param date Date to be set
     * @return reference to CEvent*/
    CEvent & setDate(const CDate & date);
    /**@return Date of the event*/
    const CDate & getDate()const;
    /**@return Name of the event*/
    const std::string & getName()const;
    /**@return Place of the event*/
    const std::string & getPlace()const;
    /**@return Attendees of the event*/
    const std::vector<std::string>& getAttendees()const;
    /**@return Start of the event*/
    std::pair<int, int>getStartTime()const;
    /**@return End of the event*/
    std::pair<int, int>getEndTime()const;
    /**Print the event
     * @param out
     * @return ostream*/
    virtual std::ostream & print(std::ostream & out)const;
    /** less than operator
     * @param rhs
     * @return true(less than), false(not less than)*/
    bool operator<(const CEvent & rhs)const;
    /**output stream operator
     * @param out
     * @param rhs
     * @return ostream*/
    friend std::ostream & operator<<(std::ostream &out, const CEvent & rhs);
    /**Prepare events to be removed, unlink the event, relink etc.
     * @param fail an error occurred in the remove method
     * @return vector of events to be removed*/
    virtual std::vector<std::shared_ptr<CEvent>> remove(bool &fail);
    /**Edit the event and all recurring events
     * @param editedEvent Event with new, updated information
     * @return reference to edited event */
    virtual CEvent & edit(const CEvent &editedEvent);
    /**Set new date to the event and prepares events to be moved
     * @param dateToMove New date, where event will be moved
     * @param fail an error occurred in the move method
     * @return map where key is the date before change to remove events from calendar and insert them at new date*/
    virtual std::map<CDate, std::shared_ptr<CEvent>> move(const CDate &dateToMove, bool &fail);
    /**Get export stream to export event and returns events that will be marked as exported events
     * @param exportStream Stringstream of the event that will be exported into the file
     * @return set of events that will be marked as exported */
    virtual std::set<std::shared_ptr<CEvent>> exportEvent(std::ostringstream &exportStream);
    /**Compare events as shared_ptrs
     * @param lhs
     * @param rhs
     * @return true (lhs < rhs), false (lhs !< rhs)*/
    static bool cmpEvents(const std::shared_ptr<CEvent> & lhs, const std::shared_ptr<CEvent> & rhs);
protected:
    std::string m_Name;
    std::string m_Place;
    CDate m_EventDate;
    std::pair<int, int>m_StartTime;
    std::pair<int, int>m_EndTime;
    std::vector<std::string>m_Attendees;
    /**Get the base export stream that is same for every event
     * @return ostringstream*/
    virtual std::ostringstream  getBaseExportStream()const;
    /** @return ostringstream in format that will be exported to the file */
    virtual std::ostringstream  getExportStream()const;
};


