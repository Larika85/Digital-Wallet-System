#ifndef DATE_H
#define DATE_H
#include <string>
using namespace std;

class Date {
private:
    int year, month, day;
public:
    Date(int year = 0, int month = 0, int day = 0);
    Date(const string &dateStr);
    
    bool isLeapYear(int year) const;
    bool isValid() const;
    string toString() const;
    
    friend ostream& operator<<(ostream &os, const Date &date);  // Operator Overloading (Output)
    friend istream& operator>>(istream &is, Date &date);        // Operator Overloading (Input)
};

#endif
