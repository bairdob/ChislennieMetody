//quadraticApprox.cpp
#include <iostream>
#include <iomanip> // setw()
#include "GaussMethod.cpp"
using namespace std;


template <size_t n>
void arr_show(const double (&arr)[n]){
	auto p = std::cout.precision(6);
	for (int i = 0; i < n; i++){
			cout << std::setw(6)  << arr[i] << " ";
	}
	cout << endl;
	std::cout.precision(p);
}


template <size_t n, size_t m>
void arr_show(const double (&arr)[n][m]){
   auto p = std::cout.precision(4);
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			cout << std::setw(8)  << arr[i][j] << " ";
		}
		cout << endl;
	}
	std::cout.precision(p);
}

template <size_t n>
double calc_a_ij(const double (&x)[n], size_t deg){
	double summ = 0;
	for (int i = 0; i < n; i++){
		summ += pow(x[i], deg);
	}
	return summ;
}

template <size_t n>
double calc_vector(const double (&x)[n], double (&y)[n],size_t deg){
	double summ = 0;
	for (int i = 0; i < n; i++){
		summ += pow(x[i], deg) * y[i];
	}
	return summ;
}

template <size_t n>
void calc_matrix(const double (&x)[n], double (&y)[n], double arr[3][4]){
	for (int i = 0; i < 3; i++){
		arr[0][i] = calc_a_ij(x, 4-i);
	}
	for (int i = 0; i < 3; i++){
		arr[1][i] = calc_a_ij(x, 3-i);
	}
	for (int i = 0; i < 3; i++){
		arr[2][i] = calc_a_ij(x, 2-i);
	}
	arr[2][2] = n;
	for (int i = 0; i < 3; i++)
		arr[i][3] = calc_vector(x, y, 2-i);

}



int main(){
	//const int n = 5; //cherkasov 7.1.4
	// double x[n] = {-2, -1, 0, 1, 2};
	// double y[n] = {3, 4, 2, 1,1};

	const int n = 11;
	double x[n] = {0, 0.12, 0.19, 0.35, 0.4, 0.45, 0.62, 0.71, 0.84, 0.91, 1.0};
	double y[n] = {1.1, 1.0, 0.7, 0.8, 0.3, 0.7, 0.4, 0.6, -0.3, -0.9, -0.9};
	double arr[3][4] = {0};
	double ex_arr[3][4] = {0};
	double arr_answer[3] = {0};

	arr_show(x);
	arr_show(y);
	cout << endl;
	calc_matrix(x, y, arr);
	arr_show(arr);
	isJoint(arr, 3, 4, ex_arr,arr_answer);
	return 0;
}