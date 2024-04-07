#include <iostream>
#include <string>
#include <fstream>

#include "Csv_helper.h"
#include "Teacher.h"

#define DELIMETER ','

using namespace std;

int Teacher::teacher_login()
{
    CSV csv;
    string _id, passwd;
    cin.ignore();
    cout << "Enter your unique id: ";
    getline(cin, _id);
    cout << "Enter your password: ";
    getline(cin, passwd);
    for (int i = 0; i < csv.total_lines("teachers.csv"); i++)
    {
        string *data = csv.split_line("teachers.csv", i, DELIMETER);
        if (data[0] == _id && data[6] == passwd)
        {
            cout << "Login successful" << endl;
            tcsv_line = i;
            unique_id = data[0];
            tname = data[1];
            tdegree = data[2];
            temail = data[3];
            tphone = data[4];
            taddress = data[5];
            return 1;
        }
    }
    cout << "Invalid unique_id or password" << endl;
    return 0;
}

void Teacher::teacher_display()
{
    CSV csv;
    string *data = csv.split_line("teachers.csv", tcsv_line, DELIMETER);
    cout << "Unique ID: " << data[0] << endl;
    cout << "Name: " << data[1] << endl;
    cout << "Degree: " << data[2] << endl;
    cout << "Email: " << data[3] << endl;
    cout << "Phone: " << data[4] << endl;
    cout << "Address: " << data[5] << endl;
}

void Teacher::teacher_update()
{
    CSV csv;
    string passwd;
    cin.ignore();
    cout << "Enter old password: ";
    getline(cin, passwd);
    string *data = csv.split_line("teachers.csv", csv_line, DELIMETER);
    if (data[6] != passwd)
    {
        cout << "Invalid old password" << endl;
        return;
    }
    cout << "Enter new password: ";
    getline(cin, passwd);
    cout << "Enter new password again: ";
    string passwd2;
    getline(cin, passwd2);
    if (passwd != passwd2)
    {
        cout << "Passwords do not match" << endl;
        return;
    }
    string new_data[7] = {data[0], data[1], data[2], data[3], data[4], data[5], passwd};
    csv.update_line("teachers.csv", csv_line, new_data, 7, DELIMETER);
}

void Teacher::upload_marks()
{
    CSV csv;
    string date, room, time, course;
    int c = 0;
    cin.ignore();
    cout << "Enter date: ";
    getline(cin, date);
    cout << "Enter time: ";
    getline(cin, time);
    string unique_id = csv.split_line("teachers.csv", tcsv_line, DELIMETER)[0];
    for (int i = 0; i < csv.total_lines("timetable.csv"); i++)
    {
        string *data = csv.split_line("timetable.csv", i, DELIMETER);
        if (data[1] == unique_id && data[2] == date && data[4] == time)
        {
            cout << "Room: " << data[0];
            cout << " | Date: " << data[2];
            cout << " | Day: " << data[3];
            cout << " | Time: " << data[4];
            cout << " | Course: " << data[5] << endl;
            room = data[0];
            course = data[5];
            c++;
            break;
        }
    }
    if (c == 0)
    {
        cout << "No classes on this date or time" << endl;
        return;
    }
    for (int i = 0; i < csv.total_lines("marks.csv"); i++)
    {
        string *data = csv.split_line("marks.csv", i, DELIMETER);
        if (data[2] == room && data[0] == date && data[1] == time)
        {
            cout << "Marks already uploaded for this class" << endl;
            return;
        }
    }
    char ch;
    cout << "Do you want to upload marks for all students in this class? (y/n): ";
    cin >> ch;
    if (ch == 'y')
    {
        for (int i = 0; i < csv.total_lines("students.csv"); i++)
        {
            string *st_data = csv.split_line("students.csv", i, DELIMETER);
            if (st_data[8] == room)
            {
                cout << "Roll No: " << st_data[0];
                cout << " | Name: " << st_data[1];
                cout << " | Room: " << st_data[8] << endl;
                cout << "Enter marks: ";
                string marks;
                cin >> marks;
                string final_data[] = {date, time, room, st_data[0], marks, unique_id, course};
                csv.write("marks.csv", final_data, 7, DELIMETER);
            }
        }
    }
}

void Teacher::take_attendance()
{
    CSV csv;
    string date, room, time, course;
    int c = 0;
    cin.ignore();
    cout << "Enter date: ";
    getline(cin, date);
    cout << "Enter time: ";
    getline(cin, time);
    string unique_id = csv.split_line("teachers.csv", tcsv_line, DELIMETER)[0];
    for (int i = 0; i < csv.total_lines("timetable.csv"); i++)
    {
        string *data = csv.split_line("timetable.csv", i, DELIMETER);
        if (data[1] == unique_id && data[2] == date && data[4] == time)
        {
            cout << "Room: " << data[0];
            cout << " | Date: " << data[2];
            cout << " | Day: " << data[3];
            cout << " | Time: " << data[4];
            cout << " | Course: " << data[5] << endl;
            room = data[0];
            course = data[5];
            c++;
            break;
        }
    }
    if (c == 0)
    {
        cout << "No classes on this date or time" << endl;
        return;
    }
    for (int i = 0; i < csv.total_lines("attendance.csv"); i++)
    {
        string *data = csv.split_line("attendance.csv", i, DELIMETER);
        if (data[2] == room && data[0] == date && data[1] == time)
        {
            cout << "Attendance already taken for this class" << endl;
            return;
        }
    }

    for (int i = 0; i < csv.total_lines("students.csv"); i++)
    {
        string *st_data = csv.split_line("students.csv", i, DELIMETER);
        if (st_data[8] == room)
        {
            cout << "Roll No: " << st_data[0];
            cout << " | Name: " << st_data[1];
            cout << " | Room: " << st_data[8] << endl;
            cout << "Enter attendance (P/A): ";
            string attendance;
            cin >> attendance;
            if (attendance != "P" && attendance != "A")
            {
                cout << "Invalid attendance" << endl;
                return;
            }
            string final_data[] = {date, time, room, st_data[0], attendance, unique_id, course};
            csv.write("attendance.csv", final_data, 7, DELIMETER);
        }
    }
}

void Teacher::teacher_timetable()
{
    CSV csv;
    string date;
    int c = 0;
    cin.ignore();
    cout << "Enter date: ";
    getline(cin, date);
    string unique_id = csv.split_line("teachers.csv", tcsv_line, DELIMETER)[0];
    for (int i = 0; i < csv.total_lines("timetable.csv"); i++)
    {
        string *data = csv.split_line("timetable.csv", i, DELIMETER);
        if (data[1] == unique_id && data[2] == date)
        {
            cout << "Room: " << data[0];
            cout << " | Date: " << data[2];
            cout << " | Day: " << data[3];
            cout << " | Time: " << data[4];
            cout << " | Course: " << data[5] << endl;
            c++;
        }
    }
    if (c == 0)
    {
        cout << "No classes on this date" << endl;
    }
}

void Teacher::teacher_salary()
{
    CSV csv;
    cin.ignore();
    for (int i = 0; i < csv.total_lines("fees.csv"); i++)
    {
        string *data = csv.split_line("fees.csv", i, DELIMETER);
        if (data[0] == unique_id)
        {
            cout << "Salary: " << data[1] << endl;
            return;
        }
    }
    cout << "No fees record found" << endl;
}

void Teacher::teacher_logout()
{
    cout << tname << " logged out" << endl;
}
