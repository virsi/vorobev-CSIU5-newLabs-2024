#pragma once

struct Size {
    int N = 0;  //строки
    int M = 0;  //столбцы
    int precision = 0;  //точность вывода
};

void Clear(double** A, int N);
double** CreateMatrix(int N, int M);
void FillMatrix(double** A, int N, int M);
int GetConsoleWidth();
void ProgrammStart();