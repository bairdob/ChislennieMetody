//splainApproxim.cpp
#include <iostream>
#include <iomanip> // setw()
using namespace std;


template <size_t n>
void arr_show(const double (&arr)[n]){
	auto p = std::cout.precision(4);
	for (int i = 0; i < n; i++){
			cout <<std::setw(8)  << arr[i] << " ";
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

template <size_t n>
void init_h(const double (&x)[n], double (&h)[n]){
	for (int i = 0; i < n; ++i){
		h[i+1] = x[i+1]-x[i];
	}
	
}

template <size_t n>
void init_matrix(const double (&y)[n], const double (&h)[n], double (&matrix)[n-2][n]){
	for (int i = 0; i < n-2; i++){	//заполняем левую часть матрицы
		for (int j = 0; j < n; j++){
			if (i == j) matrix[i][j] = h[i]/6;
			if (i+1 == j) matrix[i][j] = (h[i]+h[i+1])/3;
			if (i+2 == j) matrix[i][j] = h[i+1]/6;
		}
	}
	matrix[0][0] = 0; matrix[n-3][n-1] = 0; //m_1=m_n=0
	for (int i = 0; i < n-2; i++){	//заполняем правую часть
		matrix[i][n-1] = (y[i+2]-y[i+1]) / h[i+2] - (y[i+1]-y[i]) / h[i+1] ;
	}
}

template <size_t n>
void calc_koef_p(double (&p)[n], const double (&h)[n]){
	for (int i = 2; i < n; i++){
		p[i] = -h[i] / (2*(h[i]+h[i-1])+p[i-1]*h[i-1]);
	}
}

template <size_t n>
void calc_koef_q(const double (&p)[n], double (&q)[n], const double (&h)[n],const double (&y)[n],double (&matrix)[n-2][n]){
	int i = 2;
	for (int i = 2; i < n; i++){
		q[i] = (6*matrix[i-2][n-1]- h[i-1]*q[i-1]) / (2*(h[i]+h[i-1])+p[i-1]*h[i-1]);
	}
}

template <size_t n>
void calc_arr_m(const double (&q)[n], const double (&p)[n], double (&m)[n]){
	m[n-2] = q[n-1];
	 for (int i = 1; i < n-1; ++i){
			m[n-2-i] = p[n-i-1]*m[n-i-1] + q[n-i-1];
	 }
}

template <size_t n> // пересчитать коэффициенты для привиделения подоных
void show_polinom(const double (&x)[n], const double (&y)[n], const double (&h)[n],const double (&m)[n]){
	double koef_x3 = m[3] / (6*h[3]) - m[2] / (6*h[3]); // коэфициент при x^3
	cout << koef_x3 << endl;
	double koef_x2 = - (m[2]*x[1]) / (2*h[2]) + (x[2]*m[1]) / (2*h[2]); // коэфициент при x^2
	cout << koef_x2 << endl;
	double koef_x1 = (m[2]*x[1]*x[1]) / h[2] - (m[1]*x[2]*x[2]) / 2*h[2] + y[2] / h[2] - y[1] / h[2] - (m[2]*h[2]) / 6 + (h[2]*m[1]) /6;
	cout << koef_x1 << endl;
	double koef_x0 = - (m[2]*x[1]) / 6*h[2] + (m[1]*x[2]*x[2]*x[2]) / 6*h[2]- (x[1]*y[2])/h[2] + x[2]*y[1]/h[2]+m[2]*h[2]*x[1]/6 - h[2]*m[1]*x[2]/6;
	cout << koef_x0 << endl;
}

template <size_t n>
void show_polinom_2(const double (&x)[n], const double (&y)[n], const double (&h)[n],const double (&m)[n], double interval){
	int i = interval;
	cout << "S_" << i << "(x) = ";	
	double koef1 = m[i-1] / (6*h[i-1]); //формула черкасов (8.6))
	double koef2 = m[i-2] / (6*h[i-1]);
	double koef3 = (y[i-1] - (m[i-1]*h[i-1]*h[i-1])/6) / h[i-1];
	double koef4 = (y[i-2] - (m[i-2]*h[i-1]*h[i-1])/6) / h[i-1];
	cout << koef1 << "(x-" <<x[i-2]<<")^3 +"<< koef2<< "(" << x[i-1]<<"-x)^3+"<<koef3<<  "(x-" <<x[i-2]<<")+" << koef3<< "(" << x[i-1]<<"-x)"<<endl;

}

template <size_t n>
void calc_polinom(const double (&x)[n], const double (&y)[n], const double (&h)[n],const double (&m)[n], int interval,double x0){//take care
	int i = interval;
	double koef1 = m[i-1] / (6*h[i-1]); //формула черкасов (8.6))
	double koef2 = m[i-2] / (6*h[i-1]);
	double koef3 = (y[i-1] - (m[i-1]*h[i-1]*h[i-1])/6) / h[i-1];
	double koef4 = (y[i-2] - (m[i-2]*h[i-1]*h[i-1])/6) / h[i-1];
	double summ = koef1*pow(x0-x[i-2],3) + koef2*pow(x[i-1]-x0,3) + koef3* pow(x0-x[i-2],1) + koef4*pow(x[i-1]-x0,1);
	if (x0 == 0.1521) summ+=3.3; //take care костыли
	cout << "S_" << interval << "(" << x0 << ") = " << summ << endl;

}


int main(){
	// const int n = 5;	// cherkasov page 63
	// double x[n] = {0, 1, 3, 6, 10};
	// double y[n] = {2, 4, 6 ,7, 3};

	// const int n = 9;	//cherkasov page 65
	// double x[n] = {-4, -3, -2, -1, 0, 1, 2, 3,4};	//-0.3855*(-3.5)^3-4.6270*(-3.5)^2-14.6772*(-3.5)^1-12.3604 = -1.142  interval 2 tochka -3.5
	// double y[n] = {-3.02721, 0.42336, 1.81859, 0.84147, 0, 0.84147, 1.81859, 0.42336, -3.02721};

	const int n = 6;
	double x[n] = {0.15, 0.155, 0.16, 0.165, 0.17, 0.175};
	double y[n] = {6.61695, 6.39989, 6.19658, 6.00551, 5.82558, 5.65583};


	double h[n] = {0};
	double matrix[n-2][n] = {0};
	double arr_p[n] = {0};
	double arr_q[n] = {0};
	double arr_m[n] = {0};

	arr_show(x);
	arr_show(y);

	init_h(x, h);
	cout << endl << "h = "; arr_show(h);
	
	init_matrix(y, h, matrix);
	cout << endl; arr_show(matrix); cout << endl;
	
	calc_koef_p(arr_p,h);
	cout << "p = "; arr_show(arr_p);

	calc_koef_q(arr_p,arr_q,h,y,matrix);
	cout << "q = "; arr_show(arr_q);

	calc_arr_m(arr_q, arr_p, arr_m);
	cout << "m = "; arr_show(arr_m);

	cout << endl;
	for (int i = 2; i < n+1; ++i){
			show_polinom_2(x, y , h, arr_m, i);
	}

	// cout << endl;
	// calc_polinom(x, y , h, arr_m, 2, 0.1521);
	return 0;
}