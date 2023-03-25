#include "main.h"
using namespace std;

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
	return 0;
}
