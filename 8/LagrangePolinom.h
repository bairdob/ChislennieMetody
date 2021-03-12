//LagrangePolinom.cpp
#include <iostream>
#include <iomanip> // setw()
using namespace std;

template <size_t n, size_t m>
void init_vandermond_matrix(const double (&x)[n], const double (&y)[n], double (&vandermond)[n][m]){ //https://ru.wikipedia.org/wiki/Интерполяционный_многочлен_Лагранжа
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m-1; j++){
			vandermond[i][j] = pow(x[i],j);
		}
	}
	for (int i = 0; i < n; i++){
		vandermond[i][n] = y[i];
	}
}

template <size_t n>
void show_degree_x(const double (&arr)[n]){
	auto p = std::cout.precision(3);
	for (int i = 0; i < n; i++){
			cout << right<<std::setw(6)  << "x^"<< i ;
	}
	cout << endl;
	std::cout.precision(p);
}

template <size_t n>
double y(const double x,const double (&arr)[n]){
	double summ = 0;
	for (int i = 0; i < n; i++){
		summ += arr[i] * pow(x,i);
	}
	return summ;
}
