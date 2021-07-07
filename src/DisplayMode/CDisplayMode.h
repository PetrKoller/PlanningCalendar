#pragma once
#include "../Date/CDate.h"
#include <memory>
#include <iomanip>
#include <vector>
#include "../Event/CEvent.h"
#include "../Calendar/CCalendar.h"
#include <algorithm>
#include <iostream>


class CDisplayMode {
public:
    /** Draw the calendar corresponding to the display mode
     * @param calendar */
    virtual void draw(const CCalendar &calendar)const = 0;
    /** Flip to the next period and draw the calendar corresponding to the display mode
     * @param calendar */
    virtual void drawNextPeriod(CCalendar & calendar)const = 0;
    /** Flip to the previous period and draw the calendar corresponding to the display mode
     * @param calendar */
    virtual void drawPrevPeriod(CCalendar & calendar)const = 0;
    /**Clone the display mode
     * @return unique_ptr with display mode*/
    virtual std::unique_ptr<CDisplayMode>clone()const = 0;
    friend std::ostream & operator << (std::ostream & out, const CDisplayMode & rhs);
    /**Print the display mode */
    virtual std::ostream & print(std::ostream & out)const = 0;
    virtual ~CDisplayMode() = default;
};



