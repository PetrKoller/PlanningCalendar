#pragma once
#include "../Validator/CValidator.h"
#include "../Date/CDate.h"

class CPrompt {
public:
    /**Prompt the user to enter the date and process it
     * @param date Variable where the result will be saved
     * @return true(valid date), false(invalid date)*/
    static bool promptForDate(CDate & date);
    /** Prompt user to enter start time and end time of event
     * @param time Time where the result will be saved
     * @param startTime true(startTime), false(endTime)
     * @return true(valid time), false(invalid time format)*/
    static bool promptForTime(std::pair<int, int>&time, bool startTime = true);
    /**Prompt the user to enter attendees by their email addresses
     * @param attendees Vector where the addresses will be saved
     * @return true(valid addresses), false(invalid addresses)*/
    static bool promptForAttendees(std::vector<std::string>&attendees);
    /** Template function that prompts the user to enter specified information
     * @tparam T
     * @param input Variable where the processed information will be saved
     * @param call String that specifies what should the user enter as information
     * @return true(successfully processed), false(invalid input)*/
    template<class T>
    static bool promptUniversal(T & input, const std::string & call){
        std::cout << call << std::flush;
        std::string tmp;
        if(!(getline(std::cin, tmp)) || tmp.empty())
            return false;

        std::istringstream iss(tmp);
        if(!CValidator::readInput(input, iss)){
            std::cout << "Invalid input" << std::endl;
            return false;
        }

        if(!CValidator::noExtraChar(iss))
            return false;

        return true;
    }
    /**Prompt the user and read the whole line
     * @param input Input where the line will be saved
     * @param call Call to be printed
     * @return true(successfully processed), false(invalid input)*/
    static bool promptForLine(std::string & input, const std::string & call);
private:
};



