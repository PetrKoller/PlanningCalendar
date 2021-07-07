#pragma once

#include "CCommand.h"
#include "../DisplayMode/CDisplayMode.h"

class CChangeDisplayMode : public CCommand{
public:
    CChangeDisplayMode();
    CChangeDisplayMode(const CChangeDisplayMode & rhs);
    CChangeDisplayMode & operator=(const CChangeDisplayMode & rhs);
    bool execute(CCalendar &calendar, std::unique_ptr<CDisplayMode> &displayMode) const override;
    std::unique_ptr<CCommand> clone()const override;
    std::ostream &print(std::ostream &out) const override;

private:
    std::map<std::string, std::unique_ptr<CDisplayMode>>m_DisplayModes;
    /**Print all display modes*/
    void printDisplayModes()const;
};



