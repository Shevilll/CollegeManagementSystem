#ifndef TEACHER_H
#define TEACHER_H

#include <string>

#include "Student.h"

using namespace std;

class Teacher : public Student
{
private:
    string tpassword;

public:
    string unique_id;
    string tname;
    string tdegree;
    string temail;
    string tphone;
    string taddress;
    int tcsv_line;

    int teacher_login();
    void teacher_display();
    void teacher_update();
    void upload_marks();
    void take_attendance();
    void teacher_timetable();
    void teacher_salary();
    void teacher_logout();
};

#endif