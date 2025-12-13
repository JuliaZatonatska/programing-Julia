#include <stdio.h>
#include <math.h>


void task1() {
    double x;
    printf("Enter x: ");
    scanf("%lf", &x);
    printf("cos(x) = %lf\n", cos(x));
}

void task2() {
    double a, b;
    printf("Enter a and b: ");
    scanf("%lf %lf", &a, &b);
    double c = sqrt(a*a + b*b);
    printf("Hypotenuse c = %lf\n", c);
}


void task3() {
    double a, b, c;
    printf("Enter sides a, b, c: ");
    scanf("%lf %lf %lf", &a, &b, &c);
    double p = (a + b + c) / 2;
    double S = sqrt(p*(p-a)*(p-b)*(p-c));
    printf("Area S = %lf\n", S);
}


void task4() {
    double x;
    printf("Enter x: ");
    scanf("%lf", &x);

    double x2 = x*x;
    double y_a = x2*x2 + 2*x2 + 1;
    printf("a) y = %lf\n", y_a);

    double x3 = x2*x;
    double x4 = x2*x2;
    double y_b = x4 + x3 + x2 + x + 1;
    printf("b) y = %lf\n", y_b);

    double x5 = x4*x;
    double y_c = x5 + 5*x4 + 10*x3 + 10*x2 + 5*x + 1;
    printf("c) y = %lf\n", y_c);

    double x6 = x3*x3;
    double x9 = x6*x3;
    double y_d = x9 + x3 + 1;
    printf("d) y = %lf\n", y_d);

    double y_e = 16*x4 + 8*x3 + 4*x2 + 2*x + 1;
    printf("e) y = %lf\n", y_e);

    double y_f = x5 + x3 + x;
    printf("f) y = %lf\n", y_f);
}

double Rosenbrock2d(double x, double y) {
    return 100*(x*x - y)*(x*x - y) + (x-1)*(x-1);
}

void task5() {
    double x, y;
    printf("Enter x and y: ");
    scanf("%lf %lf", &x, &y);
    printf("Rosenbrock2d(x,y) = %lf\n", Rosenbrock2d(x, y));
}

double distance(double x1, double y1, double x2, double y2) {
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

void task6() {
    double xa, ya, xb, yb, xc, yc;
    printf("Enter A(x y): "); scanf("%lf %lf", &xa, &ya);
    printf("Enter B(x y): "); scanf("%lf %lf", &xb, &yb);
    printf("Enter C(x y): "); scanf("%lf %lf", &xc, &yc);

    double a = distance(xb, yb, xc, yc);
    double b = distance(xa, ya, xc, yc);
    double c = distance(xa, ya, xb, yb);
    double p = (a+b+c)/2;
    double S = sqrt(p*(p-a)*(p-b)*(p-c));
    printf("Area S = %lf\n", S);
}

void task7() {
    double a, b;
    printf("Enter ellipse radii a and b: ");
    scanf("%lf %lf", &a, &b);
    double S = M_PI * a * b;
    printf("Ellipse area S = %lf\n", S);
}

void task8() {
    double a, b, c;
    printf("Enter sides a, b, c: ");
    scanf("%lf %lf %lf", &a, &b, &c);

    double ma = 0.5*sqrt(2*b*b + 2*c*c - a*a);
    double mb = 0.5*sqrt(2*a*a + 2*c*c - b*b);
    double mc = 0.5*sqrt(2*a*a + 2*b*b - c*c);
    printf("Medians: ma=%lf mb=%lf mc=%lf\n", ma, mb, mc);

    double p = (a+b+c)/2;
    double la = sqrt(b*c*(p)*(p-a))/ (b+c);
    double lb = sqrt(a*c*(p)*(p-b))/ (a+c);
    double lc = sqrt(a*b*(p)*(p-c))/ (a+b);
    printf("Bisectors: la=%lf lb=%lf lc=%lf\n", la, lb, lc);

    double S = sqrt(p*(p-a)*(p-b)*(p-c));
    double ha = 2*S/a;
    double hb = 2*S/b;
    double hc = 2*S/c;
    printf("Heights: ha=%lf hb=%lf hc=%lf\n", ha, hb, hc);
}

void task9() {
    double alpha, beta, gamma, r;
    printf("Enter angles (deg) alpha, beta, gamma and radius r: ");
    scanf("%lf %lf %lf %lf", &alpha, &beta, &gamma, &r);
    double pi = 3.141592653589793;
    alpha *= pi/180;
    beta *= pi/180;
    gamma *= pi/180;
    double S = r*r*(tan(alpha/2) + tan(beta/2) + tan(gamma/2));
    printf("Area S = %lf\n", S);
}

void task10() {
    double a, b, c;
    printf("Enter sides a, b, c: ");
    scanf("%lf %lf %lf", &a, &b, &c);
    double A = acos((b*b + c*c - a*a)/(2*b*c));
    double B = acos((a*a + c*c - b*b)/(2*a*c));
    double C = acos((a*a + b*b - c*c)/(2*a*b));
    printf("Angles (rad): A=%lf B=%lf C=%lf\n", A, B, C);
    printf("Angles (deg): A=%lf B=%lf C=%lf\n", A*180/M_PI, B*180/M_PI, C*180/M_PI);
}


void task11() {
    double r, h;
    printf("Enter radius and height: ");
    scanf("%lf %lf", &r, &h);
    double V = M_PI*r*r*h;
    printf("Cylinder volume V = %lf\n", V);
}


void task12() {
    double r, h;
    printf("Enter radius and height: ");
    scanf("%lf %lf", &r, &h);
    double V = M_PI*r*r*h/3;
    printf("Cone volume V = %lf\n", V);
}


void task13() {
    double R, r;
    printf("Enter outer radius R and inner radius r: ");
    scanf("%lf %lf", &R, &r);
    double V = 2*M_PI*M_PI*R*r*r;
    printf("Torus volume V = %lf\n", V);
}

void task14() {
    double a, b, c;
    printf("Enter coefficients a, b, c: ");
    scanf("%lf %lf %lf", &a, &b, &c);
    double D = b*b - 4*a*c;
    if(D >= 0){
        double x1 = (-b + sqrt(D))/(2*a);
        double x2 = (-b - sqrt(D))/(2*a);
        printf("Roots: x1=%lf x2=%lf\n", x1, x2);
    } else {
        printf("No real roots\n");
    }
}

void task15() {
    double x, y;
    printf("Enter x and y: ");
    scanf("%lf %lf", &x, &y);


    double x2 = x*x;
    double y2 = y*y;
    double x3 = x2*x;
    double y3 = y2*y;
    double f_a = x3 + 3*x2*y + 3*x*y2 + y3;
    printf("a) f(x,y) = %lf\n", f_a);


    double x4 = x2*x2;
    double y4 = y2*y2;
    double x3y3 = x3*y3;
    double f_b = x2*y2 + x3y3 + x4*y4;
    printf("b) f(x,y) = %lf\n", f_b);


    double f_c = x + y + x2 + y2 + x3 + y3 + x4 + y4;
    printf("c) f(x,y) = %lf\n", f_c);
}


void task16() {
    double x0, y0, x, y, a, b, c;
    printf("Enter point x0 y0: ");
    scanf("%lf %lf", &x0, &y0);

    printf("Enter target point x y: ");
    scanf("%lf %lf", &x, &y);
    double d = distance(x0, y0, x, y);
    printf("Distance to point = %lf\n", d);

    printf("Enter line a b c (ax+by+c=0): ");
    scanf("%lf %lf %lf", &a, &b, &c);
    double d_line = fabs(a*x0 + b*y0 + c)/sqrt(a*a + b*b);
    printf("Distance to line = %lf\n", d_line);
}


double th(double x) { return (exp(x)-exp(-x))/(exp(x)+exp(-x)); }
double th_derivative(double x) { double t = th(x); return 1 - t*t; }

void task17() {
    double x;
    printf("Enter x: ");
    scanf("%lf", &x);
    printf("th(x) = %lf, th'(x) = %lf\n", th(x), th_derivative(x));
}


int main() {
    int choice;
    while(1) {
        printf("\nChoose task (1-17, 0 to exit): ");
        scanf("%d", &choice);
        if(choice == 0) break;
        switch(choice) {
            case 1: task1(); break;
            case 2: task2(); break;
            case 3: task3(); break;
            case 4: task4(); break;
            case 5: task5(); break;
            case 6: task6(); break;
            case 7: task7(); break;
            case 8: task8(); break;
            case 9: task9(); break;
            case 10: task10(); break;
            case 11: task11(); break;
            case 12: task12(); break;
            case 13: task13(); break;
            case 14: task14(); break;
            case 15: task15(); break;
            case 16: task16(); break;
            case 17: task17(); break;
            default: printf("No such task\n");
        }
    }
    return 0;
}
