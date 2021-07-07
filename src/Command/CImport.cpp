#include "CImport.h"
using namespace std;

bool CImport::execute(CCalendar &calendar, std::unique_ptr<CDisplayMode> &displayMode) const {
    string filename;
    if(!CPrompt::promptUniversal(filename, "Type in the filename: "))
        return false;

    ifstream file(filename);
    if(!file){
        cout << "Cannot open file " << filename << endl;
        return false;
    }

    string line;
    size_t lineNr = 0;
    while(getline(file, line)){
        istringstream iLine(line);
        if(!parseLine(iLine, calendar)){
            cout << "Invalid event format on line: " << lineNr + 1 << endl;
        }else
            cout << "Event on line " << lineNr + 1 << " added" << endl;

        lineNr++;
    }
    file.close();
    displayMode->draw(calendar);
    return true;
}

std::ostream &CImport::print(std::ostream &out) const {
    return out << "import - Import events from a given file";
}

std::unique_ptr<CCommand> CImport::clone()const {
    return make_unique<CImport>();
}

bool CImport::parseLine(istringstream &iLine, CCalendar & calendar) {
    //Correct format for recurring event: name;place; date; startTime; endTime;attendees separated by ',' ;recurring; recurrence count; recurrence days
    //Correct format for normal event: name;place; date; startTime; endTime;attendees separated by ',' ;normal
    //name and place takes in everything between the ';' because we want to save names and places with multiple words
    string eventName, eventPlace;
    CDate eventDate;
    pair<int, int>startTime;
    pair<int, int>endTime;
    vector<string>attendees;
    string eventType;
    int recCount = 0, recDays = 0;

    if(!parseString(eventName, iLine))
        return false;
    if(!parseString(eventPlace, iLine))
        return false;
    if(!parseDate(eventDate, iLine))
        return false;
    if(!parseTime(startTime, iLine))
        return false;
    if(!parseTime(endTime, iLine))
        return false;
    if(!CValidator::checkTimeIntervals(startTime, endTime))
        return false;
    if(!parseAttendees(attendees, iLine))
        return false;
    if(!parseWord(eventType, iLine))
        return false;

    if(eventType == "normal"){
        if(!iLine.eof())
            return false;
        CAddEvent::createEvent(eventName, eventPlace, eventDate, startTime, endTime, attendees, calendar);
        return true;
    }

    if(eventType == "recurring"){
        if(!parseRecurrence(recCount, iLine))
            return false;
        if(!parseRecurrence(recDays, iLine))
            return false;
        if(!iLine.eof())
            return false;

        if(!CAddEvent::createEvent(eventName, eventPlace, eventDate, startTime, endTime,attendees,recCount, recDays, calendar))
            return false;

        return true;
    }
    return false;
}

bool CImport::parseWord(string &input, istringstream &iLine) {
    string tmp;
    if(!getline(iLine, tmp, ';'))
        return false;
    istringstream iss(tmp);
    if(!CValidator::readInput(input, iss))
        return false;

    if(!CValidator::noExtraChar(iss))
        return false;
    return true;
}

bool CImport::parseString(string &input, istringstream &iLine) {
    string tmp;
    if(!getline(iLine, tmp, ';'))
        return false;
    istringstream iss(tmp);

    if(!CValidator::readLine(input, iss))
        return false;

    return true;
}

bool CImport::parseDate(CDate &eventDate, istringstream &iLine) {
    string dateString;
    if(!getline(iLine, dateString, ';'))
        return false;

    istringstream iss(dateString);
    if(!CValidator::processDate(eventDate, iss))
        return false;

    if(!CValidator::noExtraChar(iss))
        return false;

    return true;
}

bool CImport::parseTime(std::pair<int, int>&time, istringstream &iLine) {
    string timeString;
    if(!getline(iLine, timeString, ';'))
        return false;

    istringstream iss(timeString);

    if(!CValidator::readTimeFormat(time, iss))
        return false;
    if(!CValidator::noExtraChar(iss))
        return false;

    return true;
}

bool CImport::parseAttendees(vector<std::string> &attendees, istringstream &iLine) {
    string attendeesString;
    if(!getline(iLine, attendeesString, ';'))
        return false;

    istringstream iss(attendeesString);
    if(!CValidator::readAttendees(attendees, iss))
        return false;

    if(!CValidator::noExtraChar(iss))
        return false;

    return true;
}

bool CImport::parseRecurrence(int &recInfo, istringstream &iLine) {
    string info;
    if(!getline(iLine, info, ';'))
        return false;
    istringstream iss(info);

    if(!CValidator::readInput(recInfo, iss))
        return false;

    if(!CValidator::noExtraChar(iss))
        return false;

    return true;
}
