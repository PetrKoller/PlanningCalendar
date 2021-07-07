#include "CExport.h"

using namespace std;
const std::string CExport::PATH = "./examples/exportedEvents.txt";

bool CExport::execute(CCalendar &calendar, std::unique_ptr<CDisplayMode> &displayMode) const {
    ofstream file(PATH);
    if(!file){
        cout << "Cannot work with the file" << endl;
        return false;
    }

    if(calendar.getEvents().empty()){
        cout << "None events to be exported" << endl;
        return true;
    }

    set<shared_ptr<CEvent>>exportedEvents;
    for(const auto & day : calendar.getEvents()){
        for(const auto & ev : day.second ){
            if(exportedEvents.count(ev) == 0){//event hasn't been exported yet
                ostringstream exportStream;
                set<shared_ptr<CEvent>>eventsToExport = ev->exportEvent(exportStream);  //Crucial for recurring events
                exportedEvents.insert(ev);                                                 //we only want to export original event, the first one
                exportedEvents.insert(eventsToExport.begin(),eventsToExport.end());        //not the repeating ones. exportEvent returns the repeating ones
                if(!(file << exportStream.str() << endl)){
                    cout << "Unable to write into the file" << endl;
                    return false;
                }
            }
        }
    }
    file.close();
    cout << "Events exported to: " << PATH << endl;
    displayMode->draw(calendar);
    return true;
}

std::ostream &CExport::print(std::ostream &out) const {
    return out << "export - Export all events";
}

std::unique_ptr<CCommand> CExport::clone()const {
    return make_unique<CExport>();
}
