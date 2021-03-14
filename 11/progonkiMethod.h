//progonkiMethod.h
#include <iostream>
#include <iomanip> // setw()
using namespace std;

template <size_t n, size_t m_>
void calc_koef_p(double (&p)[n+1], const double (&arr)[n][m_]){
	for (int i = 1; i < n; i++){
		p[i] = arr[i-1][i+1] / (-arr[i-1][i] - arr[i-1][i-1]*p[i-1]);
	}
}

template <size_t n, size_t m_>
void calc_koef_q(const double (&p)[n+1], double (&q)[n+1], const double (&arr)[n][m_]){
	for (int i = 1; i < n+1; i++){
		q[i] = (arr[i-1][i-1]*q[i-1] - arr[i-1][m_-1]) / (-arr[i-1][i] - arr[i-1][i-1]*p[i-1]);
	}
}

template <size_t n>
void calc_y(const double (&p)[n+1], const double (&q)[n+1], double (&y)[n]){
	y[n-1] = q[n];
	for (int i = 4; i > 0; i--){
		y[i-1] = q[i] + p[i]*y[i];
	}
}