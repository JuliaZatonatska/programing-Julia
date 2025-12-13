#include <iostream>
#include <fstream>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <string>

#define M_PI 3.14159265358979323846

class RationalNumber {
private:
    int numerator;
    int denominator;

    void simplify() {
        if (denominator == 0) return;
        int common_divisor = std::gcd(std::abs(numerator), denominator);
        numerator /= common_divisor;
        denominator /= common_divisor;
    }

    void setDenominator(int den) {
        if (den == 0) {
            std::cerr << "Error: Denominator cannot be zero. Setting to 1." << std::endl;
            denominator = 1;
        } else if (den < 0) {
            numerator = -numerator;
            denominator = -den;
        } else {
            denominator = den;
        }
        simplify();
    }

public:
    RationalNumber() : numerator(1), denominator(1) {}

    RationalNumber(int num, int den) : numerator(num) {
        setDenominator(den);
    }

    void setNumerator(int num) {
        numerator = num;
        simplify();
    }

    void initDenominator(int den) {
        setDenominator(den);
    }

    void inputFromTerminal() {
        int num, den;
        std::cout << "Enter numerator: ";
        std::cin >> num;
        std::cout << "Enter denominator: ";
        std::cin >> den;
        numerator = num;
        setDenominator(den);
    }

    void printToTerminal() const {
        std::cout << numerator << "/" << denominator;
    }

    RationalNumber add(const RationalNumber& other) const {
        int new_num = numerator * other.denominator + other.numerator * denominator;
        int new_den = denominator * other.denominator;
        return RationalNumber(new_num, new_den);
    }

    RationalNumber multiply(const RationalNumber& other) const {
        int new_num = numerator * other.numerator;
        int new_den = denominator * other.denominator;
        return RationalNumber(new_num, new_den);
    }
};

class Rectangle {
private:
    float x1;
    float y1;
    float width;
    float height;

    float getX2() const {
        return x1 + width;
    }

    float getY2() const {
        return y1 - height;
    }

public:
    Rectangle(float top_x, float top_y, float w, float h) : x1(top_x), y1(top_y), width(w), height(h) {
        if (width < 0) width = 0;
        if (height < 0) height = 0;
    }

    void printWidth() const {
        std::cout << "Width: " << width;
    }

    void printHeight() const {
        std::cout << "Height: " << height;
    }

    void printArea() const {
        std::cout << "Area: " << width * height;
    }

    void printPerimeter() const {
        std::cout << "Perimeter: " << 2 * (width + height);
    }

    Rectangle intersect(const Rectangle& other) const {
        float ix1 = std::max(x1, other.x1);
        float ix2 = std::min(getX2(), other.getX2());
        float iy1 = std::min(y1, other.y1);
        float iy2 = std::max(getY2(), other.getY2());

        float new_width = ix2 - ix1;
        float new_height = iy1 - iy2;

        if (new_width <= 0 || new_height <= 0) {
            return Rectangle(-1.0f, -1.0f, -1.0f, -1.0f);
        }

        return Rectangle(ix1, iy1, new_width, new_height);
    }

    void printCoordinates() const {
        std::cout << "Rectangle: TopLeft(" << x1 << ", " << y1 << "), W(" << width << "), H(" << height << ")";
    }
};

class Triangle {
private:
    float angle_degrees;
    float side_b;
    float side_c;
    float side_a;

    void calculateSidesAndAngles() {
        float angle_radians = angle_degrees * M_PI / 180.0f;
        side_a = std::sqrt(side_b * side_b + side_c * side_c - 2 * side_b * side_c * std::cos(angle_radians));
    }

    float calculateAngleA_Radians() const {
        if (side_a == 0 || side_c == 0) return 0.0f;
        float cos_a = (side_a * side_a + side_c * side_c - side_b * side_b) / (2 * side_a * side_c);
        if (cos_a > 1.0f) cos_a = 1.0f;
        if (cos_a < -1.0f) cos_a = -1.0f;
        return std::acos(cos_a);
    }

    float calculateAngleB_Radians() const {
        if (side_a == 0 || side_b == 0) return 0.0f;
        float cos_b = (side_a * side_a + side_b * side_b - side_c * side_c) / (2 * side_a * side_b);
        if (cos_b > 1.0f) cos_b = 1.0f;
        if (cos_b < -1.0f) cos_b = -1.0f;
        return std::acos(cos_b);
    }

public:
    Triangle(float top_angle, float b, float c) : angle_degrees(top_angle), side_b(b), side_c(c) {
        if (top_angle <= 0.0f || top_angle >= 180.0f) angle_degrees = 60.0f;
        if (side_b <= 0.0f) side_b = 1.0f;
        if (side_c <= 0.0f) side_c = 1.0f;
        calculateSidesAndAngles();
    }

    void printSideA() const {
        std::cout << "Side A (Base): " << side_a;
    }

    void printSideB() const {
        std::cout << "Side B: " << side_b;
    }

    void printSideC() const {
        std::cout << "Side C: " << side_c;
    }

    void printTopAngle() const {
        std::cout << "Top Angle (degrees): " << angle_degrees;
    }

    void printBaseAngles() const {
        float angle_a_rad = calculateAngleA_Radians();
        float angle_b_rad = calculateAngleB_Radians();

        std::cout << "Base Angle 1 (degrees): " << angle_a_rad * 180.0f / M_PI << std::endl;
        std::cout << "Base Angle 2 (degrees): " << angle_b_rad * 180.0f / M_PI;
    }

    void printArea() const {
        float s = (side_a + side_b + side_c) / 2.0f;
        float area = std::sqrt(s * (s - side_a) * (s - side_b) * (s - side_c));
        std::cout << "Area: " << area;
    }

    void printPerimeter() const {
        std::cout << "Perimeter: " << side_a + side_b + side_c;
    }
};

class Time {
private:
    int hours;
    int minutes;
    int seconds;

    void normalize() {
        int total_seconds = hours * 3600 + minutes * 60 + seconds;
        total_seconds = (total_seconds % 86400 + 86400) % 86400;

        hours = total_seconds / 3600;
        minutes = (total_seconds % 3600) / 60;
        seconds = total_seconds % 60;
    }

public:
    Time(int h = 0, int m = 0, int s = 0) : hours(h), minutes(m), seconds(s) {
        normalize();
    }

    int differenceInSeconds(const Time& other) const {
        int this_total = hours * 3600 + minutes * 60 + seconds;
        int other_total = other.hours * 3600 + other.minutes * 60 + other.seconds;
        return std::abs(this_total - other_total);
    }

    void printTime() const {
        std::cout << hours << "h " << minutes << "m " << seconds << "s";
    }

    void printDifference(const Time& other) const {
        int diff_sec = differenceInSeconds(other);
        int h = diff_sec / 3600;
        int m = (diff_sec % 3600) / 60;
        int s = diff_sec % 60;

        std::cout << "Difference: " << h << "h " << m << "m " << s << "s";
    }
};

class Date {
private:
    int year;
    int month;
    int day;
    static Date* instance;

    Date(int y, int m, int d) : year(y), month(m), day(d) {}

    static bool isLeap(int y) {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    static long long daysFromEpoch(int y, int m, int d) {
        long long days = d;
        for (int yr = 1; yr < y; ++yr) {
            days += isLeap(yr) ? 366 : 365;
        }
        int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        for (int mon = 1; mon < m; ++mon) {
            if (mon == 2 && isLeap(y)) {
                days += 29;
            } else {
                days += days_in_month[mon];
            }
        }
        return days;
    }

public:
    Date(const Date&) = delete;
    Date& operator=(const Date&) = delete;

    static Date* getInstance(int y = 1, int m = 1, int d = 1) {
        if (!instance) {
            instance = new Date(y, m, d);
        }
        return instance;
    }

    static long long differenceInDays(int y1, int m1, int d1, int y2, int m2, int d2) {
        long long days1 = daysFromEpoch(y1, m1, d1);
        long long days2 = daysFromEpoch(y2, m2, d2);
        return std::abs(days1 - days2);
    }

    void printDate() const {
        std::cout << year << "-" << month << "-" << day;
    }

    void printDifference(int y_other, int m_other, int d_other) const {
        long long diff = differenceInDays(year, month, day, y_other, m_other, d_other);
        std::cout << "Difference in days: " << diff;
    }
};

Date* Date::instance = nullptr;

int main() {
    std::cout << "--- Task 1: Rational Number ---" << std::endl;
    RationalNumber r1(10, -20);
    std::cout << "R1 (10/-20 simplified to): ";
    r1.printToTerminal();
    std::cout << std::endl;
    RationalNumber r2(1, 4);
    RationalNumber r_sum = r1.add(r2);
    std::cout << "R1 + R2: ";
    r_sum.printToTerminal();
    std::cout << "\n";

    std::cout << "--- Task 6: Rectangle ---" << std::endl;
    Rectangle rect1(0, 10, 5, 4);
    Rectangle rect2(3, 8, 6, 3);
    rect1.printArea();
    std::cout << std::endl;
    Rectangle intersect_rect = rect1.intersect(rect2);
    std::cout << "Intersection: ";
    intersect_rect.printCoordinates();
    std::cout << "\n";

    std::cout << "--- Task 7: Triangle ---" << std::endl;
    Triangle t1(90.0f, 3.0f, 4.0f);
    t1.printSideA();
    std::cout << "\n";
    t1.printBaseAngles();
    std::cout << "\n";
    t1.printArea();
    std::cout << std::endl;

    std::cout << "--- Task 8a: Time ---" << std::endl;
    Time t_start(10, 30, 0);
    Time t_end(11, 0, 45);
    t_start.printTime();
    std::cout << " vs ";
    t_end.printTime();
    std::cout << "\n";
    t_start.printDifference(t_end);
    std::cout << "\n";

    std::cout << "--- Task 8b: Date (Singleton) ---" << std::endl;
    Date* d1 = Date::getInstance(2024, 1, 1);
    Date* d2 = Date::getInstance(2025, 1, 1);

    std::cout << "Date 1 (Singleton instance): ";
    d1->printDate();
    std::cout << "\n";

    std::cout << "Comparing d1 (" << 2024 << "-" << 1 << "-" << 1 << ") with " << 2025 << "-" << 1 << "-" << 1 << ": ";
    d1->printDifference(2025, 1, 1);
    std::cout << "\n";

    return 0;
}
