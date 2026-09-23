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
        cout << "Enter day number (0-Monday, ..., 6-Sunday): ";
        cin >> n;
        // Проста перевірка на межі масиву
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



struct Card {

    enum Suit { Spades, Clubs, Diamonds, Hearts };

    enum Rank { Seven=7, Eight=8, Nine=9, Ten=10, Jack=11, Queen=12, King=13, Ace=14 };

    Suit suit;
    Rank rank;

    string getSuitName() const {
        const string names[] = { "Spades (Pika)", "Clubs (Trefy)", "Diamonds (Bubna)", "Hearts (Chyrva)" };
        return names[suit];
    }

    string getRankName() const {
        switch(rank) {
            case Jack: return "Jack";
            case Queen: return "Queen";
            case King: return "King";
            case Ace: return "Ace";
            default: return to_string(rank);
        }
    }

    void input(string label) {
        int s, r;
        cout << "--- " << label << " ---" << endl;
        cout << "Enter Suit (0-Spades, 1-Clubs, 2-Diamonds, 3-Hearts): ";
        cin >> s;
        if (s < 0 || s > 3) s = 0;
        suit = static_cast<Suit>(s);

        cout << "Enter Rank (7, 8, 9, 10, 11-Jack, 12-Queen, 13-King, 14-Ace): ";
        cin >> r;

        if (r < 7) r = 7;
        if (r > 14) r = 14;
        rank = static_cast<Rank>(r);
    }

    void print() {
        cout << getRankName() << " of " << getSuitName() << endl;
    }
};

// x - карта, якою б'ють (attacker)
// y - карта, яку треба побити (defender)
// z - козирна масть (trump)
bool beat(Card x, Card y, Card::Suit z) {
    // 1. Якщо карти однієї масті
    if (x.suit == y.suit) {
        // Б'є тільки якщо ранг першої карти більший
        return x.rank > y.rank;
    }

    // 2. Якщо карти різної масті
    // Перша карта може побити другу, ТІЛЬКИ якщо перша - козир, а друга - ні.
    if (x.suit == z) {
        return true;
    }

    // У всіх інших випадках (наприклад, кинули бубну на піку без козиря) - не б'є.
    return false;
}

int main() {

    cout << "\n=== PREFERENCE CARD GAME LOGIC ===" << endl;

    Card card1, card2;
    int trumpInput;
    Card::Suit trumpSuit;

    // Вводимо дві карти
    card1.input("Card 1 (Attacking card)");
    card2.input("Card 2 (Defending card)");

    // Вводимо козир
    cout << "Enter Trump Suit (0-Spades, 1-Clubs, 2-Diamonds, 3-Hearts): ";
    cin >> trumpInput;
    if (trumpInput < 0 || trumpInput > 3) trumpInput = 0;
    trumpSuit = static_cast<Card::Suit>(trumpInput);

    cout << "\n----------------RESULT----------------" << endl;
    cout << "Trump is: ";
    const string suitNames[] = { "Spades", "Clubs", "Diamonds", "Hearts" };
    cout << suitNames[trumpSuit] << endl;

    cout << "Check if "; card1.print();
    cout << "beats    "; card2.print();


    if (beat(card1, card2, trumpSuit)) {
        cout << ">>> YES, it beats! <<<" << endl;
    } else {
        cout << ">>> NO, it does not beat. <<<" << endl;
    }

    return 0;
}