
#include "CMove.h"
#include "../MoveStrategy/CClosestDaySameTime.h"
#include "../MoveStrategy/CSpecificDateSameTime.h"

using namespace std;

CMove::CMove() {
    m_MoveStrategies["day"] = make_unique<CClosestDaySameTime>();
    m_MoveStrategies["date"] = make_unique<CSpecificDateSameTime>();
}

bool CMove::execute(shared_ptr<CEvent> &eventToWorkWith, CCalendar &calendar) const {

    printMoveStrategies();
    string input;
    if(!CPrompt::promptUniversal(input, "Choose one of the strategies: "))
        return false;
    CValidator::strToLower(input);

    auto findStrategy = m_MoveStrategies.find(input);
    if(findStrategy == m_MoveStrategies.end()){
        cout << "Unknown move strategy" << endl;
        return false;
    }

    CDate possibleMoveDate = eventToWorkWith->getDate();

    if(!findStrategy->second->findPossibleDate(possibleMoveDate, calendar, eventToWorkWith)){
        cout << "Unable to find possible date corresponding to the move strategy" << endl;
        return false;
    }

    if(!CMove::processMove(possibleMoveDate, eventToWorkWith, calendar))
        return false;

    return true;
}

std::ostream &CMove::print(std::ostream &out) const {
    return out << "move - Move event to specific date or closest next day without time collision";
}

std::unique_ptr<COperation> CMove::clone() const {
    return make_unique<CMove>();
}


CMove::CMove(const CMove &rhs) {
    for(const auto & ms : rhs.m_MoveStrategies)
        m_MoveStrategies.insert({ms.first, ms.second->clone()});
}

CMove &CMove::operator=(const CMove &rhs) {
    if(this == &rhs)
        return *this;

    CMove tmp = CMove(rhs);
    std::swap(m_MoveStrategies, tmp.m_MoveStrategies);
    return *this;
}

void CMove::printMoveStrategies() const {
    cout << "Possible move strategies" << endl;
    for(const auto & ms : m_MoveStrategies){
        cout << '\t' << *(ms.second) << endl;
    }

}

bool CMove::processMove(const CDate &possibleMoveDate,const std::shared_ptr<CEvent>&eventToMove, CCalendar & calendar) {
    bool fail = false;
    map<CDate,shared_ptr<CEvent>>eventsToMove;
    eventsToMove = eventToMove->move(possibleMoveDate, fail);
    if(fail){
        cout << "Unable to move event" << endl;
        return false;
    }

    eventsToMove.insert({eventToMove->getDate(), eventToMove});
    eventToMove->setDate(possibleMoveDate);
    for(const auto & ev : eventsToMove){
        auto moveDay = calendar.getEvents().find(ev.first);                             //loop through the map, where are events to move
        auto eventIt = find(moveDay->second.begin(), moveDay->second.end(), ev.second); // Find the date before move - key of tha map eventsToMove
        if(eventIt != moveDay->second.end()){                                           //remove from the old date and insert at the new date
            moveDay->second.erase(eventIt);
            calendar.getEvents()[ev.second->getDate()].push_back(ev.second);
        }
    }
    return true;
}
