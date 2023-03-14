#include <iostream>

double fib(int n) {
	if (n <= 1)
		return 1;
	return fib(n - 1) + fib(n - 2);
}

void fibonacci(double (*fun)(double), double a, double b, int n) {
	using namespace std;

	double xk1 = a + fib(n - 2) / fib(n) * (b - a);
	double xk2 = a + fib(n - 1) / fib(n) * (b - a);
	double fxk1 = fun(xk1);
	double fxk2 = fun(xk2);
	int k = 1;


	while (n - 2 != k) {
		if (fxk1 > fxk2) {
			a = xk1;
			xk1 = xk2;
			xk2 = a + fib(n - k - 1) / fib(n - k) * (b - a);
			fxk2 = fun(xk2);
		}
		else {
			b = xk2;
			xk2 = xk1;

			xk1 = a + fib(n - k - 2) / fib(n - k) * (b - a);
			fxk1 = fun(xk1);
		}
		k++;
	}
	cout << "f(" << (b - a) / 2 << ") = " << fun((b - a) / 2) << endl;
	cout << "Iteration: " << k << endl;
}