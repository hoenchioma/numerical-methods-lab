#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100; // max size of matrix

// Function to get cofactor of a[p][q] in res[][]. n is current dimension of a[][]
void cofactor(double a[N][N], double res[N][N], int p, int q, int n) {
  int i = 0, j = 0;

  // Looping for each element of the matrix
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      //  Copying into temporary matrix only those element
      //  which are not in given row and column
      if (row != p && col != q) {
        res[i][j++] = a[row][col];

        // Row is filled, so increase row index and reset col index
        if (j == n - 1) j = 0, i++;
      }
    }
  }
}

/* Recursive function for finding determinant of matrix.
   n is current dimension of a[][]. */
double determinant(double a[N][N], int n) {
  double d = 0;  // Initialize result

  //  Base case : if matrix contains single element
  if (n == 1) return a[0][0];

  double cofac[N][N];  // To store cofactors

  int sign = 1;  // To store sign multiplier

  // Iterate for each element of first row
  for (int f = 0; f < n; f++) {
    // Getting Cofactor of a[0][f]
    cofactor(a, cofac, 0, f, n);
    d += sign * a[0][f] * determinant(cofac, n - 1);

    // terms are to be added with alternate sign
    sign = -sign;
  }

  return d;
}

// Function to get adjoint of a[N][N] in adj[N][N].
void adjoint(double a[N][N], double adj[N][N], int n) {
  if (N == 1) {
    adj[0][0] = 1;
    return;
  }

  // cofac is used to store cofactors of a[][]
  int sign = 1;
  double cofac[N][N];

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      // Get cofactor of a[i][j]
      cofactor(a, cofac, i, j, n);

      // sign of adj[j][i] positive if sum of row
      // and column indexes is even.
      sign = ((i + j) % 2 == 0) ? 1 : -1;

      // Interchanging rows and columns to get the
      // transpose of the cofactor matrix
      adj[j][i] = (sign) * (determinant(cofac, n - 1));
    }
  }
}

// Function to calculate and store inverse, returns false if
// matrix is singular
bool inverse(double a[N][N], double inv[N][N], int n) {
  // Find determinant of A[][]
  double det = determinant(a, n);
  if (det == 0) {
    cout << "Singular matrix, can't find its inverse";
    return false;
  }

  // Find adjoint
  double adj[N][N];
  adjoint(a, adj, n);

  // Find Inverse using formula "inverse(A) = adj(A)/det(A)"
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) inv[i][j] = adj[i][j] / det;
  }

  return true;
}

// Generic function to display the matrix.
void display(double a[N][N]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) cout << a[i][j] << " ";
    cout << endl;
  }
}

// Driver program
int main() {
  double a[N][N], adj[N][N], inv[N][N];
  int n;

  cout << "Enter size of square matrix A: " << endl;
  cin >> n;

  cout << "Enter matrix (A) values: " << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> a[i][j];
    }
  }

  cout << "Input matrix is :\n";
  display(a);

  cout << "\nThe Adjoint is :\n";
  adjoint(a, adj, N);
  display(adj);

  cout << "\nThe Inverse is :\n";
  if (inverse(a, inv, N)) display(inv);

  return 0;
}