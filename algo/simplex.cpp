#include <iostream>
#include <array>
#include <string>
#include <sstream>
#include "main.h"

using namespace std;

// Вывод уравнений в понятном виде
string print_equation(int* array, int size) {
	stringstream ss;

	if (array[0] != 0) {
		if (array[0] == 1)
			ss << "x1 ";
		else if (array[0] == -1)
			ss << "-x1 ";
		else
			ss << array[0] << "x1 ";
	}
	for (int i = 1; i < size; i++) {
		if (array[i] != 0) {
			if (array[i] > 0) {
				if (array[i] == 1)
					ss << "+ " << "x" << i + 1 << ' ';
				else
					ss << "+ " << array[i] << "x" << i + 1 << ' ';
			}
			else {
				if (array[i] == -1)
					ss << "- x" << i + 1 << ' ';
				else
					ss << "- " << abs(array[i]) << "x" << i + 1 << ' ';
			}
		}
	}
	return ss.str();
}

// Выводит ограничение. Например 5x1 + 2x2 >= 32
string Limit::show_limit() {
	string ratio = "= ";
	stringstream ss;

	switch (this->ratio) {
		case t_Ratio::GRATE: {
			ratio = ">= ";
			break;
		}
		case t_Ratio::LESS: {
			ratio = "<= ";
			break;
		}
	}
	ss << print_equation(this->x.data(), this->x.size());
	ss << ratio << this->b;

	return ss.str();
}

void simplex(std::array<int, 2> x, std::array<Limit, 3> limits) {
	// максимально свободный индекс в ограничениях 
	// Иниц-ия 2, потому что первоначально 2 переменных в ограничениях
	int max_x_index = 2; 
	int fake_x_index; // индекс искусственной переменной

	std::cout << "Целевая функция: \n";
	std::cout << print_equation(x.data(), x.size()) << endl;

	std::cout << "Система ограничений: \n";
	for (auto& i : limits) {
		cout << i.show_limit() << endl;
	}

	// Правая часть неравенств должна быть не отрицательной
	for (auto& i : limits) {
		if (i.b < 0) {
			for (int j = 0; j < i.x.size(); j++) {
				if (i.x[j] != 0) 
					i.x[j] *= -1;
			}
			i.b *= -1;

			if (i.ratio == t_Ratio::LESS) {
				i.ratio = t_Ratio::GRATE;
			}
			else if (i.ratio == t_Ratio::GRATE){
				i.ratio = t_Ratio::LESS;
			}
		}
	}

	// Выделение базисных переменных. Каждое ограничение должно стать равенством
	for (auto& i : limits) {
		if (i.ratio != t_Ratio::EQUAL) {
			if (i.ratio == t_Ratio::LESS) {
				i.x[max_x_index] = 1;
				max_x_index++; // увеличение, потому что использовали
			}
			else if (i.ratio == t_Ratio::GRATE) {
				i.x[max_x_index] = -1;
				max_x_index++; // увеличение, потому что использовали
				i.x[max_x_index] = 1;
				fake_x_index = max_x_index; // индекс искусственной переменной - найден
				max_x_index++; // увеличение, потому что использовали
			}
			i.ratio = t_Ratio::EQUAL;
		}
	}

	std::cout << "Система ограничений после преобразований: \n";
	for (auto& i : limits) {
		cout << i.show_limit() << endl;
	}


}

