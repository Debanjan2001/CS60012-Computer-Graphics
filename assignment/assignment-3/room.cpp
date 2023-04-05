#include <iostream>
#include <math.h>
#ifdef __APPLE__
  #include <GLUT/glut.h>
#else 
  #include <GL/glut.h>
#endif
using namespace std;

// OpenGL Windowing and Projection Constants
#define WINDOW_X            1100.0
#define WINDOW_Y            900.0
#define FAR                 600.0
#define NEAR                -600.0

#define TEAPOT_SIZE         180

#define SPHERE_RADIUS       15.0


// Frequency of re-rendering
#define MSEC                30


void setColor(GLfloat *color1, GLfloat const *color2){
    for(int i=0; i<3; ++i){
      color1[i] = color2[i];
    }
}

void toggleSwitch(bool &switchVar){
    switchVar = !(switchVar);
}

GLfloat const grayColor[] = {0.4, 0.4, 0.4};
GLfloat const redColor[] = {1.0, 0.0, 0.0};
GLfloat const greenColor[] = {0.0, 1.0, 0.0};
GLfloat const blueColor[] = {0.0, 0.0, 1.0};
GLfloat const whiteColor[] = {1.0, 1.0, 1.0};
GLfloat const blackColor[] = {0.0, 0.0, 0.0};
GLfloat const ambientColor[] = {0.2, 0.2, 0.2, 0.2};

// Define Material Properties for teapot and light sources
GLfloat teapotSpecular[] = {0.1, 0.1, 0.1, 1.0};
GLfloat teapotShininess[] = {10.0};

// Viewpoint White Light 
GLfloat light0_position[] = {0.0, 0.0, -2*NEAR, 1.0};
// GLfloat light0_ambient[] = {0.4, 0.4, 0.4, 1.4};
GLfloat light0_diffuse[] = {0.8, 0.8, 0.8, 1.0};


// Red Light Source
GLfloat light1_position[] = {-TEAPOT_SIZE, TEAPOT_SIZE, 2*TEAPOT_SIZE, 1.0};
GLfloat light1_diffuse[] = {1.0, 0.0, 0.0, 1.0};
static bool light1_on = 1;

// Green Light Source
GLfloat light2_position[] =  {0.0, TEAPOT_SIZE, -2*TEAPOT_SIZE, 1.0};
GLfloat light2_diffuse[] = {0.0, 1.0, 0.0, 1.0};
static bool light2_on = 1;

// Blue Light Source
GLfloat light3_position[] = {TEAPOT_SIZE, TEAPOT_SIZE, 2*TEAPOT_SIZE, 1.0};
GLfloat light3_diffuse[] = {0.0, 0.0, 1.0, 1.0};
static bool light3_on = 1;


static bool ambient_light_on = 1;
static bool viewpoint_light_on = 1;

GLfloat ambientLight[] = {0.2, 0.2, 0.2, 1.0};
GLfloat ambient[] = {1,1, 1};
GLfloat diffuseLight[] = {0.7, 0.7, 0.7, 1.0};
GLfloat specularLight[] = {1.0, 1.0, 1.0, 1.0};

static int rotateLightAngle = 0;
static bool rotateLight = 0;

static int mouseDown = 0;
static int lastMouseX = 0;
static int lastMouseY = 0;
static float rotateX = 0.0;
static float rotateY = 0.0;

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
void drawLightSphere(GLfloat* position, GLfloat* diffuse, int lightColor) {
    glPushMatrix();
    glTranslatef(position[0], position[1], position[2]);
    // if(ambient_light_on){
    //   glColor3fv(diffuse);
    // }else{
    //   glColor4fv(noAmbientColor);
    // }
    
    if(lightColor == 1 && light1_on){
      glColor3fv(redColor);
    }else if(lightColor == 2 && light2_on){
      glColor3fv(greenColor);
    }else if(lightColor == 3 && light3_on){
      glColor3fv(blueColor);
    }else{
      glColor3fv(grayColor);
    }
    glutSolidSphere(SPHERE_RADIUS, 50, 50);
    glPopMatrix();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glPushMatrix();

    // Soft white ambient light
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    glRotatef(rotateX, 1.0, 0.0, 0.0);
    glRotatef(rotateY, 0.0, 1.0, 0.0);
    
    glPushMatrix();
    glRotatef(15.0, 1.0, 0.0, 0.0);
    drawTeapot();
    glPopMatrix();


    glPushMatrix();
    glRotatef(rotateLightAngle, 0.0, 1.0, 0.0);
    
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);

    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);

    glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);

    drawLightSphere(light1_position, light1_diffuse, 1);
    drawLightSphere(light2_position, light2_diffuse, 2);
    drawLightSphere(light3_position, light3_diffuse, 3);
    glPopMatrix();

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

  // // Soft white ambient light
  // glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE) ;
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE) ;  /* Front @ back faces */
 
  glEnable(GL_LIGHTING);
  // Viewpoint Light
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);
  glEnable(GL_LIGHT3);
  
  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
  // glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
  
  // glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
  // glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);

  // glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
  // glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);

  // glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
  // glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
  
  glEnable(GL_COLOR_MATERIAL) ; 
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE) ; 
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, teapotSpecular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, teapotShininess);
}

// Define function to handle keyboard input
void handleKeyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'r':
        case 'R':
            if(light1_on){
                glDisable(GL_LIGHT1);
                setColor(light1_diffuse, grayColor);
            }else{
                setColor(light1_diffuse, redColor);
                glEnable(GL_LIGHT1);
            }
            toggleSwitch(light1_on);
            break;
        case 'g':
        case 'G':
            if(light2_on){
                glDisable(GL_LIGHT2);
                setColor(light2_diffuse, grayColor);
            }else{
                setColor(light2_diffuse, greenColor);
                glEnable(GL_LIGHT2);
            }
            toggleSwitch(light2_on);
            break;
        case 'b':
        case 'B':
            if(light3_on){
                glDisable(GL_LIGHT3);
                setColor(light3_diffuse, grayColor);
            }else{
                setColor(light3_diffuse, blueColor);
                glEnable(GL_LIGHT3);
            }
            toggleSwitch(light3_on);
            break;
        case 'a':
        case 'A':
            toggleSwitch(rotateLight);
            break;
        case 'l':
        case 'L':
            if(ambient_light_on){
              setColor(ambientLight, blackColor);
            }else{
              setColor(ambientLight, ambientColor);
            }
            toggleSwitch(ambient_light_on);
            break;
        case 'v':
        case 'V':
            if(viewpoint_light_on){
              glDisable(GL_LIGHT0);
            }else{
              glEnable(GL_LIGHT0);
            }
            toggleSwitch(viewpoint_light_on);
            break;
        case 27:
            exit(0);
            break;
        default:
            break;

    }
    glutPostRedisplay();
}

// Define function to handle mouse interaction
void handleMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            mouseDown = 1;
            lastMouseX = x;
            lastMouseY = y;
        }
        else {
            mouseDown = 0;
        }
    }
}


// Define function to handle mouse motion
void handleMouseMove(int x, int y) {
    if (mouseDown) {
        rotateX += (y - lastMouseY) * 0.5;
        rotateY += (x - lastMouseX) * 0.5;
        lastMouseX = x;
        lastMouseY = y;
        glutPostRedisplay();
    }
}

void timer(int value) {
    if(rotateLight){
      rotateLightAngle = (rotateLightAngle + 1) % 360;
    }
    glutPostRedisplay();
    glutTimerFunc(MSEC, timer, 1);
}


int main(int argc, char** argv) {

  glutInit(&argc,argv) ;
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA); 
  glutInitWindowSize((int)WINDOW_X, (int)WINDOW_Y);
  glutInitWindowPosition(50, 50) ;
  glutCreateWindow("Teapot Lighting") ;
  

  // Setting Intial Parameters
  init() ;

  glutDisplayFunc(display) ;
  glutReshapeFunc(reshape) ;
  glutTimerFunc(MSEC, timer, 1) ;
  glutKeyboardFunc(handleKeyboard);
  glutMouseFunc(handleMouse);
  glutMotionFunc(handleMouseMove);

  setupLights();
  glutMainLoop();
  return 0;
}
