#include <iostream>
using namespace std;

void goldenSectionSearch(double (*fun)(double), double a, double b, double eps) {
    int count = 0;
    double gr = (sqrt(5) + 1) / 2;
    double xk1 = b - (b - a) / gr;
    double xk2 = a + (b - a) / gr;

    while (fabs(b - a) > eps) {
        if ((*fun)(xk1) < (*fun)(xk2)) {
            b = xk2;
        } 
        else {
            a = xk1;
        }

        xk1 = b - (b - a) / gr;
        xk2 = a + (b - a) / gr;
        count++;
    }

    double x = (a + b) / 2;
     cout << "f(" << x << ") = " << (*fun)(x) << endl;
     cout << "Iteration: " << count << endl << endl;
}