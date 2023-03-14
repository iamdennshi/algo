#include <iostream>

#pragma region Функция от одной переменной, приминима только к соответсвующим методам 
// Фнукция, минимум который нужно найти
double fun(double x) {
	return (-1 * x * x * x + 3 * (1 + x) * (std::log1p(x) - 1));
}
// Первая производная
double fun1(double x) {
	return -3*x * x + 3 * std::log1p(x);
}
// Вторая производная
double fun2(double x) {
	return (-6 * x * (x + 1) + 3) / (x + 1);
}
#pragma endregion

#pragma region Методы нахождения минимума от одной переменной
void dichotomy(double (*fun)(double), double a, double b, double del, double eps);
void goldenSectionSearch(double (*fun)(double), double a, double b, double eps);
void fibonacci(double (*fun)(double), double a, double b, int n);
void polylines(double (*fun)(double), double (*fun1)(double), double a, double b, double eps);
void newton(double (*fun)(double), double (*fun1)(double), double (*fun2)(double), double a, double b, double eps);
#pragma endregion

#pragma region Функция от двух переменных
// Фнукция, минимум который нужно найти
double fun(double x0, double x1) {
	return x0 * x0 + 3 * x1 * x1 + std::cos(x0 + x1);
}
// Первая производная по x0
double fun1x0(double x0, double x1) {
	return 2 * x0 - sin(x0 + x1);
}
// Первая производная по x1
double fun1x1(double x0, double x1) {
	return 6 * x1 - sin(x0 + x1);
}
#pragma endregion

#pragma region Методы нахождения минимума от двух переменых
void gradientFixedStep(double (*fun)(double, double), double (*fun1x0)(double, double), double (*fun1x1)(double, double), 
	std::pair<double, double> x0, double eps);
#pragma endregion


int main() {
	using namespace std;
	setlocale(LC_ALL, "Russian");

	#pragma region Примеры использования методов нахождения минимума от одной переменной 
	//cout << "Метод дихотомии" << endl;
	//dichotomy(&fun, -0.5, 0.5, 1e-7, 1e-6);
	//	Результат:
	//  f(2.38419e-07) = -3
	//  Iteration: 22
	//
	//cout << "Метод золотого сечения" << endl;
	//goldenSectionSearch(&fun, -0.5, 0.5, 1e-6);
	// Результат:
	// f(1.66094e-07) = -3
	// Iteration: 30
	//
	//cout << "Метод Фибоначи" << endl;
	fibonacci(&fun, -0.5, 0.5, 15);
	// Результат:
	// f(1.66094e-07) = -3
	// Iteration: 30
	//
	//cout << "Метод ломаных" << endl;
	//polylines(&fun, &fun1, 0.1, 2, 1e-6);
	// Результат:
	// f(0) = -3
	// Iteration: 39
	//
	//cout << "Метод Ньютона" << endl;
	//newton(&fun, &fun1, &fun2, -0.5, 0.5, 1e-6);
	// Результат:
	// f(-1.48354e-21) = -3
	// Iteration: 5
	#pragma endregion

	#pragma region Примеры использования методов нахождения минимума от двух переменных
	//cout << "Градиентный метод с постоянным шагом" << endl;
	//gradientFixedStep(&fun, &fun1x0, &fun1x1, make_pair(1, 1), 1e-6);
	// f(0.00373264, 0.000881153) = 1.00001
	// Iteration: 68
	#pragma endregion
	return 0;
}