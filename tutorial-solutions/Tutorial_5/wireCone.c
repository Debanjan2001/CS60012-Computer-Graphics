/* This program demonstrates how to use glutTimerFunc()
   to create a smooth animation.                    */
   
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef __APPLE__
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

#define WIN_X       800.0
#define WIN_Y       640.0 
#define F           600.0
#define N          -600.0

#define MSEC           10

#define RADIUS      150.0
#define HEIGHT      200.0

void RenderScene(void) {

  glClear(GL_COLOR_BUFFER_BIT) ;

  glLineWidth(3.0) ;
  glBegin(GL_LINES) ;
    glColor3f(0.0,1.0,1.0) ;
    glVertex3f(0.0,0.0,0.0) ;
    glVertex3f(0.0,0.0,100.0) ;                            /* Draw Z-axis */

    glColor3f(0.0,1.0,0.0) ;
    glVertex3f(0.0,0.0,0.0) ;
    glVertex3f(0.0,100.0,0.0) ;                            /* Draw Y-axis */

    glColor3f(1.0,0.0,0.0) ;
    glVertex3f(0.0,0.0,0.0) ; 
    glVertex3f(100.0,0.0,0.0) ;                            /* Draw X-axis */
  glEnd() ;
  glLineWidth(1.0) ;

  glColor3f(1.0,0.0,1.0) ;
  glutWireCone(RADIUS,HEIGHT,24,24) ; 
  glRotatef(1.0,1.0,1.0,1.0) ;            /* Rotation around axis (1,1,1) */
  glutSwapBuffers() ;
}

void TimerFunction(int value) {

  glutPostRedisplay() ;
  glutTimerFunc(MSEC,TimerFunction,1) ;    /* Register the timer callback */ 
}

void ChangeSize(int w, int h) { 

  glViewport(0,0,(GLsizei) w,(GLsizei) h) ;
  glMatrixMode(GL_PROJECTION) ;
  glLoadIdentity() ;
  glOrtho((double)-WIN_Y/2,(double)WIN_X/2,(double)-WIN_Y/2,(double)WIN_Y/2,N,F); 
  glMatrixMode(GL_MODELVIEW) ;
  glLoadIdentity() ;
}

int main(int argc, char** argv) {
 
  glutInit(&argc,argv) ;
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB) ;
  glutInitWindowSize((int)WIN_X,(int)WIN_Y) ;
  glutInitWindowPosition(0,0) ;
  glutCreateWindow("Wire Cone Animation") ;
  glutDisplayFunc(RenderScene) ;
  glutReshapeFunc(ChangeSize) ;

  glClearColor(0.0,0.0,1.0,1.0) ;

  glutTimerFunc(MSEC,TimerFunction,1) ;    /* Register the timer callback */
  glutMainLoop();
}
