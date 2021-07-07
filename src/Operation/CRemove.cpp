#include "CRemove.h"

using namespace std;
bool CRemove::execute(shared_ptr<CEvent> &eventToWorkWith, CCalendar &calendar) const {
    vector<shared_ptr<CEvent>>eventsToRemove;
    bool fail = false;

    eventsToRemove = eventToWorkWith->remove(fail);
    if(fail){
        cout << "Unable to remove event" << endl;
        return false;
    }
    eventsToRemove.push_back(eventToWorkWith);
    if(!eventsToRemove.empty()){
        for(const auto & event : eventsToRemove){                                           //loop through all the events to remove
            auto removeDay = calendar.getEvents().find(event->getDate());                   //and remove them from the calendar
            auto eventIt = find(removeDay->second.begin(), removeDay->second.end(), event);
            if(eventIt != removeDay->second.end())
                removeDay->second.erase(eventIt);
        }
    }
    cout << "Successfully removed" << endl;
    return true;
}

std::ostream &CRemove::print(std::ostream &out) const {
    return out << "remove - remove specific event";
}

unique_ptr<COperation> CRemove::clone() const {
    return make_unique<CRemove>(*this);
}
