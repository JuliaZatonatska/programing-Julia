#include <stdio.h>

enum Day { Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };
enum Month { January=1, February, March, April, May, June, July, August, September, October, November, December };
enum Color { Red, Orange, Yellow, Green, Blue, Indigo, Violet };
enum ChessPiece { King, Queen, Rook, Bishop, Knight, Pawn };

const char* dayNames[] = {"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};
const char* monthNames[] = {"", "January","February","March","April","May","June","July","August","September","October","November","December"};
const char* colorNames[] = {"Red","Orange","Yellow","Green","Blue","Indigo","Violet"};
const char* pieceNames[] = {"King","Queen","Rook","Bishop","Knight","Pawn"};

void printDay(enum Day d) { printf("%s\n", dayNames[d]); }
void printMonth(enum Month m) { printf("%s\n", monthNames[m]); }
void printColor(enum Color c) { printf("%s\n", colorNames[c]); }
void printChessPiece(enum ChessPiece p) { printf("%s\n", pieceNames[p]); }

enum Day inputDay() {
    int n;
    printf("Enter day number (0-Monday, 1-Tuesday, ..., 6-Sunday): ");
    scanf("%d", &n);
    return (enum Day)n;
}

enum Month inputMonth() {
    int n;
    printf("Enter month number (1-January, 2-February, ..., 12-December): ");
    scanf("%d", &n);
    return (enum Month)n;
}

enum Color inputColor() {
    int n;
    printf("Enter color number (0-Red, 1-Orange, ..., 6-Violet): ");
    scanf("%d", &n);
    return (enum Color)n;
}

enum ChessPiece inputPiece() {
    int n;
    printf("Enter chess piece number (0-King, 1-Queen, 2-Rook, 3-Bishop, 4-Knight, 5-Pawn): ");
    scanf("%d", &n);
    return (enum ChessPiece)n;
}

int main() {
    printf("=== Choose Day ===\n");
    enum Day d = inputDay();
    printf("You chose: "); printDay(d);

    printf("\n=== Choose Month ===\n");
    enum Month m = inputMonth();
    printf("You chose: "); printMonth(m);

    printf("\n=== Choose Color ===\n");
    enum Color c = inputColor();
    printf("You chose: "); printColor(c);

    printf("\n=== Choose Chess Piece ===\n");
    enum ChessPiece p = inputPiece();
    printf("You chose: "); printChessPiece(p);

    return 0;
}