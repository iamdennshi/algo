#include <iostream>
using namespace std;

void dichotomy(double (*f)(double), double a, double b, double del, double eps) {
    int iter = 1;
    pair<double, double> x = make_pair(
        (a + b) / 2 - del,
        (a + b) / 2 + del
    );

    while (fabs(b - a) > eps) {
        if (f(x.first) < f(x.second)) {
            b = x.second;
        }
        else {
            a = x.first;
        }

        x.first = (a + b) / 2 - del;
        x.second = (a + b) / 2 + del;
        iter++;
    }
    double result = (a + b) / 2;
    cout << "f(" << result << ") = " << f(result) << endl;
    cout << "Iteration: " << iter << endl;
}
