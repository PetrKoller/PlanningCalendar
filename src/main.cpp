#ifdef TESTING
#include <cassert>
#include <iostream>
#include "./Validator/CValidator.h"
#endif
#ifndef TESTING
#include "./Application/CApplication.h"
using namespace std;
int main() {
    CApplication app;
    try {
        app.run();
    }catch(const std::exception &e){
        cout << "Error: " << e.what() << endl;
    }catch(...){
        cout << "Unexpected error" << endl;
    }

    return 0;
}
#endif

#ifdef TESTING
using namespace std;

int main(){
    string email = "progtest@fit.cvut.cz";
    assert(CValidator::validEmail(email) == true);
    email = "kalvoda.lin@kam";
    assert(CValidator::validEmail(email) == false);
    email = "honza.matousek@retroengin.cz";
    assert(CValidator::validEmail(email) == true);
    email = "vagner-progtest@bfs.dfs.c.com";
    assert(CValidator::validEmail(email) == true);
    email = "";
    assert(CValidator::validEmail(email) == false);
    email = "   ";
    assert(CValidator::validEmail(email) == false);

    //Valid date format is DD.MM.YYYY, date range is not checked
    string date = "1.1.2000";
    assert(CValidator::validDateFormat(date) == true);
    date = "30.20.2020";
    assert(CValidator::validDateFormat(date) == false);
    date = "1.1.20000";
    assert(CValidator::validDateFormat(date) == false);
    date = "29.2.2021";
    assert(CValidator::validDateFormat(date) == true);
    date = "03.01.2000";
    assert(CValidator::validDateFormat(date) == true);
    date = "1.1.200";
    assert(CValidator::validDateFormat(date) == false);

    //Converting date string to CDate object
    CDate cdate;
    stringstream sdate(date);
    assert(CValidator::processDate(cdate, sdate) == false);
    sdate.clear();
    sdate.str("1.1.2000");
    assert(CValidator::processDate(cdate, sdate) == true);
    assert(cdate.getYear() == 2000 && cdate.getMonth() == 1 && cdate.getDay() == 1);
    cdate.nextDay();
    assert(cdate.getYear() == 2000 && cdate.getMonth() == 1 && cdate.getDay() == 2);
    cdate.nextWeek();
    assert(cdate.getYear() == 2000 && cdate.getMonth() == 1 && cdate.getDay() == 9);
    cdate.nextMonth();
    assert(cdate.getYear() == 2000 && cdate.getMonth() == 2 && cdate.getDay() == 9);
    cdate.incDays(30);
    assert(cdate.getYear() == 2000 && cdate.getMonth() == 3 && cdate.getDay() == 10);
    cdate.decDays(30);
    assert(cdate.getYear() == 2000 && cdate.getMonth() == 2 && cdate.getDay() == 9);
    cdate.prevWeek();
    assert(cdate.getYear() == 2000 && cdate.getMonth() == 2 && cdate.getDay() == 2);
    cdate.prevWeek();
    assert(cdate.getYear() == 2000 && cdate.getMonth() == 1 && cdate.getDay() == 26);
    cdate.prevMonth();
    assert(cdate.getYear() == 1999 && cdate.getMonth() == 12 && cdate.getDay() == 26);

    sdate.clear();
    sdate.str("  1 . 1. 2000  ");
    assert(CValidator::processDate(cdate, sdate) == false);
    sdate.clear();
    sdate.str("  1 . 1 . 2000  ");
    assert(CValidator::processDate(cdate, sdate) == false);
    sdate.clear();
    sdate.str(" 1. 1. 2000  ");
    assert(CValidator::processDate(cdate, sdate) == false);
    sdate.clear();
    sdate.str("  1.1. 2000  ");
    assert(CValidator::processDate(cdate, sdate) == false);
    sdate.clear();
    sdate.str(" 1.1.2000  ");
    assert(CValidator::processDate(cdate, sdate) == true);
    assert(cdate.getYear() == 2000 && cdate.getMonth() == 1 && cdate.getDay() == 1);
    sdate.clear();
    sdate.str("29.2.2021");
    assert(CValidator::processDate(cdate, sdate) == false);
    sdate.clear();
    sdate.str("29.2.2020");
    assert(CValidator::processDate(cdate, sdate) == true);
    assert(cdate.getYear() == 2020 && cdate.getMonth() == 2 && cdate.getDay() == 29);


    string s = "karel   ";
    assert(CValidator::trimTrailingSpaces(s) == "karel");
    s = "  ";
    assert(CValidator::trimTrailingSpaces(s).empty());
    s = "";
    assert(CValidator::trimTrailingSpaces(s).empty());
    s = "    karel havel    ";
    assert(CValidator::trimAllSpaces(s) == "karel havel");
    s = "    karel havel";
    assert(CValidator::trimAllSpaces(s) == "karel havel");
    s = "  ";
    assert(CValidator::trimAllSpaces(s).empty());
    s = "";
    assert(CValidator::trimAllSpaces(s).empty());

    pair<int, int>startTime, endTime;
    //Valid time format is HH:MM
    istringstream time("14:30");
    assert(CValidator::readTimeFormat(startTime, time) == true);
    time.clear();
    time.str("24:00");
    assert(CValidator::readTimeFormat(startTime, time) == false);
    time.clear();
    time.str("10:0");
    assert(CValidator::readTimeFormat(endTime, time) == true);
    assert(CValidator::checkTimeIntervals(startTime, endTime) == false);
    assert(CValidator::checkTimeIntervals(endTime, startTime) == true);
    assert(CValidator::checkTimeIntervals(startTime, startTime) == false);
    time.clear();
    time.str("Invalid time");
    assert(CValidator::readTimeFormat(endTime, time) == false);

    //correct format is not an empty string and attendees' addresses are seperated by ','
    //email address must be valid
    istringstream attendees("karel@seznam.cz\t,\t sdsakl@dsk.ds.s , cont@dsak.ds    ,   habbab@svarta.jump  , trol@lol.ca       \t");
    vector<string>readAttendees, correctAttendees = {"karel@seznam.cz", "sdsakl@dsk.ds.s", "cont@dsak.ds", "habbab@svarta.jump",
                                                     "trol@lol.ca"};

    assert(CValidator::readAttendees(readAttendees, attendees) == true);
    for(size_t i = 0; i < correctAttendees.size(); i++)
        assert(readAttendees[i] == correctAttendees[i]);

    readAttendees.clear();
    attendees.clear();
    attendees.str("");
    assert(CValidator::readAttendees(readAttendees, attendees) == false);
    attendees.clear();
    attendees.str("karel@seznam.cz        ,  test@ds.cz    , ");
    assert(CValidator::readAttendees(readAttendees, attendees) == false);
    attendees.clear();
    attendees.str("karel@seznam.cz        extraString   ");
    assert(CValidator::readAttendees(readAttendees, attendees) == false);
    attendees.clear();
    attendees.str("karel@seznam.cz , ");
    assert(CValidator::readAttendees(readAttendees, attendees) == false);

    istringstream input("   Hradec Kralove      \n"
                       "            Minove pole\n"
                       "\n"
                       "     \n"
                       "    ");
    string name;
    assert(CValidator::readLine(name, input) == true && name == "Hradec Kralove");
    assert(CValidator::readLine(name, input) == true && name == "Minove pole");
    assert(CValidator::readLine(name, input) == false);
    assert(CValidator::readLine(name, input) == false);
    assert(CValidator::readLine(name, input) == false);

    cout <<"==========EVERY TEST PASSED SUCCESSFULLY==========" << endl;



    return 0;
}

#endif