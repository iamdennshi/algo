#include <iostream>
#include <array>
#include <string>
#include <sstream>
#include "main.h"

using namespace std;

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

	if (this->x1 != 0) {
		if (this->x1 == 1)
			ss << "x1 ";
		else
			ss << x1 << "x1 ";
	}
	if (this->x2 != 0) {
		if (this->x2 > 0) {
			if (this->x2 == 1)
				ss << "+ " << "x2 ";
			else
				ss << "+ " << x2 << "x2 ";
		}
		else {
			ss << "- " << abs(x2) << "x2 ";
		}
	}

	ss << ratio << this->b;
	return ss.str();
}


void simplex(double x1, double x2, std::array<Limit, 3> limits) {
	std::cout << "Ограничения: \n";
	for (auto& i : limits) {
		cout << i.show_limit() << endl;
	}
}

