#include <iostream>
#include <cmath>
using namespace std;

const double EPS = 1e-6;

// the function to solve
double f(double x) { return x*x*x - x*x + 2; }

// bisection method
double bisection(double a, double b) {
  if (f(a) * f(b) >= 0) {
    throw invalid_argument("f(a) and f(b) need to be of opposite sign");
  }
  double c = a;
  while ((b - a) >= EPS) {
    // Find middle point
    c = (a + b) / 2;
    // Check if middle point is root
    if (f(c) == 0.0) break;
    // Decide the side to repeat the steps
    if (f(c) * f(a) < 0) b = c;
    else a = c;
  }
  return c;
}

int main() {
	double a, b;
	cout << "Enter starting points (a and b): ";
	cin >> a >> b;

	try {
		double sol = bisection(a, b);
		cout << "The solution is: " << sol << endl;
	} catch(const invalid_argument& e) {
		cout << "Invalid starting point!" << endl;
		cout << e.what() << endl;
	}

	return 0; 
}
