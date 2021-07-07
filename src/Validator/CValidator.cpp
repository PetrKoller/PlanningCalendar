
#include <regex>
#include "CValidator.h"
using namespace std;
bool CValidator::validEmail(const std::string &email) {
    const regex emailPattern ("[a-zA-Z0-9_-]+(\\.[a-zA-Z0-9_-]+)?@[a-zA-Z0-9]+(\\.([a-zA-Z0-9]+))+\\s*");

    if(regex_match(email, emailPattern))
        return true;
    return false;
}

bool CValidator::validDateFormat(const std::string &date) {
    const regex dateFormat("(0?[1-9]|[12][0-9]|3[01])\\.(0?[1-9]|1[0-2])\\.[0-9]{4}");

    if(regex_match(date, dateFormat))
        return true;

    return false;
}

bool CValidator::readTimeFormat(pair<int, int> &time, std::istream & is) {
    char delimiter;
    if(!(is >> time.first >> noskipws >> delimiter >> skipws >> time.second) || delimiter != ':' || time.first > 23 || time.first < 0 || time.second > 59 || time.second < 0){
        is.clear();
        is.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}

bool CValidator::readAttendees(vector<std::string> &attendees, std::istream & is) {
    string attendee;
    string attendeesString;

    if(!getline(is, attendeesString)){
        cout << "Invalid attendee list" << endl;
        return false;
    }
    istringstream ss(attendeesString);

    while(getline(ss , attendee, ',')){
        istringstream attS(attendee);
        if(!CValidator::readInput(attendee, attS))
            return false;
        if(!CValidator::validEmail(attendee)){
            cout << attendee << " - invalid email address format " << endl;
            return false;
        }
        if(!CValidator::noExtraChar(attS))
            return false;

        attendees.push_back(trimTrailingSpaces(attendee));
    }

    if(!CValidator::noExtraChar(ss))
        return false;

    return true;
}

void CValidator::strToLower(string &stringToLower) {
    //used from https://en.cppreference.com/w/cpp/string/byte/tolower
    transform(stringToLower.begin(),stringToLower.end(),stringToLower.begin(),[](unsigned char c){return std::tolower(c); });
}

bool CValidator::processDate(CDate &date, std::istream & is) {
    string dateString;
    if(!CValidator::readInput(dateString, is)){
        cout << "Invalid input" << endl;
        return false;
    }
    if(!CValidator::validDateFormat(dateString)){
        std::cout << "Invalid date format" << std::endl;
        return false;
    }

    try {
        date = CDate::parseDateString(dateString);
    }catch(const std::range_error& e){
        std::cout << e.what() << std::endl;
        return false;
    }
    return true;
}

bool CValidator::checkTimeIntervals(pair<int, int> &startTime, pair<int, int> &endTime) {
    return startTime < endTime;
}

std::string &CValidator::trimTrailingSpaces(string &s) {
    //source: https://stackoverflow.com/questions/1798112/removing-leading-and-trailing-spaces-from-a-string
    const char* t = " \t\n\r\f\v";
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

std::string &CValidator::trimLeadingSpaces(string &s) {
    //source: https://stackoverflow.com/questions/1798112/removing-leading-and-trailing-spaces-from-a-string
    const char* t = " \t\n\r\f\v";
    s.erase(0, s.find_first_not_of(t));
    return s;
}

std::string &CValidator::trimAllSpaces(string &s) {
    //source: https://stackoverflow.com/questions/1798112/removing-leading-and-trailing-spaces-from-a-string
    return CValidator::trimLeadingSpaces(CValidator::trimTrailingSpaces(s));
}

bool CValidator::noExtraChar(istringstream &iLine) {
    char eChar;
    if(iLine >> eChar)
        return false;

    return true;
}

bool CValidator::readLine(string &input, istream &is) {
    string tmp;
    if(!getline(is, tmp))
        return false;
    istringstream iss(tmp);
    if(CValidator::noExtraChar(iss))
        return false;

    input = trimAllSpaces(tmp);

    return true;
}

