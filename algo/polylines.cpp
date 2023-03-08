#include <iostream>
#include <algorithm>
#include <array>

const int m = 100;

void polylines(double (*fun)(double), double a, double b, double eps) {
	using namespace std;

	array<double, m> xm;
	//cout << "xm: ";

	for (int i = 0; i < xm.size(); i++) {
		xm[i] = a + fabs(b - a) / m * i;
		//cout << xm[i] << ' ';

	}
	//cout << '\n';

	double Lm[m - 1];
	for (int i = 0; i < m - 1; i++) {
		Lm[i] = fabs(fun(xm[i + 1]) - fun(xm[i])) / fabs(xm[i + 1] - xm[i]);
	}
	const double L = *max_element(Lm, Lm + m - 1);

	auto g = [=](double x, double x0) -> double {
		return fun(x0) - L * fabs(x - x0);
	};

	array<double, m> prev_p;
	array<double, m> p;

	int iteration = 0;
	double minP;
	int minP_index;
	double x;

	do {
		//cout << '\n' << "p" << iteration << ": ";
		minP = iteration == 0 ? g(xm[0], 0) : max(p[0], g(xm[0], x));
		minP_index = 0;

		for (int i = 0; i < p.size(); i++) {
			prev_p[i] = p[i];
			p[i] = iteration == 0 ? g(xm[i], 0) : max(p[i], g(xm[i], x));
			if (minP > p[i]) {
				minP_index = i;
				minP = p[i];
			}
			//cout << p[i] << " ";
		}
		x = xm[minP_index];
		//cout << '\n' << "x" << iteration + 1 << ": " << x;
		iteration++;

	} while (fabs(fun(xm[minP_index]) - prev_p[minP_index]) > eps);
	// cout << '\n';
	cout << "f(" << x << ") = " << fun(x);
	cout << '\n' << "Iteration: " << iteration << endl;
}
