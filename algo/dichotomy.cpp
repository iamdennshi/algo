#include <iostream>
using namespace std;

void dichotomy(double (*fun)(double), double a, double b, double del, double eps) {
    int count = 0;
    double xk1 = (a + b) / 2 - del;
    double xk2 = (a + b) / 2 + del;

    while (fabs(b - a) > eps) {
        if (fun(xk1) < fun(xk2)) {
            b = xk2;
        }
        else {
            a = xk1;
        }

        xk1 = (a + b) / 2 - del;
        xk2 = (a + b) / 2 + del;
        count++;
    }
    double x = (a + b) / 2;
    cout << "f(" << x << ") = " << fun(x) << endl;
    cout << "Iteration: " << count << endl << endl;
}
