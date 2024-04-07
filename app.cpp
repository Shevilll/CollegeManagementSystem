#include <iostream>
#include <string>
#include <fstream>

#include "App.h"
#include "Csv_helper.h"

using namespace std;

void App::start()
{
    CSV csv;
    int ch;
    while (1)
    {
        cout << "Welcome to College Management System" << endl;
        if (csv.total_lines("notices.csv") > 0)
        {
            cout << "Notice: " << csv.split_line("notices.csv", csv.total_lines("notices.csv") - 1, ',')[0] << ": " << csv.split_line("notices.csv", csv.total_lines("notices.csv") - 1, ',')[1] << endl;
        }
        cout << "Please select your role" << endl;
        cout << "1. Admin" << endl;
        cout << "2. Teacher" << endl;
        cout << "3. Student" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            if (admin_login())
            {
                admin_menu();
            }
            break;
        case 2:
            if (teacher_login())
            {
                teacher_menu();
            }
            break;
        case 3:
            if (student_login())
            {
                student_menu();
            }
            break;
        case 4:
            cout << "Exiting..." << endl;
            exit(0);
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
        }
    }
}

void App::admin_menu()
{
    int ch;
    while (1)
    {
        cout << "Welcome Admin" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Add Teacher" << endl;
        cout << "3. Update Fee" << endl;
        cout << "4. Add Fee" << endl;
        cout << "5. Add Timetable" << endl;
        cout << "6. Update Attendance" << endl;
        cout << "7. Update Marks" << endl;
        cout << "8. Add Notice" << endl;
        cout << "9. Remove Student" << endl;
        cout << "10. Remove Teacher" << endl;
        cout << "11. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            add_student();
            break;
        case 2:
            add_teacher();
            break;
        case 3:
            update_fee();
            break;
        case 4:
            add_fee();
            break;
        case 5:
            add_timetable();
            break;
        case 6:
            update_attendance();
            break;
        case 7:
            update_marks();
            break;
        case 8:
            add_notice();
            break;
        case 9:
            remove_student();
            break;
        case 10:
            remove_teacher();
            break;
        case 11:
            admin_logout();
            return;
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
        }
    }
}

void App::student_menu()
{
    int ch;
    while (1)
    {
        cout << "Welcome Student" << endl;
        cout << "1. Display Profile" << endl;
        cout << "2. Update Password" << endl;
        cout << "3. View Marks" << endl;
        cout << "4. View Attendance" << endl;
        cout << "5. View Timetable" << endl;
        cout << "6. View Fee" << endl;
        cout << "7. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            student_display();
            break;
        case 2:
            student_update();
            break;
        case 3:
            student_marks();
            break;
        case 4:
            student_attendance();
            break;
        case 5:
            student_timetable();
            break;
        case 6:
            student_fee();
            break;
        case 7:
            student_logout();
            return;
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
        }
    }
}

void App::teacher_menu()
{
    int ch;
    while (1)
    {
        cout << "Welcome Teacher" << endl;
        cout << "1. Display Profile" << endl;
        cout << "2. Update Password" << endl;
        cout << "3. Upload Marks" << endl;
        cout << "4. Upload Attendance" << endl;
        cout << "5. View Timetable" << endl;
        cout << "6. View Salary" << endl;
        cout << "7. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            teacher_display();
            break;
        case 2:
            teacher_update();
            break;
        case 3:
            upload_marks();
            break;
        case 4:
            take_attendance();
            break;
        case 5:
            teacher_timetable();
            break;
        case 6:
            teacher_salary();
            break;
        case 7:
            teacher_logout();
            return;
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
        }
    }
}