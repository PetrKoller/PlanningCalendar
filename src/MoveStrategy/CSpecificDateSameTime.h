#pragma once

#include "CMoveStrategy.h"

class CSpecificDateSameTime : public CMoveStrategy{
public:
    bool findPossibleDate(CDate &possibleDate, const CCalendar &calendar,
                          const std::shared_ptr<CEvent> &eventToMove) const override;

    std::ostream &print(std::ostream &out) const override;

    std::unique_ptr<CMoveStrategy> clone() const override;

private:
};



