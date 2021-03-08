//interpolation.cpp
#include <iostream>
#include <iomanip> // setw()
using namespace std;


template <size_t n>
void arr_show(double (&arr)[n]){
   auto p = std::cout.precision(6);
	for (int i = 0; i < n; i++){
			cout << std::setw(9)  << arr[i] << " ";
	}
	cout << endl;
	std::cout.precision(p);
}

double lagrange1(double* x, double* y, short n, double _x)
{
	double result = 0.0;

	for (short i = 0; i < n; i++)
	{
		double P = 1.0;

		for (short j = 0; j < n; j++)
			if (j != i)
				P *= (_x - x[j])/ (x[i] - x[j]);

		result += P * y[i];
	}	

	return result;
}

int main(){
	const int n = 6;
	double x[n] = {0.15, 0.155, 1.6, 1.65, 1.7, 1.75};
	double y[n] = {6.61695, 6.39989, 6.19658, 6.00551, 5.82558, 5.65583};

	arr_show(x);
	arr_show(y);

	cout << lagrange1(x,y,n,0.1521);

	return 0;
}