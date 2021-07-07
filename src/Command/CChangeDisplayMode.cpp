#include "CChangeDisplayMode.h"
#include "../DisplayMode/CDisplayWeek.h"
#include "../DisplayMode/CDisplayDay.h"
#include "../DisplayMode/CDisplayMonth.h"

using namespace std;

CChangeDisplayMode::CChangeDisplayMode() {
    m_DisplayModes["week"] = make_unique<CDisplayWeek>();
    m_DisplayModes["month"] = make_unique<CDisplayMonth>();
    m_DisplayModes["day"] = make_unique<CDisplayDay>();
}

bool CChangeDisplayMode::execute(CCalendar &calendar, std::unique_ptr<CDisplayMode> &displayMode) const {
    string input;

    printDisplayModes();
    if(!CPrompt::promptUniversal(input, "Choose the display mode: "))
        return false;
    CValidator::strToLower(input);

    auto findDM = m_DisplayModes.find(input);

    if(findDM == m_DisplayModes.end()){
        cout << "Invalid display mode" << endl;
        return false;
    }

    displayMode = m_DisplayModes.at(input)->clone();

    displayMode->draw(calendar);
    return true;
}

std::ostream &CChangeDisplayMode::print(std::ostream &out) const {
    return out << "change - Change the display mode";
}

unique_ptr<CCommand> CChangeDisplayMode::clone() const{
    return make_unique<CChangeDisplayMode>(*this);
}

void CChangeDisplayMode::printDisplayModes() const {
    for(const auto & dm : m_DisplayModes)
        cout <<'\t' << *(dm.second) << endl;
}

CChangeDisplayMode::CChangeDisplayMode(const CChangeDisplayMode &rhs) {
    for(const auto & dm : rhs.m_DisplayModes)
        m_DisplayModes.insert({dm.first, dm.second->clone()});
}

CChangeDisplayMode &CChangeDisplayMode::operator=(const CChangeDisplayMode &rhs) {
    if(this == &rhs)
        return *this;

    auto tmp = CChangeDisplayMode(rhs);
    std::swap(m_DisplayModes, tmp.m_DisplayModes);

    return *this;
}