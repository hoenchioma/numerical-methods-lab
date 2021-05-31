#include <iostream>
#include <cmath>
using namespace std;

const double EPS = 1e-3;

// the function to solve
double f(double x) { return pow(x, 3) + x - 1; }

// secant method
double secant(double x1, double x2) {
  if (f(x1) * f(x2) >= 0) {
    throw invalid_argument("f(x1) and f(x2) need to be of opposite sign");
  }
  double x0, x0_nxt;
  do {
    // calculate the intermediate value
    x0 = (x1 * f(x2) - x2 * f(x1)) / (f(x2) - f(x1));
    // check if x0 is root
    if (f(x0) == 0.0) break;
    // update the value of interval
    x1 = x2, x2 = x0;

    // intermediate value for new interval
    x0_nxt = (x1 * f(x2) - x2 * f(x1)) / (f(x2) - f(x1));
  } while (abs(x0_nxt - x0) >= EPS);

  return x0;
}

int main() {
	double a, b;
	cout << "Enter starting points (a and b): ";
	cin >> a >> b;

	try {
		double sol = secant(a, b);
		cout << "The solution is: " << sol << endl;
	} catch(const invalid_argument& e) {
		cout << "Invalid starting point!" << endl;
		cout << e.what() << endl;
	}

	return 0; 
}
