
#include "CEdit.h"
using namespace std;
bool CEdit::execute(shared_ptr<CEvent> &eventToWorkWith, CCalendar &calendar) const {
    vector<shared_ptr<CEvent>>eventsToEdit;

    string name, place;
    pair<int, int>startTime, endTime;
    vector<string>attendees;
    if(!validInformation(name, place, startTime, endTime, attendees)){
        cout << "Invalid information" << endl;
        return false;
    }
    auto editDay = calendar.getEvents().find(eventToWorkWith->getDate());
    auto eventIt = find(editDay->second.begin(), editDay->second.end(), eventToWorkWith);
    (*eventIt)->edit(CEvent(name,place, (*eventIt)->getDate(), startTime, endTime, attendees));

    cout << "Event successfully edited" << endl;
    return true;
}

std::ostream &CEdit::print(std::ostream &out) const {
    return out << "edit - Edit specification of the event";
}

std::unique_ptr<COperation> CEdit::clone() const {
    return make_unique<CEdit>();
}

bool CEdit::validInformation(string &name, string &place, pair<int, int> &startTime, pair<int, int> &endTime,
                             vector<std::string> &attendees) {
    if(!CPrompt::promptForLine(name, "Enter event name: "))
        return false;
    if(!CPrompt::promptForLine(place, "Enter event place: "))
        return false;
    if(!CPrompt::promptForTime(startTime))
        return false;
    if(!CPrompt::promptForTime(endTime, false))
        return false;
    if(!CValidator::checkTimeIntervals(startTime, endTime))
        return false;
    if(!CPrompt::promptForAttendees(attendees))
        return false;

    return true;
}
