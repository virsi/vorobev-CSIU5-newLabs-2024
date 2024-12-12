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

// void PrintMatrix(double B[10][10], int size) {
//   for (int i = 0; i < size; ++i) {
//     for (int j = 0; j < size; ++j) {
//       std::cout << std::fixed << std::setw(6) << std::setprecision(0) << *(B[i] + j);
//     }
//     std::cout << std::endl;
//   }

//   std::cout.unsetf(std::ios_base::fixed);
//   std::cout << std::endl;
// }








// void PrintDinamicMatrix(double** A, int N, int M, int eps, char format) {
//     switch (format)
//     {
//     case 'B':
//         for (int i = 0; i < N; ++i)
//         {
//         for (int j = 1; j < M; ++j) {
//             std::cout << std::right << std::fixed << std::setw(6) << std::setprecision(0) << A[i][j] << " ";
//         }
//         std::cout << std::endl;
//         }
//         std::cout << "\n\n\n";
//         break;
//     case 'A':
//         for (int i = 1; i < N; ++i)
//         {
//             for (int j = 1; j < M; ++j) {
//                 std::cout << std::right << std::fixed << std::setw(eps + 4) << std::setprecision(eps) << A[i][j] << " ";
//             }
//             std::cout << std::endl;
//         }
//         std::cout << "\n\n\n";
//         break;
//     case 'a':
//         for (int i = 1; i < N; ++i)
//         {
//             for (int j = 1; j < M; ++j) {
//                 std::cout << std::right << std::scientific << std::setw(eps + 4) << std::setprecision(eps) << A[i][j] << " ";
//             }
//             std::cout << std::endl;
//         }
//         std::cout << "\n\n\n";
//         break;
//     }
    
// }

// void PrintStaticMatrix(double B[10][10]) {
//     double* A [10]{};
//     for (int i = 0; i < 10; i++) {
//         A[i] = B[i];
//     }
//     PrintDinamicMatrix(A, 10, 10, 2, 'B');
//     Clear(A, 10);
// }


// void PrintDinamicMatrix(double** A, int N, int M, int eps) {
//     int width = GetConsoleWidth();
//     for (int i = 1; i < N; ++i)
//     {
//         for (int j = 1; j < M; ++j) {
//             int K = floor(width / M) - 1;
//             if (A[i][j] > 1.0)
//                 std::cout << std::left << std::fixed << std::setw(K) << std::setprecision(K - 5) << A[i][j] << " ";
//             else
//                 std::cout << std::left << std::fixed << std::setw(K) << std::setprecision(eps) << A[i][j] << " ";
//         }
//         std::cout << std::endl;
//     }
//     std::cout << "\n\n\n";
// }