/* This program demonstrates how to use the camera
   to create an fly-by animation                */
   
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef __APPLE__
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

#define WIN_X        800.0
#define WIN_Y        640.0 
#define F           2000.0
#define N            100.0

#define MSEC            10

#define RADIUS       150.0
#define HEIGHT       200.0

#define INNER_RADIUS  30.0
#define OUTER_RADIUS  70.0

#define AXIS_LENGTH 1000.0

#define PARAM_RADIUS 500.0

#define GAZEx          0.0
#define GAZEy          0.0
#define GAZEz          0.0

#define UPx            0.0
#define UPy            0.0
#define UPz            1.0

#define VIEW_ANGLE    80.0
#define ASPECT_RATIO   1.0

GLfloat t = 0.0 ;
GLfloat h = 0.0 ;

void RenderScene(void) {

  glClear(GL_COLOR_BUFFER_BIT) ;

  glLineWidth(3.0) ;
  glBegin(GL_LINES) ;
    glColor3f(0.0,1.0,1.0) ;
    glVertex3f(0.0,0.0,0.0) ;
    glVertex3f(0.0,0.0,AXIS_LENGTH) ;                      /* Draw Z-axis */

    glColor3f(0.0,1.0,0.0) ;
    glVertex3f(0.0,0.0,0.0) ;
    glVertex3f(0.0,AXIS_LENGTH,0.0) ;                      /* Draw Y-axis */

    glColor3f(1.0,0.0,0.0) ;
    glVertex3f(0.0,0.0,0.0) ; 
    glVertex3f(AXIS_LENGTH,0.0,0.0) ;                      /* Draw X-axis */
  glEnd() ;
  glLineWidth(1.0) ;

  glColor3f(1.0,0.0,1.0) ;
  glutWireCone(RADIUS,HEIGHT,24,24) ; /* A 3D wiremesh cone at the origin */ 
  glPushMatrix() ; 
  glTranslatef( -400.0, -400.0, 0.0) ; 
  glutWireCone(RADIUS,HEIGHT,24,24) ;    /* Another cone at (-400,-400,0) */
  glPopMatrix() ; 
  glTranslatef( 400.0, 400.0, 0.0) ;
  glutWireTorus(INNER_RADIUS,OUTER_RADIUS,24,24); /* Torus at (400,400,1) */
  glutSwapBuffers() ;
}

void TimerFunction(int value) {

  glMatrixMode(GL_PROJECTION) ;     /* Operation on the Projection matrix */
  glLoadIdentity() ;
  gluPerspective(VIEW_ANGLE,ASPECT_RATIO,N,F) ;     /* Define view volume */
  glMatrixMode(GL_MODELVIEW) ;       /* Operation on the modelview matrix */
  glLoadIdentity() ;
                                                   /* Position the camera */
  gluLookAt(PARAM_RADIUS*cos(t),PARAM_RADIUS*sin(t),h,GAZEx,GAZEy,GAZEz,UPx,UPy,UPz) ;
  t += 0.01 ;            /* Progress in the path of the parametric circle */
  h += 1.0 ;                                  /* Increasing camera height */
  glutPostRedisplay() ;
  glutTimerFunc(MSEC,TimerFunction,1) ; 
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
  glutCreateWindow("Camera for Animation") ;
  glutDisplayFunc(RenderScene) ;
  glutReshapeFunc(ChangeSize) ;

  glClearColor(0.0,0.0,1.0,1.0) ;

  glutTimerFunc(MSEC,TimerFunction,1) ;
  glutMainLoop();
}
