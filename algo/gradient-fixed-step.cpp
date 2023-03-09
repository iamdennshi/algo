#include <iostream>
using namespace std;

void gradientFixedStep(double (*fun)(double, double), double (*fun1x0)(double, double), double (*fun1x1)(double, double),
	pair<double, double> x0, double eps) {
	unsigned iteration = 1;
	double a = 0.1;
	auto prev_xk = x0;
	auto xk = make_pair(
		(prev_xk.first - fun1x0(prev_xk.first, prev_xk.second) * a),
		(prev_xk.second - fun1x1(prev_xk.first, prev_xk.second) * a)
	);

	while (fabs(fun(xk.first, xk.second) - fun(prev_xk.first, prev_xk.second)) > eps) {
		prev_xk = xk;
		xk = make_pair(
			(prev_xk.first - fun1x0(prev_xk.first, prev_xk.second) * a),
			(prev_xk.second - fun1x1(prev_xk.first, prev_xk.second) * a)
		);

		if (fun(xk.first, xk.second) > fun(prev_xk.first, prev_xk.second)) {
			a *= 0.5;
		}
		++iteration;
	}

	cout << "f(" << xk.first << ", " << xk.second << ") = " << fun(xk.first, xk.second) << '\n';
	cout << "Iteration: " << iteration << endl;
}