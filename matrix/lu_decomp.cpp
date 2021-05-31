#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
using namespace std;

// max size of matrices
const int N = 100;

// matrix a will be decomposed into lower triangular l and upper triangular u
// A = LU
// the main diagonal of l will consist of only 1s
// (swap the commented lines if u is needed with 1s in diagonal)
// returns false if factorization impossible, otherwise true
bool lu_decomp(double a[N][N], double l[N][N], double u[N][N], int n) {
  // step 1: set top left value
  if (a[0][0] == 0) return false; // factorization impossible
  // satisfy l[0][0] * u[0][0] == a[0][0]
  // l[0][0] = a[0][0], u[0][0] = 1;
  l[0][0] = 1, u[0][0] = a[0][0];

  // step 2
  for (int j = 1; j < n; j++) {
    u[0][j] = a[0][j] / l[0][0]; // 1st row of u
    l[j][0] = a[j][0] / u[0][0]; // 1st col of l
  }

  // step 3
  for (int i = 1; i < n-1; i++) {
    // step 4: set diagonal values
    double tmp = a[i][i];
    for (int k = 0; k < i; k++) {
      tmp -= l[i][k] * u[k][i];
    }
    if (tmp == 0) return false; // factorization impossible
    // satisfy l[i][i] * u[i][i] = a[i][i]
    // l[i][i] = tmp, u[i][i] = 1;
    l[i][i] = 1, u[i][i] = tmp;
    
    // step 5: fill i th row of u and i th col of l
    for (int j = i+1; j < n; j++) {
      double tmp1 = a[i][j];
      for (int k = 0; k < i; k++) {
        tmp1 -= l[i][k] * u[k][j];
      }
      u[i][j] = tmp1 / l[i][i];
      double tmp2 = a[j][i];
      for (int k = 0; k < i; k++) {
        tmp2 -= l[j][k] * u[k][i];
      }
      l[j][i] = tmp2 / u[i][i];
    }
  }

  // step 6: set bottom right value
  double tmp = a[n-1][n-1];
  for (int k = 0; k < n-1; k++) {
    tmp -= l[n-1][k] * u[k][n-1];
  }
  if (tmp == 0) return false;
  // satisfy l[n-1][n-1] * u[n-1][n-1] = a[n-1][n-1]
  // l[n-1][n-1] = tmp, u[n-1][n-1] = 1;
  l[n-1][n-1] = 1, u[n-1][n-1] = tmp; 
  
  return true;
}

// solve for x, when LUx = b
void solve(double l[N][N], double u[N][N], double b[N], double x[N], int n) {
  // solve L y = b
  static double y[N];
  y[0] = b[0] / l[0][0];
  for (int i = 1; i < n; i++) {
    double tmp = b[i];
    for (int j = 0; j < i; j++) {
      tmp -= l[i][j] * y[j];
    }
    y[i] = tmp / l[i][i];
  }

  // solve U x = y
  x[n-1] = y[n-1] / u[n-1][n-1];
  for (int i = n-2; i >= 0; i--) {
    double tmp = y[i];
    for (int j = i+1; j < n; j++) {
      tmp -= u[i][j] * x[j];
    }
    x[i] = tmp / u[i][i];
  }
}

int main() {
  double a[N][N], l[N][N], u[N][N];
  int n;

  cout << "Enter size of square matrix A: " << endl;
  cin >> n;

  cout << "Enter matrix (A) values: " << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> a[i][j];
    }
  }
  lu_decomp(a, l, u, n);
  cout << "L Decomposition is as follows..." << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << l[i][j] << " ";
    }
    cout << endl;
  }
  cout << "U Decomposition is as follows..." << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << u[i][j] << " ";
    }
    cout << endl;
  }

  double b[N], x[N];
  cout << "Enter b (Ax = b)" << endl;
  for (int i = 0; i < n; i++) cin >> b[i];

  solve(l, u, b, x, n);
  cout << "The solution is as follows..." << endl;
  for (int i = 0; i < n; i++) cout << x[i] << " ";
  cout << endl;

  return 0;
}
