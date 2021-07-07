
#pragma once
#include <iostream>
#include <limits>
#include "../Date/CDate.h"
#include <vector>

class CValidator {
public:
    /**Template function for input reading
     * @tparam T
     * @param input Variable, where the input will be saved
     * @param is Input stream - form where the input will be processed, std::cin is default value
     * @return true(input successfully processed), false(input reading error)*/
    template<class T>
    static bool readInput(T & input, std::istream & is = std::cin){
        if(!(is >> input) && !is.eof()){
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return false;
        }
        return true;
    }
    /**Check if the given email is a valid format
     * @param email Email to be checked
     * @return true(valid), false(invalid)*/
    static bool validEmail(const std::string & email);
    /**Check if the given date string is in specified format DD.MM.YYYY
     * @param date Date string to be checked
     * @return true(valid), false(invalid)*/
    static bool validDateFormat(const std::string & date);
    /**Processes given time from cin and checks if time format is correct
     * @param time time.first represents hours, time.second represents minutes
     * @param is Input stream from where the time will be processed, default value is std::cin
     * @return true (valid), false (invalid)*/
    static bool readTimeFormat(std::pair<int, int>&time, std::istream & is = std::cin);
    /**Read attendees who are represented by email addresses
     * @param attendees vector where email addresses will be saved if parsing was successful
     * @param is Input stream from where email addresses will be parsed, default value is std::cin
     * @return (successfully parsed), (unsuccessfully parsed - invalid email format)*/
    static bool readAttendees(std::vector<std::string>&attendees, std::istream & is = std::cin);
    /**Transform given string to lower case
     * source https://en.cppreference.com/w/cpp/string/byte/tolower
     * @param stringToLower String to be transformed*/
    static void strToLower(std::string & stringToLower);
    /**Process date from input stream and convert it from the string to CDate object
     * @param date Date where final result will be saved
     * @param is Input stream from where the date string will be read
     * @return true(successfully processed), false(invalid date format)*/
    static bool processDate(CDate & date, std::istream & is = std::cin);
    /**Check if the first time interval is lower than the second one
     * @param startTime
     * @param endTime
     * @return true (is lower), false (is not lower)*/
    static bool checkTimeIntervals(std::pair<int, int>&startTime, std::pair<int, int>&endTime);
    /**Trim trailing spaces from the string
     * source: https://stackoverflow.com/questions/1798112/removing-leading-and-trailing-spaces-from-a-string
     * @param s String to be trimmed
     * @return trimmed string*/
    static std::string& trimTrailingSpaces(std::string& s);
    /**Trim leading spaces from the string
     * source: https://stackoverflow.com/questions/1798112/removing-leading-and-trailing-spaces-from-a-string
     * @param s String to be trimmed
     * @return trimmed string*/
    static std::string& trimLeadingSpaces(std::string & s);
    /**Trim leading and trailing spaces from the string
     * source: https://stackoverflow.com/questions/1798112/removing-leading-and-trailing-spaces-from-a-string
     * @param s String to be trimmed
     * @return trimmed string*/
    static std::string& trimAllSpaces(std::string & s);
    /**Check if in the line are extra characters except whitespaces
    * @param iLine Line to be checked
    * @return true(no extra characters), false(an extra character)*/
    static bool noExtraChar(std::istringstream & iLine);
    /** Read whole line and save it to the variable
     * @param input Variable where the input will be saved
     * @param is Input stream, default value is cin
     * @return bool true (successfully processed), false (invalid input or only whitespaces) */
    static bool readLine(std::string & input, std::istream & is = std::cin);
};



