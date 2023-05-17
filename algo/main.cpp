#include "main.h"
#include <array>
using namespace std;

#pragma region Функция от одной переменной, приминима только к соответсвующим методам 
// Функция, минимум который нужно найти
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

#pragma region Функция от двух переменных
// Функция, минимум который нужно найти
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


int main() {
	setlocale(LC_ALL, "Russian");

	#pragma region Примеры использования методов нахождения минимума от одной переменной 
	//cout << "Метод дихотомии" << endl;
	//dichotomy(&f, -0.5, 0.5, 1e-7, 1e-6);
	//	Результат:
	//	f(2.38419e-07) = -3
	//  Iteration: 22
	//
	//cout << "Метод золотого сечения" << endl;
	//golden_section_search(&f, -0.5, 0.5, 1e-6);
	//	Результат:
	//	f(1.66094e-07) = -3
	//	Iteration: 30
	//
	//cout << "Метод Фибоначи" << endl;
	//fibonacci(&f, -0.5, 0.5, 15);
	//	Результат:
	//	f(0.00151976) = -3
	//	Iteration: 13
	//
	//cout << "Метод ломаных" << endl;
	//polylines(&f, &dfx, -0.5, 0.5, 1e-6);
	//	Результат:
	//	f(0) = -3
	//	Iteration: 39
	//
	//cout << "Метод Ньютона" << endl;
	//newton(&f, &dfx, &df_x, -0.5, 0.5, 1e-6);
	//	Результат:
	//	f(-1.48354e-21) = -3
	//	Iteration: 6
	#pragma endregion

	#pragma region Примеры использования методов нахождения минимума от двух переменных
	//cout << "Градиентный метод с постоянным шагом" << endl;
	//gradient_fixed_step(&f, &dfx0, &dfx1, make_pair(1, 1), 1e-6);
	//	Результат:
	//	f(0.00373264, 0.000881153) = 1.00001
	//	Iteration: 68

	//cout << "Градиентный метод с оптимальным шагом" << endl;
	//gradient_min_step(&f, &dfx0, &dfx1, make_pair(1, 1), 1e-6);

	//cout << "Метод Хука-Дживса" << endl;
	//pattern_search(&f, make_pair(1, 1), 1e-6);
	//	Результат:
	//	f(0, 0) = 1
	//	Iteration: 21
	#pragma endregion

	#pragma region Примеры использования методов линейного программирования
	//cout << "Симплекс Метод. Нахождение максимума функций ограниченной системой" << endl;
	// Система ограничений для симплекс метода
	//std::array<Limit, 3> limits  = {
	//	Limit(5, -2, t_Ratio::LESS, 4),
	//	Limit(1, -2, t_Ratio::GRATE, -4),
	//	Limit(1, 1, t_Ratio::GRATE, 4)
	//};

	//simplex({ 1, 2}, limits);
	//	Результат:
	//	Xmax = {2, 3, 0, 0, 1, 0}
	//	fmax = 8

	cout << "Транспортная задача. Метод потенциалов" << endl;
	potential_method({ { {4,5,5,7}, {8,7,5,4}, {9,6,4,5}, {3,2,9,3} } }, { 100, 120, 150, 130 }, { 140, 130, 90, 140 });
	#pragma endregion

	return 0;
}
