#include <iostream>
#include <fstream>
#include <string>

#include "Csv_helper.h"

using namespace std;

void CSV::write(string filename, string *data, int size, const char delimiter)
{
    ofstream file;
    file.open(filename, ios::app);
    for (int i = 0; i < size; i++)
    {
        try
        {
            if (data[i].find(delimiter) != string::npos)
            {
                throw "Invalid argument: Data contains delimiter.\nFalied to update file.";
            }
        }
        catch (const char *msg)
        {
            cerr << msg << endl;
            throw msg;
        }
    }
    for (int i = 0; i < size; i++)
    {
        file << data[i];
        if (i < size - 1)
        {
            file << delimiter;
        }
    }
    file << endl;
    file.close();
}

int CSV::total_lines(string filename)
{
    ifstream file;
    file.open(filename, ios::in);
    string line;
    int count = 0;
    while (getline(file, line))
    {
        count++;
    }
    return count;
}

string *CSV::split_line(string filename, int line_no, const char delimiter)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
        return nullptr;
    }

    string line;
    int i = 0;
    while (getline(file, line))
    {
        if (i == line_no)
        {
            string *arr = new string[10];
            int j = 0;
            string token;
            for (char c : line)
            {
                if (c == delimiter)
                {
                    arr[j++] = token;
                    token.clear();
                }
                else
                {
                    token += c;
                }
            }
            arr[j] = token;
            return arr;
        }
        i++;
    }
    cerr << "Error: Line number out of bounds." << endl;
    return nullptr;
}

void CSV::delete_line(string filename, int line_no)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
        return;
    }
    int i = 0;
    string line, temp_line;
    ofstream temp("temp.csv");
    while (getline(file, line))
    {
        if (i != line_no)
        {
            temp << line << endl;
        }
        else
        {
            temp_line = line;
        }
        i++;
    }
    file.close();
    temp.close();
    remove(filename.c_str());
    rename("temp.csv", filename.c_str());
}

void CSV::update_line(string filename, int line_no, string *data, int size, const char delimiter)
{
    string *temp_line = split_line(filename, line_no, delimiter);
    if (temp_line == nullptr)
    {
        cerr << "Error: Failed to update line. Reverting changes." << endl;
        return;
    }

    delete_line(filename, line_no);

    try
    {
        write(filename, data, size, delimiter);
    }
    catch (const char *msg)
    {
        write(filename, temp_line, size, delimiter);
    }
}

int CSV::find_line(string filename, string to_find, const char delimiter)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
        return -1;
    }

    string line;
    int i = 0;
    while (getline(file, line))
    {
        string token;
        for (char c : line)
        {
            if (c == delimiter)
            {
                if (token == to_find)
                {
                    return i;
                }
                token.clear();
            }
            else
            {
                token += c;
            }
        }
        i++;
    }
    return -1;
}