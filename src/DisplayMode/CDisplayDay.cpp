//
// Created by progtest on 16.04.21.
//

#include "CDisplayDay.h"

using namespace std;



void CDisplayDay::draw(const CCalendar &calendar) const {
    CDate currDate = calendar.getCurrentDate();
    vector<shared_ptr<CEvent>> eventsToday;

    cout << currDate.getWeekDay()<<" - " <<currDate<<endl;

    if(!CDisplayDay::getEventsToday(eventsToday, calendar))
        return;

    CDisplayDay::printEvents(eventsToday);
}

void CDisplayDay::drawNextPeriod(CCalendar &calendar) const {
    calendar.getCurrentDate().nextDay();
    draw(calendar);
}

void CDisplayDay::drawPrevPeriod(CCalendar &calendar) const {
    calendar.getCurrentDate().prevDay();
    draw(calendar);
}

bool CDisplayDay::getEventsToday(vector<std::shared_ptr<CEvent>> &events, const CCalendar &calendar) {
    CDate currDate = calendar.getCurrentDate();
    if(calendar.getEvents().count(currDate) != 0 && !calendar.getEvents().at(currDate).empty())
        events = calendar.getEvents().at(currDate);
    else{
        cout<<'\t'<<'\t' << "None events this day" << endl << endl;
        return false;
    }

    sort(events.begin(), events.end(), CEvent::cmpEvents);
    return true;
}

void CDisplayDay::printEvents(const vector<std::shared_ptr<CEvent>> &events) {
    for(size_t i = 0; i < events.size(); i++)
        cout<<'\t' << i + 1 << ") " << *(events[i]) << endl << endl;

}

unique_ptr<CDisplayMode> CDisplayDay::clone() const {
    return make_unique<CDisplayDay>();
}

ostream &CDisplayDay::print(ostream &out) const {
    return out << "day - Change the display mode to day mode";
}
