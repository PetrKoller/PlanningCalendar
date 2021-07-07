#pragma once

#include "CDisplayMode.h"

class CDisplayMonth : public CDisplayMode {
public:
    void draw(const CCalendar &calendar) const override;

    void drawNextPeriod(CCalendar &calendar) const override;

    void drawPrevPeriod(CCalendar &calendar) const override;

    std::ostream &print(std::ostream &out) const override;

    std::unique_ptr<CDisplayMode> clone() const override;

private:
    static void printWeekDays();
    /** Padding to start printing days accurately to their weekday
     * @param date */
    static void printFirstDayPadding(const CDate & date);
    /** Print whole month with event indication
     * @param date
     * @param calendar*/
    static void printWholeMonth(const CDate & date, const CCalendar & calendar);
};



