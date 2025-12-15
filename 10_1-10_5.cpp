#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int gcd(int a, int b) {
    while (b) {
        a %= b;
        int temp = a;
        a = b;
        b = temp;
    }
    return a < 0 ? -a : a;
}

typedef struct {
    int day;
    int month;
    int year;
} Date;

Date inputDate() {
    Date d;
    printf("Enter the date (day month year): ");
    scanf("%d %d %d", &d.day, &d.month, &d.year);
    return d;
}

void printDate(Date d) {
    printf("%02d.%02d.%04d", d.day, d.month, d.year);
}

typedef struct {
    char column;
    int row;
} ChessSquare;

ChessSquare inputChessSquare() {
    ChessSquare cs;
    printf("Enter a chess square (e.g., a5): ");
    scanf(" %c%d", &cs.column, &cs.row);
    if (cs.column >= 'A' && cs.column <= 'H') cs.column += ('a' - 'A');
    if (cs.column < 'a' || cs.column > 'h' || cs.row < 1 || cs.row > 8) {
        printf("[!] Invalid square. Set to a1.\n");
        cs.column = 'a';
        cs.row = 1;
    }
    return cs;
}

void printChessSquare(ChessSquare cs) {
    printf("%c%d", cs.column, cs.row);
}

typedef struct {
    double x;
    double y;
} Point;

Point inputPoint() {
    Point p;
    printf("Enter point coordinates (x y): ");
    scanf("%lf %lf", &p.x, &p.y);
    return p;
}

void printPoint(Point p) {
    printf("(%.2f, %.2f)", p.x, p.y);
}

typedef struct {
    Point p1;
    Point p2;
} Rectangle;

Rectangle inputRectangle() {
    Rectangle r;
    printf("\nInput for the first vertex of the rectangle:\n");
    r.p1 = inputPoint();
    printf("Input for the second vertex of the rectangle:\n");
    r.p2 = inputPoint();
    return r;
}

void printRectangle(Rectangle r) {
    printf("Rectangle defined by vertices: ");
    printPoint(r.p1);
    printf(" and ");
    printPoint(r.p2);
}

typedef struct {
    int degree;
    double *coefficients;
} Polynomial;

Polynomial inputPolynomial() {
    Polynomial p;
    printf("Enter the degree of the polynomial: ");
    scanf("%d", &p.degree);
    p.coefficients = (double *)calloc(p.degree + 1, sizeof(double));
    if (p.coefficients == NULL) {
        perror("Memory allocation error");
        p.degree = -1;
        return p;
    }
    printf("Enter %d coefficients (from x^0 to x^%d):\n", p.degree + 1, p.degree);
    for (int i = 0; i <= p.degree; i++) scanf("%lf", &p.coefficients[i]);
    return p;
}

void printPolynomial(Polynomial p) {
    if (p.degree < 0) return;
    bool is_first = true;
    for (int i = p.degree; i >= 0; i--) {
        double coeff = p.coefficients[i];
        if (coeff != 0.0) {
            if (!is_first) printf(coeff > 0 ? " + " : " - ");
            else if (coeff < 0) printf("-");
            double abs_coeff = coeff < 0 ? -coeff : coeff;
            if (i == 0 || abs_coeff != 1.0) printf("%.2f", abs_coeff);
            if (i > 0) {
                printf("x");
                if (i > 1) printf("^%d", i);
            }
            is_first = false;
        }
    }
    if (is_first) printf("0");
}

void freePolynomial(Polynomial p) {
    if (p.coefficients != NULL) {
        free(p.coefficients);
        p.coefficients = NULL;
    }
}

bool canQueenMove(ChessSquare from, ChessSquare to) {
    int col_diff = (from.column - 'a') - (to.column - 'a');
    int row_diff = from.row - to.row;
    if (col_diff == 0 && row_diff == 0) return false;
    bool is_horizontal = row_diff == 0;
    bool is_vertical = col_diff == 0;
    bool is_diagonal = (col_diff < 0 ? -col_diff : col_diff) == (row_diff < 0 ? -row_diff : row_diff);
    return is_horizontal || is_vertical || is_diagonal;
}

const int DAYS_IN_MONTH[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

bool isLeap(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

Date getNextDay(Date d) {
    int days_in_current_month = DAYS_IN_MONTH[d.month];
    if (d.month == 2 && isLeap(d.year)) days_in_current_month = 29;
    d.day++;
    if (d.day > days_in_current_month) {
        d.day = 1;
        d.month++;
        if (d.month > 12) {
            d.month = 1;
            d.year++;
        }
    }
    return d;
}

int getDayOfWeek(Date d) {
    int day_count = d.day;
    for (int m = 1; m < d.month; m++) {
        day_count += DAYS_IN_MONTH[m];
        if (m == 2 && isLeap(d.year)) day_count += 1;
    }
    int day_of_week_1_jan = 1;
    return (day_count - 1 + day_of_week_1_jan) % 7;
}

void printDayOfWeek(int dow) {
    char *days[] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
    printf("%s", days[dow]);
}

typedef struct {
    int numerator;
    unsigned int denominator;
} Rational;

Rational reduceRational(Rational r) {
    if (r.denominator == 0) {
        printf("[!] Error: Denominator cannot be zero.\n");
        return r;
    }
    if (r.numerator == 0) {
        r.denominator = 1;
        return r;
    }
    int common_divisor = gcd(r.numerator, (int)r.denominator);
    r.numerator /= common_divisor;
    r.denominator /= common_divisor;
    return r;
}

Rational addRational(Rational r1, Rational r2) {
    Rational result;
    result.numerator = r1.numerator * r2.denominator + r2.numerator * r1.denominator;
    result.denominator = r1.denominator * r2.denominator;
    return reduceRational(result);
}

Rational multiplyRational(Rational r1, Rational r2) {
    Rational result;
    result.numerator = r1.numerator * r2.numerator;
    result.denominator = r1.denominator * r2.denominator;
    return reduceRational(result);
}

int compareRational(Rational r1, Rational r2) {
    long long val1 = (long long)r1.numerator * r2.denominator;
    long long val2 = (long long)r2.numerator * r1.denominator;
    if (val1 < val2) return -1;
    else if (val1 > val2) return 1;
    else return 0;
}

void printRational(Rational r) {
    printf("%d/%u", r.numerator, r.denominator);
}

typedef struct {
    char name[100];
    int height;
} Mountain;

Mountain inputMountain() {
    Mountain m;
    printf("Enter the name of the mountain (up to 99 characters): ");
    scanf("%99s", m.name);
    printf("Enter the height of the mountain (in meters): ");
    scanf("%d", &m.height);
    return m;
}

void printMountain(Mountain m) {
    printf("Name: %s, Height: %d m\n", m.name, m.height);
}

void inputMountainArray(Mountain array[], int size) {
    for (int i = 0; i < size; i++) array[i] = inputMountain();
}

void printMountainArray(Mountain array[], int size) {
    for (int i = 0; i < size; i++) printMountain(array[i]);
}

char* findHighestMountainName(Mountain array[], int size) {
    if (size <= 0) return NULL;
    int max_height = array[0].height;
    char* highest_name = array[0].name;
    for (int i = 1; i < size; i++) {
        if (array[i].height > max_height) {
            max_height = array[i].height;
            highest_name = array[i].name;
        }
    }
    return highest_name;
}

void printMountainHeightByName(Mountain array[], int size, const char *name) {
    for (int i = 0; i < size; i++) {
        if (strcmp(array[i].name, name) == 0) {
            printf("The height of the mountain '%s' is %d m.\n", name, array[i].height);
            return;
        }
    }
    printf("Mountain with the name '%s' not found in the array.\n", name);
}

int main() {
    printf("TASKS DEMONSTRATION\n\n");

    Date today = inputDate();
    printf("Entered date: ");
    printDate(today);
    printf("\n\n");

    ChessSquare start_sq = inputChessSquare();
    printf("Entered square: ");
    printChessSquare(start_sq);
    printf("\n\n");

    Rectangle rect = inputRectangle();
    printRectangle(rect);
    printf("\n\n");

    Polynomial poly = inputPolynomial();
    if (poly.degree >= 0) {
        printPolynomial(poly);
        printf("\n");
        freePolynomial(poly);
    }

    ChessSquare sq1 = {'a',1}, sq2={'b',2}, sq3={'a',8}, sq4={'h',1}, sq5={'b',3};
    printf("Can the queen move from "); printChessSquare(sq1); printf(" to "); printChessSquare(sq2);
    printf("? -> %s\n", canQueenMove(sq1, sq2) ? "Yes":"No");
    printf("Can the queen move from "); printChessSquare(sq1); printf(" to "); printChessSquare(sq3);
    printf("? -> %s\n", canQueenMove(sq1, sq3) ? "Yes":"No");
    printf("Can the queen move from "); printChessSquare(sq1); printf(" to "); printChessSquare(sq4);
    printf("? -> %s\n", canQueenMove(sq1, sq4) ? "Yes":"No");
    printf("Can the queen move from "); printChessSquare(sq1); printf(" to "); printChessSquare(sq5);
    printf("? -> %s\n", canQueenMove(sq1, sq5) ? "Yes":"No");

    Date date_ex = {31,12,2024};
    printf("Current date: "); printDate(date_ex); printf("\n");
    Date next_day = getNextDay(date_ex);
    printf("Tomorrow's date: "); printDate(next_day); printf("\n");
    Date date_for_dow = {15,12,2025};
    int dow = getDayOfWeek(date_for_dow);
    printf("Day of the week for "); printDate(date_for_dow); printf(": ");
    printDayOfWeek(dow); printf(" (%d)\n", dow);

    Rational rA={-3,9}, rB={4,6};
    Rational rA_reduced = reduceRational(rA);
    printf("Fraction "); printRational(rA); printf(" in simplest form: "); printRational(rA_reduced); printf("\n");
    Rational rB_reduced = reduceRational(rB);
    printf("Fraction "); printRational(rB); printf(" in simplest form: "); printRational(rB_reduced); printf("\n");
    Rational rSum = addRational(rA_reduced,rB_reduced);
    printf("Sum: ("); printRational(rA_reduced); printf(")+("); printRational(rB_reduced); printf(")="); printRational(rSum); printf("\n");
    Rational rProd = multiplyRational(rA_reduced,rB_reduced);
    printf("Product: ("); printRational(rA_reduced); printf(")*("); printRational(rB_reduced); printf(")="); printRational(rProd); printf("\n");
    int comp_res = compareRational(rA_reduced,rB_reduced);
    printf("Comparison: %d\n", comp_res);

    const int N=3;
    Mountain mountain_data[N];
    strcpy(mountain_data[0].name,"Everest"); mountain_data[0].height=8848;
    strcpy(mountain_data[1].name,"Mont_Blanc"); mountain_data[1].height=4809;
    strcpy(mountain_data[2].name,"Hoverla"); mountain_data[2].height=2061;
    printMountainArray(mountain_data,N);
    char* highest_name = findHighestMountainName(mountain_data,N);
    if(highest_name!=NULL) printf("\nName of the highest peak: %s\n", highest_name);
    printMountainHeightByName(mountain_data,N,"Mont_Blanc");
    printMountainHeightByName(mountain_data,N,"Kilimanjaro");

    return 0;
}
