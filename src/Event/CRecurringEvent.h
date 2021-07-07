#pragma once

#include "CEvent.h"

class CRecurringEvent : public CEvent {
public:
    CRecurringEvent(const std::string & name,const std::string & place,const CDate & date, const std::pair<int, int>&startTime,
                    const std::pair<int, int>&endTime, const std::vector<std::string>& attendees, int recCount, int recDays);
    /**Set original event
     * @param originalEvent */
    void setOriginalEvent(const std::shared_ptr<CRecurringEvent>& originalEvent);
    /**Set previous event
     * @param prevEvent */
    void setPrevEvent(const std::shared_ptr<CRecurringEvent>& prevEvent);
    /**Set next event
     * @param nextEvent */
    void setNextEvent(const std::shared_ptr<CRecurringEvent>& nextEvent);

    std::ostream &print(std::ostream &out) const override;

    std::vector<std::shared_ptr<CEvent>> remove(bool &fail) override;

    CEvent & edit(const CEvent &editedEvent) override;

    std::map<CDate, std::shared_ptr<CEvent>> move(const CDate &dateToMove, bool &fail) override;

    std::set<std::shared_ptr<CEvent>> exportEvent(std::ostringstream &exportStream) override;



private:
    int m_RecCount;
    int m_RecDays;
    std::weak_ptr<CRecurringEvent>m_OriginalEvent;
    std::weak_ptr<CRecurringEvent>m_PrevEvent;
    std::weak_ptr<CRecurringEvent>m_NextEvent;
    /**Unlink the event and correct the links*/
    void unlinkEvent();
    std::ostringstream getExportStream() const override;
};



