#include "Utils.h"
#include "mprinter.h"
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <random>

long long Factorial(int n) {
    if (n == 0 || n == 1) return 1;
    else return n * Factorial(n - 1);
}

void Clear(double** A, int N) {
    for (int i = 1; i < N; ++i) {
        delete[] A[i];
        A[i] = nullptr;
    }
    delete[] A;
    A = nullptr;
}

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
                A[i][j] = 1 / pow(Factorial(j), i);
            } else {
                // Формула для элементов ниже главной диагонали
                A[i][j] = pow(-1, i) / pow(Factorial(j), i);
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

    double** A = CreateMatrix(matrixSizes.N + 1, matrixSizes.M + 1);

    PrintMatrix(A, matrixSizes.N + 1, matrixSizes.M + 1, matrixSizes.precision, 1);
    //PrintMatrix(A, matrixSizes.N + 1, matrixSizes.M + 1, matrixSizes.precision, 2);

    double B[10][10];

    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            B[i][j] = 10 * i + j;

    std::cout << "Матрица B \n\n\n";
    PrintMatrix(B, 10);

    std::cout<<B<<"  "<<B[0]<<"  "<<B[2]<<std::endl;
    std::cout<<B[0][0]<<"  "<<**B <<"  "<<*B[0]<<std::endl;
    std::cout<<*(*(B+1))<<"  "<<*B[1]<<std::endl;
    std::cout<<*(B[0]+1)<<"  " <<*(*B+1)<<std::endl;
    std::cout<<B[0][9]<<"  "<<*(B[0]+20)<<"  "<<*B[2]<<std::endl;

    Clear(A, matrixSizes.N + 1);
}
