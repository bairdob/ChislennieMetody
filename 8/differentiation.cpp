//differentiation.cpp 
#include <iostream>
#include <iomanip> // setw()
#include "GaussMethod.h"
#include "LagrangePolinom.h"
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

template <size_t n>
void show_lagrange_polinom(const double (&arr)[n]){
	cout << "Lagrange Polinom " << endl << "P(x) = ";
	auto p = std::cout.precision(3);
	for (int i = 0; i < n; i++){
			cout << fixed << std::showpos << arr[i] << "*x^" << std::noshowpos << i << " ";
	}
	cout << endl;
	std::cout.precision(p);
}

template <size_t n>
void show_first_differential(const double (&arr)[n], const double (&x)[n], const double x0){
	auto p = std::cout.precision(4);
	double h = x[1] - x[0];

	double differential_o_h = (y(x0+h, arr) - y(x0, arr)) / h;
	cout << "P'(" << x0 << ") = " << differential_o_h << " + O(h)" <<endl;

	double differential_o_hh_1 = (y(x0+h, arr) - y(x0-h, arr)) / (2*h);
 	cout << "P'(" << x0 << ") = " << differential_o_hh_1 << " + O(h^2)" << endl;

 	double differential_o_hh_2 = (-3*y(x0, arr) + 4*y(x0+h, arr) - y(x0+2*h, arr)) / (2*h);
 	cout << "P'(" << x0 << ") = " << differential_o_hh_2 << " + O(h^2)" << endl;

 	double differential_o_hhh = (-2*y(x0-h, arr) - 3*y(x0, arr) + 6*y(x0+h, arr)- y(x0+2*h, arr)) / (6*h);
 	cout << "P'(" << x0 << ") = " << differential_o_hhh << " + O(h^3)" << endl;

 	std::cout.precision(p);
}

template <size_t n>
void show_second_differential(const double (&arr)[n], const double (&x)[n], const double x0){
	auto p = std::cout.precision(4);
	double h = x[1] - x[0];
	double differential_o_hh = (y(x0+h, arr) - 2*y(x0, arr) + y(x0+2*h, arr)) / (h*h);
 	cout << "P''(" << x0 << ") = " << differential_o_hh << " + O(h^2)" << endl;
 	std::cout.precision(p);
}

int main(){
	const int n = 6;  
	double x[n] = {0.15, 0.155, 0.16, 0.165, 0.17, 0.175};
	double y[n] = {6.61695, 6.39989, 6.19658, 6.00551, 5.82558, 5.65583};
	double x0 = 0.1521;

	double vandermond_matrix[n][n+1] = {0};
	double arr_answer[n] = {0};// an,an-1 ... a1,a0 
	
	arr_show(x);
	arr_show(y);
	init_vandermond_matrix(x, y, vandermond_matrix);
	isJoint(vandermond_matrix, arr_answer);
	cout<< endl;
	show_lagrange_polinom(arr_answer);
	show_first_differential(arr_answer,x, x0);
	show_second_differential(arr_answer,x, x0);

	return 0;
}

