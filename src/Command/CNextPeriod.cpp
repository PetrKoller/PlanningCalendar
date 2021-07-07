#include "CNextPeriod.h"
using namespace std;

bool CNextPeriod::execute(CCalendar &calendar, std::unique_ptr<CDisplayMode> &displayMode) const{
    displayMode->drawNextPeriod(calendar);
    return true;
}

std::ostream &CNextPeriod::print(std::ostream & out) const {
    return out << "next - Turn calendar to the next period (depends on the display mode)";
}

unique_ptr<CCommand> CNextPeriod::clone()const {
    return make_unique<CNextPeriod>(*this);

}
