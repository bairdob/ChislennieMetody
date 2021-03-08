//sekushihMethod.cpp
#include <iostream>
#include <iomanip> // setw()
using namespace std;


double f(const double x){
	return pow(2,x)*x - 1;
}

double calc_c(const double a,const double b, double &c){
	c = (a*f(b) - b*f(a)) / (f(b) - f(a));
	return c;
}

void set_interval(double &a, double &b, double &c){
	calc_c(a,b,c);
	a = c; 
}

int main(){
	double a, b, c , temp;
	double eps = 0.01;
	a = 0; b = 8;

	do{		
		temp = c;
		set_interval(a,b,c);
		cout << c << endl;
	}
	while (abs(f(c)) > eps || abs(temp-c) > eps);
	cout << "root = "<<c;

	return 0;
}