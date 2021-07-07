#include "CFindEvent.h"
#include "../Operation/CRemove.h"
#include "../Operation/CEdit.h"
#include "../Operation/CMove.h"
using namespace std;
CFindEvent::CFindEvent() {
    m_Operations["remove"] = make_unique<CRemove>();
    m_Operations["edit"] = make_unique<CEdit>();
    m_Operations["move"] = make_unique<CMove>();
}

bool CFindEvent::execute(CCalendar &calendar, std::unique_ptr<CDisplayMode> &displayMode) const {
    vector<shared_ptr<CEvent>>foundEvents;

    if(!CFindEvent::findEvents(foundEvents, calendar))
        return true;

    CFindEvent::printEvents(foundEvents);

    shared_ptr<CEvent>eventToWorkWith = chooseEvent(foundEvents);
    if(eventToWorkWith == nullptr)
        return false;

    printOperations();

    if(!CFindEvent::processOperation(eventToWorkWith, calendar))
        return false;


    displayMode->draw(calendar);
    return true;
}

std::ostream &CFindEvent::print(std::ostream &out) const {
    return out << "find - Find events by name or place to perform operations (remove/move/edit)";
}

bool CFindEvent::findEvents(vector<shared_ptr<CEvent>> &foundEvents, const CCalendar &calendar) {
    bool findByName = true;
    string choice;
    string toFind;

    if(!CPrompt::promptUniversal(choice, "Find events by name or by place? (name/place): ")){
        cout << "Invalid choice" << endl;
        return false;
    }

    CValidator::strToLower(choice);

    if(choice == "place")
        findByName = false;
    else if(choice != "name")
        return false;

    if(findByName){
        if(!CPrompt::promptForLine(toFind, "Enter event name: "))
            return false;
    }else{
        if(!CPrompt::promptForLine(toFind, "Enter event place: "))
            return false;
    }

    for(const auto & day : calendar.getEvents()){
        for(const auto & event : day.second){
            if((findByName && event->getName() == toFind) || (!findByName && event->getPlace() == toFind))
                foundEvents.push_back(event);
        }
    }
    if(foundEvents.empty())
        return false;

    return true;
}

void CFindEvent::printEvents(const vector<std::shared_ptr<CEvent>> &foundEvents) {
    for(size_t i = 0; i < foundEvents.size(); i++)
        cout<<'\t' << i + 1 <<')'<< *(foundEvents[i]) << endl;
    cout << endl;
}

unique_ptr<CCommand> CFindEvent::clone()const {
    return make_unique<CFindEvent>(*this);

}

CFindEvent::CFindEvent(const CFindEvent &rhs) {
    for(const auto & op : rhs.m_Operations)
        m_Operations.insert({op.first, op.second->clone()});
}

CFindEvent &CFindEvent::operator=(const CFindEvent &rhs) {
    if(this == &rhs)
        return *this;

    auto tmp = CFindEvent(rhs);
    std::swap(m_Operations, tmp.m_Operations);
    return *this;
}

void CFindEvent::printOperations() const {
    cout << "Available operations with the event" << endl;

    for(const auto & op : m_Operations)
        cout << '\t' << *(op.second) << endl;
}

std::shared_ptr<CEvent> CFindEvent::chooseEvent(const vector<std::shared_ptr<CEvent>> &foundEvents) {
    size_t idxToChoose = 0;

    if(!CPrompt::promptUniversal(idxToChoose, "Type in the number of event you want to work with: "))
        return nullptr;

    if(idxToChoose == 0 || idxToChoose > foundEvents.size()){
        return nullptr;
    }

    return foundEvents.at(idxToChoose - 1);
}

bool CFindEvent::processOperation(shared_ptr<CEvent> &eventToWorkWith, CCalendar &calendar)const {
    string opChoice;
    if(!CPrompt::promptUniversal(opChoice, "Choose the operation: ")){
        cout << "Invalid input";
        return false;
    }
    CValidator::strToLower(opChoice);

    auto findOp = m_Operations.find(opChoice);
    if(findOp == m_Operations.end())
        return false;

    if(!m_Operations.at(opChoice)->execute(eventToWorkWith, calendar))
        return false;

    return true;
}

