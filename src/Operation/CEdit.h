
#pragma once
#include "COperation.h"

class CEdit : public COperation{
public:
    bool execute(std::shared_ptr<CEvent> &eventToWorkWith, CCalendar &calendar) const override;
    std::ostream &print(std::ostream &out) const override;
    std::unique_ptr<COperation> clone() const override;
private:
    /**Checks if every information is valid
     * @param name
     * @param place
     * @param startTime
     * @param endTime
     * @param attendees
     * @return true (valid), false (invalid) */
    static bool validInformation(std::string & name, std::string & place, std::pair<int, int>&startTime, std::pair<int, int>&endTime,
                                 std::vector<std::string>&attendees);
};



