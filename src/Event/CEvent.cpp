#include "CEvent.h"
using namespace std;
CEvent::CEvent(const std::string &name,const std::string & place, const CDate & date,const std::pair<int, int>&startTime, const std::pair<int, int>&endTime, const std::vector<std::string> &attendees)
:m_Name(name),m_Place(place),m_EventDate(date) ,m_StartTime(startTime), m_EndTime(endTime), m_Attendees(attendees){
}

CEvent &CEvent::setDate(const CDate &date) {
    m_EventDate = date;
    return *this;
}


const CDate &CEvent::getDate() const {
    return m_EventDate;
}

bool CEvent::operator<(const CEvent &rhs) const {
    if(m_EventDate != rhs.m_EventDate)
        return m_EventDate < rhs.m_EventDate;

    if(m_StartTime != rhs.m_StartTime)
        return m_StartTime < rhs.m_StartTime;

    return m_EndTime < rhs.m_EndTime;
}

std::ostream &operator<<(std::ostream &out, const CEvent &rhs) {
    return rhs.print(out);
}

std::ostream &CEvent::print(ostream &out)const {
    out<<'\t' << m_Name << " - " <<m_EventDate << " ("<<setw(2) << setfill('0')
                        << m_StartTime.first << ":" <<setw(2)<< m_StartTime.second <<" - "
                        <<setw(2) <<m_EndTime.first << ":"<<setw(2) << m_EndTime.second << ")" << endl;
    out << setfill(' ');
    out <<'\t' << '\t' << "Place: " << m_Place << endl;
    bool first = true;
    out<<'\t'<<'\t' << "Attendees: ";
    for(size_t i = 0; i < m_Attendees.size(); i++){
        if(!first)
            out << ", ";
        if(i % 5 == 0 && i != 0)
            out << endl << '\t' << '\t';
        out << m_Attendees[i];
        first = false;
    }
    return out;
}

const std::string &CEvent::getName() const {
    return m_Name;
}

std::vector<std::shared_ptr<CEvent>> CEvent::remove(bool &fail) {
    cout << "Removing normal event" << endl;
    fail = false;
    return vector<shared_ptr<CEvent>>();
}

CEvent & CEvent::edit(const CEvent &editedEvent) {
    *this = editedEvent;

    return *this;
}

std::map<CDate, std::shared_ptr<CEvent>> CEvent::move(const CDate &dateToMove, bool &fail) {
    cout << "Moving event to " << dateToMove << endl;
    fail = false;
    return std::map<CDate, std::shared_ptr<CEvent>>();
}

const std::vector<std::string> &CEvent::getAttendees() const {
    return m_Attendees;
}

std::pair<int, int> CEvent::getStartTime() const {
    return m_StartTime;
}

std::pair<int, int> CEvent::getEndTime() const {
    return m_EndTime;
}

bool CEvent::cmpEvents(const shared_ptr<CEvent> &lhs, const shared_ptr<CEvent> &rhs) {
    return *lhs < *rhs;
}

std::set<std::shared_ptr<CEvent>> CEvent::exportEvent(ostringstream &exportStream) {
    exportStream << getExportStream().str();
    return std::set<std::shared_ptr<CEvent>>();
}

std::ostringstream CEvent::getExportStream() const {
    ostringstream oss = getBaseExportStream();
    oss << ';' << "normal";
    return oss;
}

std::ostringstream CEvent::getBaseExportStream() const {
    ostringstream oss;
    oss << m_Name << ';' << m_Place << ';' << m_EventDate.getDay() << '.' << m_EventDate.getMonth() << '.' << m_EventDate.getYear()
        << ';' << m_StartTime.first << ':' << m_StartTime.second << ';' << m_EndTime.first << ':' << m_EndTime.second<<';';

    for(size_t i = 0; i < m_Attendees.size(); i++){
        oss << m_Attendees[i];
        if(i < m_Attendees.size() - 1)
            oss << ',';
    }
    return oss;
}

const std::string &CEvent::getPlace() const {
    return m_Place;
}



