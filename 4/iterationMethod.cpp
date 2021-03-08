//iterationMethod.cpp
#include <iostream>
#include <iomanip> // setw()
using namespace std;


// double f(const double x){
// 	return x*x*x - x*x + x - 5;
// }

// double g(const double x, double &x1){
// 	x1 = pow(x*x - x + 5,(1.0/3.0));
// 	return x1;
// }

// double g_dif(const double x){
// 	return (2*x -1) / (3*pow(x*x - x + 5,(2.0/3.0)));
// }

double f(const double x){
	return pow(2,x)*x - 1;
}

double g(const double x, double &x1){
	x1 = 1 / pow(2,x);
	return x1;
}

double g_dif(const double x){
	return -log(2) * pow(2,-x);
}



int main(){
	double a, b, x1 , temp;
	double eps = 0.01;
	a = 0; b = 8; x1 = 8;
	do{
		cout << g(x1, x1) << " ";
		cout <<g_dif(x1) << endl; 
	} while (abs(g_dif(x1)) < 1 && abs(f(x1)) > eps );
	cout << "root = " << x1;
	return 0;
}