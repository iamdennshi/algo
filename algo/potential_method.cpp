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

void potential_method(Matrix costs, Amount a, Amount b) {
	cout << "ћатрица стоимости:\n";
	print_matrix("C", costs, a, b);
	
	// проверка услови€ баланса ai = bi
	if (accumulate(a.begin(), a.end(), 0) == accumulate(b.begin(), b.end(), 0)) {
		cout << "”словие баланса выполн€етс€\n";
	}
	else {
		// FIXME: при не выполнении нужно добавить фиктивного производител€ или потребител€
		cout << "”словие баланса Ќ≈ выполн€етс€\n";
	}

	// построение опорного плана X0 (по методу наименьшей стоимости)
	Matrix plan = init_first_plan(costs, a, b);
	cout << "\nќпорный план со стоимостью " << get_plan_cost(plan, costs) << '\n';
	print_matrix("X0", plan, a, b);

}
