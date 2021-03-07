//rotationMethod.cpp
#include <iostream>
#include <iomanip> // setw()
using namespace std;


struct max_elem_data{
	double value;
	size_t row;
	size_t col;
	double angle;
};

template <size_t n, size_t m>
void arr_show(double (&arr)[n][m]){
   auto p = std::cout.precision(4);
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			cout << std::setw(8)  << arr[i][j] << " ";
		}
		cout << endl;
	}
	std::cout.precision(p);
}

template <size_t n, size_t m>
void copy_arr(double (&dest)[n][m],double (&resource)[n][m]){
	memcpy(dest, resource, sizeof(double)*n*m);
}

template <size_t n, size_t m>
double max_elem_above_diag(double (&arr)[n][m]){
	double max = abs(arr[0][1]);
	for (int i = 0; i < n-1; i++){
		for (int j = i+1; j < n; j++){
			if ((i < j) && (abs(arr[i][j]) >= max)){
				max = abs(arr[i][j]);
			}
		}
	}
	return max;
}

template <size_t n, size_t m>
double max_elem_row(double (&arr)[n][m]){
	double max = abs(arr[0][1]);
	int max_row;
	for (int i = 0; i < n-1; i++){
		for (int j = i+1; j < n; j++){
			if ((i < j) && (abs(arr[i][j]) >= max)){
				max = abs(arr[i][j]);
				max_row = i;
			}
		}
	}
	return max_row;
}

template <size_t n, size_t m>
double max_elem_col(double (&arr)[n][m]){
	size_t max_elem_col;
	double max = abs(arr[0][1]);
	for (int i = 0; i < n-1; i++){
		for (int j = i+1; j < n; j++){
			if ((i < j) && (abs(arr[i][j]) >= max)){
				max = abs(arr[i][j]);
				max_elem_col = j;
			}
		}
	}
	return max_elem_col;
}

template <size_t n, size_t m>
double angle(double (&arr)[n][m], size_t k, size_t l){
	double angle = 0;
	angle = atan(2*arr[k][l] / (arr[k][k]-arr[l][l])) / 2;
	//cout << "divisor = "<<(arr[k][k] - arr[l][l])<< endl;
	return angle;
}

template <size_t n, size_t m>
void calc_matrix_h1(double (&matrix_h1)[n][m], double angle){
	matrix_h1[0][0] = 1;
	matrix_h1[1][1] = cos(angle);
	matrix_h1[1][2] = -sin(angle);
	matrix_h1[2][2] = cos(angle);
	matrix_h1[2][1] = sin(angle);
}

template <size_t n, size_t m>
void calc_matrix_h2(double (&matrix_h2)[n][m], double angle){
	matrix_h2[0][0] = cos(angle);
	matrix_h2[0][1] = -sin(angle);
	matrix_h2[1][1] = cos(angle);
	matrix_h2[1][0] = sin(angle);
	matrix_h2[2][2] = 1;
}

template <size_t n, size_t m>
void calc_matrix_h3(double (&matrix_h3)[n][m], double angle){
	matrix_h3[0][0] = cos(angle);
	matrix_h3[0][2] = -sin(angle);
	matrix_h3[2][2] = cos(angle);
	matrix_h3[2][0] = sin(angle);
	matrix_h3[1][1] = 1;
}

template <size_t n, size_t m>
void transpose_matrix(double (&matrix_h)[n][m], double (&matrix_h_transpose)[n][m]){
	for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++)
            matrix_h_transpose[i][j] = matrix_h[j][i];
    }
}

template <size_t n, size_t m>
void multiply_matrix(double (&A)[n][m], double (&B)[n][m], double (&C)[n][m]){ //A*B=C
	for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++)
            C[i][j] = 0;
    }
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n 	; j++)
			for(int k = 0; k < n; k++){
				C[i][j]+=A[i][k]*B[k][j];
			}
}

template <size_t n, size_t m>
void calc_max_elem_struct(double (&arr)[n][m], max_elem_data &data){
	data.value = max_elem_above_diag(arr);
	data.row = max_elem_row(arr);
	data.col = max_elem_col(arr);
	data.angle = angle(arr, data.row, data.col);
}

void show_struct(const max_elem_data &data){
	cout << "max = " << data.value << " ["<<data.row <<"]["<<data.col <<"]"<< endl;
	cout << "angle = " << data.angle << endl;
}

template <size_t n, size_t m>
void calc_matrix_a1(double (&arr)[n][m], max_elem_data &data, double (&matrix_a1)[n][m], double (&matrix_mul)[n][m]){
	calc_max_elem_struct(arr, data); 
	show_struct(data);
	double temp[n][m] = {0}; 
	double matrix_h1[n][m] = {0};
	double matrix_h1_transpose[n][m] = {0};
	calc_matrix_h1(matrix_h1, angle(arr, data.row, data.col));
	transpose_matrix(matrix_h1,matrix_h1_transpose);
	//arr_show(matrix_h1_transpose);
	multiply_matrix(matrix_h1_transpose,arr,temp);
	//arr_show(temp);
	multiply_matrix(temp,matrix_h1,matrix_a1);
	cout << endl; arr_show(matrix_a1); 
	if (matrix_mul[0][0] == 0) {
		copy_arr(matrix_mul, matrix_h1);
	} else {
		double temp2[n][m] = {0};
		copy_arr(temp, matrix_mul);
		multiply_matrix(temp,matrix_h1,matrix_mul);
	}
}

template <size_t n, size_t m>
void calc_matrix_a2(double (&arr)[n][m], max_elem_data &data, double (&matrix_a2)[n][m], double (&matrix_mul)[n][m]){
	calc_max_elem_struct(arr, data);
	show_struct(data);
	double temp[n][m] = {0}; 
	double matrix_h2[n][m] = {0};
	double matrix_h2_transpose[n][m] = {0};
	calc_matrix_h2(matrix_h2, angle(arr, data.row, data.col));
	transpose_matrix(matrix_h2,matrix_h2_transpose);
	//arr_show(matrix_h2_transpose);
	multiply_matrix(matrix_h2_transpose,arr,temp);
	//arr_show(temp);
	multiply_matrix(temp,matrix_h2,matrix_a2);
	cout << endl; arr_show(matrix_a2); 
	if (matrix_mul[0][0] == 0) {
		copy_arr(matrix_mul, matrix_h2);
	} else {
		double temp2[n][m] = {0};
		copy_arr(temp, matrix_mul);
		multiply_matrix(temp,matrix_h2,matrix_mul);
	}
}

template <size_t n, size_t m>
void calc_matrix_a3(double (&arr)[n][m], max_elem_data &data, double (&matrix_a3)[n][m], double (&matrix_mul)[n][m]){
	calc_max_elem_struct(arr, data);
	show_struct(data);
	double temp[n][m] = {0}; 
	double matrix_h3[n][m] = {0};
	double matrix_h3_transpose[n][m] = {0};
	calc_matrix_h3(matrix_h3, angle(arr, data.row, data.col));
	transpose_matrix(matrix_h3,matrix_h3_transpose);
	//arr_show(matrix_h3_transpose);
	multiply_matrix(matrix_h3_transpose,arr,temp);
	//arr_show(temp);
	multiply_matrix(temp,matrix_h3,matrix_a3);
	cout << endl; arr_show(matrix_a3); 
	if (matrix_mul[0][0] == 0) {
		copy_arr(matrix_mul, matrix_h3);
	} else {
		double temp2[n][m] = {0};
		copy_arr(temp, matrix_mul);
		multiply_matrix(temp,matrix_h3,matrix_mul);
	}
}

//В качестве критерия окончания итерационного процесса используется условие 
//малости суммы квадратов внедиагональных элементов
template <size_t n, size_t m>
double calc_eps (double (&arr)[n][m]){
	double summ = 0;
	for (int i = 0; i < n-1; i++){
		for (int j = i+1; j < n; j++){
				summ += pow (arr[i][j],2);
			}
	}
	return sqrt(summ);
}

template <size_t n, size_t m>
void show_answer(double (&matrix_mul_h)[n][m], double (&arr)[n][m]){
	cout<< endl << "lambda = ";
	auto p = std::cout.precision(4);
	for (int i = 0; i < n; i++){
			cout << std::setw(8)  << arr[i][i] << " ";
	}
	cout<< endl << "matrix sobstvennih vectorov"<< endl;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			matrix_mul_h[i][j]/= matrix_mul_h[i][i]; //нормируем матрицу
			cout << std::setw(8)  << matrix_mul_h[i][j] << " ";
		}
		cout << endl;
	}
	std::cout.precision(p);
}


int main(){
	const size_t n = 3;
	const size_t m = 3;
	const size_t variant = 3;
	// double arr[n][m] = {{50 + 3*variant, 10 - variant, 3},
	// 					{10 - variant, 20 + 2*variant, 10 - variant},
	// 					{3, 10 - variant, 90 - variant}};
	double arr[n][m] = {{17, 1, 1},
						{1, 17, 2},
						{1, 2, 4}};
	// double arr[n][m] = {{4, 2, 1},
	// 					{2, 5, 3},
	// 					{1, 3, 6}};
	double matrix_a1[n][m] = {0};
	double matrix_a2[n][m] = {0};
	double matrix_a3[n][m] = {0};
	double matrix_mul_h[n][m] = {0};
	max_elem_data max;
	double eps = 0.01;

	arr_show(arr); 
	calc_max_elem_struct(arr, max); 

	while (eps < calc_eps(arr)){
		if (max.row == 1 && max.col == 2){ 
			calc_matrix_a1(arr,max, matrix_a1, matrix_mul_h);
			copy_arr(arr, matrix_a1);
			calc_max_elem_struct(arr, max);
		}
		
		if (max.row == 0 && max.col == 2){ 
			calc_matrix_a3(arr, max, matrix_a3, matrix_mul_h);
			copy_arr(arr, matrix_a3);
			calc_max_elem_struct(arr, max);
		}
		if (max.row == 0 && max.col == 1){ 
			calc_matrix_a2(arr, max, matrix_a2, matrix_mul_h);
			copy_arr(arr, matrix_a2);
			calc_max_elem_struct(arr, max);
		}
	}

	show_answer(matrix_mul_h, arr);

	return 0;
}