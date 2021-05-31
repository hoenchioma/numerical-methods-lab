#include <GL/glut.h>

#include <functional>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>
#include <cmath>
using namespace std;

struct pnt { double x, y; };

const int W = 1600;
const int H = 900;
const double XBEG = -800;
const double XEND = 800;
const double XSTEP = 0.2;
const double YSHIFT = 3.5;
const double XSHIFT = 3.5;

const vector<pnt> a = {
  {-500, -100}, {-300, 40}, {-100, 50}, {100, -50}, {300, 200}
};

namespace ipol {
  struct cubic_spline {
    int n;
    vector<double> x; // x[0...n] x co-ordinate of points
    vector<double> a, b, c, d; // [0...n-1] co-efficients

    // make cubic spline for a given set of points
    void make_spline(const vector<pnt>& p) {
      n = p.size() - 1;
      x.resize(n+1), a.resize(n+1);
      b.resize(n), c.resize(n), d.resize(n);
      for (int i = 0; i <= n; i++) {
        x[i] = p[i].x, a[i] = p[i].y;
      }

      // step 1: compute h
      vector<double> h(n);
      for(int j = 0; j < n; j++) h[j] = x[j+1] - x[j];

      // step 2: compute alpha
      vector<double> alp(n+1);
      alp[0] = alp[n] = 0;
      for (int j = 1; j < n; j++) { 
        alp[j] = 3 * (a[j+1] - a[j]) / h[j] - 3 * (a[j] - a[j-1]) / h[j-1];
      }

      // steps 3, 4, 5 and part of 6 solve a tridiagonal linear system

      // step 3
      vector<double> u(n+1), z(n+1);
      u[0] = 0, z[0] = 0;

      // step 4
      for (int i = 1; i < n; i++) {
        double l = 2 * (x[i+1] - x[i-1]) - h[i-1] * u[i-1];
        u[i] = h[i] / l;
        z[i] = (alp[i] - h[i-1] * z[i-1]) / l;
      }

      // step 5
      z[n] = 0, c[n] = 0;

      // step 6: finish solve for c, and find b and d respectively
      for (int j = n-1; j >= 0; j--) {
        c[j] = z[j] - u[j] * c[j+1];
        b[j] = (a[j+1] - a[j]) / h[j] - h[j] * (c[j+1] + 2 * c[j]) / 3;
        d[j] = (c[j+1] - c[j]) / (3 * h[j]);
      }
    }

    // interpolation function of cublic spline
    double f(double x_inp) {
      if (x_inp < x[0] or x_inp > x[n]) return NAN; // undefined when out of range
      int idx = upper_bound(x.begin(), x.end(), x_inp) - x.begin() - 1;
      double x_int = x_inp - x[idx];
      double y = a[idx] + b[idx] * x_int + c[idx] * pow(x_int, 2) + d[idx] * pow(x_int, 3);
      // cout << idx << " " << x_inp << " " << y << endl;
      return y;
    }
  };
}

ipol::cubic_spline spl;

void display(void) {  // callback
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glPushMatrix();

  // draw axes
  glColor3ub(128, 128, 128);
  glPointSize(1);
  glBegin(GL_LINES);
  glVertex2i(0, -H / 2);
  glVertex2i(0, H / 2);
  glVertex2i(-W / 2, 0);
  glVertex2i(W / 2, 0);
  glEnd();


  // glPointSize(1);
  // glBegin(GL_POINTS);
  // for(int m=0; m<N; m++){
  //     glColor3ub(m*60, 0, 255-m*60);
  //     for (X = -800.0; X < 800; X+=0.5) {
  //         Y=partial_interpolate(f, X, N, m);
  //         glVertex2d(X,Y);
  //     }
  // }
  // glEnd();

  // draw function
  glPointSize(1);
  glColor3ub(0, 0, 255);
  glBegin(GL_POINTS);
  for (double x = XBEG; x < XEND; x += XSTEP) {
    double y = spl.f(x);
    // cout << "pnt " << x << " " << y << endl;
    glVertex2d(x, y);
  }
  glEnd();

  // draw points
  glColor3ub(255, 0, 0);
  glPointSize(7);
  glBegin(GL_POINTS);
  for (int i = 0; i < a.size(); i++) {
    glVertex2d(a[i].x, a[i].y);
  }
  glEnd();

  glPopMatrix();
  glFlush();
}

void reshape(int w, int h) {  // projection setting
  GLfloat aspect = (GLfloat)w / (GLfloat)h;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-W / 2, W / 2, -H / 2, H / 2, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void init() {  // lighting setting
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glEnable(GL_COLOR_MATERIAL);

  // precompute the interpolation function
  spl.make_spline(a);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);                    // initialization
  glutInitDisplayMode(GLUT_RGB);            // 24 bit color
  glutInitWindowSize(W, H);                 // WxH window
  glutCreateWindow("Cubic Spline Interpolation");  // title
  init();                                   // lighting
  glutReshapeFunc(reshape);                 // projection
  glutDisplayFunc(display);                 // callback
  glutMainLoop();
  return (0);
}
