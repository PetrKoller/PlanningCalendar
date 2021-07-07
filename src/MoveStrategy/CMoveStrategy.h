#pragma once

#include "../Date/CDate.h"
#include "../Calendar/CCalendar.h"
#include "../Event/CEvent.h"

class CMoveStrategy {
public:
    /**Find possible move date corresponding to the move strategy
     * @param possibleDate Possible move date found by move strategy
     * @param calendar Source of the events
     * @param eventToMove Event that we want to move
     * @return true(found possible move date), false (possible move date not found) */
    virtual bool findPossibleDate(CDate & possibleDate, const CCalendar & calendar, const std::shared_ptr<CEvent>& eventToMove)const = 0;
    /**@param out
     * @param rhs
     * @return ostream*/
    friend std::ostream & operator << (std::ostream & out, const CMoveStrategy & rhs);
    /**Print the move strategy
     * @param out
     * @return ostream */
    virtual std::ostream & print(std::ostream & out)const = 0;
    /** Clone the strategy
     * @return unique_ptr to the strategy*/
    virtual std::unique_ptr<CMoveStrategy>clone()const = 0;
    virtual ~CMoveStrategy() = default;

protected:
    /**Checks if the given event is overlapping any other event or not
     * @param possibleMoveDate Date where we want to move the event
     * @param calendar Calendar with the events
     * @param eventToMove Event that we want to move to the possible date
     * @return true (event is not overlapping with any other event), false (event is overlapping) */
    static bool notTimeOverlap(const CDate &possibleMoveDate, const CCalendar &calendar, const std::shared_ptr<CEvent>& eventToMove);
};



