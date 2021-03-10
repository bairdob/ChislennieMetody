//NewtonPolinom.cpp
#include <iostream>
#include <iomanip> // setw()
//#include "GaussMethod.h"
using namespace std;


template <size_t n>
void arr_show(const double (&arr)[n]){
	auto p = std::cout.precision(4);
	for (int i = 0; i < n; i++){
			cout <<std::setw(8)  << arr[i] << " ";
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
void copy_arr(double (&arr1)[n],double (&arr2)[n]){
	memcpy(arr1,arr2, sizeof(double)*n);
}

template <size_t n>
void init_delta_y(const double (&y)[n], double (&delta_y)[n-1]){
	double temp[n] = {0};
	double temp1[n-1][n] = {0};
	for (int i = 0; i < n - 1; i++){//заполняем таблицу конечных разностей
		temp1[0][i] = y[i+1] - y[i];
	}
	for (int k = 0; k < n-1; k++){ 
		for (int i = 0; i < n - 1; i++){
			temp1[k+1][i] = temp1[k][i+1] - temp1[k][i];
			if (temp1[k][i+1] == 0) temp1[k+1][i] = 0;
		}
	}
	for (int i = 0; i < n - 1; i++){
		delta_y[i] = temp1[i][0];
	}
	//arr_show(delta_y);
}

int factorial(const int n){
	int fact = 1;
	if (n == 0) return 1; // 0!=1
	for (int i = 1; i < n+1; ++i){
		fact *= i;
	}
	return fact;
}
template <size_t n>
void show_polinom(double (&x)[n], double (&y)[n], double (&delta_y)[n-1]){
	cout << endl;
	//arr_show(delta_y);
	double h = x[n-1] - x[n-2];
	cout << "слагаемые полинома Ньютона: (построчно, без приведения подобных)" << endl;
	cout << y[0];
	for (int m = 0; m < n-1; m++){
		int k = m;
		cout << endl;
		cout << showpos	<<delta_y[k] / (factorial(k+1)*pow(h,k+1));
		while (k != -1){
			cout << noshowpos << "(x-" << x[k]<<")";
			k--;
		}
	}
	cout << endl;
}

template <size_t n>
double calc_polinom_x(double (&x)[n],const double (&y)[n], double (&delta_y)[n-1], double x0){
	double summ = y[0];
	double h = x[n-1] - x[n-2];
	for (int m = 0; m < n-1; m++){
		int k = m;
		double temp = delta_y[k] / (factorial(k+1)*pow(h,k+1));
		double temp1 = 1;
		for (k = m; k>-1;k-- )temp1 *=(x0-x[k]);
		summ += temp*temp1;
	}
	return summ;
}


int main(){
	const int n = 6;  
	double x[n] = {0.15, 0.155, 0.16, 0.165, 0.17, 0.175};
	double y[n] = {6.61695, 6.39989, 6.19658, 6.00551, 5.82558, 5.65583};
	// const int n = 4; // cherkasov page 53
	// double x[n] = {0, 1, 2, 3};
	// double y[n] = {-5, -6, 3, 28};
	double delta_y[n-1] = {0};
	double x0 = 0.1521;

	arr_show(x);
	arr_show(y);
	init_delta_y(y, delta_y);
	show_polinom(x, y, delta_y);
	cout << endl << "f(" << x0 << ") = " << calc_polinom_x(x, y, delta_y, x0);

	return 0;
}

