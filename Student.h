#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>

using namespace std;
class Student
{
private:
    string password;

public:
    string name;
    string roll_no;
    string branch;
    string semester;
    string email;
    string phone;
    string address;
    string room;
    int csv_line;

    int student_login();
    void student_display();
    void student_update();
    void student_marks();
    void student_attendance();
    void student_timetable();
    void student_fee();
    void student_logout();
};

#endif