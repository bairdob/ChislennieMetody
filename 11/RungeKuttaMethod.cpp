//RungeKuttaMethod.cpp 
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

template <size_t n, size_t m>
void init_k(int i, double (&k)[m], const double (&x)[n], double (&y)[n], double (&z)[n], const double &h){
		k[0] = z[i-1];
		k[1] = f(x[i-1], y[i-1], z[i-1]); //k1z
		k[2] = z[i-1] + (h/2)*k[1];	//k2y
		k[3] = f(x[i-1] + h/2, y[i-1] + (h/2)*k[0], z[i-1] + (h/2)*k[1]); 	//k2z
		k[4] = z[i-1] + (h/2)*k[3];	//k3y
		k[5] = f(x[i-1] + h/2, y[i-1] + (h/2)*k[2], z[i-1] + (h/2)*k[3]); 	//k3z;
		k[6] = z[i-1] + (h)*k[5];	//k4y;
		k[7] = f(x[i-1] + h, y[i-1] + (h)*k[4], z[i-1] + (h)*k[5]); 	//k3z;;
}

template <size_t n>
void init_x(double (&x)[n], const double &h){
	for (int i = 1; i < n; ++i){
		x[i] = x[i-1] + h;
	}
}

template <size_t n, size_t m>
void init_y(int i, double (&y)[n], double (&k)[m], const double &h){
		y[i] = y[i-1] + (h/6)*(k[0] + 2*k[2] + 2*k[4] + k[6]);
}

template <size_t n, size_t m>
void init_z(int i,double (&z)[n], double (&k)[m], const double &h){
		z[i] = z[i-1] + (h/6)*(k[1] + 2*k[3] + 2*k[5] + k[7]);
}


int main(){
	double x0 = 0.5;
	double y0 = 1;
	double z0 = 1.2;
	double h = 0.1;
	const int n = 10+1;
	const int m = 8;
	double x[n] = {x0};
	double y[n] = {y0};
	double z[n] = {z0};
	double k[m] = {z0};

	for (int i = 1; i < n; ++i){
		init_x(x, h);
		init_k(i, k, x, y, z, h);
		//cout << "k = "; arr_show(k);
		init_y (i, y, k, h);
		init_z (i, z, k, h);
	}

	cout << "x = "; arr_show(x);
	cout << "y = "; arr_show(y);
	cout << "z = "; arr_show(z);
	return 0;
}

