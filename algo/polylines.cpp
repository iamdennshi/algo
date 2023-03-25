#include <iostream>
#include <algorithm>
#include <array>
using namespace std;

const int m = 100; // Кол-во точек на которых разобъется отрезок [a,b]

void polylines(double (*f)(double), double (*dfx)(double), double a, double b, double eps) {
	array<double, m> xm; // Координаты точек по x

	for (int i = 0; i < xm.size(); i++) {
		xm[i] = a + fabs(b - a) / m * i;
	}

	array<double, m> lxm; // Значения константы Липшица в каждой координате
	// Вычисление константы Липшица (L) при помощи макс. значения производной
	for (int i = 0; i < m; i++) {
		lxm[i] = fabs(dfx(xm[i]));
	}
	double L = *max_element(lxm.begin(), lxm.end());

	// Функция ломаной
	auto g = [=](double x, double x0) -> double {
		return f(x0) - L * fabs(x - x0);
	};

	array<double, m> p; // Значения общей ломаной
	array<double, m> prev_p; // Значения общей ломаной, шагом назад

	int iter = 0;
	double minP; // Минимальное значение в общей ломаной
	int minP_index;
	double x; // Точка от которой будет стоится ломаная

	do {
		minP = iter == 0 ? g(xm[0], 0) : max(p[0], g(xm[0], x));
		minP_index = 0;

		for (int i = 0; i < p.size(); i++) {
			prev_p[i] = p[i];
			p[i] = iter == 0 ? g(xm[i], 0) : max(p[i], g(xm[i], x));
			if (minP > p[i]) {
				minP_index = i;
				minP = p[i];
			}
		}
		x = xm[minP_index];
		iter++;

	} 
	while (fabs(f(xm[minP_index]) - prev_p[minP_index]) > eps);

	cout << "f(" << x << ") = " << f(xm[minP_index]);
	cout << '\n' << "Iteration: " << iter << endl;
}
