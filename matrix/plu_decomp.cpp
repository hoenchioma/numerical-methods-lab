#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
using namespace std;

const int N = 4;  // max size of matrix

// solve Ax = b
bool plu_decomp(double a[N][N], double p[N][N], double l[N][N], double u[N][N], int n) {
	// initializing variables
	// P = I, L = 0, U = A
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			p[i][j] = (i == j? 1: 0);
			l[i][j] = 0;
			u[i][j] = a[i][j];
		}
	}

  for (int i = 0; i < n-1; i++) {
    // find p for which abs(u[p][i]) is max 
    int p_ = -1; double p_val = -INFINITY;
    for (int j = i; j < n; j++) {
      if (abs(u[j][i]) > p_val) {
        p_ = j;
        p_val = abs(u[j][i]);
      }
    }
    if (u[p_][i] == 0) {
      cout << "Factorization not possible" << endl;
      return false;
    }

    if (p_ != i) {
      // swap row p and row i
      for (int k = 0; k < n; k++) swap(u[i][k], u[p_][k]);
      for (int k = 0; k < n; k++) swap(l[i][k], l[p_][k]);
      // column exchange (row exchange in transpose(p))
      for (int k = 0; k < n; k++) swap(p[k][i], p[k][p_]);
    }

    for (int j = i+1; j < n; j++) {
      double tmp = u[j][i] / u[i][i];
      for (int k = 0; k < n; k++) {
        u[j][k] -= tmp * u[i][k];
      }
      l[j][i] = -tmp;
    }
  }

  // L = L + I
  for (int i = 0; i < n; i++) {
  	l[i][i] += 1;
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
  double a[N][N] = {
  	{0, 0, -1, 1},
  	{1, 1, -1, 2},
  	{-1, -1, 2, 0},
  	{1, 2, 0, 2}
  };
  double p[N][N], l[N][N], u[N][N];
  plu_decomp(a, p, l, u, N);
  print(p, N, N);
  cout << endl;
  print(l, N, N);
  cout << endl;
  print(u, N, N);

  return 0;
}