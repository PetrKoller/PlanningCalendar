
#include "CPrompt.h"
using namespace std;

bool CPrompt::promptForDate(CDate &date) {
    cout << "Enter event date (DD.MM.YYYY): "<<flush;
    string tmp;
    if(!(getline(cin, tmp)))
        return false;

    istringstream iss(tmp);
    if(!CValidator::processDate(date, iss))
        return false;

    if(!CValidator::noExtraChar(iss))
        return false;

    return true;
}

bool CPrompt::promptForTime(pair<int, int> &time, bool startTime) {
    cout << "Enter event " << (startTime == true ? "start" : "end") << " time (HH:MM - 24H): "<<flush;
    string tmp;
    if(!(getline(cin, tmp)))
        return false;

    istringstream iss(tmp);
    if(!CValidator::readTimeFormat(time, iss)){
        cout << "Invalid time format" << endl;
        return false;
    }

    if(!CValidator::noExtraChar(iss))
        return false;

    return true;
}

bool CPrompt::promptForAttendees(vector<std::string> &attendees) {
    cout << "Enter attendees by their email addresses, separate them by comma ',' and end input by enter" << endl;
    string tmp;
    if(!(getline(cin, tmp)))
        return false;

    istringstream iss(tmp);
    if(!CValidator::readAttendees(attendees, iss))
        return false;
    if(!CValidator::noExtraChar(iss))
        return false;
    return true;
}

bool CPrompt::promptForLine(string &input, const string &call) {
    cout << call << flush;

    if(!CValidator::readLine(input))
        return false;

    return true;
}

