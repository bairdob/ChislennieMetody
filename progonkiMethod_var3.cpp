//progonkiMethod.cpp
#include <iostream>
#include <iomanip> // setw()
using namespace std;


void arr_show(double arr[4][6],int n,int m){
	auto p = std::cout.precision(3);
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			cout << std::setw(8) << arr[i][j] << " ";
		}
		cout << endl;
	}
	std::cout.precision(p);
}
double calc_koef_p (double arr[4][6],int n,int m, double &p, int iteration){
	double p_i_plus_one;
	double c, b, a;
	int i = iteration;
	c = arr[i][i+2]; 	//cout <<"c = "<< c << endl;
	if ((i + 1) == n) c = 0;
	b = -arr[i][i+1];	//cout <<"b = "<< b << endl;
	a = arr[i][i];		//cout <<"a = "<< a << endl;
	p_i_plus_one = c / (b - a*p);
	p = p_i_plus_one;
	return p_i_plus_one;
	
}

double calc_koef_q (double arr[4][6],int n,int m, double &p, double &q,int iteration){
	double q_i_plus_one;
	double d, b, a;
	int i = iteration;
	d = arr[i][m-1];	//cout <<"d = "<< d << endl;
	b = -arr[i][i+1];	//cout <<"b = "<< b << endl;
	a = arr[i][i];		//cout <<"a = "<< a << endl;
	q_i_plus_one = (a * q - d) / (b - a*p);
	q = q_i_plus_one;
	return q_i_plus_one;
	
}

void arr_show(double *arr, int n){
	auto p = std::cout.precision(5);
	for (int i = 0; i < n; i++) {
		cout << std::setw(10)<<arr[i];
		if (i < 2) cout << " "; 
	}
	cout << endl;
	std::cout.precision(p);
}
void calc_answer(double arr_p[],double arr_q[], double *arr_answer,int n){
	arr_answer[n-1] = arr_q[n]; 
	for (int i = n-2; i >= 0; i--){
		arr_answer[i] = arr_q[i+1] + arr_p[i+1] * arr_answer[i+1]; 
	}

}


int main(){
	const int n = 4; //variant 3
	const int m = 6; 
	double arr[n][m] = {{0, 6, -1, 0, 0, 10.4}, 
						{0, 1, 7, -1, 0, 6.7},
						{0, 0, 1, 9, -5, 14.2},
						{0, 0, 0, 1, 5,  8.5}};
	double arr_p[m-1] = {0};
	double arr_q[m-1] = {0};
	double arr_answer[n] = {0};
	double p = 0;
	double q = 0;
	arr_show(arr, n, m);
	for (int i = 0; i < m-1; i++){
		arr_q[i+1] = calc_koef_q(arr, n, m, p, q, i);
		arr_p[i+1] = calc_koef_p(arr, n, m, p, i);
	}
	cout << "p ="; arr_show(arr_p,m-1);
	cout << "q ="; arr_show(arr_q,m-1);
	calc_answer(arr_p,arr_q,arr_answer,n);
	cout << "x ="; arr_show(arr_answer,n);
	return 0;
}