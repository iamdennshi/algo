#ifndef MAIN_H
#define MAIN_H


#include <iostream>

#pragma region Функция от одной переменной, приминима только к соответсвующим методам 
// Фнукция, минимум который нужно найти
double f(double x);
// Первая производная
double dfx(double x);
// Вторая производная
double df_x(double x);
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
double f(double x0, double x1);
// Первая производная по x0
double dfx0(double x0, double x1);
// Первая производная по x1
double dfx1(double x0, double x1);
#pragma endregion

#pragma region Методы нахождения минимума от двух переменых
void gradient_fixed_step(double (*f)(double, double), double (*dfx0)(double, double), double (*dfx1)(double, double),
	std::pair<double, double> x0, double eps);
void gradient_min_step(double (*f)(double, double), double (*dfx0)(double, double), double (*dfx1)(double, double),
	std::pair<double, double> x0, double eps);
void pattern_search(double (*f)(double, double), std::pair<double, double> x0, double eps);
#pragma endregion

#pragma region Линейное программирование

// Вид соотношения
enum t_Ratio {
	EQUAL, // =
	GRATE, // >=
	LESS // <=
};

// Ограничение для симплекс метода
class Limit {
public: 
	int x1, x2;
	t_Ratio ratio;
	int b;

	Limit(int x1, int x2, t_Ratio ratio, int b) : x1(x1), x2(x2), ratio(ratio), b(b) {}

	std::string show_limit();
};

void simplex(double x1, double x2, std::array<Limit, 3> limits);
#pragma endregion

#endif // !MAIN_H