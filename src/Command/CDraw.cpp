#include "CDraw.h"
using namespace std;
bool CDraw::execute(CCalendar &calendar, std::unique_ptr<CDisplayMode> &displayMode) const {
    displayMode->draw(calendar);
    return true;
}

std::ostream &CDraw::print(std::ostream & out) const {
    return out <<"draw - Show current calendar";
}

std::unique_ptr<CCommand> CDraw::clone()const {
    return make_unique<CDraw>(*this);

}
