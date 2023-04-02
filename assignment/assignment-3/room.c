#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifdef __APPLE__
  #include <GLUT/glut.h>
#else 
  #include <GL/glut.h>
#endif


// OpenGL Windowing and Projection Constants
#define WINDOW_X            1200.0
#define WINDOW_Y            800.0
#define FAR                 600.0
#define NEAR                -600.0

#define TEAPOT_SIZE         WINDOW_Y/4


// Define variables for teapot and light sources
GLfloat teapotSpecular[] = {1.0, 1.0, 1.0, 0.5};
GLfloat teapotShininess[] = {50.0};
GLfloat light0_position[] = {0.0, 0.0, -NEAR, 1.0};
GLfloat light0_diffuse[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light1_position[] = {-10.0, 0.0, 0.0, 1.0};
GLfloat light1_diffuse[] = {1.0, 0.0, 0.0, 1.0};
GLfloat light2_position[] = {0.0, 10.0, 0.0, 1.0};
GLfloat light2_diffuse[] = {0.0, 1.0, 0.0, 1.0};
GLfloat light3_position[] = {10.0, 0.0, 0.0, 1.0};
GLfloat light3_diffuse[] = {0.0, 0.0, 1.0, 1.0};
GLfloat ambientLight[] = {0.2, 0.2, 0.2, 1.0};
GLfloat viewpointLight[] = {1.0, 1.0, 1.0, 0.0};
GLfloat lightIntensity = 1.0;

GLfloat const grayColor[] = {0.56, 0.61, 0.61};

void init(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

}

void drawTeapot(){
  glPushMatrix();
    glColor3fv(grayColor);
    glutSolidTeapot(TEAPOT_SIZE);
  glPopMatrix();
  glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(20, 1, 0, 0);
    drawTeapot();
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h){
  glViewport(0,0, (GLsizei) w, (GLsizei) h) ;
  glMatrixMode(GL_PROJECTION) ;
  glLoadIdentity() ;
  glOrtho((double)-WINDOW_Y/2, (double)WINDOW_X/2, (double)-WINDOW_Y/2, (double)WINDOW_Y/2, NEAR, FAR); 
  glMatrixMode(GL_MODELVIEW) ;
  glLoadIdentity() ;
}


// Define function to set up the lights
void setupLights() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    glEnable(GL_DEPTH_TEST);
    // glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    // glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    // glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    // glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    // glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
    // glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
    // glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
    // glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
    // glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
    glMaterialfv(GL_FRONT, GL_SPECULAR, teapotSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, teapotShininess);
    // glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, viewpointLight);
}

int main(int argc, char** argv) {

  glutInit(&argc,argv) ;
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA); 
  glutInitWindowSize((int)WINDOW_X, (int)WINDOW_Y);
  glutInitWindowPosition(100, 100) ;
  glutCreateWindow("Teapot Lighting") ;
  

  // Setting Intial Parameters
  init() ;

  glutDisplayFunc(display) ;
  glutReshapeFunc(reshape) ;
  setupLights();
  
  glutMainLoop();
}
