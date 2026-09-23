#include <iostream>
#include <string>
#include <cctype> // Для функції tolower
using namespace std;

// =======================
// 1. Попередні класи (Дні, Місяці, Кольори, Шахи)
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
        cout << "Enter day number (0-Monday...): "; cin >> n;
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
        cout << "Enter month number (1-January...): "; cin >> n;
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
        cout << "Enter color number (0-Red...): "; cin >> n;
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
        cout << "Enter chess piece number (0-King...): "; cin >> n;
        if (n < 0 || n > 5) n = 5;
        piece = static_cast<PieceEnum>(n);
    }
    void print() { cout << pieceNames[piece] << endl; }
};

// =======================
// 2. Структура Card (Карти)
// =======================

struct Card {
    enum Suit { Spades, Clubs, Diamonds, Hearts };
    enum Rank { Seven=7, Eight=8, Nine=9, Ten=10, Jack=11, Queen=12, King=13, Ace=14 };
    Suit suit; Rank rank;

    string getSuitName() const { const string n[] = { "Spades", "Clubs", "Diamonds", "Hearts" }; return n[suit]; }
    string getRankName() const {
        if (rank <= 10) return to_string(rank);
        if (rank == 11) return "Jack"; if (rank == 12) return "Queen";
        if (rank == 13) return "King"; return "Ace";
    }
    void input(string label) {
        int s, r;
        cout << "-- " << label << " --\nSuit (0-3): "; cin >> s;
        if(s<0||s>3) s=0; suit = static_cast<Suit>(s);
        cout << "Rank (7-14): "; cin >> r;
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
// 3. Клас LengthConverter (Довжина)
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
        if (n < 0 || n > 4) n = 3;
        unit = static_cast<Unit>(n);
    }
    double convertToMeters() {
        switch (unit) {
            case MM: return value * 0.001;
            case CM: return value * 0.01;
            case DM: return value * 0.1;
            case M:  return value * 1.0;
            case KM: return value * 1000.0;
            default: return 0.0;
        }
    }
    void print() { cout << value << " " << unitNames[unit] << " = " << convertToMeters() << " m" << endl; }
};

// =======================
// 4. НОВИЙ КЛАС: SyllableCounter (Лічильник складів)
// =======================

class SyllableCounter {
public:
    // Перелік голосних. None використовується, якщо літера приголосна.
    enum Vowel { A, E, I, O, U, Y, None };

private:
    string sentence;

    // Функція перевіряє символ і повертає тип голосної або None
    Vowel checkVowel(char c) {
        // Переводимо в нижній регістр для спрощення
        c = tolower(c);
        switch(c) {
            case 'a': return A;
            case 'e': return E;
            case 'i': return I;
            case 'o': return O;
            case 'u': return U;
            case 'y': return Y; // 'y' в англійській часто рахується як голосна (rhythm, fly)
            default: return None;
        }
    }

public:
    void inputAndCount() {
        cout << "\n=== Syllable Counter (Vowels) ===" << endl;
        cout << "Enter a sentence (English): ";

        // ВАЖЛИВО: очищуємо буфер після попередніх cin >>, інакше getline не спрацює
        cin.ignore();
        getline(cin, sentence);

        int count = 0;
        for (char c : sentence) {
            // Якщо символ відповідає будь-якій голосній з ENUM
            if (checkVowel(c) != None) {
                count++;
            }
        }

        cout << "Sentence: \"" << sentence << "\"" << endl;
        cout << "Total vowels (syllables): " << count << endl;
    }
};

// =======================
// Main
// =======================

int main() {
    // 1. Попередні завдання (коротко)
    cout << "=== Test Previous Classes ===" << endl;
    Day d; d.input(); d.print();

    // 2. Карти
    Card c1; c1.input("Card");
    // Для прикладу тут не викликаємо beat, щоб скоротити вивід

    // 3. Конвертер довжини
    LengthConverter lc; lc.input(); lc.print();

    // 4. НОВЕ ЗАВДАННЯ: Лічильник складів
    SyllableCounter sc;
    sc.inputAndCount();

    return 0;
}