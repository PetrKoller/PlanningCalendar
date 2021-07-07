#pragma once

#include "COperation.h"

class CRemove : public COperation{
public:
    bool execute(std::shared_ptr<CEvent> &eventToWorkWith, CCalendar &calendar) const override;

    std::unique_ptr<COperation> clone() const override;

    std::ostream &print(std::ostream &out) const override;
};



