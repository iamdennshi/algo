#include <iostream>
#include <vector>
#include <algorithm>

// Фнукция, минимум который нужно найти
double fun(double x) {
	return (-1 * x * x * x + 3 * (1 + x) * (std::log1p(x) - 1));
}

void dichotomy(double (*fun)(double), double a, double b, double del, double eps);
void goldenSectionSearch(double (*fun)(double), double a, double b, double eps);

int main() {
	using namespace std;
	setlocale(LC_ALL, "Russian");

	//	&fun - указатель на функцию
	cout << "Метод дихотомии" << endl;
	 dichotomy(&fun, -0.5, 0.5, 1e-7, 1e-6);
	//	Результат:
	//  f(2.38419e-07) = -3
	//  Iteration: 21

	cout << "Метод золотого сечения" << endl;
	goldenSectionSearch(&fun, -0.5, 0.5, 1e-6);
	// Результат:
	// f(1.66094e-07) = -3
	// Iteration: 29
	return 0;
}