#include <iostream>

double fun(double x) {
    return (-1 * x * x * x + 3 * (1 + x) * (std::log1p(x) - 1));
}

void dichotomy(double a, double b, double del, double eps)
{
    using namespace std;
    double xk1, xk2;
    int count = 0;

    while (1) {
        xk1 = (a + b) / 2 - del;
        xk2 = (a + b) / 2 + del;
        count++;
        
        if (fun(xk1) < fun(xk2)) {
            b = xk2;
        }
        else {
            a = xk1;
        }

        if (fabs(b - a) <= eps) {
            double x = (a + b) / 2;
            cout << "f(" << x << ") = " << fun(x) << endl;
            cout << "Iteration: " << count << endl;
            break;
        }
    }
}
