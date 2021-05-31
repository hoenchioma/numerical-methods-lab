#include <iostream>
#include <cmath>
using namespace std;

// const double EPS = 0.01;
const int MAX_ITER = 100;

// the function to solve
double f(double x) { return x*x*x - x*x + 2; }

// false position method
double false_position(double a, double b) {
  if (f(a) * f(b) >= 0) {
    throw invalid_argument("f(a) and f(b) need to be of opposite sign");
  }
  double c = a;
  for (int i = 0; i < MAX_ITER; i++) {
    // Find the point that touches the x axis
    c = (a*f(b) - b*f(a)) / (f(b) - f(a));
    // Check if point is root
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
		double sol = false_position(a, b);
		cout << "The solution is: " << sol << endl;
	} catch(const invalid_argument& e) {
		cout << "Invalid starting point!" << endl;
		cout << e.what() << endl;
	}

	return 0; 
}
