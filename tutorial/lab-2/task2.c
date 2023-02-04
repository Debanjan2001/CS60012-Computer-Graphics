/* This program spins a square around itself in 2D */

#include <math.h>
#include <stdlib.h>
#ifdef __APPLE__
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

static GLfloat spin = 0.0 ;

void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glShadeModel(GL_FLAT);
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT) ;
  glPushMatrix() ;
  glRotatef(spin, 0.0, 0.0, 1.0) ;
  glColor3f(1.0, 0.0, 1.0) ;
  glutSolidCube(400);
  glPopMatrix() ;
  glutSwapBuffers() ;
}

void spinDisplay(void)
{
  spin = spin + 2.0 ;
  if (spin > 360.0)
    spin = spin - 360.0 ;
  glutPostRedisplay() ;
}

void reshape(int w, int h)
{
  glViewport(0,0,(GLsizei) w,(GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-500,500,-500,500,-500,500);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
  switch (button) {
    case GLUT_LEFT_BUTTON:
      if (state == GLUT_DOWN)
        glutIdleFunc(spinDisplay) ;
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
  glutInitWindowSize(250,250) ;
  glutInitWindowPosition(100,100) ;
  glutCreateWindow("Spinning Square") ;
  init() ;
  glutDisplayFunc(display) ;
  glutReshapeFunc(reshape) ;
  glutMouseFunc(mouse) ;
  glutMainLoop() ;
}
