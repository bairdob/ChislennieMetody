//RungeKutta4degMethod.cpp 
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

double calc_right_side_equation(const double &x, const double &y){
	//double right = y * (1-x); // example 80 zenkov 
	//double right = y / (2*x); //example cherkasov page 63
	double right = (1-y*y)*cos(x) + 0.5*y; 
	return right;
}

template <size_t n>
void init_arr_r(const double &x0, const double &y0,  const double &h, double (&r)[n]){
	r[0] = h * calc_right_side_equation(x0, y0);	
	double temp_x0 = x0 + h/2; 
	double temp_y0 = y0 + r[0]/2;
	r[1] = h * calc_right_side_equation(temp_x0, temp_y0);
	temp_x0 = x0 + h/2;
	temp_y0 = y0 + r[1]/2;
	r[2] = h*calc_right_side_equation(temp_x0,temp_y0);
	temp_x0 = x0 + h;
	temp_y0 = y0 + r[2];
	r[3] = h*calc_right_side_equation(temp_x0,temp_y0);
}

template <size_t n>
double  calc_answer(double &y_k, const double (&r)[n]){
	double y_k_plus_one = y_k + (r[0] + 2*r[1] + 2*r[2] +r[3]) / 6;
	y_k = y_k_plus_one;
	return y_k_plus_one;
}



int main(){
	// double a = 0; // example 80 zenkov 
	// double b = 0.5;
	// double h = 0.05;
	// double x0 = 0; 
	// double y0 = 1;

	// double a = 1; //example cherkasov page 63
	// double b = 10;
	// double h = 1.8;
	// double x0 = 1; 
	// double y0 = 2;

	double a = 0; 
	double b = 1;
	double h = 0.1;
	double x0 = 0; 
	double y0 = 0;

	double r[4] = {0};

	int iteration = (b-a)/h;
	for (int i = 0; i < iteration; i++){
		init_arr_r(x0 + h*i, y0, h, r);
		cout << "x = "<<x0+h*(i+1) ;
		//cout << "r = "; arr_show(r);
		cout <<std::setw(10)<< " y = "<<calc_answer(y0, r)<<endl;
	}

	return 0;
}

