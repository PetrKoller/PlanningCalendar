#include "CExit.h"

using namespace std;
bool CExit::execute(CCalendar &calendar, std::unique_ptr<CDisplayMode> &displayMode) const {
    calendar.setCalendarExit(true);
    displayMode->draw(calendar);
    return true;
}

std::ostream &CExit::print(std::ostream &out) const {
    return out << "exit - Exit calendar";
}

std::unique_ptr<CCommand> CExit::clone()const {
    return make_unique<CExit>(*this);

}
