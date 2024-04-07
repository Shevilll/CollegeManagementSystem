#include <iostream>
#include <string>
#include <fstream>

#include "Student.h"
#include "Csv_helper.h"

#define DELIMETER ','

using namespace std;

int Student::student_login()
{
    CSV csv;
    string roll, passwd;
    cin.ignore();
    cout << "Enter your roll no: ";
    getline(cin, roll);
    cout << "Enter your password: ";
    getline(cin, passwd);
    for (int i = 0; i < csv.total_lines("students.csv"); i++)
    {
        string *data = csv.split_line("students.csv", i, DELIMETER);
        if (data[0] == roll && data[7] == passwd)
        {
            cout << "Login successful" << endl;
            csv_line = i;
            roll_no = data[0];
            name = data[1];
            branch = data[2];
            semester = data[3];
            email = data[4];
            phone = data[5];
            address = data[6];
            room = data[8];
            return 1;
        }
    }
    cout << "Invalid roll no or password" << endl;
    return 0;
}

void Student::student_display()
{
    CSV csv;
    string *data = csv.split_line("students.csv", csv_line, DELIMETER);
    cout << "Roll No: " << data[0] << endl;
    cout << "Name: " << data[1] << endl;
    cout << "Branch: " << data[2] << endl;
    cout << "Semester: " << data[3] << endl;
    cout << "Email: " << data[4] << endl;
    cout << "Phone: " << data[5] << endl;
    cout << "Address: " << data[6] << endl;
    cout << "Room: " << data[8] << endl;
}
void Student::student_update()
{
    CSV csv;
    string passwd;
    cin.ignore();
    cout << "Enter old password: ";
    getline(cin, passwd);
    string *data = csv.split_line("students.csv", csv_line, DELIMETER);
    if (data[7] != passwd)
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
    string new_data[] = {data[0], name, branch, semester, email, phone, address, passwd2, room};
    csv.update_line("students.csv", csv_line, new_data, 9, DELIMETER);
}
void Student::student_marks()
{
    CSV csv;
    int c = 0;
    for (int i = 0; i < csv.total_lines("marks.csv"); i++)
    {
        string *data = csv.split_line("marks.csv", i, DELIMETER);
        if (data[3] == roll_no)
        {
            cout << "Course: " << data[6];
            cout << " | Marks: " << data[4] << endl;
            c++;
        }
    }
    if (c == 0)
    {
        cout << "No marks found" << endl;
    }
}
void Student::student_attendance()
{
    CSV csv;
    string date;
    int c = 0;
    cin.ignore();
    cout << "Enter date: ";
    getline(cin, date);
    for (int i = 0; i < csv.total_lines("attendance.csv"); i++)
    {
        string *data = csv.split_line("attendance.csv", i, DELIMETER);
        if (data[3] == roll_no && data[0] == date)
        {
            string teacher_name = csv.split_line("teachers.csv", csv.find_line("teachers.csv", data[5], DELIMETER), DELIMETER)[1];
            cout << "Date: " << data[0];
            cout << " | Time: " << data[1];
            cout << " | Room: " << data[2];
            cout << " | Course: " << data[6];
            cout << " | Teacher: " << teacher_name;
            cout << " | Status: " << data[4] << endl;
            c++;
        }
    }

    if (c == 0)
    {
        cout << "No attendance on this day" << endl;
    }
}

void Student::student_timetable()
{
    CSV csv;
    string date;
    int c = 0;
    cout << "Enter date: ";
    cin.ignore();
    getline(cin, date);
    for (int i = 0; i < csv.total_lines("timetable.csv"); i++)
    {
        string *data = csv.split_line("timetable.csv", i, DELIMETER);
        if (data[2] == date && data[0] == room)
        {
            cout << "Time: " << data[4];
            cout << " | Day: " << data[3];
            cout << " | Course: " << data[5];
            cout << " | Room: " << data[0];
            int line_no = csv.find_line("teachers.csv", data[1], DELIMETER);
            string teacher_name = csv.split_line("teachers.csv", line_no, DELIMETER)[1];
            cout << " | Teacher: " << teacher_name << endl;
            c++;
        }
    }
    if (c == 0)
    {
        cout << "No classes on this day" << endl;
    }
}
void Student::student_fee()
{
    CSV csv;
    for (int i = 0; i < csv.total_lines("fees.csv"); i++)
    {
        string *data = csv.split_line("fees.csv", i, DELIMETER);
        if (data[0] == roll_no)
        {
            cout << "Fees: " << data[1] << endl;
            return;
        }
    }
    cout << "No fees found" << endl;
}

void Student::student_logout()
{
    cout << name << " logged out" << endl;
}
