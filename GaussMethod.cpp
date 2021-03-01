//GaussMethod.cpp
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

double determinant(double arr[3][4],int n,int m){//triangle rule
	double plus = arr[0][0]*arr[1][1]*arr[2][2] + arr[0][1]*arr[1][2]*arr[2][0] + arr[0][2]*arr[1][0]*arr[2][1];
	double minus = arr[0][2]*arr[1][1]*arr[2][0] + arr[0][1]*arr[1][0]*arr[2][2] + arr[0][0]*arr[1][2]*arr[2][1];
	double determinant = plus - minus;
	return determinant;
}

void gaussMethod(double arr[3][4],int n,int m){
	float tmp;
    int k;
    for (int i = 0; i < n; i++){
        tmp = arr[i][i];
        for (int j = n; j >= i; j--){
            arr[i][j] /= tmp;
        }
        for (int j = i + 1; j<n; j++){
            tmp = arr[j][i];
            for (k = n; k >= i; k--)
                arr[j][k] -= tmp*arr[i][k];
        }
    }
}

void answer(double arr[3][4],int n,int m, double *answer){
	answer[2] = arr[2][3];
	answer[1] = arr[1][3]-arr[1][2]*answer[2];
	answer[0] = arr[0][3]-arr[0][2]*answer[2]-arr[0][1]*answer[1];
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

void fil_ex_arr(double first[3][4],int n,int m, double second[3][4]){
	memcpy(second, first, sizeof(double)*n*m);
	second[0][2]=second[0][3];
	second[1][2]=second[1][3];
	second[2][2]=second[2][3];
}

void isJoint(double arr[3][4],int n,int m,double ex_arr[3][4],double arr_answer[3]){//теорема кронекера-капели
	fil_ex_arr(arr, n, m,ex_arr);
	gaussMethod(arr, n, m);
	gaussMethod(ex_arr,n,m);

	double rangA = determinant(arr,n,m) * n;
	double rangAB = determinant(ex_arr,n,m) * n;
	const double eps = 0.0001;
	if ((fabs(rangA-rangAB) < eps) && (fabs(rangA-n) < eps)) {
		cout << "система совместна ";
		cout << endl; arr_show(arr, n, m);
		answer(arr,n,m,arr_answer);
		arr_show(arr_answer,n);
	} else {
		cout << "система несовместна" << endl;
	}
		
}


int main(){
	const int n = 3;
	const int m = 4; 
	double arr[n][m] = {{3.5,-2.12,-4.03,-7.5},
						{0.61,3.71,-0.05,0.44},
						{-1.03,-2.05,5.87,-1.16}};
	double ex_arr[n][m] = {0};
	double arr_answer[n] = {0};
	arr_show(arr, n, m);
	isJoint(arr, n, m, ex_arr,arr_answer);
	return 0;
}