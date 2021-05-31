#include <GL/glut.h>

#include <functional>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

// a class to describe the points
struct pnt { double x, y; };

const int W = 1200;
const int H = 900;
const double XBEG = -800;
const double XEND = 800;
const double XSTEP = 0.2;
const double YSHIFT = 3.5;
const double XSHIFT = 3.5;

const vector<pnt> a = {
  {-500, -50}, {-200, 40}, {-50, 50}, {40, -50}, {400, 200}
};

namespace ipol {
	// lagrange interpolation function
	double f(double x) {
		int n = a.size();
		// P(x) = sum (f(x_k) * L_k(x))
		double res = 0;
    for (int i = 0; i < n; i++) {
    	// compute f(x_k) * L_k(x)
      double val = a[i].y;
      for (int j = 0; j < n; j++) {
        if (j != i) val *= (x - a[j].x)/(a[i].x - a[j].x);
      }
      // then add to result
      res += val;
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
  for (int i = 0; i < (int) a.size(); i++) {
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
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);                    // initialization
  glutInitDisplayMode(GLUT_RGB);            // 24 bit color
  glutInitWindowSize(W, H);                 // WxH window
  glutCreateWindow("Lagrange Polynomial");  // title
  init();                                   // lighting
  glutReshapeFunc(reshape);                 // projection
  glutDisplayFunc(display);                 // callback
  glutMainLoop();
  return (0);
}
