#pragma once
#include "CCommand.h"
#include "../Validator/CValidator.h"
#include "CAddEvent.h"
#include <fstream>
class CImport : public CCommand {
public:
    bool execute(CCalendar &calendar, std::unique_ptr<CDisplayMode> &displayMode) const override;

    std::ostream &print(std::ostream &out) const override;

    std::unique_ptr<CCommand> clone()const override;

private:
    /** Parse the whole line into information for event creation
     * @param iLine Line to be parsed
     * @param calendar Calendar where the event will be saved
     * @return true(event created), false(invalid format)*/
    static bool parseLine(std::istringstream & iLine, CCalendar & calendar);
    /**Parse word from the line
     * @param input Input where the result will be saved
     * @param iLine Source from where the word will be parsed
     * @return true (word successfully parsed), false (missing word or extra chars)*/
    static bool parseWord(std::string & input, std::istringstream & iLine);
    /**Parse the whole string from the line
     * @param input Input where the string will be saved
     * @param iLine Source from where the string will be parsed
     * @return true (successfully parsed), false (invalid)
     */
    static bool parseString(std::string & input, std::istringstream & iLine);
    /**Parse the event date from the line
     * @param eventDate Date where the result will be saved
     * @param iLine Source from where date will be parsed
     * @return true(Date successfully parsed), false(invalid date)*/
    static bool parseDate(CDate & eventDate, std::istringstream & iLine);
    /**Parse time from the line
     * @param time Variable, where the time will be stored
     * @param iLine iLine Source from where time will be parsed
     * @return true (Time successfully parsed), false(invalid time format) */
    static bool parseTime(std::pair<int, int>&time, std::istringstream & iLine);
    /** Parse attendees' emails from the line
     * @param attendees Vector where the emails will be stored
     * @param iLine Source from where data will be parsed
     * @return true(emails parsed successfully), false(invalid email format)*/
    static bool parseAttendees(std::vector<std::string> & attendees, std::istringstream & iLine);
    /**Parse the info about the recurrence if the event is recurring
     * @param recInfo recurrence info to be parsed
     * @param iLine Source from where the info will be parsed
     * @return true(successfully parsed), false(invalid info)*/
    static bool parseRecurrence(int & recInfo, std::istringstream & iLine);

};



