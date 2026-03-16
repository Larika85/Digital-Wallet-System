#include "Date.h"
#include <sstream>
#include <iomanip>
#include <iostream>
using namespace std;

Date::Date(int year, int month, int day) : year(year), month(month), day(day) {}

Date::Date(const string &dateStr) {
    istringstream ss(dateStr);
    char delimiter;
    ss >> year >> delimiter >> month >> delimiter >> day;

    // Ensure valid input format
    if (delimiter != '-' || ss.fail()) {
        throw invalid_argument("Invalid date format. Expected format: YYYY-MM-DD");
    }
}

bool Date::isLeapYear(int year) const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool Date::isValid() const {
    // Ensure valid month and day range
    if (year < 1 || month < 1 || month > 12 || day < 1) return false;

    // Days in each month (index 0 is Jan, index 1 is Feb, etc.)
    int daysInMonth[] = {31, isLeapYear(year) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // Check if day is within valid range for the given month
    return day <= daysInMonth[month - 1];
}

string Date::toString() const {
    ostringstream oss;
    oss << setfill('0') << setw(4) << year << "-"
        << setw(2) << month << "-" << setw(2) << day;
    return oss.str();
}

ostream& operator<<(ostream &os, const Date &date) {
    os << date.toString();
    return os;
}

istream& operator>>(istream &is, Date &date) {
    char delimiter;
    is >> date.year >> delimiter >> date.month >> delimiter >> date.day;
    // Check for invalid format after parsing
    if (delimiter != '-') {
        throw invalid_argument("Invalid date format. Expected format: YYYY-MM-DD");
    }
    return is;
}
