//konechnihRaznosteyMethod.cpp 
#include <iostream>
#include <iomanip> // setw()
#include <cmath>
#include "progonkiMethod.h"
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
void init_x(double (&x)[n], const double &a, const double &b){
	double h = (b-a) / (n-1);
	for (int i = 0; i < n; ++i){
		x[i] = a + i*h;
	}
}

double k_x(double x){
	//double k_x = 2*x*x; //cherkasov page 83
	// double k_x = 2; //cherkasov page 85
	double k_x = 1; 
	return k_x;
}

double l_x(double x){
	// double l_x = x;	//cherkasov page 83
	// double l_x = 2;	//cherkasov page 85
	double l_x = x;
	return l_x;
}

double m_x(double x){
	// double m_x = 1;	//cherkasov page 83
	//double m_x = -4;	//cherkasov page 85
	double m_x = 1;
	return m_x;
}

double f_x(double x){
	// double f_x = 2*sqrt(x);	//cherkasov page 83
	// double f_x = 1 - 2*x;	//cherkasov page 85
	double f_x = x + 1;
	return f_x;
}

template <size_t n>
double calc_a_i(const double (&x)[n], int i, double h){
	double a_i = k_x(x[i]) / (h*h) - l_x(x[i]) / (2*h); 
	return a_i;
}

template <size_t n>
double calc_b_i(const double (&x)[n], int i, double h){
	double b_i = -(2*k_x(x[i]) / (h*h) - m_x(x[i])); 
	return b_i;
}

template <size_t n>
double calc_c_i(const double (&x)[n], int i, double h){
	double c_i = k_x(x[i]) / (h*h) + l_x(x[i]) / (2*h); 
	return c_i;
}

template <size_t n, size_t m_>
void init_matrix(double (&arr)[n][m_], const double (&x)[n],const double &a, const double &b){
	int i = 1;
	double k = k_x(x[i]), l = l_x(x[i]), m = m_x(x[i]);
	// double r = 0, s = 1, v = 0, w = 1, z = 2*sqrt(10), t = 2; //cherkasov page 83
	// double r = 0, s = 1, v = 2, w = 4, z = 9, t = 1; //cherkasov page 83
	double r = 2, s = 1, v = 1, w = 0, z = 1.2, t = 1; 
	double h = (b-a) / (n-1);
	arr[0][1] = -(r/h - s);	//b_1
	arr[0][2] = r/h;	//c_1
	arr[n-1][m_-3] = -v / h;	//a_n
	arr[n-1][m_-2] = v/h + w;	//b_n
	arr[0][m_-1] = t; //d_1
	arr[n-1][m_-1] = z;	//d_n
	for (int i = 1; i < n-1; i++){
		for (int j = 0; j < m_; j++){
			if (i == j) arr[i][j+1] = calc_b_i(x, i , h);	//b_i
			if (i-1 == j) arr[i][j+1] = calc_a_i(x, i , h);	//a_i
			if (i == j-1) arr[i][j+1] = calc_c_i(x, i , h);	//a_i
		}
	}
	for (int i = 1; i < n-1; i++){ 
		arr[i][m_-1] = f_x(x[i]);	//d_i 
	}
}

int main(){
	// double a = 1;  //cherkasov page 83
	// double b = 10;

	// double a = 0;  //cherkasov page 85
	// double b = 4;

	double a = 0.5;  //cherkasov page 85
	double b = 0.8;

	const int n = 5; // my var3 n = 4???
	double x[n] = {0};
	double y[n] = {0};
	double matrix[n][n+2] = {0};
	double arr_p[n+1] = {0};
	double arr_q[n+1] = {0};

	init_x(x, a, b);
	init_matrix(matrix, x, a, b);
	arr_show(matrix);

	cout << endl;
	calc_koef_p(arr_p, matrix);
	cout << "p = "; arr_show(arr_p);

	calc_koef_q(arr_p,arr_q,matrix);
	cout << "q = "; arr_show(arr_q);

	cout << endl;
	calc_y(arr_p, arr_q, y);
	cout << "x = "; arr_show(x);
	cout << "y = "; arr_show(y);

	return 0;
}

