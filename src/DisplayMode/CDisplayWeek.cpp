//
// Created by progtest on 16.04.21.
//

#include "CDisplayWeek.h"


using namespace std;

void CDisplayWeek::draw(const CCalendar &calendar) const {
    CDisplayWeek::printWeek(calendar.getCurrentDate());
    CDisplayWeek::printEvents(calendar);
}

void CDisplayWeek::drawNextPeriod(CCalendar &calendar) const {
    calendar.getCurrentDate().nextWeek();
    draw(calendar);
}

void CDisplayWeek::drawPrevPeriod(CCalendar &calendar) const {
    calendar.getCurrentDate().prevWeek();
    draw(calendar);
}

void CDisplayWeek::printWeek(const CDate & date) {
    CDate weekBegin = date.getWeekBegin();
    CDate weekEnd = date.getWeekEnd();
    cout << weekBegin << " - " << weekEnd << endl;
    for(int i = 0; i < CDate::DAYSINWEEK; i++){
        stringstream s;
        s << weekBegin.getWeekDay() << " " <<setw(2)<< weekBegin.getDay();
        cout << setw(i == 0 ? 12 : 16) << s.str() << flush;
        weekBegin.nextDay();
    }
    cout << endl;
}

void CDisplayWeek::printEvents(const CCalendar &calendar) {
    CDate weekBegin = calendar.getCurrentDate().getWeekBegin();
    for(int i = 0; i < CDate::DAYSINWEEK; i++){
        size_t eventCount = 0;
        stringstream s;
        if(calendar.getEvents().count(weekBegin) != 0)
            eventCount = calendar.getEvents().at(weekBegin).size();

        s << eventCount << " Event" <<(eventCount == 1 ? "" : "s");
        cout << setw(i == 0 ? 12 : 16) << s.str() << flush;
        weekBegin.nextDay();
    }
    cout << endl;
}

unique_ptr<CDisplayMode> CDisplayWeek::clone() const {
    return make_unique<CDisplayWeek>();
}

ostream &CDisplayWeek::print(ostream &out) const {
    return out << "week - Change the display mode to week mode";
}
