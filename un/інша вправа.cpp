//
// Created by User on 05.09.2025.
//
#include <stdio.h>
#include <math.h>

double perimetre(double a , double b, double c ) {
    return a+b+c;
}
int main(){
    double a,b,c,p,s;
    a=1;
    b=2;
    c=3;
    p=perimetre(a,b,c)/2;
    s=sqrt(p*(p-a)*(p+b)*(p-c));
    printf("S=%lf\n",s);
}