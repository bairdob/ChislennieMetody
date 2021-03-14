//RungeKutta4degMethod.cpp 
#include <iostream>
#include <iomanip> // setw()
#include <cmath>
using namespace std;


template <size_t n>
void arr_show(const double (&arr)[n]){
	auto p = std::cout.precision(5);
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


double f_y(const double &x, const double &y){ //calc_right_side_equation
	//double right = (y-x) / (y+x); //example Katzman 6.2
	 double right = (1-y*y)*cos(x) + 0.5*y; 
	return right;
}

template <size_t n>
void init_arr_x_y_1_3(double (&x)[n], double (&y)[n]){	
	// x[0] = 0;		y[0] = 1;	//example Katzman 6.2
	// x[1] = 0.05;	y[1] = 1.0477;
	// x[2] = 0.1;		y[2] = 1.0912;
	// x[3] = 0.15;	y[3] = 1.1311;	

	x[0] = 0;	y[0] = 0;
	x[1] = 0.1;	y[1] = 0.102026;
	x[2] = 0.2;	y[2] = 0.206133;
	x[3] = 0.3;	y[3] = 0.309362;
}

template <size_t n>
void calc_y(double (&x)[n],double (&y)[n],const double &h){
	double y_n_plus_one;
	for (int i = 4; i<n;i++){
		x[i] = x[i-1] + h;
		y_n_plus_one = y[i-1] + (h/24) * (55*f_y(x[i-1],y[i-1]) - 59*f_y(x[i-2],y[i-2]) + 37*f_y(x[i-3],y[i-3]) - 9*f_y(x[i-4],y[i-4]));
		y_n_plus_one = y[i-1] + (h/24) * (9*f_y(x[i],y_n_plus_one) + 19*f_y(x[i-1],y[i-1]) - 5*f_y(x[i-2],y[i-2]) +f_y(x[i-3],y[i-3])); //уточним значение по интерполяционной формуле (а можно этого и не делать, тогда погрешность метода будет больше)
		y[i] = y_n_plus_one;
	}
}


int main(){
	const int n = 10 + 1;
	double h = 0.1;
	double x[n] = {0};
	double y[n] = {0};

	init_arr_x_y_1_3(x, y);
	calc_y(x, y, h);
	cout << "x = "; arr_show(x);
	cout << "y = "; arr_show(y);

	return 0;
}

