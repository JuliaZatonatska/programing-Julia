#include <iostream>
#include <string>
#include <cctype>
#include <cmath>   // Для sqrt (корінь) та pow (степінь)
#include <vector>  // Для зберігання списку команд
#include <iomanip> // Для setprecision (гарний вивід чисел)

using namespace std;

// =======================
// 1. Попередні класи
// =======================

class Day {
public:
    enum DayEnum { Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };
private:
    DayEnum day;
    const string dayNames[7] = {"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};
public:
    void input() {
        int n; cout << "Enter day (0-6): "; cin >> n;
        if(n<0||n>6) n=0; day = static_cast<DayEnum>(n);
    }
    void print() { cout << dayNames[day] << endl; }
};

class Month {
public:
    enum MonthEnum { January=1, February, March, April, May, June, July, August, September, October, November, December };
private:
    MonthEnum month;
    const string monthNames[13] = {"", "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
public:
    void input() {
        int n; cout << "Enter month (1-12): "; cin >> n;
        if(n<1||n>12) n=1; month = static_cast<MonthEnum>(n);
    }
    void print() { cout << monthNames[month] << endl; }
};

class Color {
public:
    enum ColorEnum { Red, Orange, Yellow, Green, Blue, Indigo, Violet };
private:
    ColorEnum color;
    const string colorNames[7] = {"Red","Orange","Yellow","Green","Blue","Indigo","Violet"};
public:
    void input() {
        int n; cout << "Enter color (0-6): "; cin >> n;
        if(n<0||n>6) n=0; color = static_cast<ColorEnum>(n);
    }
    void print() { cout << colorNames[color] << endl; }
};

class ChessPiece {
public:
    enum PieceEnum { King, Queen, Rook, Bishop, Knight, Pawn };
private:
    PieceEnum piece;
    const string pieceNames[6] = {"King","Queen","Rook","Bishop","Knight","Pawn"};
public:
    void input() {
        int n; cout << "Enter chess piece (0-5): "; cin >> n;
        if(n<0||n>5) n=5; piece = static_cast<PieceEnum>(n);
    }
    void print() { cout << pieceNames[piece] << endl; }
};

// =======================
// 2. Структура Card
// =======================
struct Card {
    enum Suit { Spades, Clubs, Diamonds, Hearts };
    enum Rank { Seven=7, Eight=8, Nine=9, Ten=10, Jack=11, Queen=12, King=13, Ace=14 };
    Suit suit; Rank rank;

    string getSuitName() const { const string n[] = {"Spades","Clubs","Diamonds","Hearts"}; return n[suit]; }
    string getRankName() const {
        if(rank<=10) return to_string(rank);
        if(rank==11) return "Jack"; if(rank==12) return "Queen";
        if(rank==13) return "King"; return "Ace";
    }
    void input(string label) {
        int s, r; cout << "-- " << label << " --\nSuit(0-3): "; cin >> s;
        if(s<0||s>3) s=0; suit = static_cast<Suit>(s);
        cout << "Rank(7-14): "; cin >> r;
        if(r<7) r=7; if(r>14) r=14; rank = static_cast<Rank>(r);
    }
    void print() { cout << getRankName() << " of " << getSuitName() << endl; }
};

bool beat(Card x, Card y, Card::Suit z) {
    if (x.suit == y.suit) return x.rank > y.rank;
    if (x.suit == z) return true;
    return false;
}

// =======================
// 3. Length Converter
// =======================
class LengthConverter {
public:
    enum Unit { MM, CM, DM, M, KM };
private:
    double value; Unit unit;
    const string unitNames[5] = { "mm", "cm", "dm", "m", "km" };
public:
    void input() {
        cout << "\n--- Length Converter ---" << endl;
        cout << "Value: "; cin >> value;
        int n; cout << "Unit (0-mm, 1-cm, 2-dm, 3-m, 4-km): "; cin >> n;
        if (n < 0 || n > 4) n = 3; unit = static_cast<Unit>(n);
    }
    double convertToMeters() {
        switch (unit) {
            case MM: return value * 0.001; case CM: return value * 0.01;
            case DM: return value * 0.1; case M: return value * 1.0;
            case KM: return value * 1000.0; default: return 0.0;
        }
    }
    void print() { cout << value << " " << unitNames[unit] << " = " << convertToMeters() << " m" << endl; }
};

// =======================
// 4. Syllable Counter
// =======================
class SyllableCounter {
public:
    enum Vowel { A, E, I, O, U, Y, None };
private:
    string sentence;
    Vowel checkVowel(char c) {
        c = tolower(c);
        switch(c) {
            case 'a': return A; case 'e': return E; case 'i': return I;
            case 'o': return O; case 'u': return U; case 'y': return Y;
            default: return None;
        }
    }
public:
    void inputAndCount() {
        cout << "\n=== Syllable Counter ===" << endl;
        cout << "Enter sentence: ";
        cin.ignore(); getline(cin, sentence);
        int count = 0;
        for (char c : sentence) if (checkVowel(c) != None) count++;
        cout << "Total vowels: " << count << endl;
    }
};

// =======================
// 5. НОВИЙ КЛАС: ShipNavigator
// =======================

class ShipNavigator {
public:
    // Напрямки (розставлені за годинниковою стрілкою для зручності математики)
    // N=0, E=1, S=2, W=3
    enum Course { N, E, S, W };

    // Команди: Вперед (без змін), Назад (розворот), Вліво (-90), Вправо (+90)
    enum Order { Forward, Back, Left, Right };

private:
    Course currentCourse;
    double speed;       // Швидкість (одиниць за годину/хвилину)
    double x, y;        // Координати (Старт в 0,0)

    const string courseNames[4] = { "North", "East", "South", "West" };

public:
    ShipNavigator() : x(0), y(0), currentCourse(N), speed(0) {}

    void startNavigation() {
        cout << "\n=== Ship Navigation ===" << endl;

        // 1. Ввід початкових даних
        int c;
        cout << "Initial Course (0-N, 1-E, 2-S, 3-W): ";
        cin >> c;
        if(c < 0 || c > 3) c = 0;
        currentCourse = static_cast<Course>(c);

        cout << "Ship Speed (km/h or m/s): ";
        cin >> speed;

        int moves;
        cout << "How many movements? ";
        cin >> moves;

        // Вектори для команд і часу
        vector<Order> orders(moves);
        vector<double> times(moves);

        // 2. Ввід команд
        cout << "Enter orders (0-Fwd, 1-Back, 2-Left, 3-Right) and Time for each:" << endl;
        for(int i = 0; i < moves; i++) {
            int ord;
            cout << "Move #" << (i+1) << " Order: "; cin >> ord;
            cout << "Move #" << (i+1) << " Time:  "; cin >> times[i];

            if (ord < 0 || ord > 3) ord = 0; // Захист
            orders[i] = static_cast<Order>(ord);
        }

        // 3. Обробка руху
        processMovement(orders, times);
    }

    void processMovement(const vector<Order>& orders, const vector<double>& times) {
        for(size_t i = 0; i < orders.size(); i++) {
            // Змінюємо курс на основі команди
            changeDirection(orders[i]);

            // Обчислюємо пройдену дистанцію на цьому етапі
            double dist = speed * times[i];

            // Змінюємо координати залежно від поточного курсу
            switch(currentCourse) {
                case N: y += dist; break; // Північ -> +Y
                case S: y -= dist; break; // Південь -> -Y
                case E: x += dist; break; // Схід -> +X
                case W: x -= dist; break; // Захід -> -X
            }
        }

        printResult();
    }

    void changeDirection(Order order) {
        int current = static_cast<int>(currentCourse);

        switch (order) {
            case Forward:
                // Курс не змінюється
                break;
            case Right:
                // Поворот направо (+1 за годинниковою стрілкою): N->E->S->W->N
                current = (current + 1) % 4;
                break;
            case Back:
                // Розворот (+2)
                current = (current + 2) % 4;
                break;
            case Left:
                // Поворот наліво (-1 або +3 за модулем 4): N->W->S->E->N
                current = (current + 3) % 4;
                break;
        }
        currentCourse = static_cast<Course>(current);
    }

    void printResult() {
        // Абсолютна відстань за теоремою Піфагора: sqrt(x^2 + y^2)
        double distance = sqrt(pow(x, 2) + pow(y, 2));

        cout << "\n--- Navigation Result ---" << endl;
        cout << "Final Course: " << courseNames[currentCourse] << endl;
        cout << "Final Coordinates: X=" << x << ", Y=" << y << endl;
        cout << "Absolute displacement from start: " << fixed << setprecision(2) << distance << endl;
    }
};

// =======================
// MAIN
// =======================

int main() {
    // Для економії місця попередні тести закоментовано,
    // але ви можете їх розкоментувати за потреби.

    /*
    Day d; d.input(); d.print();
    Card c; c.input("Card"); c.print();
    SyllableCounter sc; sc.inputAndCount();
    */

    // ТЕСТ 6: Навігація корабля
    ShipNavigator ship;
    ship.startNavigation();

    return 0;
}