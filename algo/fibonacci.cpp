#include <iostream>
using namespace std;

double fib(int n) {
	if (n <= 1)
		return 1;
	return fib(n - 1) + fib(n - 2);
}

void fibonacci(double (*f)(double), double a, double b, int n) {
	pair<double, double> x = make_pair(
		a + fib(n - 2) / fib(n) * (b - a),
		a + fib(n - 1) / fib(n) * (b - a)
	);
	double fx0 = f(x.first);
	double fx1 = f(x.second);
	int iter = 1;

	while (n - 2 != iter) {
		if (fx0 > fx1) {
			a = x.first;
			x.first = x.second;
			x.second = a + fib(n - iter - 1) / fib(n - iter) * (b - a);
			fx1 = f(x.second);
		}
		else {
			b = x.second;
			x.second = x.first;

			x.first = a + fib(n - iter - 2) / fib(n - iter) * (b - a);
			fx0 = f(x.first);
		}
		iter++;
	}
	cout << "f(" << (b - a) / 2 << ") = " << f((b - a) / 2) << endl;
	cout << "Iteration: " << iter << endl;
}