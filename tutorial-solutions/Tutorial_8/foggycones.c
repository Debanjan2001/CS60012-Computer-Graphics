/* This program demonstrates how to use light sources, front and back 
   faces, and Z-buffer techniques to render objects with realism, and
   include the fog effect */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>
#ifdef __APPLE__
  #include <GLUT/glut.h>
#else 
  #include <GL/glut.h>
#endif

#define ALPHA          1.0

#define WIN_X        800.0
#define WIN_Y        640.0 
#define F           2000.0
#define N            100.0

#define MSEC            25

#define RADIUS       150.0
#define HEIGHT       200.0

#define INNER_RADIUS  30.0
#define OUTER_RADIUS  70.0

#define AXIS_LENGTH 1000.0

#define PARAM_RADIUS 800.0
#define PARAM_AMPLIT 250.0

#define GAZEx          0.0
#define GAZEy          0.0
#define GAZEz          0.0

#define UPx            0.0
#define UPy            0.0
#define UPz            1.0

#define VIEW_ANGLE    80.0
#define ASPECT_RATIO   1.0

GLfloat ambientlight[] = {0.3,0.3,0.3,1.0} ;
GLfloat diffuselight[] = {0.7,0.7,0.7,1.0} ;
GLfloat specular[] = {1.0,1.0,1.0,1.0} ;
GLfloat specref[] = {1.0,1.0,1.0,1.0} ;
GLfloat lightposition[] = {0.0,0.0,0.0} ;

GLfloat fogcolor[] = {0.3,0.3,0.3,0.0} ;

GLfloat t = 0.0 ;
GLfloat theta = 0.0 ;

void RenderScene(void) {

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ; 

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
  glPushMatrix() ;
  glTranslatef(0.0,300.0,0.0) ; 
  glColor4f(0.5,0.2,0.1,ALPHA) ;
  glutSolidCone(RADIUS,HEIGHT,240,240) ;            /* A cone @ (0,300,0) */
  glPopMatrix() ;

  glPushMatrix() ;
  glTranslatef(-300.0,-300.0,0.0) ; 
  glColor4f(0.3,0.1,0.3,ALPHA) ;
  glutSolidCone(RADIUS,HEIGHT,240,240) ;  /* Another cone @ (-300,-300,0) */
  glPopMatrix() ;

  glutSwapBuffers() ;
}

void TimerFunction(int value) {

  glMatrixMode(GL_PROJECTION) ;     /* Operation on the Projection matrix */
  glLoadIdentity() ;
  gluPerspective(VIEW_ANGLE,ASPECT_RATIO,N,F) ;     /* Define view volume */
  glMatrixMode(GL_MODELVIEW) ;       /* Operation on the modelview matrix */
  glLoadIdentity() ;
   /* light source at origin  of the viewing volume so that it moves with */
                                                            /* the camera */
  glLightfv(GL_LIGHT0,GL_POSITION,lightposition) ;
                                                   /* Position the camera */
  gluLookAt(PARAM_RADIUS*cos(t),PARAM_RADIUS*sin(t),PARAM_AMPLIT*sin(theta),GAZEx,GAZEy,GAZEz,UPx,UPy,UPz) ;
  if (t >= M_PI*2.0) t = 0.0 ;
  t += 0.01 ;            /* Progress in the path of the parametric circle */
  if (theta >= M_PI*2.0) theta = 0.0 ;
              /* Go under and over the scene using a sine wave for height */
  theta += 0.0125 ;
  glutPostRedisplay() ;
  glutTimerFunc(MSEC,TimerFunction,1) ; 
}

void ChangeSize(int w, int h) { 

  glViewport(0,0, (GLsizei) w, (GLsizei) h) ;
  glMatrixMode(GL_PROJECTION) ;
  glLoadIdentity() ;
  glOrtho((double)-WIN_Y/2,(double)WIN_X/2,(double)-WIN_Y/2,(double)WIN_Y/2,N,F); 
  glMatrixMode(GL_MODELVIEW) ;
  glLoadIdentity() ;
}

int main(int argc, char** argv) {

  glutInit(&argc,argv) ;
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB) ;  /* Z-buffer */
  glutInitWindowSize((int)WIN_X,(int)WIN_Y) ;
  glutInitWindowPosition(0,0) ;
  glutCreateWindow(argv[0]) ;
  glutDisplayFunc(RenderScene) ;
  glutReshapeFunc(ChangeSize) ;

  glClearColor(fogcolor[0],fogcolor[1],fogcolor[2],fogcolor[3]) ;

  glEnable(GL_BLEND) ;
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA) ;
  glEnable(GL_POINT_SMOOTH) ;
  glEnable(GL_LINE_SMOOTH) ;
  glEnable(GL_POLYGON_SMOOTH) ;

  glEnable(GL_FOG) ;
  glFogf(GL_FOG_MODE,GL_EXP) ;
  glFogf(GL_FOG_DENSITY,0.0025) ;
  glFogfv(GL_FOG_COLOR,fogcolor) ;
  glFogf(GL_FOG_START,10.0) ;
  glFogf(GL_FOG_END,1250.0) ;
  

  glEnable(GL_DEPTH_TEST) ;                            /* Enable Z-buffer */
  glFrontFace(GL_CCW) ;             /* Counterclockwise polygons face out */
                                                    /* Force true normals */
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE) ;
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE) ;  /* Front @ back faces */
  glShadeModel(GL_SMOOTH) ;                            /* Gouraud shading */
  glEnable(GL_LIGHTING) ;

  glLightfv(GL_LIGHT0,GL_AMBIENT,ambientlight) ;
  glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuselight) ;
  glLightfv(GL_LIGHT0,GL_SPECULAR,specular) ;

  glEnable(GL_LIGHT0) ;
  glEnable(GL_COLOR_MATERIAL) ; 
  glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE) ; 
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specref) ;
  glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,16) ;
  
  glutTimerFunc(MSEC,TimerFunction,1) ;
  glutMainLoop();
}
