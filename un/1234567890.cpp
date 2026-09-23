#include <iostream>
#include <string>
#include <vector>
#include <cmath>    // sqrt, pow
#include <cctype>   // tolower
#include <chrono>   // Для вимірювання часу (benchmark)
#include <iomanip>  // setprecision

using namespace std;

// ==========================================
// 1. БАЗОВІ КЛАСИ (День, Місяць, Колір, Шахи)
// ==========================================

class Day {
public:
    enum DayEnum { Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };
private:
    DayEnum day;
    const string dayNames[7] = {"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};
public:
    void input() {
        int n; cout << "Enter day (0-Monday ... 6-Sunday): "; cin >> n;
        if(n<0||n>6) n=0; day = static_cast<DayEnum>(n);
    }
    void print() { cout << "Result: " << dayNames[day] << endl; }
};

class Month {
public:
    enum MonthEnum { January=1, February, March, April, May, June, July, August, September, October, November, December };
private:
    MonthEnum month;
    // Варіант Б: Масив (Table Lookup)
    const string monthNames[13] = {"", "January","February","March","April","May","June","July","August","September","October","November","December"};
public:
    void input() {
        int n; cout << "Enter month (1-12): "; cin >> n;
        if(n<1||n>12) n=1; month = static_cast<MonthEnum>(n);
    }
    void print() { cout << "Result: " << monthNames[month] << endl; }
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
    void print() { cout << "Result: " << colorNames[color] << endl; }
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
    void print() { cout << "Result: " << pieceNames[piece] << endl; }
};

// ==========================================
// 2. ГРА В КАРТИ (Преферанс)
// ==========================================

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
        int s, r; 
        cout << "-- " << label << " --\nSuit (0-Spades, 1-Clubs, 2-Diamonds, 3-Hearts): "; cin >> s;
        if(s<0||s>3) s=0; suit = static_cast<Suit>(s);
        cout << "Rank (7, 8... 11-J, 12-Q, 13-K, 14-A): "; cin >> r;
        if(r<7) r=7; if(r>14) r=14; rank = static_cast<Rank>(r);
    }
    void print() { cout << getRankName() << " of " << getSuitName() << endl; }
};

bool beat(Card x, Card y, Card::Suit z) {
    if (x.suit == y.suit) return x.rank > y.rank;
    if (x.suit == z) return true;
    return false;
}

// ==========================================
// 3. КОНВЕРТЕР ДОВЖИНИ
// ==========================================

class LengthConverter {
public:
    enum Unit { MM, CM, DM, M, KM };
private:
    double value; Unit unit;
    const string unitNames[5] = { "mm", "cm", "dm", "m", "km" };
public:
    void input() {
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
    void print() { cout << "Result: " << value << " " << unitNames[unit] << " = " << convertToMeters() << " m" << endl; }
};

// ==========================================
// 4. ЛІЧИЛЬНИК СКЛАДІВ (ГОЛОСНИХ)
// ==========================================

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
        cout << "Enter sentence (English): ";
        cin.ignore(); getline(cin, sentence);
        int count = 0;
        for (char c : sentence) if (checkVowel(c) != None) count++;
        cout << "Total syllables (vowels): " << count << endl;
    }
};

// ==========================================
// 5. НАВІГАЦІЯ КОРАБЛЯ
// ==========================================

class ShipNavigator {
public:
    enum Course { N, E, S, W }; 
    enum Order { Forward, Back, Left, Right };
private:
    Course currentCourse;
    double speed,