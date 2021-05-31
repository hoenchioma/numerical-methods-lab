#include <iostream>
#include <cmath>
using namespace std;

const double EPS = 1e-3;

// the function to solve
double f(double x) { return x*x*x - x*x + 2; }

// derivative of function
double f_(double x) { return 3*x*x - 2*x; }

// newton's method
double newton(double x0) {
  double h = INFINITY;
  do {
  	// x(i+1) = x(i) - f(x) / f'(x)
  	h = f(x0) / f_(x0);
  	x0 = x0 - h;
  } while (abs(h) >= EPS);

  return x0;
}

int main() {
	double x0;
	cout << "Enter starting point: ";
	cin >> x0;

	try {
		double sol = newton(x0);
		cout << "The solution is: " << sol << endl;
	} catch(const invalid_argument& e) {
		cout << "Invalid starting point!" << endl;
		cout << e.what() << endl;
	}

	return 0; 
}
