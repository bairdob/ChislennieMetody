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

double f(const double x, const double y, const double z){
	return x + 1 - x*z - y;
	//return -z / (2*x); //cherkasov page 77
}

template <size_t n>
void init_x(double (&x)[n], const double &h){
	for (int i = 1; i < n; ++i){
		x[i] = x[i-1] + h;
	}
}

template <size_t n>
void init_z_and_y(double (&z)[n], const double (&x)[n], double (&y)[n], const double &h){
	for (int i = 1; i < n; ++i){
		y[i] = y[i-1] + h*z[i-1];
		z[i] = z[i-1] + h*f(x[i-1],y[i-1],z[i-1]);
	}
}


int main(){
	double x0 = 0.5;
	double y0 = 1;
	double z0 = 1.2;
	double h = 0.1;
	const int n = 10+1;
	double x[n] = {x0};
	double y[n] = {y0};
	double z[n] = {z0};

	init_x(x, h);
	cout << "x = "; arr_show(x);
	init_z_and_y(z, x, y, h);
	//cout << "z = "; arr_show(z);
	cout << "y = "; arr_show(y);

	return 0;
}

