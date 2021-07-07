#pragma once

#include "CCommand.h"

class CDraw : public CCommand {
public:
    bool execute(CCalendar &calendar, std::unique_ptr<CDisplayMode> &displayMode) const override;

    std::unique_ptr<CCommand> clone()const override;

    std::ostream &print(std::ostream & out) const override;
private:
};



