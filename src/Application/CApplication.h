#pragma once

#include "../Calendar/CCalendar.h"
#include "../Command/CCommand.h"
#include "../InputHandler/CInputHandler.h"
#include "../DisplayMode/CDisplayMode.h"
#include "../DisplayMode/CDisplayMonth.h"
#include "../Prompt/CPrompt.h"
#include <map>
#include <memory>


class CApplication {
public:
    CApplication();
    CApplication(const CApplication & rhs) = delete;
    CApplication & operator=(const CApplication & rhs) = delete;
    /** Run the application*/
    void run();
private:
    CCalendar m_Calendar;
    CInputHandler m_InputHandler;
    std::unique_ptr<CDisplayMode>m_DisplayMode;
    /** Print all the commands */
    void printCommands()const;
    /**
     * Process the command from input string
     * @param input command to be processed
     * @return true (command successfully processed), false (An invalid operation occurred)
     */
    bool processCommand(const std::string & input);
};



