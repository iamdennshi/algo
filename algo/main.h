#pragma once
#include <iostream>

#pragma region Функция от одной переменной, приминима только к соответсвующим методам 
// Фнукция, минимум который нужно найти
double f(double x) {
	return (-1 * x * x * x + 3 * (1 + x) * (std::log1p(x) - 1));
}
// Первая производная
double dfx(double x) {
	return -3 * x * x + 3 * std::log1p(x);
}
// Вторая производная
double df_x(double x) {
	return (-6 * x * (x + 1) + 3) / (x + 1);
}
#pragma endregion

#pragma region Методы нахождения минимума от одной переменной
void dichotomy(double (*f)(double), double a, double b, double del, double eps);
void golden_section_search(double (*f)(double), double a, double b, double eps);
void fibonacci(double (*f)(double), double a, double b, int n);
void polylines(double (*f)(double), double (*dfx)(double), double a, double b, double eps);
void newton(double (*f)(double), double (*dxf)(double), double (*dx_f)(double), double a, double b, double eps);
#pragma endregion

#pragma region Функция от двух переменных
// Фнукция, минимум который нужно найти
double f(double x0, double x1) {
	//return x0 * x0 + std::pow(1.61, x1 * x1 + x0 * x0) + 4 * x0 + 3 * x1;
	return x0 * x0 + 3 * x1 * x1 + std::cos(x0 + x1);
}
// Первая производная по x0
double dfx0(double x0, double x1) {
	//return 2 * x0 + 2 * x0 * std::pow(1.61, x0 * x0 + x1 * x1) + 4;
	return 2 * x0 - sin(x0 + x1);
}
// Первая производная по x1
double dfx1(double x0, double x1) {
	//return 2 * x0 * std::pow(1.61, x1 * x1 + x0 * x0) + 2 * x1 + 3;
	return 6 * x1 - sin(x0 + x1);
}
#pragma endregion

#pragma region Методы нахождения минимума от двух переменых
void gradient_fixed_step(double (*f)(double, double), double (*dfx0)(double, double), double (*dfx1)(double, double),
	std::pair<double, double> x0, double eps);
void gradient_min_step(double (*f)(double, double), double (*dfx0)(double, double), double (*dfx1)(double, double),
	std::pair<double, double> x0, double eps);
void pattern_search(double (*f)(double, double), std::pair<double, double> x0, double eps);
#pragma endregion