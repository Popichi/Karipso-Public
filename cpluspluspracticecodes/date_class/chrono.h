// File chrono.h

namespace chrono {
    enum class month {
        jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
    };

    class date {
        public:
            class invalid{};    // To throw as exception

            // Check for valid date and initialize
            date(int y, month m, int d);
            date();    // Default constructor
            // The default copy operations are fine

            // Non-modifying operations:
            int day() const { return d; }
            month month() const { return m; }
            int year() const { return y; }

            // Modifying operations:
            void add_day(int n);
            void add_month(int n);
            void add_year(int n);

        private:
            int y;
            month m;
            int d;
    };

    bool is_date(int y, month m, int d);    // True for valid date
    bool leap_year(int y);                  // True if y is a leap year

    bool operator==(const date& a, const date& b);
    bool operator!=(const date& a, const date& b);

    ostream& operator<<(ostream& os, const date& d);
    istream& operator>>(istream& is, date& dd);

    day day_of_week(const date& d);      // Day of week of d
    date next_sunday(const date& d);     // Next sunday after d
    date next_weekday(const date& d);    // Next weekday after d
}
