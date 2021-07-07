#pragma once

#include "CCommand.h"
#include <fstream>
class CExport : public CCommand{
public:
    bool execute(CCalendar &calendar, std::unique_ptr<CDisplayMode> &displayMode) const override;

    std::ostream &print(std::ostream &out) const override;

    std::unique_ptr<CCommand> clone()const override;

private:
    static const std::string PATH;
};



