#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
using namespace std;

const int N = 100;  // max size of matrix

// solve Ax = b
bool gaussian_elim_part_pivot(double a[N][N], double b[N], double x[N], int n) {
  static int nrow[N];
  // step 1: initialize row pointer
  for (int i = 0; i < n; i++) nrow[i] = i;

  // step 2
  for (int i = 0; i < n-1; i++) {
    // step 3
    int p = -1; double p_val = -INFINITY;
    for (int j = i; j < n; j++) {
      if (abs(a[nrow[j]][i]) > p_val) {
        p = j;
        p_val = abs(a[nrow[j]][i]);
      }
    }

    // step 4
    if (a[nrow[p]][i] == 0) {
      cout << "No unique solution exists" << endl;
      return false;
    }

    // step 5
    if (nrow[i] != nrow[p]) {
      swap(nrow[i], nrow[p]); // simulated row exchange
    }

    // step 6
    for (int j = i+1; j < n; j++) {
      // step 7
      double tmp = a[nrow[j]][i] / a[nrow[i]][i];
      // step 8: Ej = Ej - tmp * Ei
      for (int k = 0; k < n; k++) {
        a[nrow[j]][k] -= tmp * a[nrow[i]][k];
      }
      b[nrow[j]] -= tmp * b[nrow[i]];
    }
  }

  // step 9
  if (a[nrow[n-1]][n-1] == 0) {
    cout << "No unique solution exists" << endl;
    return false;
  }

  // step 10: start back substitution
  x[n-1] = b[nrow[n-1]] / a[nrow[n-1]][n-1];

  // step 11: back substitution
  for (int i = n-2; i >= 0; i--) {
    double tmp = b[nrow[i]];
    for (int j = i+1; j < n; j++) {
      tmp -= a[nrow[i]][j] * x[j];
    }
    x[i] = tmp / a[nrow[i]][i];
  }

  return true;
}


int main() {
  double a[N][N], b[N], x[N];
  int n;

  cout << "Enter size of square matrix A: " << endl;
  cin >> n;

  cout << "Enter matrix (A) values: " << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> a[i][j];
    }
  }
  cout << "Enter b (Ax = b)" << endl;
  for (int i = 0; i < n; i++) cin >> b[i];

  gaussian_elim_part_pivot(a, b, x, n);
  cout << "The solution is as follows..." << endl;
  for (int i = 0; i < n; i++) cout << x[i] << " ";
  cout << endl;

  return 0;
}