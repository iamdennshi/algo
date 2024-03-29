# Реализация Алгоритмов Минимизации на С++ и Java
В ходе учебного курса "Методы оптимизации" требовалось реализовать алгоритмы минимизации  
Примеры использования алгоритмов находятся в [`main.cpp`](./algo/main.cpp)  
Некоторые алгоритмы реализованы на **Java** находятся в отдельном репозитории [`optimization-algorithm`](https://github.com/iamdennshi/optimization-algorithm)

## Методы нахождения минимума от одной переменной
### Методы нулевого порядка
* Метод деления отрезка пополам (дихотомии) - [`dichotomy.cpp`](./algo/dichotomy.cpp)
* Метод золотого сечения - [`golden-section-search.cpp`](./algo/golden-section-search.cpp)
* Метод Фибоначчи - [`fibonacci.cpp`](./algo/fibonacci.cpp)

### Методы первого порядка
* Метод ломаных - [`polylines.cpp`](./algo/polylines.cpp)

### Методы второго порядка
* Метод Ньютона - [`newton.cpp`](./algo/newton.cpp)

## Методы нахождения минимума от двух переменных
### Методы прямого поиска (нулевого порядка)
* Метод Хука-Дживса - [`pattern-search.cpp`](./algo/pattern-search.cpp)

### Методы первого порядка
* Градиентный метод с постоянным шагом - [`gradient-fixed-step.cpp`](./algo/gradient-fixed-step.cpp)

## Методы линейного программирования
* Симплекс метод. Нахождение максимума функций ограниченной системой - [`simplex.cpp`](./algo/simplex.cpp)
* Транспортная задача, метод потенциалов - [`potential-method.cpp`](./algo/potential-method.cpp)
