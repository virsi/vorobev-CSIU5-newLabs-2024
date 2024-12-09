#include "Utils.h"
#include "mprinter.h"
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <random>

long long factorial(int n) {
    if (n == 0 || n == 1) return 1;
    else return n * factorial(n - 1);
}

void Clear(double** A, int N) {
    for (int i = 1; i < N; ++i)
        delete[] A[i];
    delete[] A;
}

// double** CreateMatrix(int N, int M) {
//     double** A = new double* [N];
//     for (int i = 1; i < N; ++i)
//     {
//         A[i] = new double[M];
//         for (int j = 1; j < M; ++j)
//             A[i][j] = 0;
//     }
//     return A;
// }

// void FillMatrix(double** A, int N, int M) {
//     for (int i = 1; i < N; i++) {
//         for (int j = 1; j < M; j++) {
//             if (i == 1) {
//                 A[i][j] = 1;
//             }
//             else {
//                 if (j == 1)
//                     A[i][j] = A[i - 1][j] / i;
//                 else
//                     A[i][j] = pow(A[i][1], j);
//             }
//         }
//     }
// }

double** CreateMatrix(int N, int M) {
    double** A = new double*[N];
    for (int i = 0; i < N; i++) {
        A[i] = new double[M];
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (i == j) {
                A[i][j] = 1;  // Главная диагональ
            } else if (i < j) {
                // Формула для элементов выше главной диагонали
                A[i][j] = 1 / pow(factorial(j), i);
            } else {
                // Формула для элементов ниже главной диагонали
                A[i][j] = pow(-1, i) / pow(factorial(j), i); 
            }
        }
    }

    return A;
}


Size GenerateMatrixSizes() {
    Size matrixSizes{};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribSize(8, 15);
    std::uniform_int_distribution<> distribPrecision(3, 8);
    
    matrixSizes.N = distribSize(gen);
    matrixSizes.M = distribSize(gen);
    matrixSizes.precision = distribPrecision(gen);

    return matrixSizes;
}

int GetConsoleWidth() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

void ProgrammStart() {
    Size matrixSizes = GenerateMatrixSizes();
    
    if (GetConsoleWidth() / matrixSizes.N < matrixSizes.precision + 2) {
        std::cout << "Невозможно напечатать матрицу!";
        return;
    }
   
    double** A = CreateMatrix(matrixSizes.N + 1, matrixSizes.M + 1);
    //FillMatrix(A, matrixSizes.N + 1, matrixSizes.M + 1);
    PrintDinamicMatrix(A, matrixSizes.N + 1, matrixSizes.M + 1);
    Clear(A, matrixSizes.N + 1);

    double B[10][10];

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            B[i][j] = 10 * i + j;

    std::cout << "Матрица B \n\n\n";
    PrintStaticMatrix(B);
}
