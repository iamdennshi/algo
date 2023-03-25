#include <iostream>
using namespace std;

double goldenSectionSearch(double (*f)(double, double), double x0, double y0, double dx, double dy, double eps) {
    double a = 0, b = 1; 
    double t = (sqrt(5) - 1) / 2;
    double x1 = b;
    double x2 = a;

    while (fabs(b - a) > eps) {
        if (f(x0 - x1 * dx, y0 - x1 * dy) < f(x0 - x2 * dx, y0 - x2 * dy)) {
            b = x2;
        }
        else {
            a = x1;
        }
        x1 = b - (b - a) / t;
        x2 = a + (b - a) / t;
    }
    return (a + b) / 2;
}

void gradient_min_step(double (*f)(double, double), double (*dfx0)(double, double), double (*dfx1)(double, double),
    pair<double, double> x0, double eps) {

    int iter = 1;
    double a = 0.5;	// шаг сходимости
    auto prev_xk = x0;
    auto xk = make_pair(
        (prev_xk.first - dfx0(prev_xk.first, prev_xk.second) * a),
        (prev_xk.second - dfx1(prev_xk.first, prev_xk.second) * a)
    );
    pair<double, double> dx = make_pair(dfx0(x0.first, x0.second), dfx1(x0.first, x0.second));

    while (fabs(f(xk.first, xk.second) - f(prev_xk.first, prev_xk.second)) > eps) {
        prev_xk = xk;
        xk = make_pair(
            (prev_xk.first - dfx0(prev_xk.first, prev_xk.second) * a),
            (prev_xk.second - dfx1(prev_xk.first, prev_xk.second) * a)
        );

        a = goldenSectionSearch(f, x0.first, x0.second, dx.first, dx.second, eps);  // ищем оптимальный шаг
        ++iter;
    }

    cout << "f(" << xk.first << ", " << xk.second << ") = " << f(xk.first, xk.second) << '\n';
    cout << "Iteration: " << iter << endl;
}