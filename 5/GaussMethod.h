//GaussMethod.h

template <size_t n, size_t m>
void gaussMethod(double (&arr)[n][m]){
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

template <size_t n, size_t m>
void answer(double (&arr)[n][m], double (&answer)[n]){// ответы справо налево
 	answer[n-1]=arr[n-1][n]/arr[n-1][n-1];
    for (int i = n-2; i >= 0; i-- )
    {
        double buf =0;
        for (int j = i+1 ; j < n ; j++)
            buf=buf+arr[i][j]*answer[j];
        answer[i]=1.0/arr[i][i]*(arr[i][n]-buf);
    }
}

template <size_t n, size_t m>
void isJoint(double (&arr)[n][m], double (&arr_answer)[n]){
	gaussMethod(arr);
	answer(arr, arr_answer);
	//arr_show(arr_answer);		
}
