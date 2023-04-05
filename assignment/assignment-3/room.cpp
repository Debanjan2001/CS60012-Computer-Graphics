/*
 * Name- Debanjan Saha
 * Roll- 19CS30014
 * Email- debanjansaha2001@gmail.com
 * Assignment- 3
 * Description- A simple animation of teapot with light sources and materials
*/
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

// Teapot Size
#define TEAPOT_SIZE         180

// Light Sphere Radius
#define SPHERE_RADIUS       15.0

// Frequency of re-rendering
#define MSEC                30

// OpenGL Color Constants
GLfloat const grayColor[] = {0.4, 0.4, 0.4};
GLfloat const redColor[] = {1.0, 0.0, 0.0};
GLfloat const greenColor[] = {0.0, 1.0, 0.0};
GLfloat const blueColor[] = {0.0, 0.0, 1.0};
GLfloat const whiteColor[] = {1.0, 1.0, 1.0};
GLfloat const blackColor[] = {0.0, 0.0, 0.0};
GLfloat const ambientWhiteColor[] = {0.2, 0.2, 0.2};
GLfloat const noAmbientWhiteColor[] = {0.05, 0.05, 0.05};


// Define Material Properties for teapot and light sources
GLfloat materialSpecular[] = {0.1, 0.1, 0.1, 1.0};
GLfloat materialShininess[] = {50.0};

// Viewpoint White Light
GLfloat light0_position[] = {0.0, 0.0, -2 * NEAR, 1.0};
GLfloat light0_diffuse[] = {0.8, 0.8, 0.8, 1.0};
// GLfloat light0_ambient[] = {0.4, 0.4, 0.4, 1.0};


// RGB Light Sources switches
static bool red_light_on = 1;
static bool green_light_on = 1;
static bool blue_light_on = 1;

// Red Light Source
GLfloat red_light_position[] = { -TEAPOT_SIZE, TEAPOT_SIZE, 2 * TEAPOT_SIZE, 1.0};
GLfloat red_light_diffuse[] = {1.0, 0.0, 0.0, 1.0};

// Green Light Source
GLfloat green_light_position[] =  {0.0, TEAPOT_SIZE, -2 * TEAPOT_SIZE, 1.0};
GLfloat green_light_diffuse[] = {0.0, 1.0, 0.0, 1.0};

// Blue Light Source
GLfloat blue_light_position[] = {TEAPOT_SIZE, TEAPOT_SIZE, 2 * TEAPOT_SIZE, 1.0};
GLfloat blue_light_diffuse[] = {0.0, 0.0, 1.0, 1.0};

// Viewpoint Light and Ambient Light Switch
static bool ambient_light_on = 1;
static bool viewpoint_light_on = 1;

// Different Types of Light Sources
GLfloat ambientLight[] = {0.2, 0.2, 0.2, 1.0};
GLfloat diffuseLight[] = {0.7, 0.7, 0.7, 1.0};
GLfloat specularLight[] = {1.0, 1.0, 1.0, 1.0};

// Static variables for rotation of RGB lights
static int rotateLightAngle = 0;
static bool rotateLight = 0;

// Mouse Movement Static Variables
static int mouseDown = 0;
static int lastMouseX = 0;
static int lastMouseY = 0;
static float rotateX = 0.0;
static float rotateY = 0.0;


/*
 * Purpose: Change the color of a color array using a secondary array
 */
void setColor(GLfloat *color1, GLfloat const *color2) {
	for (int i = 0; i < 3; ++i) {
		color1[i] = color2[i];
	}
}

/*
 * Purpose: Toggle a boolean variable or flip a switch
 */
void toggleSwitch(bool &switchVar) {
	switchVar = !(switchVar);
}

/*
 * Purpose: Set Initial parameters: 
 * Clear the screen, set shading model, enable depth test, enable color material
 */
void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
}

/*
 * Purpose: Apply material Properties to teapot and light sources
 */
void applyMaterialProperties(){
	glEnable(GL_COLOR_MATERIAL) ;
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE) ;
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);
}

/*
 * Purpose: Define function to draw a teapot
 */
void drawTeapot() {
	glPushMatrix();
	glColor3fv(grayColor);
	glutSolidTeapot(TEAPOT_SIZE);
	glPopMatrix();
	glFlush();
}

/*
 * Purpose: Define function to draw a light sphere with intended color when,
 * ambient light is on and viewpoint light is off
 * or ambient light is off and viewpoint light is off
*/
bool isRGBLightOnWhenBackgroundLightOff(int lightColor){
  if(ambient_light_on){
    if(!viewpoint_light_on){
      return true;
    }
    return false;
  }

  if(viewpoint_light_on){
    return false;
  }
  if(
      (lightColor == 1 && red_light_on) 
      || 
      (lightColor == 2 && green_light_on)
      ||
      (lightColor == 3 && blue_light_on)
  ){
    return true;
  }
  return false;
}

/*
 * Purpose: Define function to draw a light sphere with intended color
 *
 * Input: position:   position of the center of sphere to be drawn
 *
*/
void drawLightSphere(GLfloat* position, int lightColor) {
	glPushMatrix();
    glTranslatef(position[0], position[1], position[2]);
    
    // Turn off ambient light
    if(isRGBLightOnWhenBackgroundLightOff(lightColor)){
        glDisable(GL_LIGHTING);
    }

    if (lightColor == 1 && red_light_on) {
      glColor3fv(redColor);
    } else if (lightColor == 2 && green_light_on) {
      glColor3fv(greenColor);
    } else if (lightColor == 3 && blue_light_on) {
      glColor3fv(blueColor);
    } else {
      glColor3fv(grayColor);
    }
    glutSolidSphere(SPHERE_RADIUS, 50, 50);

    if(isRGBLightOnWhenBackgroundLightOff(lightColor)){
        glEnable(GL_LIGHTING);
    }
    
	glPopMatrix();
  glFlush();
}

/*
 * Purpose: Define function to setup a viewpoint light source
 */
void setupViewpointLightSource() {
	glPushMatrix();

	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, light0_diffuse);
	// glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);

	glPopMatrix();
	glFlush();
}

/*
 * Purpose: Define function to setup an ambient light source 
 */
void setupAmbientLightSource() {
	glPushMatrix();

	// Soft white ambient light
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	glPopMatrix();
	glFlush();
}

/*
 * Purpose: Define function to setup RGB light sources along with rotation on keypress
 */
void setupRGBLightSources() {
	glPushMatrix();
    glRotatef(rotateLightAngle, 0.0, 1.0, 0.0);

    glLightfv(GL_LIGHT1, GL_POSITION, red_light_position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, red_light_diffuse);

    glLightfv(GL_LIGHT2, GL_POSITION, green_light_position);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, green_light_diffuse);

    glLightfv(GL_LIGHT3, GL_POSITION, blue_light_position);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, blue_light_diffuse);

    drawLightSphere(red_light_position, 1);
    drawLightSphere(green_light_position, 2);
    drawLightSphere(blue_light_position, 3);
	glPopMatrix();
	glFlush();
}

/*
 * Purpose: Display function for rendering the animation scene
 */
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
    applyMaterialProperties();
    glRotatef(rotateX, 1.0, 0.0, 0.0);
    glRotatef(rotateY, 0.0, 1.0, 0.0);

    setupRGBLightSources();
    setupAmbientLightSource();

    glPushMatrix();
      glRotatef(15.0, 1.0, 0.0, 0.0);
      drawTeapot();
    glPopMatrix();

	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

/*
 * Purpose: Reshape function for defining viewport, setting up orthographic projection etc.
 */
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h) ;
	glMatrixMode(GL_PROJECTION) ;
	glLoadIdentity() ;
	glOrtho((double) - WINDOW_Y / 2, (double)WINDOW_X / 2, (double) - WINDOW_Y / 2, (double)WINDOW_Y / 2, NEAR, FAR);
	glMatrixMode(GL_MODELVIEW) ;
	glLoadIdentity() ;
}

/*
 * Purpose: Function to setup the RGB Lights, Ambient Light and Viewpoint Light
*/
void setupLights() {

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE) ;
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE) ;  /* Front & back faces */

	glEnable(GL_LIGHTING);

	// Enable Viewpoint Light Source
	glEnable(GL_LIGHT0);
	// Enable Red light Source
	glEnable(GL_LIGHT1);
	// Enable Green light Source
	glEnable(GL_LIGHT2);
	// Enable Blue light Source
	glEnable(GL_LIGHT3);

  // Setup Viewpoint Light Source
	setupViewpointLightSource();
}

/*
 * Purpose: Defined function to handle keyboard input
 */
void handleKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'r':
	case 'R':
		if (red_light_on) {
			glDisable(GL_LIGHT1);
			setColor(red_light_diffuse, grayColor);
		} else {
			setColor(red_light_diffuse, redColor);
			glEnable(GL_LIGHT1);
		}
		toggleSwitch(red_light_on);
		break;
	case 'g':
	case 'G':
		if (green_light_on) {
			glDisable(GL_LIGHT2);
			setColor(green_light_diffuse, grayColor);
		} else {
			setColor(green_light_diffuse, greenColor);
			glEnable(GL_LIGHT2);
		}
		toggleSwitch(green_light_on);
		break;
	case 'b':
	case 'B':
		if (blue_light_on) {
			glDisable(GL_LIGHT3);
			setColor(blue_light_diffuse, grayColor);
		} else {
			setColor(blue_light_diffuse, blueColor);
			glEnable(GL_LIGHT3);
		}
		toggleSwitch(blue_light_on);
		break;
	case 'a':
	case 'A':
		toggleSwitch(rotateLight);
		break;
	case 'l':
	case 'L':
		if (ambient_light_on) {
			// setColor(ambientLight, blackColor);
			setColor(ambientLight, noAmbientWhiteColor);
		} else {
			setColor(ambientLight, ambientWhiteColor);
		}
		toggleSwitch(ambient_light_on);
		break;
	case 'v':
	case 'V':
		if (viewpoint_light_on) {
			glDisable(GL_LIGHT0);
		} else {
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

/*
 * Purpose: Defined function to handle mouse input
 */
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

/*
 * Purpose: Defined function to handle mouse movement
 */
void handleMouseMove(int x, int y) {
	if (mouseDown) {
		rotateX += (y - lastMouseY) * 0.5;
		rotateY += (x - lastMouseX) * 0.5;
		lastMouseX = x;
		lastMouseY = y;
		glutPostRedisplay();
	}
}

/*
 * Purpose: Defined function to update values and based on frequency of re-rendering
*/
void timer(int value) {
	if (rotateLight) {
		rotateLightAngle = (rotateLightAngle + 1) % 360;
	}
	glutPostRedisplay();
	glutTimerFunc(MSEC, timer, 1);
}


int main(int argc, char** argv) {

	// Initializing GLUT
	glutInit(&argc, argv) ;

	// Set the display mode
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	// Define the window width x height
	glutInitWindowSize((int)WINDOW_X, (int)WINDOW_Y);
	// Define the window position
	glutInitWindowPosition(50, 50) ;
	// Creating a GLUT window
	glutCreateWindow("Teapot Lighting") ;


	// Setting Intial Parameters
	init() ;
	// Setting up the lights
	setupLights();


	// Setting a display function
	glutDisplayFunc(display) ;

	// Reshape function
	glutReshapeFunc(reshape) ;

	// Glut timer function for re-rendering
	glutTimerFunc(MSEC, timer, 1) ;

	// Keyboard function to handle keyboard input
	glutKeyboardFunc(handleKeyboard);

	// Mouse function to handle mouse input
	glutMouseFunc(handleMouse);

	// Mouse function to handle mouse movement
	glutMotionFunc(handleMouseMove);

	// Calling the main loop
	glutMainLoop();
	return 0;
}