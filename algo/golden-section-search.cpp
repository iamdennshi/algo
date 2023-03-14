#include <iostream>

void goldenSectionSearch(double (*fun)(double), double a, double b, double eps) {
    using namespace std;
    
    int iteration = 1;
    double t = (sqrt(5) + 1) / 2;
    double xk1 = b - (b - a) / t;
    double xk2 = a + (b - a) / t;


    while (fabs(b - a) > eps) {
        if (fun(xk1) < fun(xk2)) {
            b = xk2;
        } 
        else {
            a = xk1;

        }

        xk1 = b - (b - a) / t;
        xk2 = a + (b - a) / t;
        iteration++;
    }
    double x = (a + b) / 2;
    cout << "f(" << x << ") = " << fun(x) << endl;
    cout << "Iteration: " << iteration << endl << endl;
}