#pragma once

#include "../Event/CEvent.h"
#include "../Calendar/CCalendar.h"
#include "../Validator/CValidator.h"
#include <algorithm>

class COperation {
public:
    /**Execute the operation on the given event
     * @param eventToWorkWith
     * @param calendar
     * @return true(executed successfully), false(operation aborted)*/
    virtual bool execute(std::shared_ptr<CEvent> &eventToWorkWith, CCalendar & calendar)const = 0;
    /**@param out
     * @param rhs
     * @return ostream*/
    friend std::ostream & operator << (std::ostream & out, const COperation & rhs);
    /**Print the operation
     * @param out
     * @return ostream*/
    virtual std::ostream & print(std::ostream & out)const = 0;
    /**Clone the operation
     * @return unique_ptr of the operation*/
    virtual std::unique_ptr<COperation>clone()const = 0;
    virtual ~COperation() = default;
private:
};



