#include "CMoveStrategy.h"

using namespace std;
std::ostream &operator<<(std::ostream &out, const CMoveStrategy &rhs) {
    return rhs.print(out);
}

bool CMoveStrategy::notTimeOverlap(const CDate &possibleMoveDate, const CCalendar &calendar,
                                   const std::shared_ptr<CEvent> &eventToMove) {

    vector<shared_ptr<CEvent>>events = calendar.getEvents().at(possibleMoveDate);
    for(const auto & ev : events){
        if((ev->getStartTime() < eventToMove->getStartTime() && ev->getEndTime() > eventToMove->getStartTime()) ||  //check if the given event
           (ev->getStartTime() < eventToMove->getEndTime() && ev->getEndTime() > eventToMove->getEndTime())||       //is overlapping with any other event
           (ev->getStartTime() < eventToMove->getStartTime() && ev->getEndTime() > eventToMove->getEndTime())||     // at the possible move date
           (ev->getStartTime() >= eventToMove->getStartTime() && ev->getEndTime() <= eventToMove->getEndTime()))
            return false;
    }
    return true;
}
