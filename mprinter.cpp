#include "mprinter.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>

void PrintMatrix(double** matrix, int n, int m, int precision, int format) {
  if (format == 1) {
    std::cout << std::fixed;
  } else if (format == 2) {
    std::cout << std::scientific;
  }

  int k = 0;
  int c = 80/(precision + 9);
  while (k < m) {
    for (int i = 0; i < n; ++i) {
      for (int j = k; j < k + c; ++j) {
        if (j < m) {
          if (format == 1) {
            std::cout << std::setw(5 + precision) << std::setprecision(precision)
                      << matrix[i][j];
          } else {
            std::cout << std::setw(5 + precision) << matrix[i][j];
          }
        } else {
          break;
        }
      }
      std::cout << std::endl;
    }

    k += 80/(precision + 9);

    std::cout << std::endl;
    for (int i = 0; i < 100; ++i) {
      if (k < m) {
        std::cout << "-";
      } else {
        std::cout << "=";
      }
    }
    std::cout << std::endl << std::endl;
  }

  if (format == 1) {
    std::cout.unsetf(std::ios_base::fixed);
  } else if (format == 2) {
    std::cout.unsetf(std::ios_base::scientific);
  }
}

void PrintMatrix(double B[10][10], int size) {
    double* A [10]{};
    for (int i = 0; i < size; i++) {
        A[i] = B[i];
    }
    PrintMatrix(A, 10, 10, 0, 1);
    Clear(A, 10);
}
