//simpleIterationMethod.cpp
#include <iostream>
#include <iomanip> // setw()
using namespace std;


void arr_show(double arr[3][4],int n,int m){
	auto p = std::cout.precision(2);
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			cout << std::setw(8)  << arr[i][j] << " ";
		}
		cout << endl;
	}
	std::cout.precision(p);
}

void arr_show(double *answer, int n){
	auto p = std::cout.precision(3);
	cout << "x = {";
	for (int i = 0; i < n; i++) {
		cout <<answer[i];
		if (i < 2) cout << ", "; 
	}
	cout << "}";
	std::cout.precision(p);
}

void init_freecol(double arr[3][4],int n,int m,double arr_ans1[3]){
	arr_ans1[0] = arr[0][3];
	arr_ans1[1] = arr[1][3];
	arr_ans1[2] = arr[2][3];
}

void calc_answer(double arr[3][4],int n,int m,double arr_ans1[3],double arr_ans2[3]){
	arr_ans2[0] = (arr[0][3]-arr[0][1]*arr_ans1[1]-arr[0][2]*arr_ans1[2]) / arr[0][0];
	arr_ans2[1] = (arr[1][3]-arr[1][0]*arr_ans1[0]-arr[1][2]*arr_ans1[2]) / arr[1][1];
	arr_ans2[2] = (arr[2][3]-arr[2][0]*arr_ans1[0]-arr[2][1]*arr_ans1[1]) / arr[2][2];
}

void copy_arr(double arr_ans1[3],double arr_ans2[3]){
	memcpy(arr_ans1,arr_ans2, sizeof(double)*3);
}

void copy_arr(double arr_ans1[3][4],double arr_ans2[3][4]){
	memcpy(arr_ans1,arr_ans2, sizeof(double)*12);
}

double norma_matrix(double arr_b[3][4],int n,int m){
	double norma_one = 0;
	double max_line = 0;
	for (int i = 0; i < n;i++){
		max_line = 0;
		for (int j = 0; j < n; j++){
			max_line += abs(arr_b[i][j]);
			
		}
		if (max_line > norma_one) norma_one = max_line;
	}
	double norma_two = 0;
	double max_column = 0;
	for (int j = 0; j < n;j++){
		max_column = 0;
		for (int i = 0; i < n; i++){
			max_column += abs(arr_b[i][j]);
			
		}
		if (max_column > norma_two) norma_two = max_column;
	}
	double min = norma_one;
	if (norma_two < min) min = norma_two;
	return min;
}

void init_arr_b(double arr[3][4],int n,int m, double arr_b[3][4]){
	copy_arr(arr_b,arr);
	double temp;
	//arr_show(arr_b,n,m);
	for (int i = 0; i < n;i++){
		for (int j = 0; j < m; j++){
			
			if (i == 0) arr_b[i][j] /= -arr[0][0];
			if (i == 1) arr_b[i][j] /= -arr[1][1];
			if (i == 2) arr_b[i][j] /= -arr[2][2];
			if (i == j) arr_b[i][j] = 0;
			if (j == 3) arr_b[i][j] = - arr_b[i][j];
		}
	}
	//arr_show(arr_b,n,m);
}

double calc_eps(double norma, int n,double norma_vector){
	double eps;
	eps = (pow(norma,n)* norma_vector) / (1-norma) ;
	return eps;
}

double norma_vector(double arr_b[3][4],int n,int m){
	double norma_vector = abs(arr_b[0][3]);
	for (int i = 0; i < n; i++){
		if (abs(arr_b[i][3]) > norma_vector) norma_vector = abs(arr_b[i][3]);
	}
	return norma_vector;
}

double calc_beta(double arr_ans1[3],double arr_ans2[3], int n){
	double norma_dif = 0;
	for (int i = 0;i < n; i++){
		if  (abs(arr_ans1[i] - arr_ans2[i])> norma_dif ) norma_dif = abs(arr_ans1[i] - arr_ans2[i]);
	}
	return norma_dif;
}


void show_answer(double arr[3][4],int n,int m,double arr_ans1[3],double arr_ans2[3],double arr_b[3][4],int iter){
	copy_arr(arr_ans1,arr_ans2);
	calc_answer(arr,n,m,arr_ans1,arr_ans2);
	arr_show(arr_ans2,n); 
	cout <<" eps = " << calc_eps(norma_matrix(arr_b, n, m),iter,norma_vector(arr_b, n, m));
	cout << " beta = " << calc_beta(arr_ans1,arr_ans2,n);
	cout << endl;
}


int main(){
	const int n = 3;
	const int m = 4; 
	// double arr[n][m] = {{3.5,-2.12,-4.03,-7.5},
	// 					{0.61,3.71,-0.05,0.44},
	// 					{-1.03,-2.05,5.87,-1.16}};	
	double arr[n][m] = {{20, 4, -8, 1},
						{-3, 15, 5, -2},
						{6, 3, -18, 3}};
	double arr_b[n][m] = {0};
	double eps = 0.01;
	double arr_ans1[n] = {0};
	double arr_ans2[n] = {0};
	double arr_answer[n] = {0};
	double arr_eps[n] = {0};
	init_arr_b(arr, n, m, arr_b);
	arr_show(arr, n, m);
	//init_freecol(arr, n, m, arr_ans1);
	//arr_show(arr_ans1,n);
	calc_answer(arr, n, m, arr_ans1, arr_ans2);
	arr_show(arr_ans2, n); cout <<endl;
	int iteration = 1;
	while (calc_eps(norma_matrix(arr_b, n, m),iteration,norma_vector(arr_b, n, m))>eps){
		show_answer(arr, n, m, arr_ans1, arr_ans2, arr_b,iteration);
		iteration++;
	}
	return 0;
}