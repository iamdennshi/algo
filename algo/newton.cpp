#include <iostream>

void newton(double (*fun)(double), double (*fun1)(double), double (*fun2)(double), double a, double b, double eps) {
	using namespace std;

	int iteration = 1;
	double x0 = a;
	double xn = x0 - fun1(x0) / fun2(x0);

	while (fabs(xn - x0) >= eps) {
		x0 = xn;
		xn = x0 - fun1(x0) / fun2(x0);
		iteration++;
	}

	cout << "f(" << xn << ") = " << fun(xn) << endl;
	cout << "Iteration: " << iteration << endl;
}