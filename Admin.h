#ifndef ADMIN_H
#define ADMIN_H

#include <string>

#include "Teacher.h"

using namespace std;

class Admin : public Teacher
{
public:
    string notice, notice_desc;

    int admin_login();
    void add_student();
    void add_teacher();
    void update_fee();
    void add_fee();
    void add_timetable();
    void update_attendance();
    void update_marks();
    void add_notice();
    void remove_student();
    void remove_teacher();
    void admin_logout();
};

#endif