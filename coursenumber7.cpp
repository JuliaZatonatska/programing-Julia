#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cctype>
#include <chrono>
#include <iomanip>

using namespace std;

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

class ShipNavigator {
public:
    enum Course { N, E, S, W };
    enum Order { Forward, Back, Left, Right };
private:
    Course currentCourse;
    double speed, x, y;
    const string courseNames[4] = { "North", "East", "South", "West" };
public:
    ShipNavigator() : x(0), y(0), currentCourse(N), speed(0) {}

    void startNavigation() {
        int c, moves;
        cout << "Start Course (0-N, 1-E, 2-S, 3-W): "; cin >> c;
        if(c<0||c>3) c=0; currentCourse = static_cast<Course>(c);

        cout << "Speed: "; cin >> speed;
        cout << "Number of moves: "; cin >> moves;

        vector<Order> orders(moves);
        vector<double> times(moves);

        for(int i=0; i<moves; i++) {
            int ord;
            cout << "Move " << i+1 << " (0-Fwd, 1-Back, 2-Left, 3-Right): "; cin >> ord;
            if(ord<0||ord>3) ord=0; orders[i] = static_cast<Order>(ord);
            cout << "Time: "; cin >> times[i];
        }
        processMovement(orders, times);
    }

    void processMovement(const vector<Order>& orders, const vector<double>& times) {
        for(size_t i=0; i<orders.size(); i++) {
            int current = static_cast<int>(currentCourse);
            switch (orders[i]) {
                case Right: current = (current + 1) % 4; break;
                case Back:  current = (current + 2) % 4; break;
                case Left:  current = (current + 3) % 4; break;
                case Forward: break;
            }
            currentCourse = static_cast<Course>(current);
            double dist = speed * times[i];
            switch(currentCourse) {
                case N: y+=dist; break; case S: y-=dist; break;
                case E: x+=dist; break; case W: x-=dist; break;
            }
        }
        cout << "Final: " << courseNames[currentCourse] << ", X=" << x << " Y=" << y
             << ", Dist=" << fixed << setprecision(2) << sqrt(x*x + y*y) << endl;
    }
};

string getMonthNameSwitch(int m) {
    switch(m) {
        case 1: return "January"; case 2: return "February"; case 3: return "March";
        case 4: return "April";   case 5: return "May";      case 6: return "June";
        case 7: return "July";    case 8: return "August";   case 9: return "September";
        case 10: return "October"; case 11: return "November"; case 12: return "December";
        default: return "";
    }
}

string getMonthNameArray(int m) {
    static const string names[] = {"", "January","February","March","April","May","June","July","August","September","October","November","December"};
    if (m < 1 || m > 12) return "";
    return names[m];
}

void runBenchmark() {
    long long iterations = 10000000;
    int dummyMonth = 9;

    cout << "\n=== PERFORMANCE TEST (Iterations: " << iterations << ") ===" << endl;

    auto startA = chrono::high_resolution_clock::now();
    for (long long i = 0; i < iterations; ++i) {
        string s = getMonthNameSwitch(dummyMonth);
        if (s.empty()) dummyMonth = 1;
    }
    auto endA = chrono::high_resolution_clock::now();
    chrono::duration<double> durationA = endA - startA;

    auto startB = chrono::high_resolution_clock::now();
    for (long long i = 0; i < iterations; ++i) {
        string s = getMonthNameArray(dummyMonth);
        if (s.empty()) dummyMonth = 1;
    }
    auto endB = chrono::high_resolution_clock::now();
    chrono::duration<double> durationB = endB - startB;

    cout << "Implementation A (Switch): " << durationA.count() << " seconds." << endl;
    cout << "Implementation B (Array):  " << durationB.count() << " seconds." << endl;

    if (durationB.count() < durationA.count())
        cout << ">> Array Lookup (B) is faster!" << endl;
    else
        cout << ">> Switch (A) is faster (or compiler optimized both efficiently)." << endl;
}

int main() {
    while (true) {
        cout << "\n================ MENU ================" << endl;
        cout << "1. Basic Enums (Day, Month, Color, Chess)" << endl;
        cout << "2. Card Game (Preference)" << endl;
        cout << "3. Length Converter" << endl;
        cout << "4. Syllable Counter" << endl;
        cout << "5. Ship Navigation" << endl;
        cout << "6. Compare Speed (Switch vs Array)" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose option: ";

        int choice; cin >> choice;

        if (choice == 0) break;

        switch (choice) {
            case 1: {
                Day d; d.input(); d.print();
                Month m; m.input(); m.print();
                Color c; c.input(); c.print();
                ChessPiece p; p.input(); p.print();
                break;
            }
            case 2: {
                Card c1, c2; int tr;
                c1.input("Attacker"); c2.input("Defender");
                cout << "Trump (0-3): "; cin >> tr;
                if (beat(c1, c2, static_cast<Card::Suit>(tr))) cout << ">> BEATS!" << endl;
                else cout << ">> DOES NOT BEAT." << endl;
                break;
            }
            case 3: {
                LengthConverter lc; lc.input(); lc.print();
                break;
            }
            case 4: {
                SyllableCounter sc; sc.inputAndCount();
                break;
            }
            case 5: {
                ShipNavigator sn; sn.startNavigation();
                break;
            }
            case 6: {
                runBenchmark();
                break;
            }
            default: cout << "Invalid option." << endl;
        }
    }
    return 0;
}