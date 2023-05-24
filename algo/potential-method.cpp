#include <iostream>
#include <array>
#include <iomanip>
#include <string>
#include <numeric>
#include <algorithm>

using namespace std;

using Amount = array<int, 4>;
using Matrix = array<Amount, 4>;

void print_matrix(string name, Matrix& body) {
	string spaces(name.length() + 3, ' ');
	for (int i = 0; i < body.size(); i++) {
		cout << (i == 1 ? name + " = |" : spaces + "|");
		for (int j = 0; j < body[0].size(); j++) {
			cout << setw(3) << body[i][j];
			cout << (j == body[0].size() - 1 ? "|" : " ");
		}
		cout << '\n';
	}
	cout << '\n';
}

void print_matrix(string name, Matrix& body, Amount a, Amount b) {
	string spaces(name.length() + 3, ' ');
	for (int i = 0; i < a.size(); i++) {
		cout << (i == 1 ? name + " = |" : spaces + "|");
		for (int j = 0; j < b.size(); j++) {
			cout << setw(3) << body[i][j];
			cout << (j == b.size() - 1 ? "|" : " ");
		}
		cout << a[i] << '\n';
	}
	cout << "     ";
	for (int i = 0; i < b.size(); i++) {
		cout << setw(3) << b[i] << ' ';
	}
	cout << "\n\n";
}

Matrix& init_first_plan(Matrix body, Amount a, Amount b) {
	static Matrix plan = {0};
	
	for (int i = 0; i < body.size(); i++) {
		while (a[i] != 0) {
			auto smallest = std::min_element(body[i].begin(), body[i].end());
			int smallest_index = std::distance(body[i].begin(), smallest);
			
			if (body[i][smallest_index] != std::numeric_limits<int>::max()) {
				plan[i][smallest_index] = std::min(a[i], b[smallest_index]);

				a[i] -= plan[i][smallest_index];
				b[smallest_index] -= plan[i][smallest_index];

				body[i][smallest_index] = std::numeric_limits<int>::max();
			}
		}
	}

	return plan;
}

int get_plan_cost(Matrix& plan, Matrix& costs) {
	int cost = 0;
	for (int i = 0; i < plan.size(); i++) {
		for (int j = 0; j < plan.size(); j++) {
			if (plan[i][j] > 0) {
				cost += plan[i][j] * costs[i][j];
			}
		}
	}
	return cost;
}

// получение кол-во базисных переменных
int get_number_basis_var(Matrix& plan) {
	int count{ 0 };
	for (auto i : plan) {
		for (auto& j : i) {
			if (j > 0)
				count++;
		}
	}
	return count;
}

void potential_method(Matrix costs, Amount a, Amount b) {
	cout << "Матрица стоимости:\n";
	print_matrix("C", costs, a, b);
	
	// проверка условия баланса ai = bi
	if (accumulate(a.begin(), a.end(), 0) == accumulate(b.begin(), b.end(), 0)) {
		cout << "Условие баланса выполняется\n";
	}
	else {
		// FIXME: при не выполнении нужно добавить фиктивного производителя или потребителя
		cout << "Условие баланса НЕ выполняется\n";
	}

	// построение опорного плана X0 (по методу наименьшей стоимости)
	Matrix plan = init_first_plan(costs, a, b);
	cout << "\nОпорный план со стоимостью " << get_plan_cost(plan, costs) << '\n';
	print_matrix("X0", plan, a, b);

	// проверка, на то покрывает ли план все значения
	int number_basis_var = get_number_basis_var(plan); // кол-во базисных переменных в плане
	pair<int, int> point;
	Amount u{0}, v{0};
	bool isFound = false;
	int iter = 0;

	cout << "Кол-во базисных переменных: " << number_basis_var << '\n';
	cout << "Кол-во потенциалов u, v: " << u.size() + v.size() - 1 << '\n' << '\n';

	// нахождение координаты первой базисной точки
	for (int i = 0; i < plan.size(); i++) {
		for (int j = 0; j < plan.size(); j++) {
			if (plan[i][j] > 0) {
				point = make_pair(i, j);
				// при u0 = 0
				v[j] = costs[i][j] + u[i];
				goto end;
			}
		}
	}
	end:

	// проверяем обход плана и находим u,v
	for (int i = 0; i < number_basis_var - 1; i++) {
		isFound = false;
		// поиск по горизонтали
		for (int x = point.second + 1; x < plan.size(); x++) {
			if (plan[point.first][x] > 0) {
				isFound = true;
				point.second = x;
				v[x] = costs[point.first][x] + u[point.first];
				break;
			}
		}
		if (!isFound) {
			// поиск по вертикали
			for (int y = 0; y < plan.size(); y++) {
				if (plan[y][point.second] > 0 && y != point.first) {
					point.first = y;
					isFound = true;
					u[y] = v[point.second] - costs[y][point.second];
					break;

				}
			}
			if (!isFound) {
				// FIXME: Добавляется фиктивная поставка в план
				cout << "План вырожденный" << endl;
				break;
			}
		}
	}

	// план невырожденный, находим матрицу оценок
	Matrix c{ 0 };
	bool isNegative = false; // есть ли отрицательные оценки
	if (isFound) {
		cout << "План невырожденный. Матрица оценок для X" << iter << ": " << endl;
		for (int i = 0; i < c.size(); i++)
		{
			for (int j = 0; j < c.size(); j++) {
				if (plan[i][j] > 0) {
					c[i][j] = 0;
				}
				else {
					c[i][j] = costs[i][j] - (v[j] - u[i]);
					if (c[i][j] < 0)
						isNegative = true;
				}
			}
		}

	}
	// FIXME: вырожденный план
	else {

	}

	print_matrix("С1", c);
	if (isNegative) {
		cout << "Оценки отрицательные! План можно улучшить" << endl;
	}
	else {
		cout << "Оценки не отрицательные! План X" << iter << " оптимальный" << " F(X" << iter << ") = " << get_plan_cost(plan, costs) << endl;
	}


}