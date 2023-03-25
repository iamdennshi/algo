#include <iostream>
using namespace std;

void golden_section_search(double (*f)(double), double a, double b, double eps) {
    int iter = 1;
    double t = (sqrt(5) + 1) / 2;
    pair<double, double> x = make_pair(
        b - (b - a) / t,
        a + (b - a) / t
    );

    while (fabs(b - a) > eps) {
        if (f(x.first) < f(x.second)) {
            b = x.second;
        } 
        else {
            a = x.first;

        }

        x.first = b - (b - a) / t;
        x.second = a + (b - a) / t;
        iter++;
    }
    double result = (a + b) / 2;
    cout << "f(" << result << ") = " << f(result) << endl;
    cout << "Iteration: " << iter << endl;
}