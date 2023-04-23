#include <iostream>
#include <array>

// Метод Хука-Дживса
void pattern_search(double (*f)(double, double), std::pair<double, double> x0, double eps) {
	using namespace std;
	double a = 1; // ускоряющий множитель
	const int n = 9; // кол-во новых точек
	int iter = 0;

	pair<double, double> xk[n]; // координаты точек окресности
	array<double, n> fk; 

	pair<double, double> mxk = make_pair(x0.first, x0.second); // координаты мин. точки
	double mf = f(x0.first, x0.second); // мин. значение функции

	do {
		iter++;

		xk[0].first = x0.first; xk[0].second = x0.second;
		xk[1].first = x0.first; xk[1].second = x0.second + a;
		xk[2].first = x0.first; xk[2].second = x0.second - a;

		xk[3].first = x0.first + a; xk[3].second = x0.second;
		xk[4].first = x0.first + a; xk[4].second = x0.second + a;
		xk[5].first = x0.first + a; xk[5].second = x0.second - a;

		xk[6].first = x0.first - a; xk[6].second = x0.second;
		xk[7].first = x0.first - a; xk[7].second = x0.second + a;
		xk[8].first = x0.first - a; xk[8].second = x0.second - a;		

		for (int i = 0; i < n; i++) {
			fk[i] = f(xk[i].first, xk[i].second);
			if (mf > fk[i]) {
				mf = fk[i];
				mxk.first = xk[i].first;
				mxk.second = xk[i].second;
			}
		}

		if (fk[0] <= mf) {
			a *= 0.5;
		}
		else {
			x0.first = x0.first + a * (mxk.first - x0.first);
			x0.second = x0.second + a * (mxk.second - x0.second);
			mf = f(x0.first, x0.second);
		}
	} while (a > eps);

	cout << "f(" << mxk.first << ", " << mxk.second << ") = " << mf << '\n';
	cout << "Iteration: " << iter << endl;


}