
#pragma once


#include "CMoveStrategy.h"

class CClosestDaySameTime : public CMoveStrategy{
public:
    static const size_t MAXDAYS = 10000;
    bool findPossibleDate(CDate & possibleDate, const CCalendar & calendar, const std::shared_ptr<CEvent>& eventToMove) const override;

    std::ostream &print(std::ostream &out) const override;

    std::unique_ptr<CMoveStrategy> clone() const override;
};



