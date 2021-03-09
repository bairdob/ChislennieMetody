//LagrangePolinom.cpp
#include <iostream>
#include <iomanip> // setw()
#include "GaussMethod.h"
using namespace std;


template <size_t n>
void arr_show(const double (&arr)[n]){
	auto p = std::cout.precision(3);
	for (int i = 0; i < n; i++){
			cout << fixed <<std::setw(8)  << arr[i] << " ";
	}
	cout << endl;
	std::cout.precision(p);
}

template <size_t n, size_t m>
void arr_show(const double (&arr)[n][m]){
   auto p = std::cout.precision(4);
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			cout << std::setw(8)  << std::defaultfloat << arr[i][j] << " ";
		}
		cout << endl;
	}
	std::cout.precision(p);
}

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
double check_answer(const double x,const double (&arr)[n]){
	double summ = 0;
	for (int i = 0; i < n; i++){
		summ += arr[i] * pow(x,i);
	}
	return summ;
}

int main(){
	// const int n = 5;  // wiki example https://ru.wikipedia.org/wiki/Интерполяционный_многочлен_Лагранжа
	// double x[n] = {-1.5, -0.75, 0, 0.75, 1.5};
	// double y[n] = {-14, -0.931596, 0 ,0.931596,14.1014};
	const int n = 6;  
	double x[n] = {0.15, 0.155, 0.16, 0.165, 0.17, 0.175};
	double y[n] = {6.61695, 6.39989, 6.19658, 6.00551, 5.82558, 5.65583};
	double vandermond_matrix[n][n+1] = {0};
	double arr_answer[n] = {0};// an,an-1 ... a1,a0 
	
	arr_show(x);
	arr_show(y);
	init_vandermond_matrix(x, y, vandermond_matrix);
	cout << endl;
	arr_show(vandermond_matrix);
	isJoint(vandermond_matrix, arr_answer);
	cout<< endl;
	arr_show(arr_answer);
	show_degree_x(arr_answer);
	cout << check_answer(x[0], arr_answer) << endl;

	return 0;
}

