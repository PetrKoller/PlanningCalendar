#pragma once

#include "CDisplayMode.h"

class CDisplayDay : public CDisplayMode{
public:
    void draw(const CCalendar &calendar) const override;

    void drawNextPeriod(CCalendar &calendar) const override;

    void drawPrevPeriod(CCalendar &calendar) const override;

    std::unique_ptr<CDisplayMode> clone() const override;

    std::ostream &print(std::ostream &out) const override;

private:
    /**Get today's events and store into events vector
     * @param events vector where found events are stored
     * @param calendar
     * @return true (an event this day), false(none event this day)*/
    static bool getEventsToday(std::vector<std::shared_ptr<CEvent>>&events, const CCalendar & calendar);
    /** Print every event from the vector
     * @param events events to be printed */
    static void printEvents(const std::vector<std::shared_ptr<CEvent>>&events);
};

