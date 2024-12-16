#include "GaussJordan.h"
#include <iostream>
#include <random>
#include <iomanip>

double **SelectionMemory(size_t N, size_t M) {
	double **A = new double *[N];
	for (size_t i = 0; i < N; ++i) {
    	A[i] = new double[M];
  	}
  	return A;
}

void ClearMemory(double **A, size_t N) {
	for (size_t i = 0; i < N; ++i) {
    	delete[] A[i];
  	}
  	delete[] A;
}

void FillMatrix(double **A, double **B, size_t N, size_t M) {
  	double r = 0;
  	for (size_t i = 0; i < N; ++i) {
    	for (size_t j = 0; j < N; ++j) {
        	std::cin >> r;
        	A[i][j] = r;
        	B[i][j] = A[i][j];
      	}
    }

  	for (size_t i = 0; i < N; ++i) {
    	    for (size_t j = N; j < M; ++j) {
        	    if(i + N == j){
            	    A[i][j] = 1;
                	B[i][j] = 1;
            	} else {
                	A[i][j] = 0;
                	B[i][j] = 0;
            	}
      		}
    }
}

void FillMatrixString(double **C, size_t N){
  	double r = 0;
  	for (size_t i = 0; i < N; ++i) {
    	std::cin >> r;
      	C[i][0] = r;
    }
}

void PrintMatrix(double **A, size_t N, size_t M ) {
	for (size_t i = 0; i < N; ++i) {
    	for (size_t j = 0; j < M; ++j) {
    		std::cout << std::fixed << std::setw(kFormattedOutput) << std::setprecision(kInaccuracy) << A[i][j] << "\t";
    	}
    	std::cout << std::endl;
  	}
}

void PrintMatrixString(double **C, size_t N) {
	for (size_t i = 0; i < N; ++i) {
    	std::cout << C[i][0] << std::endl;
    }
}

void MultiplicationMatrix(double **A, double **B, size_t N, size_t M){
    double **S = SelectionMemory(N, N);
    for (size_t i = 0; i < N; ++i) {
    	for (size_t j = 0; j < M; ++j) {
        	S[i][j] = 0;
      	}
    }

	for(size_t i = 0; i < N; ++i){
    	for(size_t k = 0; k < N; k++){
        	for(size_t j = 0; j < N; ++j){
            	S[i][k] += B[i][j] * A[j][k+N];
        	}
    	}
	}
	PrintMatrix(S,  N, N);
}

void MultiplicationMatrixString(double **A, double **C, size_t N){
	double **S = SelectionMemory(N, 0);
    for (size_t i = 0; i < N; ++i) {
        S[i][0] = 0;
    }

    for(size_t i = 0; i < N; ++i){
        for(size_t j = 0; j < N; ++j){
            S[i][0] += C[j][0] * A[i][j+N];
        }
        std::cout << "x" << i+1 << " = " << S[i][0] << std::endl;
	}
}


void SolveInverseMatrix(double **A, double **B, double **C, size_t N, size_t M){
    for(size_t k = 0; k < N; k++){

    	if(A[k][k] == 0){
      		bool found = false;
        	for(size_t i = k+1; i < N; ++i){
            	if(A[i][k] != 0 ){
                	std::swap(A[k],A[i]);
                	found = true;
                	break;
            	}
        	}
        	if(!found){
            	std::cout << "Обратная матрица не существует" << std::endl;
            	return;
        	}
    	}

    	double diagonal = A[k][k];
    	for (size_t j = 0; j < M; ++j) {
        	A[k][j] /= diagonal;
        }
    	for(size_t i = k+1; i < N; ++i){
        	double factor = A[i][k];
        	for (size_t j = 0; j < M; ++j) {
            	    A[i][j] -= A[k][j] * factor;
            }
	    }
	}

	std::cout << "---------------------------------------" << std::endl;
	std::cout << "\tПрямой ход" << std::endl;
	PrintMatrix(A,  N, M);

	for(size_t h = N - 1; h < N; h--){

    	for(size_t i = h-1; i < N; i--){
        	double factor = A[i][h];
        	for (size_t j = M - 1; j < M; j--) {
                	A[i][j] -= A[h][j] * factor;
            }
    	}
	}
	std::cout << "---------------------------------------" << std::endl;
    std::cout << "\tОбратный ход" << std::endl;
    PrintMatrix(A,  N, M);
    std::cout << "---------------------------------------" << std::endl;
    MultiplicationMatrix(A, B,  N, N);
    std::cout << "---------------------------------------" << std::endl;
    MultiplicationMatrixString(A, C,  N);
}

int CycleApp::ContinueWork() {
    char userChoise = 'y';
    while (userChoise == 'y') {
		int N;
		std::cout << "Введите размер квадратной матрицы, N > 0, N - целое: ";
		std::cin >> N;
		if (N <= 0) {
			std::cout << "Невозможно создать матрицу размером " << N << " * " << N << std::endl;
			return 1;
		}
		size_t M = static_cast<int>(2*N);

		double **A = SelectionMemory(N, M);
		double **B = SelectionMemory(N, M);
		double **C = SelectionMemory(N, 0);

		std::cout << "Введите коэффициенты: " << std::endl;
		FillMatrix(A, B, N, M);
		std::cout << "Введите значения строк" << std::endl;
		FillMatrixString(C, N);

		std::cout << "---------------------------------------" << std::endl;
		PrintMatrix(A,  N, M);

		SolveInverseMatrix( B, A, C, N,  M);

		ClearMemory(A, N);
		ClearMemory(B, N);
		ClearMemory(C, N);

		std::cout << "Продолжить работу? (y/n):" << std::endl;
		std::cin >> userChoise;
    }
	return 0;
}
