#pragma once

#include "CCommand.h"
#include "../Event/CEvent.h"
#include "../Operation/COperation.h"

class CFindEvent : public CCommand{
public:
    CFindEvent();
    CFindEvent(const CFindEvent & rhs);
    CFindEvent & operator = (const CFindEvent & rhs);
    bool execute(CCalendar &calendar, std::unique_ptr<CDisplayMode> &displayMode) const override;

    std::unique_ptr<CCommand> clone()const override;

    std::ostream &print(std::ostream &out) const override;

private:
    /**Ask the user, if he wants to find events by name or by place and find them all
     * @param foundEvents Found events
     * @param calendar    Source of the events
     * @return true(events successfully found), false(invalid input or none event was found)*/
    static bool findEvents(std::vector <std::shared_ptr<CEvent>> &foundEvents, const CCalendar &calendar);
    /**Print every found event so user can choose the one he wants to work with
     * @param foundEvents Found events that will be printed*/
    static void printEvents(const std::vector <std::shared_ptr<CEvent>> &foundEvents);
    /** Print every available operation*/
    void printOperations()const;
    /**Process the operation and execute it
     * @param eventToWorkWith Event on which the operation will be executed on
     * @param calendar CCalendar object
     * @return true(Operation processed and executed successfully), false(an error has occurred - invalid input, invalid operation)*/
    bool processOperation(std::shared_ptr<CEvent>& eventToWorkWith, CCalendar & calendar)const;
    /** User chooses the event that he wants to work with
     * @param foundEvents Found events from which the user will chose an event
     * @return null_ptr (Invalid event choice), shared_ptr to chosen event*/
    static std::shared_ptr<CEvent>chooseEvent(const std::vector <std::shared_ptr<CEvent>> &foundEvents);
    std::map<std::string, std::unique_ptr<COperation>>m_Operations;
};



