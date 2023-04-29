#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
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

	int fake_x_index = 0; // индекс искусственной переменной
	vector<int> table_x; // Индексы базисных переменных для таблицы
	int iteration = 0; // кол-во итераций
	bool isDEBUG = true; // включить промежуточные вычисление

	if (isDEBUG) {
		std::cout << "Целевая функция: \n";
		std::cout << print_equation(x.data(), x.size()) << "\n\n";

		std::cout << "Система ограничений: \n";
		for (auto& i : limits) {
			cout << i.show_limit() << "\n";
		}
		cout << "\n";
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
				table_x.push_back(max_x_index);
				max_x_index++; // увеличение, потому что использовали
			}
			else if (i.ratio == t_Ratio::GRATE) {
				i.x[max_x_index] = -1;
				max_x_index++; // увеличение, потому что использовали
				i.x[max_x_index] = 1;
				table_x.push_back(max_x_index);
				fake_x_index = max_x_index; // индекс искусственной переменной - найден
				max_x_index++; // увеличение, потому что использовали
			}
			i.ratio = t_Ratio::EQUAL;
		}
	}

	if (isDEBUG) {
		std::cout << "Система ограничений после преобразований: \n";
		for (auto& i : limits) {
			cout << i.show_limit() << "\n";
		}
		cout << '\n';
	}

	// Вычисление коэффициентов новой целевой функции
	// FIME: Не реализовано действие, если искусственной переменной нету
	vector<int> x_after; // Коэффициенты целевой функции после преобразования
	if (fake_x_index > 0) {
		for (int i = 0; i <= fake_x_index; i++) {
			if (i == fake_x_index) {
				x_after.push_back(-1000);
			}
			else if (i < 2) {
				x_after.push_back(x[i]);
			}
			else {
				x_after.push_back(0);
			}
		}
		if (isDEBUG) {
			std::cout << "Целевая функция после преобразований: \n";
			std::cout << print_equation(x_after.data(), x_after.size()) << "\n\n";
		}
	}

	// FIXME: Размер таблицы должен быть задан динамически
	array<array<double, 7>, 4> table; // Значения симплекс таблицы, 3 базисных переменных + 1 для шапки
	array<array<double, 7>, 4> table_new; // новая таблица

	while (true) {
		bool isNegative = false; // Для проверки на отрицательность оценок
		if (iteration == 0) {
			// Первое заполнение таблицы, с конца
			// Заполнение тело
			for (int i = table.size() - 1; i >= 1; i--) {
				table[i][0] = limits[i - 1].b;
				for (int j = 1; j < table[0].size(); j++) {
					table[i][j] = limits[i - 1].x[j - 1];
				}
			}

			// Заполнение шапки
			// Вычисление значения целевой функции при базисных переменных
			table[0][0] = 0;
			for (int i = 0; i < table_x.size(); i++) {
				if (x_after[table_x[i]] != 0) {
					table[0][0] += x_after[table_x[i]] * table[i + 1][0];
				}
			}
			// Вычисление оценок начиная c table[0][1]
			for (int i = 1; i < table[0].size(); i++) {
				table[0][i] = 0;
				for (int j = 0; j < table_x.size(); j++) {
					if (x_after[table_x[j]] != 0) {
						table[0][i] += x_after[table_x[j]] * table[j + 1][i];
					}
				}
				table[0][i] -= x_after[i - 1];
				if (table[0][i] < 0)
					isNegative = true;
			}
		}
		else {
			// находим опорный элемент
			auto min_column = min_element(table[0].begin() + 1, table[0].end()); // минимальный элемент среди оценок
			int min_column_index = distance(table[0].begin(), min_column); // находим его индекс в таблице по столбцу

			// минимальное положительное соотношение значение функции и элемента в найденном столбце
			double min_row = 1000;
			int min_row_index;
			for (int i = 1; i < table.size(); i++) {
				if (table[i][min_column_index] > 0) {
					double start = table[i][0] / table[i][min_column_index];
					if (start < min_row) {
						min_row = start;
						min_row_index = i;
					}
				}
			}
			// Заменяем базисную переменную на новую
			table_x[min_row_index - 1] = min_column_index - 1;

			// Следующее заполнение таблицы
			// Заполнение тело
			for (int i = 1; i < table_new.size(); i++) {
				for (int j = 0; j < table_new[0].size(); j++) {
					if (i == min_row_index) {
						table_new[i][j] = table[i][j] / table[min_row_index][min_column_index];
					}
					else {
						table_new[i][j] = table[i][j] - table[min_row_index][j] * table[i][min_column_index] / table[min_row_index][min_column_index];
					}
				}
			}

			// Заполнение шапки
			// Вычисление значения целевой функции при базисных переменных
			table_new[0][0] = 0;
			for (int i = 0; i < table_x.size(); i++) {
				if (x_after[table_x[i]] != 0) {
					table_new[0][0] += x_after[table_x[i]] * table_new[i + 1][0];
				}
			}

			// Вычисление оценок начиная c table_new[0][1]
			for (int i = 1; i < table_new[0].size(); i++) {
				table_new[0][i] = 0;
				for (int j = 0; j < table_x.size(); j++) {
					if (x_after[table_x[j]] != 0) {
						table_new[0][i] += x_after[table_x[j]] * table_new[j + 1][i];
					}
				}
				table_new[0][i] -= x_after[i - 1];
				if (table[0][i] < 0)
					isNegative = true;
			}

			// скопировать table_new в table
			for (int i = 0; i < table.size(); i++) {
				copy(table_new[i].begin(), table_new[i].end(), table[i].begin());
			}
		}

		if (isDEBUG) {
			// Вывод таблицы
			cout << "Cимплекс таблица " << iteration + 1 << endl;
			for (int i = 0; i < table.size(); i++) {
				for (int j = 0; j < table[0].size() + 1; j++) {
					if (i == 0 && j == 0) {
						cout << "  ";
					}
					else if (j == 0) {
						cout << "x" << table_x[i - 1] + 1 << ' ';
					}
					else {
						cout << table[i][j - 1] << ' ';
					}
				}
				cout << '\n';
			}
			cout << '\n';
		}

		iteration++;

		// Если оценки не отрицательные то выводим ответ
		if (!isNegative) {
			// FIXME: длина массива должна зависеть от кол-во x
			array<int, 6> x_max = { 0 };

			// 3 - кол-во базисов 
			for (int i = 0; i < 3; i++) {
				x_max[table_x[i]] = table[i + 1][0];
			}

			cout << "Xmax = {";
			for (int i = 0; i < x_max.size(); i++) {
				if (i != x_max.size() - 1) {
					cout << x_max[i] << ", ";
				}
				else {
					cout << x_max[i] << "}\n";
				}
			}
			cout << "fmax = " << table[0][0];
			break;
		}
	}

}

