#include <iostream>

#include "App.h"

// Default Password: unique_id/roll_no + name
// Admin username_password: admin_password

// g++ -std=c++11 ./*.cpp -o main
// chmod +x main
// ./main

using namespace std;

int main(void)
{
    App app;
    app.start();
    return 0;
}