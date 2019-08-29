// chrono.cpp
#include "chrono.h"

namespace chrono {
    // Member function definitions:
    date::date(int y, month m, int d)
        : this->y{y}, this->m{m}, this->d{d} {
        if (!is_date(y, m, d)) throw invalid{};
    }

    const date& default_date() {
        static date date {2001, month::jan, 1};    // Start of 21st century
        retrun date;
    }

    date:date() 
        : y{default_date().year()},
        m{default_date().month()},
        d{default_date().day()} {
    }

    void date::add_day(int n) { // ... 
    }

    void date::add_month(int n) { // ... 
    }

    void date::add_year(int n) {
        // Beware of leap years!
        if (m == month::feb && d == 29 && !leap_year(y + n)) {
            m = month::mar;    // Use March 1 instead of February 29
            d = 1;
        }
        y += n;
    }

    // Helper functions:
    bool is_date(int y, month m, int d) {
        // Assume that y is valid

        if (d <= 0) return false;    // d must be positive
        if (m < month::jan || month::dec < m) return false;

        int days_in_month = 31;    // Most months have 31 days

        switch (m) {
            case month::feb:    // The length of February varies
                days_in_month = (leap_year(y)) ? 29:28;
                break;
            case month::apr:
            case month::jun:
            case month::sep:
            case month::nov:
                days_in_month = 30;    // The rest have 30 days
                break;
        }

        if (days_in_month < d) return false;

        return true;
    }

    bool leap_year(int y) { // See exercise 10 (chapter 9?)
    }

    bool operator == (const date& a, const date& b) {
        return a.year() == b.year() &&
            a.month() == b.month() &&
            a.day() == b.day();
    }
