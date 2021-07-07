#pragma once

#include "CDisplayMode.h"

class CDisplayWeek : public CDisplayMode{
public:
    void draw(const CCalendar &calendar) const override;

    void drawNextPeriod(CCalendar &calendar) const override;

    void drawPrevPeriod(CCalendar &calendar) const override;

    std::ostream &print(std::ostream &out) const override;

    std::unique_ptr<CDisplayMode> clone() const override;

private:
    /**Print whole week, every weekday
     * @param date */
    static void printWeek(const CDate &date);
    /** Print number of events to the corresponding day
     * @param calendar */
    static void printEvents(const CCalendar & calendar);
};



