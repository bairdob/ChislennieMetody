//dihotomiiMethod.cpp
#include <iostream>
#include <iomanip> // setw()
using namespace std;


double calc_func(const double x){
	return pow(2,x)*x - 1;
}

double calc_second_diff(const double x){
	return log(x)*log(x)*pow(2,x)*x + log(x)*pow(2,1+x);
}

double calc_first_diff(const double x){
	return log(x)*pow(2,x)*x + pow(2,x);;
}

// double calc_func(const double x){
// 	return pow(x,2) - 2;
// }

// double calc_second_diff(const double x){
// 	return 2;
// }

// double calc_first_diff(const double x){
// 	return 2*x;
// }

double calc_a1(double &a0, double &a1){
	double a_1;
	a_1 = a0 - calc_func(a0) / calc_first_diff(a0);
	
	a1 = a_1;
	cout << "a0 = " << a0 << " a1 = "<< a1 << endl;
	a0 = a_1;
	return a_1;
}

bool is_condition(const double x){ //f(a0)f''(a0) > 0
	if (calc_func(x)*calc_second_diff(x) > 0) return true;
		else return false;
}

int main(){
	double a, b, a0, a1, temp;
	double eps = 0.01;
	a = 0; b = 8;
	a0 = b;
	
	temp = a0; 
	calc_a1(a0, a1);
	while (temp - a0 > eps){
		temp = a0;
		calc_a1(a0, a1);
	}	
	cout << "root = " << a0 << endl;

	return 0;
}