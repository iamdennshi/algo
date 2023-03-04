#include <iostream>
#include <vector>
#include <algorithm>

// �������, ������� ������� ����� �����
double fun(double x) {
	return (-1 * x * x * x + 3 * (1 + x) * (std::log1p(x) - 1));
}

void dichotomy(double (*fun)(double), double a, double b, double del, double eps);
void goldenSectionSearch(double (*fun)(double), double a, double b, double eps);

int main() {
	using namespace std;
	setlocale(LC_ALL, "Russian");

	//	&fun - ��������� �� �������
	cout << "����� ���������" << endl;
	 dichotomy(&fun, -0.5, 0.5, 1e-7, 1e-6);
	//	���������:
	//  f(2.38419e-07) = -3
	//  Iteration: 21

	cout << "����� �������� �������" << endl;
	goldenSectionSearch(&fun, -0.5, 0.5, 1e-6);
	// ���������:
	// f(1.66094e-07) = -3
	// Iteration: 29
	return 0;
}