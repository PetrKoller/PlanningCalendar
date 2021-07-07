

#pragma once
#include <iostream>
#include "../Calendar/CCalendar.h"
#include "../Validator/CValidator.h"
#include "../DisplayMode/CDisplayMode.h"
#include "../Prompt/CPrompt.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <map>
#include <set>

class CCommand {
public:
    /** Execute the command
     * @param calendar CCalendar object to work with
     * @param displayMode CDisplayMode object to work with
     * @return true (successfully executed), false (unsuccessfully executed) */
    virtual bool execute(CCalendar &calendar, std::unique_ptr<CDisplayMode> &displayMode) const = 0;
    friend std::ostream & operator << (std::ostream & out, const CCommand & rhs);
    /**Print the command*/
    virtual std::ostream & print(std::ostream & out)const = 0;
    /**Clone the command*/
    virtual std::unique_ptr<CCommand>clone() const = 0;
    virtual ~CCommand() = default;
private:
};




