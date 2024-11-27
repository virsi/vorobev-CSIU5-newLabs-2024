#include "Utils.h"
#include <iostream>
#include <cmath>
#include <iomanip>

#include "CalculateIntegral.h"
#include "Utils.h"
#include "Functions.h"

void PrintTabl(I_print i_prn[], int k) {
    const char SIDE_SYBMOL = '|';
    const char HORIZONTAL_SYBMOL = '-';
    const char CONNECTOR_SYBMOL = '+';

    const int m = 4;                // число столбцов таблицы
    int wn[m] = {18, 18, 18, 10};   // ширина столбцов таблицы
    char *title[m] = {(char *) "Function", (char *) "Integral", (char *) "IntSum", (char *) "N "};
    int size[m];
    for (int i = 0; i < m; i++) {
        size[i] = (int) strlen(title[i]);
    }

    // шапка таблицы
    std::cout << CONNECTOR_SYBMOL << std::setfill(HORIZONTAL_SYBMOL);
    for (int j = 0; j < m - 1; j++)
        std::cout << std::setw(wn[j]) << CONNECTOR_SYBMOL;
    std::cout << std::setw(wn[m - 1]) << CONNECTOR_SYBMOL << std::endl;

    std::cout << SIDE_SYBMOL;
    for (int j = 0; j < m; j++)
        std::cout << std::setw((wn[j] - size[j]) / 2) << std::setfill(' ') << ' ' << title[j]
             << std::setw((wn[j] - size[j]) / 2) << SIDE_SYBMOL;
    std::cout << std::endl;

    // заполнение таблицы
    for (int i = 0; i < k; i++) {
        std::cout << CONNECTOR_SYBMOL << std::fixed;
        for (int j = 0; j < m - 1; j++)
            std::cout << std::setfill(HORIZONTAL_SYBMOL) << std::setw(wn[j]) << CONNECTOR_SYBMOL;
        std::cout << std::setw(wn[m - 1]) << CONNECTOR_SYBMOL << std::setfill(' ') << std::endl;

        std::cout << SIDE_SYBMOL << std::setw((int) (wn[0] - strlen(i_prn[i].name)) / 2) << ' ' << i_prn[i].name
             << std::setw((int) (wn[0] - strlen(i_prn[i].name)) / 2) << SIDE_SYBMOL;
        std::cout << std::setw(wn[1] - 1) << std::setprecision(10) << i_prn[i].i_toch << SIDE_SYBMOL
             << std::setw(wn[2] - 1) << i_prn[i].i_sum << std::setprecision(6) << SIDE_SYBMOL
             << std::setw(wn[3] - 1) << i_prn[i].n << SIDE_SYBMOL << std::endl;
    }

    // низ таблицы
    std::cout << CONNECTOR_SYBMOL << std::setfill(HORIZONTAL_SYBMOL);
    for (int j = 0; j < m - 1; ++j)
        std::cout << std::setw(wn[j]) << CONNECTOR_SYBMOL;
    std::cout << std::setw(wn[m - 1]) << CONNECTOR_SYBMOL << std::setfill(' ') << std::endl;
}

void h1(const char* s) {
    std::cout << std::setw(38) << s << "\n\n\n";
}

void Do(TPM method) {
    int a{};
    int b{};
    std::cout << "Введите пределы интегрирования (Формат ввода: int int)\n";
    std::cin >> a >> b;

    double epss[5] = { 0.01, 0.001, 0.0001, 0.00001, 0.000001 };

    const char* functions[4] = {
        "y=x ",
        "y=sin(22*x) ",
        "y=x^4 ",
        "y=arctg(x)  "
    };

    TPF Func[4] = {
        f1,
        f2,
        f3,
        f4
    };

    double Int[4] = {
        (b * b - a * a) / 2.0,
        (std::cos(a * 22.0) - std::cos(b * 22.0)) / 22.0,
        (b * b * b * b * b - a * a * a * a * a) / 5.0,
        (b * std::atan(b) - a * std::atan(a) - (std::log(b * b + 1) - std::log(a * a + 1)) / 2.0)
    };
    
    for (int epsIndex = 0; epsIndex < 5; ++epsIndex)
    {
        double eps = epss[epsIndex];

        I_print printData[4]{};
        for (int i = 0; i < 4; i++) {
            printData[i].name = functions[i];
            printData[i].i_sum = Int[i];
            printData[i].i_toch = Integrate(Func[i], method, a, b, eps, printData[i].n);
        }

        std::cout << std::setw(34) << "Precision: " << std::setprecision(epsIndex + 2) << eps << "\n";
        PrintTabl(printData, 4);
        std::cout << "\n\n\n";

    }
}

void ProgramExecution() {
    h1("Rectangle method");
    Do(IntRect);
    h1("Trapeze method");
    Do(IntTrap);
}