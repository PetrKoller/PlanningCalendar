#include "CPrevPeriod.h"
using namespace std;
bool CPrevPeriod::execute(CCalendar &calendar, std::unique_ptr<CDisplayMode> &displayMode) const {
    displayMode->drawPrevPeriod(calendar);
    return true;
}

std::ostream &CPrevPeriod::print(std::ostream &out) const {
    return out << "prev - Turn calendar to the previous period (depends on the display mode)";
}

std::unique_ptr<CCommand> CPrevPeriod::clone()const {
    return make_unique<CPrevPeriod>(*this);

}
