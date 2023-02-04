/*
Name- Debanjan Saha
Roll- 19CS30014
Assignment- 1
Description- Trajectory of a Bouncing Ball

#ifdef __APPLE__
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

int main(int argc, char **argv){

}
*/

/* This program spins a square around itself in 2D */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

// static GLfloat spin = 0.0 ;

static GLfloat xTranslate = 0.0, yTranslate=30.0;
static float horizontalVelocity = 0.05;
static float velocity = 0.0;
static float accelaration = 0.005;
const float loss = 0.05;
static int upwardMotion = 0;

GLfloat getMax(GLfloat a, GLfloat b){
  if(a>b){
    return a;
  }
  return b;
}

float getMaxf(float a, float b){
  if(a>b){
    return a;
  }
  return b;
}

void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glShadeModel(GL_FLAT);
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT) ;

  // Draw sample Axes for better visualization
  glColor3f(0.0, 0.0, 0.0) ;
  glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(40, 0);
    glVertex2f(0, 0);
    glVertex2f(0, 40);
  glEnd();

  glPushMatrix() ;

  // glTranslatef(0, 0, -20);
  // glRotatef(spin, 1.0, 0.5, 0.5) ;
  glTranslatef(xTranslate, yTranslate, -40.0);

  glColor3f(0.0, 0.0, 0.0) ;
  glutWireSphere(10, 20, 20);

  glPopMatrix() ;
  glutSwapBuffers();
}

// void spinDisplay(void)
// {
//   spin = spin + 1.0 ;
//   if (spin > 360.0)
//     spin = spin - 360.0 ;
//   glutPostRedisplay() ;
// }

void translateDisplay(void)
{
  xTranslate = xTranslate + horizontalVelocity ;

  if(upwardMotion){
    velocity -= accelaration;
    yTranslate = yTranslate + velocity;
    if(velocity <= 0){
      upwardMotion = 0;
    }
  } else {
    velocity += accelaration;
    yTranslate = getMax(yTranslate - velocity, 0.0);
    if(yTranslate == 0){
      upwardMotion = 1;
      velocity = getMaxf(velocity-loss, 0.0);
    }
  }

  // printf("v=%f, a=%f\n", velocity, accelaration);
  glutPostRedisplay() ;
}

void reshape(int w, int h)
{
  float aspectRatio = (float)w / (float)h;
  glViewport(0,0,(GLsizei) w,(GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Get a Flat view
  glOrtho(-10.0, 100.0, -10.0, 100.0, -50.0, 50.0);

  // Get a 3d View
  // glFrustum (-10.0, 50.0, -10.0, 50.0, 10, 100);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
  switch (button) {
    case GLUT_LEFT_BUTTON:
      if (state == GLUT_DOWN)
        glutIdleFunc(translateDisplay) ;
      break ;
    case GLUT_MIDDLE_BUTTON:
      if (state == GLUT_DOWN)
        glutIdleFunc(NULL) ;
      break ;
    default:
    break ;
  }
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv) ;
  glutInitDisplayMode(GLUT_DOUBLE) ;
  glutInitWindowSize(800,800) ;
  glutInitWindowPosition(100,100) ;
  glutCreateWindow("Spinning Square") ;
  init() ;
  glutDisplayFunc(display) ;
  glutReshapeFunc(reshape) ;
  glutMouseFunc(mouse) ;
  glutMainLoop() ;
}
