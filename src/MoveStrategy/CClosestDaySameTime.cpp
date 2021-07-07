#include "CClosestDaySameTime.h"

using namespace std;
bool CClosestDaySameTime::findPossibleDate(CDate & possibleDate, const CCalendar & calendar, const std::shared_ptr<CEvent>& eventToMove) const {
    possibleDate.nextDay();
    size_t i = 0;
    while(i < MAXDAYS){
        if(calendar.getEvents().count(possibleDate) == 0 || calendar.getEvents().at(possibleDate).empty()){
            break;
        }else{
            if(notTimeOverlap(possibleDate, calendar, eventToMove))
                break;
        }
        possibleDate.nextDay();
        i++;
    }

    return i < MAXDAYS;
}

std::ostream &CClosestDaySameTime::print(std::ostream &out) const {
    return out << "day - Find closest possible day without time collision at the same time";
}

std::unique_ptr<CMoveStrategy> CClosestDaySameTime::clone() const {
    return make_unique<CClosestDaySameTime>();
}
