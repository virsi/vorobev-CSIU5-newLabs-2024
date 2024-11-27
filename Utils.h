#pragma once

typedef double (*TPF)(double);
typedef double (*TPM)(TPF f, double a, double b, int n);

struct I_print {	  //данные для печати результатов интегрирования
    const char* name; //название функции
    double i_sum;	  //значение интегральной суммы
    double i_toch;	  //точное значение интеграла
    int n;	          //число разбиений области интегрирования, при котором достигнута требуемая точность
};

void PrintTabl(I_print i_prn[], int k);
void Do(TPM method);
void h1(const char* s);
void ProgramExecution();