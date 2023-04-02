#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifdef __APPLE__
  #include <GLUT/glut.h>
#else 
  #include <GL/glut.h>
#endif


// OpenGL Windowing and Projection Constants
#define WINDOW_X            1000.0
#define WINDOW_Y            800.0
#define FAR                 600.0
#define NEAR                -600.0

#define TEAPOT_SIZE         WINDOW_Y/5

#define SPHERE_RADIUS       15.0


// Define Material Properties for teapot and light sources
GLfloat teapotSpecular[] = {0.1, 0.1, 0.1, 1.0};
GLfloat teapotShininess[] = {50.0};

// Viewpoint White Light 
GLfloat light0_position[] = {0.0, 0.0, -2*NEAR, 1.0};
GLfloat light0_ambient[] = {0.3, 0.3, 0.3, 1.0};
GLfloat light0_diffuse[] = {1.0, 1.0, 1.0, 1.0};


// Red Light Source
GLfloat light1_position[] = {-1.5*TEAPOT_SIZE, 2*TEAPOT_SIZE, 3*TEAPOT_SIZE, 1.0};
GLfloat light1_diffuse[] = {1.0, 0.0, 0.0, 1.0};

// Green Light Source
GLfloat light2_position[] =  {0.0, 2*TEAPOT_SIZE, -3*TEAPOT_SIZE, 1.0};
GLfloat light2_diffuse[] = {0.0, 1.0, 0.0, 1.0};

// Blue Light Source
GLfloat light3_position[] = {1.5*TEAPOT_SIZE, 2*TEAPOT_SIZE, 3*TEAPOT_SIZE, 1.0};
GLfloat light3_diffuse[] = {0.0, 0.0, 1.0, 1.0};

GLfloat ambientLight[] = {0.3, 0.3, 0.3, 1.0};
GLfloat diffuseLight[] = {0.7, 0.7, 0.7, 1.0};
GLfloat specularLight[] = {1.0, 1.0, 1.0, 1.0};

// GLfloat viewpointLight[] = {1.0, 1.0, 1.0, 0.0};
// GLfloat lightIntensity = 1.0;

GLfloat const grayColor[] = {0.4, 0.4, 0.4};

void init(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
}

void drawTeapot(){
  glPushMatrix();
    glColor3fv(grayColor);
    glutSolidTeapot(TEAPOT_SIZE);
  glPopMatrix();
  glFlush();
}


// Define function to draw a colored sphere for the light sources
void drawSphere(GLfloat* position, GLfloat* diffuse) {
    glPushMatrix();
    glTranslatef(position[0], position[1], position[2]);
    glColor3fv(diffuse);
    glutSolidSphere(SPHERE_RADIUS, 50, 50);
    glPopMatrix();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glPushMatrix();
    glRotatef(20.0, 1.0, 0.0, 0.0);
    drawTeapot();
    glPopMatrix();

    glPushMatrix();
    drawSphere(light1_position, light1_diffuse);
    glPopMatrix();

    glPushMatrix();
    drawSphere(light2_position, light2_diffuse);
    glPopMatrix();

    glPushMatrix();
    drawSphere(light3_position, light3_diffuse);
    glPopMatrix();

    glFlush();
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

  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE) ;
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE) ;  /* Front @ back faces */
  glEnable(GL_LIGHTING);

  // Soft white ambient light
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);
  glEnable(GL_LIGHT3);

  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);


  glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);

  glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);

  glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
  glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
  
  glEnable(GL_COLOR_MATERIAL) ; 
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE) ; 
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, teapotSpecular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, teapotShininess);
        
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);


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
