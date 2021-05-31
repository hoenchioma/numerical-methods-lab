#include <GL/glut.h>

#include <functional>
#include <iostream>
#include <iomanip>
#include <vector>
#include <assert.h>
using namespace std;

struct pnt { double x, y; };

const int W = 1600;
const int H = 900;
const double XBEG = -800;
const double XEND = 800;
const double XSTEP = 0.2;
const double YSHIFT = 3.5;
const double XSHIFT = 3.5;

// set of points
const vector<pnt> a = {
  {-500, -100}, {-300, 40}, {-100, 50}, {100, -50}, {300, 200}
};


namespace ipol {
  vector<vector<double>> d; // difference table
  vector<double> x_; // x values
  double h; // interval

  void precompute(const vector<pnt>& a) {
    int n = a.size();
    d.assign(n, vector<double>(n));
    x_.resize(n);
    h = a[1].x - a[0].x;

    // the points must be equidistant
    for (int i = 1; i < n; i++) assert(a[i].x - a[i-1].x == h);

    // save the x values
    for (int i = 0; i < n; i++) x_[i] = a[i].x;

    // compute the difference table
    for (int j = 0; j < n; j++) d[0][j] = a[j].y;
    for (int i = 1; i < n; i++) {
      for (int j = n-1; j >= i; j--) {
        d[i][j] = d[i-1][j] - d[i-1][j-1];
      }
    }
  }

  // interpolated function
  double f(double x) {
    int n = x_.size();
    double s = (x - x_[n-1]) / h;
    double u = 1;
    double res = d[0][n-1];
    for (int i = 1; i < n; i++) {
      u = u * (s + i - 1) / i;
      res += u * d[i][n-1];
    }
    return res;
  }
}

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
    glVertex2d(x, ipol::f(x));
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
  ipol::precompute(a);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);                    // initialization
  glutInitDisplayMode(GLUT_RGB);            // 24 bit color
  glutInitWindowSize(W, H);                 // WxH window
  glutCreateWindow("Newton's Backword Difference Interpolation");  // title
  init();                                   // lighting
  glutReshapeFunc(reshape);                 // projection
  glutDisplayFunc(display);                 // callback
  glutMainLoop();
  return (0);
}
