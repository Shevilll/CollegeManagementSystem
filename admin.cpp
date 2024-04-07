#include <iostream>
#include <string>
#include <fstream>

#include "Admin.h"
#include "Csv_helper.h"

#define DELIMETER ','

int Admin::admin_login()
{
    string username, password;
    cin.ignore();
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);
    if (username == "admin" && password == "password")
    {
        cout << "Login successful" << endl;
        return 1;
    }
    else
    {
        cout << "Invalid username or password" << endl;
        return 0;
    }
}

void Admin::add_student()
{
    CSV csv;
    char passwd[20];
    cin.ignore();
    cout << "Enter student roll no: ";
    getline(cin, roll_no);
    for (int i = 0; i < csv.total_lines("students.csv"); i++)
    {
        string *data = csv.split_line("students.csv", i, DELIMETER);
        if (data[0] == roll_no)
        {
            cout << "Student with this roll no already exists" << endl;
            return;
        }
    }
    cout << "Enter student name: ";
    getline(cin, name);
    cout << "Enter student branch: ";
    getline(cin, branch);
    cout << "Enter student semester: ";
    getline(cin, semester);
    cout << "Enter student email: ";
    getline(cin, email);
    cout << "Enter student phone: ";
    getline(cin, phone);
    cout << "Enter student address: ";
    getline(cin, address);
    cout << "Enter room number: ";
    getline(cin, room);
    strcpy(passwd, roll_no.c_str());
    strcat(passwd, name.c_str());
    string data[] = {roll_no, name, branch, semester, email, phone, address, passwd, room};
    csv.write("students.csv", data, 9, DELIMETER);
}

void Admin::add_teacher()
{
    CSV csv;
    char passwd[20];
    cin.ignore();
    cout << "Enter teacher unique id: ";
    getline(cin, unique_id);
    for (int i = 0; i < csv.total_lines("teachers.csv"); i++)
    {
        string *data = csv.split_line("teachers.csv", i, DELIMETER);
        if (data[0] == unique_id)
        {
            cout << "Teacher with this unique id already exists" << endl;
            return;
        }
    }
    cout << "Enter teacher name: ";
    getline(cin, tname);
    cout << "Enter teacher degree: ";
    getline(cin, tdegree);
    cout << "Enter teacher email: ";
    getline(cin, temail);
    cout << "Enter teacher phone: ";
    getline(cin, tphone);
    cout << "Enter teacher address: ";
    getline(cin, taddress);
    strcpy(passwd, unique_id.c_str());
    strcat(passwd, tname.c_str());
    string data[] = {unique_id, tname, tdegree, temail, tphone, taddress, passwd};
    csv.write("teachers.csv", data, 7, DELIMETER);
}
void Admin::update_fee()
{
    CSV csv;
    string id, fees;
    cin.ignore();
    cout << "Enter roll_no or unique_id: ";
    getline(cin, id);
    cout << "Enter new fees: ";
    getline(cin, fees);
    for (int i = 0; i < csv.total_lines("fees.csv"); i++)
    {
        string *data = csv.split_line("fees.csv", i, DELIMETER);
        if (data[0] == id)
        {
            char ch;
            cout << "Are you sure you want to update this fee? (y/n): " << endl;
            cout << "Old fee: " << data[1] << endl;
            cin >> ch;
            if (ch != 'y')
            {
                cout << "Fee not updated" << endl;
                return;
            }
            string new_data[] = {id, fees};
            csv.update_line("fees.csv", i, new_data, 2, DELIMETER);
            cout << "Fee updated successfully" << endl;
            return;
        }
    }
    cout << "Id not found" << endl;
}
void Admin::add_fee()
{
    CSV csv;
    string id, fees;
    cin.ignore();
    cout << "Enter roll_no or unique_id: ";
    getline(cin, id);
    cout << "Enter fees: ";
    getline(cin, fees);
    string data[] = {id, fees};
    if (csv.find_line("fees.csv", id, DELIMETER) != -1)
    {
        cout << "Id already added" << endl;
        return;
    }
    csv.write("fees.csv", data, 2, DELIMETER);
}
void Admin::add_timetable()
{
    CSV csv;
    string room, unique_id, date, day, time, course;
    cin.ignore();
    cout << "Enter teacher unique id: ";
    getline(cin, unique_id);
    if (csv.split_line("teachers.csv", 0, DELIMETER)[0] != unique_id)
    {
        cout << "Teacher with this unique id does not exist" << endl;
        return;
    }
    cout << "Enter date: ";
    getline(cin, date);
    cout << "Enter day: ";
    getline(cin, day);
    cout << "Enter time: ";
    getline(cin, time);
    cout << "Enter room number: ";
    getline(cin, room);
    cout << "Enter course: ";
    getline(cin, course);
    string data[] = {room, unique_id, date, day, time, course};
    csv.write("timetable.csv", data, 6, DELIMETER);
}

void Admin::update_attendance()
{
    CSV csv;
    string roll_no, date, status, time;
    cin.ignore();
    cout << "Enter student roll no: ";
    getline(cin, roll_no);
    cout << "Enter date: ";
    getline(cin, date);
    cout << "Enter time: ";
    getline(cin, time);
    for (int i = 0; i < csv.total_lines("attendance.csv"); i++)
    {
        string *data = csv.split_line("attendance.csv", i, DELIMETER);
        if (data[3] == roll_no && data[0] == date && data[1] == time)
        {
            char ch;
            cout << "Are you sure you want to update this attendance? (y/n): " << endl;
            cout << "Old status: " << data[4] << endl;
            cin >> ch;
            if (ch != 'y')
            {
                cout << "Attendance not updated" << endl;
                return;
            }
            cin.ignore();
            cout << "Enter new status: ";
            getline(cin, status);
            string new_data[] = {date, time, data[2], roll_no, status, data[5], data[6]};
            csv.update_line("attendance.csv", i, new_data, 7, DELIMETER);
            cout << "Attendance updated successfully" << endl;
            return;
        }
    }
    cout << "Attendance not found" << endl;
}
void Admin::update_marks()
{
    CSV csv;
    string roll_no, date, marks, time;
    cin.ignore();
    cout << "Enter student roll no: ";
    getline(cin, roll_no);
    cout << "Enter date: ";
    getline(cin, date);
    cout << "Enter time: ";
    getline(cin, time);
    cout << "Enter marks: ";

    getline(cin, marks);
    for (int i = 0; i < csv.total_lines("marks.csv"); i++)
    {
        string *data = csv.split_line("marks.csv", i, DELIMETER);
        if (data[3] == roll_no && data[0] == date && data[1] == time)
        {
            char ch;
            cout << "Are you sure you want to update this marks? (y/n): " << endl;
            cout << "Old marks: " << data[4] << endl;
            cin >> ch;
            if (ch != 'y')
            {
                cout << "Marks not updated" << endl;
                return;
            }
            string new_data[] = {date, time, data[2], roll_no, marks, data[5], data[6]};
            csv.update_line("marks.csv", i, new_data, 7, DELIMETER);
            cout << "Marks updated successfully" << endl;
            return;
        }
    }
    cout << "Marks not found" << endl;
}

void Admin::add_notice()
{
    CSV csv;
    cin.ignore();
    cout << "Enter date: ";
    getline(cin, notice);
    cout << "Enter notice description: ";
    getline(cin, notice_desc);
    string data[] = {notice, notice_desc};
    csv.write("notices.csv", data, 2, DELIMETER);
}

void Admin::remove_student()
{
    CSV csv;
    string roll_no;
    cin.ignore();
    cout << "Enter student roll no: ";
    getline(cin, roll_no);
    for (int i = 0; i < csv.total_lines("students.csv"); i++)
    {
        string *data = csv.split_line("students.csv", i, DELIMETER);
        if (data[0] == roll_no)
        {
            char ch;
            cout << "Are you sure you want to remove this student? (y/n): " << endl;
            csv_line = i;
            student_display();
            cin >> ch;
            if (ch != 'y')
            {
                cout << "Student not removed" << endl;
                return;
            }
            csv.delete_line("students.csv", i);
            cout << "Student removed successfully" << endl;
            return;
        }
    }
    cout << "Student not found" << endl;
}

void Admin::remove_teacher()
{
    CSV csv;
    string unique_id;
    cin.ignore();
    cout << "Enter teacher unique_id: ";
    getline(cin, unique_id);
    for (int i = 0; i < csv.total_lines("teachers.csv"); i++)
    {
        string *data = csv.split_line("teachers.csv", i, DELIMETER);
        if (data[0] == unique_id)
        {
            char ch;
            cout << "Are you sure you want to remove this teacher? (y/n): " << endl;
            tcsv_line = i;
            teacher_display();
            cin >> ch;
            if (ch != 'y')
            {
                cout << "Teacher not removed" << endl;
                return;
            }
            csv.delete_line("teachers.csv", i);
            cout << "Teacher removed successfully" << endl;
            return;
        }
    }
    cout << "Teacher not found" << endl;
}

void Admin::admin_logout()
{
    cout << "Admin logged out successfully" << endl;
}