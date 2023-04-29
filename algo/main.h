#ifndef MAIN_H
#define MAIN_H


#include <iostream>
#include <array>

using namespace std;

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

#pragma region Методы линейного программирования
// Вид соотношения
enum t_Ratio {
	EQUAL, // =
	GRATE, // >=
	LESS // <=
};

// Ограничение для симплекс метода
class Limit {
public: 
	// FIME: Костыль, неизвестных в ограничений может быть больше
	std::array<int, 6> x = { 0 };
	t_Ratio ratio;
	int b;

	Limit(int x1, int x2, t_Ratio ratio, int b) : ratio(ratio), b(b) {
		x[0] = x1;
		x[1] = x2;
	}

	std::string show_limit();
};
// x - коэффициенты целевой функции
// limits - 3 ограничения
void simplex(std::array<int, 2> x, std::array<Limit, 3> limits);

// costs - матрица стоимости 4 на 4
// a - объемы производства
// b - объемы потребления
void potential_method(array<array<int, 4>, 4> costs, array<int, 4> a, array<int, 4> b);

#pragma endregion

#endif // !MAIN_H