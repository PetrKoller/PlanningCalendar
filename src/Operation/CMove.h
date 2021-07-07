#pragma once

#include "COperation.h"
#include "../MoveStrategy/CMoveStrategy.h"

class CMove : public COperation{
public:
    CMove();
    CMove(const CMove & rhs);
    CMove & operator=(const CMove & rhs);
    bool execute(std::shared_ptr<CEvent> &eventToWorkWith, CCalendar &calendar) const override;

    std::ostream &print(std::ostream &out) const override;

    std::unique_ptr<COperation> clone() const override;

private:
    /**Print all available move strategies*/
    void printMoveStrategies()const;
    /**Move the event to specific date
     * @param possibleMoveDate Date where the event will be moved
     * @param eventToMove Event to move
     * @param calendar Calendar where the old event will be removed and new inserted
     * @return true(Move processed and correctly executed), false(an error)*/
    static bool processMove(const CDate & possibleMoveDate,const std::shared_ptr<CEvent>&eventToMove, CCalendar & calendar);
    std::map<std::string, std::unique_ptr<CMoveStrategy>>m_MoveStrategies;
};



