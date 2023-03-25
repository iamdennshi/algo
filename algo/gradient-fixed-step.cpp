#include <iostream>
using namespace std;

void gradient_fixed_step(double (*f)(double, double), double (*dfx0)(double, double), double (*dfx1)(double, double),
	pair<double, double> x0, double eps) {
	unsigned iter = 1;
	double a = 0.5;	// шаг сходимости
	auto prev_xk = x0;
	auto xk = make_pair(
		(prev_xk.first - dfx0(prev_xk.first, prev_xk.second) * a),
		(prev_xk.second - dfx1(prev_xk.first, prev_xk.second) * a)
	);

	while (fabs(f(xk.first, xk.second) - f(prev_xk.first, prev_xk.second)) > eps) {
		prev_xk = xk;
		xk = make_pair(
			(prev_xk.first - dfx0(prev_xk.first, prev_xk.second) * a),
			(prev_xk.second - dfx1(prev_xk.first, prev_xk.second) * a)
		);

		if (f(xk.first, xk.second) > f(prev_xk.first, prev_xk.second)) {
			a *= 0.5; 
		}
		++iter;
	}

	cout << "f(" << xk.first << ", " << xk.second << ") = " << f(xk.first, xk.second) << '\n';
	cout << "Iteration: " << iter << endl;
}