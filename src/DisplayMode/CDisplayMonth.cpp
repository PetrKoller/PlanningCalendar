#include "CDisplayMonth.h"

using namespace std;
void CDisplayMonth::draw(const CCalendar &calendar) const {
    CDate monthBegin = calendar.getCurrentDate().getMonthBegin();

    cout << CDate::MONTHNAMES[monthBegin.getMonthIdx()] << " - " << monthBegin.getYear() << endl;
    cout << "'*' - An event planned that day" << endl;

    CDisplayMonth::printWeekDays();
    CDisplayMonth::printFirstDayPadding(monthBegin);
    CDisplayMonth::printWholeMonth(monthBegin, calendar);
}

void CDisplayMonth::printWeekDays() {
    for(const auto & weekDay : CDate::WEEKDAYS){
        cout<< setw(10)<<weekDay<<flush;
    }
    cout << endl;
}

void CDisplayMonth::printFirstDayPadding(const CDate &date) {
    for(int i = 0; i < date.getWeekDayIdx(); i++)
        cout << setw(10) <<""<<flush;
}

void CDisplayMonth::printWholeMonth(const CDate &date, const CCalendar & calendar) {
    CDate tmpDate = date;
    for(int i = 1; i <= date.getDaysInMonth(); i++ ){
        if(calendar.getEvents().count(tmpDate) != 0 && !calendar.getEvents().at(tmpDate).empty()){
            cout << setw(8) << "*" << flush;
            cout << setw(2) << i << flush;
        }else
            cout << setw(10) << i << flush;

        if((i + date.getWeekDayIdx()) % 7 == 0)//end of the week, end line after sunday
            cout << endl;
        tmpDate.nextDay();
    }
    cout << endl << endl;
}

void CDisplayMonth::drawNextPeriod(CCalendar &calendar) const {
    CDate monthBegin = calendar.getCurrentDate().getMonthBegin();
    monthBegin.nextMonth(); //must be month begin. Problem if current day is greater than prev month max day (mktime) will convert to next month
    calendar.setDate(monthBegin);
    CDisplayMonth::draw(calendar);
}

void CDisplayMonth::drawPrevPeriod(CCalendar &calendar) const {
    CDate monthBegin = calendar.getCurrentDate().getMonthBegin();
    monthBegin.prevMonth(); //must be month begin. Problem if actual day is greater than prev month max day (mktime) will convert to next month
    calendar.setDate(monthBegin);
    CDisplayMonth::draw(calendar);
}

unique_ptr<CDisplayMode> CDisplayMonth::clone() const {
    return make_unique<CDisplayMonth>();
}

ostream &CDisplayMonth::print(ostream &out) const {
    return out << "month - Change the display mode to month mode";
}


