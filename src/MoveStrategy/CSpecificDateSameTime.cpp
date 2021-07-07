#include "CSpecificDateSameTime.h"

using namespace std;
bool CSpecificDateSameTime::findPossibleDate(CDate &possibleDate, const CCalendar &calendar,
                                             const std::shared_ptr<CEvent> &eventToMove) const {
    if(!CPrompt::promptForDate(possibleDate))
        return false;
    if(eventToMove->getDate() == possibleDate){
        cout << "Same date" << endl;
        return false;
    }

    if(calendar.getEvents().count(possibleDate) == 0 || calendar.getEvents().at(possibleDate).empty() ) {
        return true;
    }
    if(notTimeOverlap(possibleDate, calendar, eventToMove)) {
        return true;
    }
    return false;
}

std::ostream &CSpecificDateSameTime::print(std::ostream &out) const {
    return out << "date - Specific date at the same time";
}

std::unique_ptr<CMoveStrategy> CSpecificDateSameTime::clone() const {
    return make_unique<CSpecificDateSameTime>();
}
