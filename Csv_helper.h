#ifndef CSV_HELPER_H
#define CSV_HELPER_H

#include <string>

using namespace std;

class CSV
{
public:
    void write(string filename, string *data, int size, const char delimiter);
    string *split_line(string filename, int line_no, const char delimiter);
    int total_lines(string filename);
    void delete_line(string filename, int line_no);
    void update_line(string filename, int line_no, string *data, int size, const char delimiter);
    int find_line(string filename, string to_find, const char delimiter);
};

#endif