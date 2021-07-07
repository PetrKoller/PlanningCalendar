#pragma once

#include <vector>
#include "CCommand.h"
#include "../Date/CDate.h"
#include "../Event/CEvent.h"
#include "../Event/CRecurringEvent.h"
#include "../Validator/CValidator.h"

class CAddEvent : public CCommand{
public:
    const static int MAXRECCOUNT = 1000;
    const static int MAXRECDAYS = 1000;
    bool execute(CCalendar &calendar, std::unique_ptr<CDisplayMode> &displayMode) const override;

    std::ostream &print(std::ostream &out) const override;

    std::unique_ptr<CCommand> clone() const override;
    /** Create the recurring event
     * @param name
     * @param place
     * @param eventDate
     * @param startTime
     * @param endTime
     * @param attendees
     * @param recCount
     * @param recDays
     * @param calendar
     * @return true(successfully created recurring event), false(event creation failed)*/
    static bool createEvent(const std::string &name, const std::string &place, const CDate &eventDate,
                            std::pair<int, int> startTime,
                            std::pair<int, int> endTime, const std::vector<std::string> &attendees, int recCount,
                            int recDays,
                            CCalendar &calendar);
    /** Create normal event
     * @param name
     * @param place
     * @param eventDate
     * @param startTime
     * @param endTime
     * @param attendees
     * @param calendar
     * @return true(successfully created recurring event), false(event creation failed)*/
    static bool createEvent(const std::string &name, const std::string &place, const CDate &eventDate,
                            std::pair<int, int> startTime,
                            std::pair<int, int> endTime, const std::vector<std::string> &attendees,
                            CCalendar &calendar);
private:
    /**Get all the information necessary for the event creation and validate them
     * @param name
     * @param place
     * @param eventDate
     * @param startTime
     * @param endTime
     * @param attendees
     * @param recChoice
     * @return true (All information is valid), false (Invalid information)*/
    static bool validInformation(std::string & name, std::string & place,CDate & eventDate, std::pair<int, int>&startTime, std::pair<int, int>&endTime,
                                 std::vector<std::string>&attendees, std::string & recChoice);
};



