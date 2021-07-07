#include "CAddEvent.h"

using namespace std;
bool CAddEvent::execute(CCalendar &calendar, std::unique_ptr<CDisplayMode> &displayMode) const {
    string name, place, recChoice;
    CDate eventDate;
    pair<int, int>startTime, endTime;
    vector<string>attendees;

    if(!CAddEvent::validInformation(name, place, eventDate, startTime, endTime, attendees, recChoice))
        return false;

    if(recChoice == "yes") {
        int recCount = 0, recDays = 0;
        if(!CPrompt::promptUniversal(recCount, "Enter how many times will the event repeat: "))
            return false;

        if(!CPrompt::promptUniversal(recDays, "After how many days will the event repeat: "))
            return false;

        if(!CAddEvent::createEvent(name, place, eventDate, startTime, endTime, attendees,recCount, recDays, calendar)){
            cout << "Unable to create recurring event" << endl;
            return false;
        }
    }else if(recChoice == "no"){
        CAddEvent::createEvent(name, place, eventDate, startTime, endTime, attendees, calendar);
    }else{
        cout << "Invalid choice" << endl;
        return false;
    }

    cout << "Event successfully added" << endl;
    displayMode->draw(calendar);
    return true;
}

std::ostream &CAddEvent::print(std::ostream &out) const {
    return out << "add - Add new event";
}


bool CAddEvent::createEvent(const std::string &name, const std::string &place, const CDate &eventDate,
                            std::pair<int, int> startTime,
                            std::pair<int, int> endTime, const std::vector<std::string> &attendees, int recCount,
                            int recDays,
                            CCalendar &calendar) {

    if(recCount <= 0 || recDays <= 0){
        cout << "Invalid info about recurring event" << endl;
        return false;
    }

    if(recCount > MAXRECCOUNT || recDays > MAXRECDAYS){
        cout << "Maximum for recurrence exceeded" << endl;
        return false;
    }

    CDate nextDate = eventDate;
    shared_ptr<CRecurringEvent>origEvent = make_shared<CRecurringEvent>(name, place, eventDate, startTime, endTime, attendees, recCount, recDays);
    shared_ptr<CRecurringEvent>prev = origEvent;
    calendar.getEvents()[eventDate].push_back(origEvent);
    //Link all the events, every event will have shared_ptr to original event(the first one) except the original event.
    //Then they will have shared_ptr to the next event and previous event, so it's a linked list. Important for move and remove operations.
    for(int i = 0; i < recCount; i++){
        shared_ptr<CRecurringEvent>tmp = make_shared<CRecurringEvent>(name,place, nextDate.incDays(recDays), startTime,
                                                                      endTime, attendees, recCount, recDays);
        tmp->setOriginalEvent(origEvent);
        tmp->setPrevEvent(prev);
        prev->setNextEvent(tmp);
        calendar.getEvents()[nextDate].push_back(tmp);

        prev = tmp;
    }

    return true;
}

bool CAddEvent::createEvent(const std::string &name, const std::string &place, const CDate &eventDate,
                            std::pair<int, int> startTime,
                            std::pair<int, int> endTime, const std::vector<std::string> &attendees,
                            CCalendar &calendar) {
    CEvent event(name, place,eventDate, startTime, endTime, attendees);
    calendar.getEvents()[eventDate].push_back(make_shared<CEvent>(event));

    return true;
}

unique_ptr<CCommand> CAddEvent::clone() const{
    return make_unique<CAddEvent>(*this);
}

bool CAddEvent::validInformation(string &name, string &place, CDate &eventDate, pair<int, int> &startTime,
                                 pair<int, int> &endTime, vector<std::string> &attendees, std::string & recChoice) {
    if(!CPrompt::promptForLine(name, "Enter the event name: "))
        return false;
    if(!CPrompt::promptForLine(place, "Enter the event place: "))
        return false;
    if(!CPrompt::promptForDate(eventDate))
        return false;
    if(!CPrompt::promptForTime(startTime))
        return false;
    if(!CPrompt::promptForTime(endTime, false))
        return false;

    if(!CValidator::checkTimeIntervals(startTime, endTime)){
        cout << "Invalid time intervals" << endl;
        return false;
    }

    if(!CPrompt::promptForAttendees(attendees))
        return false;
    if(!CPrompt::promptUniversal(recChoice, "Recurring event? (Yes/No): "))
        return false;
    CValidator::strToLower(recChoice);

    return true;
}

