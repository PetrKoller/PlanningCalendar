#include "CApplication.h"

using namespace std;

CApplication::CApplication() {
    m_DisplayMode = make_unique<CDisplayMonth>();
    m_InputHandler.handleCommand("draw")->execute(m_Calendar, m_DisplayMode);
}

void CApplication::run() {

    while(!m_Calendar.getCalendarExit() && !cin.eof()){
        string input;
        cout << "Calendar's commands" << endl;
        printCommands();

        if(!CPrompt::promptUniversal(input, "Type in the command: ")){
            cout << "Invalid input" << endl;
            continue;
        }
        CValidator::strToLower(input);

        if(!processCommand(input))
            cout << "Unable to process command" << endl;
    }
    cout << "Goodbye" << endl;
}

void CApplication::printCommands() const {
    m_InputHandler.printCommands();
}

bool CApplication::processCommand(const std::string & input) {
    unique_ptr<CCommand> command = m_InputHandler.handleCommand(input);
    if(command != nullptr){
        if(!command->execute(m_Calendar, m_DisplayMode))
            return false;

        return true;
    }

    return false;
}
