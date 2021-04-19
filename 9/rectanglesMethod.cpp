//rectanglesMethod.cpp  https://ru.wikipedia.org/wiki/Метод_прямоугольников
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

double f(double x){ 
	//double f_x = sin(x); // example Cherkasov page 57
	double f_x = log10(x+2) / x;
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
double calc_integral_left(const double (&y)[n],const double &a, const double &b ){
	double summ = 0;
	double h = (b-a) / (n-1);
	for (int i = 0; i < n-1; i++){
		summ += y[i];
	}
	return summ*h;
}

template <size_t n>
double calc_integral_right(const double (&y)[n],const double &a, const double &b ){
	double summ = 0;
	double h = (b-a) / (n-1);
	for (int i = 1; i < n; i++){
		summ += y[i];
	}
	return summ*h;
}

template <size_t n>
double calc_integral_average(const double (&y)[n],const double &a, const double &b ){
	double summ = 0;
	double h = (b-a) / (n-1);
	for (int i = 1; i < n-1; i++){
		summ += y[i];
	}
	summ+=y[0]/2;
	summ+=y[n-1]/2;
	return summ*h;
}

int main(){
	const int n = 8+1; //n+1  
	double x[n] = {0};
	double y[n] = {0};
	double a = 1.2; 
	double b = 2;
	
	init_arr_x(x, a, b);
	cout << "x = "; arr_show(x);
	init_arr_y(x, y);
	cout << "y = "; arr_show(y);
	cout << "I = "<< calc_integral_left(y, a, b) << " - left" << endl;
	cout << "I = "<< calc_integral_right(y, a, b) << " - right" << endl;
	cout << "I = "<< calc_integral_average(y, a, b) << " - average" << endl;
	return 0;
}

