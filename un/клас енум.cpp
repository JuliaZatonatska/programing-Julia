#include <iostream>
#include <string>
using namespace std;
class Day {
public:
    enum DayEnum { Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };
private:
    DayEnum day;
    const string dayNames[7] = {"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};

public:
    void input() {
        int n;
        cout << "Enter day number (0-Monday, 1-Tuesday, ..., 6-Sunday): ";
        cin >> n;
        day = static_cast<DayEnum>(n);
    }
    void print() {
        cout << dayNames[day] << endl;
    }
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
        cout << "Enter month number (1-January, 2-February, ..., 12-December): ";
        cin >> n;
        month = static_cast<MonthEnum>(n);
    }
    void print() {
        cout << monthNames[month] << endl;
    }
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
        cout << "Enter color number (0-Red, 1-Orange, ..., 6-Violet): ";
        cin >> n;
        color = static_cast<ColorEnum>(n);
    }
    void print() {
        cout << colorNames[color] << endl;
    }
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
        cout << "Enter chess piece number (0-King, 1-Queen, 2-Rook, 3-Bishop, 4-Knight, 5-Pawn): ";
        cin >> n;
        piece = static_cast<PieceEnum>(n);
    }
    void print() {
        cout << pieceNames[piece] << endl;
    }
};


int main() {
    cout << "=== Choose Day ===" << endl;
    Day d;
    d.input();
    cout << "You chose: "; d.print();

    cout << "\n=== Choose Month ===" << endl;
    Month m;
    m.input();
    cout << "You chose: "; m.print();

    cout << "\n=== Choose Color ===" << endl;
    Color c;
    c.input();
    cout << "You chose: "; c.print();

    cout << "\n=== Choose Chess Piece ===" << endl;
    ChessPiece p;
    p.input();
    cout << "You chose: "; p.print();

    return 0;
}