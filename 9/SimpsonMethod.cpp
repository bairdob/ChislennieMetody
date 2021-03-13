//SimpsonMethod.cpp 
#include <iostream>
#include <iomanip> // setw()
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

double f(double x){ 
	//double f_x = cos(x) / (x+2); // example Дружинин 14.2
	double f_x = exp(-x*x);
	return f_x;
}

template <size_t n>
void init_arr_x(double (&x)[n], const double &a, const double &b){
	double h = (b-a) / (n-1);
	for (int i = 0; i < n; i++) x[i] = a + i*h;
}

template <size_t n>
void init_arr_y(const double (&x)[n], double (&y)[n]){
	for (int i = 0; i < n; i++){
		y[i] = f(x[i]);
	}
}

template <size_t n>
double calc_integral(const double (&y)[n],const double &a, const double &b ){
	double summ = 0;
	double h = (b-a) / (n-1);
	double chetn = 0;
	double ne_chetn = 0;
	for (int i = 1; i < n-1; i++){
		if (i % 2 != 0) ne_chetn += y[i];
			else chetn += y[i];
	}
	summ = (h/3)*(y[0] + y[n-1] + 4*ne_chetn + 2*chetn);
	return summ;
}

int main(){
	const int n = 11;  //n+1
	double x[n] = {0};
	double y[n] = {0};
	double a = 0; 
	double b = 1;
	
	init_arr_x(x, a, b);
	cout << "x = "; arr_show(x);
	init_arr_y(x, y);
	cout << "y = "; arr_show(y);
	cout << "I = "<< calc_integral(y, a, b);

	return 0;
}

