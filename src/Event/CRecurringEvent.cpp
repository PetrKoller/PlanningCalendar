
#include "CRecurringEvent.h"

using namespace std;
CRecurringEvent::CRecurringEvent(const std::string &name,const std::string & place,const CDate & date, const std::pair<int, int> &startTime,
                                 const std::pair<int, int> &endTime, const std::vector<std::string> &attendees, int recCount, int recDays)
                                 : CEvent(name,place,date, startTime, endTime, attendees), m_RecCount(recCount), m_RecDays(recDays){
}

void CRecurringEvent::setOriginalEvent(const shared_ptr<CRecurringEvent> &originalEvent) {
    m_OriginalEvent = originalEvent;
}

void CRecurringEvent::setPrevEvent(const shared_ptr<CRecurringEvent> &prevEvent) {
    m_PrevEvent = prevEvent;
}

void CRecurringEvent::setNextEvent(const shared_ptr<CRecurringEvent> &nextEvent) {
    m_NextEvent = nextEvent;
}

ostream &CRecurringEvent::print(ostream &out) const {
    CEvent::print(out) << endl;
    if(m_RecCount != -1)
        cout <<'\t'<<'\t' << "Recurring event" << flush;

    return cout;

}

std::vector<std::shared_ptr<CEvent>> CRecurringEvent::remove(bool &fail) {
    string choice;
    if(!CPrompt::promptUniversal(choice,
                                 "Remove only this event or all recurring events? (yes - this event | no - all recurring events): ")){
        fail = true;
        return vector<shared_ptr<CEvent>>();
    }
    CValidator::strToLower(choice);

    vector<shared_ptr<CEvent>>eventsToRemove;
    if(choice == "no"){
        shared_ptr<CRecurringEvent>next = m_OriginalEvent.lock();
        if(next == nullptr)//original event                         //If next == nullptr then we work with the original event (the first one)
            next = m_NextEvent.lock();                              //and that event will be removed anyway in Remove operation so we skip to the
                                                                    //next one. After that we loop through every recurring event and push it
        while(next){                                                //into eventsToRemove
            eventsToRemove.push_back(next);
            next = next->m_NextEvent.lock();
        }
    }else if(choice == "yes"){//This event will be removed in Remove operation, so we have just to unlink it from others
        unlinkEvent();        //link together the previous and next event
    }else
        fail = true;

    return eventsToRemove;
}

CEvent & CRecurringEvent::edit(const CEvent &editedEvent) {
    m_Name = editedEvent.getName();
    m_Place = editedEvent.getPlace();
    m_StartTime = editedEvent.getStartTime();
    m_EndTime = editedEvent.getEndTime();
    m_Attendees = editedEvent.getAttendees();

    shared_ptr<CRecurringEvent>next = m_OriginalEvent.lock();
    if(next == nullptr)
        next = m_NextEvent.lock();

    while(next){
        next->m_Name = m_Name;
        next->m_Place = m_Place;
        next->m_StartTime = m_StartTime;
        next->m_EndTime = m_EndTime;
        next->m_Attendees = m_Attendees;

        next = next->m_NextEvent.lock();
    }
    return *this;
}

std::map<CDate, std::shared_ptr<CEvent>> CRecurringEvent::move(const CDate &dateToMove, bool &fail) {
    string choice;
    if(!CPrompt::promptUniversal(choice,
                                 "Move only this event or all recurring events? (yes - this event | no - all recurring events): ")){
        fail = true;
        return map<CDate, std::shared_ptr<CEvent>>();
    }
    CValidator::strToLower(choice);
                                                    //Moving events means changing their date, as the key we choose the date before moving event
    map<CDate, std::shared_ptr<CEvent>>eventsToMove;//then we set new date to the event. Then we can find the event in the calendar, remove it and
    if(choice == "no"){                             //push it to the new corresponding date in calendar.
        std::shared_ptr<CRecurringEvent>prev = m_PrevEvent.lock();
        std::shared_ptr<CRecurringEvent>next = m_NextEvent.lock();
        if(prev != nullptr){
            CDate newDate = dateToMove;
            while(prev){
                newDate.decDays(m_RecDays);
                eventsToMove.insert({prev->getDate(), prev});
                prev->m_EventDate = newDate;
                prev = prev->m_PrevEvent.lock();
            }                                         //We move all the recurring events so we have to
        }                                             //change all their dates to the corresponding
        if(next != nullptr){                          //ones and insert them into the map
            CDate newDate = dateToMove;
            while(next){
                newDate.incDays(m_RecDays);
                eventsToMove.insert({next->getDate(), next});
                next->m_EventDate = newDate;
                next = next->m_NextEvent.lock();
            }
        }
    }else if(choice == "yes"){
        unlinkEvent();          //We are moving only one event, we set RecCount -1 (just for exporting, there will be exported as normal event)
        m_RecCount = -1;        //and unlink it from the recurrence
    }else
        fail = true;
    cout << "Moving event to " << dateToMove << endl;
    return eventsToMove;
}

void CRecurringEvent::unlinkEvent() {
    shared_ptr<CRecurringEvent>next = m_OriginalEvent.lock();
    if(next == nullptr){//original event
        shared_ptr<CRecurringEvent>newOriginal = m_NextEvent.lock();
        if(newOriginal != nullptr){
            newOriginal->m_OriginalEvent.reset();       //The original event is being unlinked so we have to chose
            newOriginal->m_PrevEvent.reset();           //new original event (next event) and set him up.
            next = newOriginal->m_NextEvent.lock();     //Then we set this new original event to every recurring event
        }
        while(next){
            next->m_OriginalEvent = newOriginal;
            next = next->m_NextEvent.lock();
        }
    }else{//not original event
        m_PrevEvent.lock()->m_NextEvent = m_NextEvent.lock();     //not original event so we link previous event to the next event
        if(m_NextEvent.lock() != nullptr)                         // to remove this event from recurring, previous event always exists
            m_NextEvent.lock()->m_PrevEvent = m_PrevEvent.lock();// so we just take in account the next event, it might be null_ptr

    }
    m_NextEvent.reset();
    m_PrevEvent.reset();
    m_OriginalEvent.reset();
}

std::set<std::shared_ptr<CEvent>> CRecurringEvent::exportEvent(ostringstream &exportStream) {
    set<shared_ptr<CEvent>>eventsToExport;
    shared_ptr<CRecurringEvent>original = m_OriginalEvent.lock();
    if(original != nullptr)
        exportStream = original->getExportStream();  //we only want to export the original event
    else                                             //if original == null_ptr it means that we work with the original event
        exportStream = getExportStream();            //then insert all the recurring events into set, we want to mark them as exported

    shared_ptr<CRecurringEvent>next = m_NextEvent.lock();
    shared_ptr<CRecurringEvent>prev = m_PrevEvent.lock();
    while(next){
        eventsToExport.insert(next);
        next = next->m_NextEvent.lock();
    }
    while(prev){
        eventsToExport.insert(prev);
        prev = prev->m_PrevEvent.lock();
    }

    return eventsToExport;
}

ostringstream CRecurringEvent::getExportStream() const {
    if(m_RecCount == -1)
        return CEvent::getExportStream();

    ostringstream oss = getBaseExportStream();
    oss << ';' << "recurring" << ';' << m_RecCount << ';' << m_RecDays;
    return oss;
}

