#include "mprinter.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>


void PrintDinamicMatrix(double** A, int N, int M) {
    int width = GetConsoleWidth();
    for (int i = 1; i < N; i++)
    {
        for (int j = 1; j < M; j++) {
            int K = floor(width / M) - 1;
            if (A[i][j] > 0.01)
                std::cout << std::left << std::fixed << std::setw(K) << std::setprecision(K - 3) << A[i][j] << " ";
            else
                std::cout << std::left << std::fixed << std::setw(K) << std::setprecision(K - 7) << std::scientific << A[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "\n\n\n";
}

void PrintStaticMatrix(double B[10][10]) {
    double** A = new double* [10];
    for (int i = 0; i < 10; i++) {
        A[i] = new double[10];
        for (int j = 0; j < 10; j++) {
            A[i][j] = B[i][j];
        }
    }
    PrintDinamicMatrix(A, 10, 10);
    Clear(A, 10);
}