#ifndef APP_H
#define APP_H

#include "Admin.h"

class App : public Admin
{
public:
    void start();
    void admin_menu();
    void teacher_menu();
    void student_menu();
};

#endif