#include <iostream>
using namespace std;

void newton(double (*f)(double), double (*dfx)(double), double (*df_x)(double), double a, double b, double eps) {

	int iter = 1;
	double x0 = a;
	double xn = x0 - dfx(x0) / df_x(x0);

	while (fabs(xn - x0) >= eps) {
		x0 = xn;
		xn = x0 - dfx(x0) / df_x(x0);
		iter++;
	}

	cout << "f(" << xn << ") = " << f(xn) << endl;
	cout << "Iteration: " << iter << endl;
}