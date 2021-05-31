#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

const int N = 100;  // max size of matrix

// solve Ax = b
bool gaussian_elim(double a[N][N], double b[N], double x[N], int n) {
  // step 1
  for (int i = 0; i < n-1; i++) {
    // step 2
    int p = -1;
    for (int j = i; j < n; j++) {
      if (a[j][i] != 0) {
        p = j;
        break;
      }
    }
    if (p == -1) {
      cout << "No unique solution exists" << endl;
      return false;
    }

    // step 3
    if (p != i) {
      // swap row p and row i
      for (int k = 0; k < n; k++) swap(a[i][k], a[p][k]);
      swap(b[i], b[p]);
    }

    // step 4
    for (int j = i+1; j < n; j++) {
      // step 5
      double tmp = a[j][i] / a[i][i];
      // step 6: Ej = Ej - tmp * Ei
      for (int k = 0; k < n; k++) {
        a[j][k] -= tmp * a[i][k];
      }
      b[j] -= tmp * b[i];
    }
  }

  // step 7
  if (a[n-1][n-1] == 0) {
    cout << "No unique solution exists" << endl;
    return false;
  }

  // step 8: start back substitution
  x[n-1] = b[n-1] / a[n-1][n-1];

  // step 9: back substitution
  for (int i = n-2; i >= 0; i--) {
    double tmp = b[i];
    for (int j = i+1; j < n; j++) {
      tmp -= a[i][j] * x[j];
    }
    x[i] = tmp / a[i][i];
  }

  return true;
}

void print(double a[N][N], int m, int n) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      cout << fixed << setprecision(3);
      cout << a[i][j] << "\t";
    }
    cout << endl;
  }
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

  gaussian_elim(a, b, x, n);
  cout << "The solution is as follows..." << endl;
  for (int i = 0; i < n; i++) cout << x[i] << " ";
  cout << endl;

  return 0;
}