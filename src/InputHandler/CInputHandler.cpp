
#include "CInputHandler.h"
#include "../Command/CDraw.h"
#include "../Command/CNextPeriod.h"
#include "../Command/CPrevPeriod.h"
#include "../Command/CExit.h"
#include "../Command/CChangeDisplayMode.h"
#include "../Command/CFindEvent.h"
#include "../Command/CAddEvent.h"
#include "../Command/CImport.h"
#include "../Command/CExport.h"

using namespace std;


CInputHandler::CInputHandler() {
    m_Commands["draw"] = make_unique<CDraw>();
    m_Commands["next"] = make_unique<CNextPeriod>();
    m_Commands["prev"] = make_unique<CPrevPeriod>();
    m_Commands["exit"] = make_unique<CExit>();
    m_Commands["change"] = make_unique<CChangeDisplayMode>();
    m_Commands["add"] = make_unique<CAddEvent>();
    m_Commands["find"] = make_unique<CFindEvent>();
    m_Commands["import"] = make_unique<CImport>();
    m_Commands["export"] = make_unique<CExport>();
}

unique_ptr<CCommand>CInputHandler::handleCommand(const string &input) const{
    auto command = m_Commands.find(input);
    if(command == m_Commands.end())
        return unique_ptr<CCommand>(nullptr);

    return command->second->clone();
}

void CInputHandler::printCommands() const {
    for(const auto & command : m_Commands)
        cout <<'\t' <<*(command.second) << endl;
}




