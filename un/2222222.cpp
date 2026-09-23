#include <iostream>
#include <string>
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
        int n;
        cout << "Enter day number (0-Monday, ..., 6-Sunday): ";
        cin >> n;
        if (n < 0 || n > 6) n = 0;
        day = static_cast<DayEnum>(n);
    }
    void print() { cout << dayNames[day] << endl; }
};

class Month {
public:
    enum MonthEnum { January=1, February, March, April, May, June, July, August, September, October, November, December };
private:
    MonthEnum month;
    const string monthNames[13] = {"", "January","February","March","April","May","June","July","August","September","October","November","December"};
public:
    void input() {
        int n;
        cout << "Enter month number (1-January, ..., 12-December): ";
        cin >> n;
        if (n < 1 || n > 12) n = 1;
        month = static_cast<MonthEnum>(n);
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
        int n;
        cout << "Enter color number (0-Red, ..., 6-Violet): ";
        cin >> n;
        if (n < 0 || n > 6) n = 0;
        color = static_cast<ColorEnum>(n);
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
        int n;
        cout << "Enter chess piece number (0-King, ..., 5-Pawn): ";
        cin >> n;
        if (n < 0 || n > 5) n = 5;
        piece = static_cast<PieceEnum>(n);
    }
    void print() { cout << pieceNames[piece] << endl; }
};

// =======================
// 2. Структура Card (Карти)
// =======================

struct Card {
    enum Suit { Spades, Clubs, Diamonds, Hearts }; // Піка, Трефа, Бубна, Чирва
    enum Rank { Seven=7, Eight=8, Nine=9, Ten=10, Jack=11, Queen=12, King=13, Ace=14 };

    Suit suit;
    Rank rank;

    string getSuitName() const {
        const string names[] = { "Spades", "Clubs", "Diamonds", "Hearts" };
        return names[suit];
    }
    string getRankName() const {
        if (rank <= 10) return to_string(rank);
        if (rank == 11) return "Jack";
        if (rank == 12) return "Queen";
        if (rank == 13) return "King";
        return "Ace";
    }

    void input(string label) {
        int s, r;
        cout << "--- " << label << " ---" << endl;
        cout << "Suit (0-Spades, 1-Clubs, 2-Diamonds, 3-Hearts): ";
        cin >> s;
        if (s < 0 || s > 3) s = 0;
        suit = static_cast<Suit>(s);

        cout << "Rank (7, 8, 9, 10, 11-J, 12-Q, 13-K, 14-A): ";
        cin >> r;
        if (r < 7) r = 7; if (r > 14) r = 14;
        rank = static_cast<Rank>(r);
    }

    void print() { cout << getRankName() << " of " << getSuitName() << endl; }
};

bool beat(Card x, Card y, Card::Suit z) {
    if (x.suit == y.suit) return x.rank > y.rank;
    if (x.suit == z) return true;
    return false;
}

// =======================
// 3. НОВИЙ КЛАС: Конвертер Довжини
// =======================

class LengthConverter {
public:
    // Перелік величин: мм, см, дм, м, км
    enum Unit { MM, CM, DM, M, KM };

private:
    double value; // Введене число
    Unit unit;    // Обрана одиниця виміру
    const string unitNames[5] = { "mm", "cm", "dm", "m", "km" };

public:
    void input() {
        cout << "\n--- Length Converter ---" << endl;
        cout << "Enter length value (e.g., 10.5): ";
        cin >> value;

        int n;
        cout << "Enter unit (0-mm, 1-cm, 2-dm, 3-m, 4-km): ";
        cin >> n;

        // Перевірка на коректність
        if (n < 0 || n > 4) {
            cout << "Invalid unit, defaulting to meters (3)." << endl;
            n = 3;
        }
        unit = static_cast<Unit>(n);
    }

    // Функція переведення в метри
    double convertToMeters() {
        switch (unit) {
            case MM: return value * 0.001;  // 1 мм = 0.001 м
            case CM: return value * 0.01;   // 1 см = 0.01 м
            case DM: return value * 0.1;    // 1 дм = 0.1 м
            case M:  return value * 1.0;    // 1 м = 1 м
            case KM: return value * 1000.0; // 1 км = 1000 м
            default: return 0.0;
        }
    }

    void print() {
        cout << "Result: " << value << " " << unitNames[unit]
             << " = " << convertToMeters() << " meters." << endl;
    }
};

// =======================
// Main
// =======================

int main() {
    // 1. Тест днів (попереднє завдання)
    cout << "=== Choose Day ===" << endl;
    Day d; d.input(); cout << "You chose: "; d.print();

    // 2. Тест карт (попереднє завдання)
    cout << "\n=== Card Game Check ===" << endl;
    Card c1, c2;
    c1.input("Attacker");
    c2.input("Defender");

    int tr;
    cout << "Trump Suit (0-3): "; cin >> tr;
    Card::Suit trump = static_cast<Card::Suit>(tr);

    if (beat(c1, c2, trump)) cout << ">> Beats!" << endl;
    else cout << ">> Does NOT beat." << endl;

    // 3. Тест конвертера довжини (НОВЕ ЗАВДАННЯ)
    LengthConverter lc;
    lc.input();
    lc.print();

    return 0;
}