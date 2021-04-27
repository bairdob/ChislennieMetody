//EulerMethod.cpp 
#include <iostream>
#include <iomanip> // setw()
#include <cmath>
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

double f(const double &x, const double &y){
	double f = (1 - pow(y,2)*cos(x) + 0.5*y); 
	return f;
}

template <size_t n>
void init_arr_x(double (&x)[n],const double &h){
	for (int i = 1; i < n; ++i){
		x[i] = x[i-1] + h; 
	}
}

template <size_t n>
void init_arr_y(const double (&x)[n], double (&y)[n],const double &h){
	for (int i = 1; i < n; ++i){
		y[i] = y[i-1] + h * f(x[i-1],y[i-1]);
	}
}

template <size_t n>
double  calc_answer(double &y_k, const double (&r)[n]){
	double y_k_plus_one = y_k + (r[0] + 2*r[1] + 2*r[2] +r[3]) / 6;
	y_k = y_k_plus_one;
	return y_k_plus_one;
}


int main(){
	double a = 0; 
	double b = 1;
	double h = 0.1;
	double x0 = 0; 
	double y0 = 0;
	const int n = 11; 
	double x[n] = {x0};
	double y[n] = {y0};
	int iteration = (b-a)/h;
	cout << "x = "; init_arr_x(x, h);
	arr_show(x);
	cout << "y = ";init_arr_y(x, y, h);
	arr_show(y);
	return 0;
}

