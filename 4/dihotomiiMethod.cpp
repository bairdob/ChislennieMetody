//dihotomiiMethod.cpp
#include <iostream>
#include <iomanip> // setw()
using namespace std;


double calc_func(const double x){
	return pow(2,x)*x - 1;
}

double calc_eps (const double a, const double b){
	return abs(b-a);
}

void set_interval(double &a,double &b, double &c){
	auto p = std::cout.precision(4);

	cout <<left <<std::setw(8)<< a <<b <<endl;;
	 c = (a + b) / 2;
       if(calc_func(b) * calc_func(c) < 0)
            a = c;
        else
            b = c;

        std::cout.precision(p);
   }


int main(){
	double a, b, c;
	double eps = 0.01;
	a = 0; b = 8;
	
	cout <<left <<std::setw(8)<< "a" <<"b"<<endl;
	while (calc_eps(a,b) > eps){
		set_interval(a, b, c);
	}
	cout << "root = "<<(a+b) /2<<endl;

	return 0;
}