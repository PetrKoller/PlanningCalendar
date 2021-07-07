#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include "../Date/CDate.h"
#include "../Command/CCommand.h"

class CInputHandler {
public:
    CInputHandler();
    /** Print all the commands*/
    void printCommands()const;
    /**Process the string input and return corresponding CCommand
     * @param input Input to be processed
     * @return unique_ptr to corresponding command*/
    std::unique_ptr<CCommand> handleCommand(const std::string & input)const;
private:
    std::map<std::string, std::unique_ptr<CCommand>>m_Commands;
};



