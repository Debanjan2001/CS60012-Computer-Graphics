/*
 * Name- Debanjan Saha
 * Roll- 19CS30014
 * Email- debanjansaha2001@gmail.com
 * Assignment- 2
 * Description- A simple animation of a cartoon scene
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
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

// Sun Radius
#define SUN_RADIUS          50.0

// Mathematical Constant pi
#define PI                  acos(-1.0)

// Car Characteristics
#define CAR_HEIGHT          100.0
#define CAR_WIDTH           250.0
#define CAR_WHEEL_RADIUS    38.0
#define WHEEL_RIM_RADIUS    32.0
#define CAR_VELOCITY        3

// House Characteristics
#define HOUSE_WINDOW_SIDE   80.0
#define HOUSE_DOOR_HEIGHT   130.0
#define HOUSE_DOOR_WIDTH    100.0

// Tree Characteristics
#define TREE_HEIGHT         150.0

// Frequency of re-rendering
#define MSEC                30

// Static variables for animation
static int sun_rotation     = 0;
static int car_translateX   = 0;
static int wheel_rotation   = 0;

// OpenGL Color Constants
GLfloat const WHITE_COLOR[] = {1.0, 1.0, 1.0};
GLfloat const BLACK_COLOR[] = {0.0, 0.0, 0.0};
GLfloat const BROWN_COLOR[] = {0.34, 0.05, 0.06};

// OpenGL Color Constants for different objects to be drawn
// These colors were picked using a color picker.
GLfloat const SKY_COLOR[] = {0.06, 0.71, 0.94};
GLfloat const GRASS_COLOR[] = {0.04, 0.9, 0.16};
GLfloat const ROAD_COLOR[] = {0.24, 0.27, 0.28};
GLfloat const SUN_COLOR[] = {1.0, 0.9, 0.0};
GLfloat const HOUSE_OUTER_WALL_COLOR[] = {0.81, 0.16, 0.16};
GLfloat const HOUSE_DOOR_INNER_WALL_COLOR[] = {0.85, 0.63, 0.08};
GLfloat const HOUSE_WINDOW_INNER_WALL_COLOR[] = {0.7, 0.33, 0.49};
GLfloat const CAR_COLOR[] = {0.13, 0.08, 0.76};
GLfloat const CAR_WHEEL_RIM_COLOR[] = {0.56, 0.61, 0.67};
GLfloat const CAR_GLASS_COLOR[] = {0.7, 0.86, 0.87};
GLfloat const TREE_LEAF_COLOR[] = {0.13, 0.53, 0.03};

// Purpose: Set Initial parameters: Clear the screen, set shading
void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_FLAT);
}

/*
 * Purpose: Draw the sky using Sky Color
*/
void drawSky() {
    glPushMatrix();
    glBegin(GL_POLYGON);
        // Sky Color
        glColor3fv(SKY_COLOR);
        glVertex3f(-WINDOW_X / 2, -WINDOW_Y / 10, -FAR / 2);
        glVertex3f(WINDOW_X / 2, -WINDOW_Y / 10, -FAR / 2);
        glVertex3f(WINDOW_X / 2, WINDOW_Y / 2, -FAR / 2);
        glVertex3f(-WINDOW_X / 2, WINDOW_Y / 2, -FAR / 2);
    glEnd();
    glPopMatrix();
    glFlush();
}

/*
 * Purpose: Draw Ground using Grass Color
*/
void drawGround() {
    glPushMatrix();
    glBegin(GL_POLYGON);
        // Grass Color
        glColor3fv(GRASS_COLOR);
        glVertex3f(WINDOW_X / 2, -WINDOW_Y / 10, -FAR / 2);
        glVertex3f(-WINDOW_X / 2, -WINDOW_Y / 10, -FAR / 2);
        glVertex3f(-WINDOW_X / 2, -WINDOW_Y / 2, -FAR / 2);
        glVertex3f(WINDOW_X / 2, -WINDOW_Y / 2, -FAR / 2);
    glEnd();
    glPopMatrix();
    glFlush();
}

/*
 * Purpose:
 *      Draw Road on top of ground
 *      Draws a pitch coloured road
 *      Draws a white colored divider on top of it
*/
void drawRoad() {
    glPushMatrix();
    // The Road
    glBegin(GL_POLYGON);
        // Road Color
        glColor3fv(ROAD_COLOR);
        glVertex3f(-WINDOW_X / 2, -2 * WINDOW_Y / 5, -FAR / 4);
        glVertex3f(WINDOW_X / 2, -2 * WINDOW_Y / 5, -FAR / 4);
        glVertex3f(WINDOW_X / 2, -WINDOW_Y / 5, -FAR / 4);
        glVertex3f(-WINDOW_X / 2, -WINDOW_Y / 5, -FAR / 4);
    glEnd();

    // The Road Markings/Divider
    glBegin(GL_POLYGON);
        // Road Color
        glColor3fv(WHITE_COLOR);
        glVertex3f(-WINDOW_X / 2, -8 * WINDOW_Y / 25, -FAR / 4);
        glVertex3f(WINDOW_X / 2, -8 * WINDOW_Y / 25, -FAR / 4);
        glVertex3f(WINDOW_X / 2, -7 * WINDOW_Y / 25, -FAR / 4);
        glVertex3f(-WINDOW_X / 2, -7 * WINDOW_Y / 25, -FAR / 4);
    glEnd();
    glPopMatrix();
    glFlush();
}

/*
 * Purpose:
        Utility function for drawHouse()
        Draws a window for the house around the current origin
        Draws an inner wall visible from the window
        Draws 2 window bars
*/
void drawHouseWindow() {
    glPushMatrix();
    // The Window
    glBegin(GL_POLYGON);
        // Window Color
        glColor3fv(BROWN_COLOR);
        glVertex3f(-HOUSE_WINDOW_SIDE / 2, -HOUSE_WINDOW_SIDE / 2, 0.0);
        glVertex3f(HOUSE_WINDOW_SIDE / 2, -HOUSE_WINDOW_SIDE / 2, 0.0);
        glVertex3f(HOUSE_WINDOW_SIDE / 2, HOUSE_WINDOW_SIDE / 2, 0.0);
        glVertex3f(-HOUSE_WINDOW_SIDE / 2, HOUSE_WINDOW_SIDE / 2, 0.0);
    glEnd();

    // Draw the visible inner side of the house
    glBegin(GL_POLYGON);
        glColor3fv(HOUSE_WINDOW_INNER_WALL_COLOR);
        glVertex3f(-HOUSE_WINDOW_SIDE / 2 + 10, -HOUSE_WINDOW_SIDE / 2 + 5, 0.0);
        glVertex3f(HOUSE_WINDOW_SIDE / 2 - 5, -HOUSE_WINDOW_SIDE / 2 + 5, 0.0);
        glVertex3f(HOUSE_WINDOW_SIDE / 2 - 5, HOUSE_WINDOW_SIDE / 2 - 5, 0.0);
        glVertex3f(-HOUSE_WINDOW_SIDE / 2 + 10, HOUSE_WINDOW_SIDE / 2 - 5, 0.0);
    glEnd();

    // Put 2 bars on the windows
    glLineWidth(5.0);
    glBegin(GL_LINES);
        glColor3fv(BROWN_COLOR);
        glVertex3f(-HOUSE_WINDOW_SIDE / 6, -HOUSE_WINDOW_SIDE / 2, 0.0);
        glVertex3f(-HOUSE_WINDOW_SIDE / 6, HOUSE_WINDOW_SIDE / 2, 0.0);

        glVertex3f(HOUSE_WINDOW_SIDE / 6, -HOUSE_WINDOW_SIDE / 2, 0.0);
        glVertex3f(HOUSE_WINDOW_SIDE / 6, HOUSE_WINDOW_SIDE / 2, 0.0);
    glEnd();
    glPopMatrix();
    glFlush();
}

/*
 * Purpose:
 *      Utility Function for drawHouse()
 *      Draws a rectangular door space showing inner walls in the house around the current origin
 *      Draws a door which looks as if the door is open
*/
void drawHouseDoor() {
    // Draw the inner side of the house
    glPushMatrix();
    glBegin(GL_POLYGON);
        glColor3fv(HOUSE_DOOR_INNER_WALL_COLOR);
        glVertex3f(-HOUSE_DOOR_WIDTH / 2, -HOUSE_DOOR_HEIGHT / 2, 0.0);
        glVertex3f(HOUSE_DOOR_WIDTH / 2, -HOUSE_DOOR_HEIGHT / 2, 0.0);
        glVertex3f(HOUSE_DOOR_WIDTH / 2, HOUSE_DOOR_HEIGHT / 2, 0.0);
        glVertex3f(-HOUSE_DOOR_WIDTH / 2, HOUSE_DOOR_HEIGHT / 2, 0.0);
    glEnd();

    // Draw the door covering the inner walls of the house
    glBegin(GL_POLYGON);
        glColor3fv(BROWN_COLOR);
        glVertex3f(-HOUSE_DOOR_WIDTH / 2, -HOUSE_DOOR_HEIGHT / 2, 0.0);
        glVertex3f(HOUSE_DOOR_WIDTH / 4 , -HOUSE_DOOR_HEIGHT / 3, 0.0);
        glVertex3f(HOUSE_DOOR_WIDTH / 4, HOUSE_DOOR_HEIGHT / 3, 0.0);
        glVertex3f(-HOUSE_DOOR_WIDTH / 2, HOUSE_DOOR_HEIGHT / 2, 0.0);
    glEnd();
    glPopMatrix();
    glFlush();
}

/*
 * Purpose:
 *      Draws the house using above utility functions
 *      Draws the outer wall, Roof
 *      Applies translation to proper window locations and draws windows using drawHouseWindow() function
 *      Applies translation to proper door location and draws door using drawHouseDoor() function
*/
void drawHouse() {
    glPushMatrix();
    glTranslatef(0.0, -WINDOW_Y / 25, 0.0);
    // Draw wall
    glBegin(GL_POLYGON);
        // House Color
        glColor3fv(HOUSE_OUTER_WALL_COLOR);
        glVertex3f(-WINDOW_X / 6, -WINDOW_Y / 7, -FAR / 4);
        glVertex3f(WINDOW_X / 6, -WINDOW_Y / 7, -FAR / 4);
        glVertex3f(WINDOW_X / 6, WINDOW_Y / 6, -FAR / 4);
        glVertex3f(-WINDOW_X / 6, WINDOW_Y / 6, -FAR / 4);
    glEnd();

    // Draw roof
    glBegin(GL_POLYGON);
        // Roof Color
        glColor3fv(BROWN_COLOR);
        glVertex3f(-WINDOW_X / 6 - 10, WINDOW_Y / 6 + 50, -FAR / 4);
        glVertex3f(WINDOW_X / 6 + 10, WINDOW_Y / 6 + 50, -FAR / 4);
        glVertex3f(WINDOW_X / 6 + 10, WINDOW_Y / 6 - 50, -FAR / 4);
        glVertex3f(-WINDOW_X / 6 - 10, WINDOW_Y / 6 - 50, -FAR / 4);
    glEnd();

    glPushMatrix();
    glTranslatef(-WINDOW_X / 12 - 20, 0.0, -FAR / 4);
    // Draw window
    drawHouseWindow();
    glTranslatef(WINDOW_X / 6 + 40, 0.0, 0.0);
    // Draw window
    drawHouseWindow();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, -WINDOW_Y / 7 + HOUSE_DOOR_HEIGHT / 2, -FAR / 4);
    // Draw Door
    drawHouseDoor();
    glPopMatrix();

    glPopMatrix();
    glFlush();
}

/*
 * Purpose:
 *      Draw Sun using GL_POLYGON and several points around the circle
 *      Draw the Sun rays using GL_LINES
*/
void drawSun() {
    glPushMatrix();
    glRotatef((GLfloat) sun_rotation, 0.0, 0.0, 1.0);
    // Sun Color
    glColor3fv(SUN_COLOR);

    glBegin(GL_POLYGON);
        for (double theta = 0.0; theta < 360.0; theta += 0.1) {
            glVertex3f(SUN_RADIUS * cos(theta), SUN_RADIUS * sin(theta), 0.0);
        }
    glEnd();

    glLineWidth(2.0);
    for (double theta = 0.0; theta < 360.0; theta += 30.0) {
        glRotatef(30.0, 0.0, 0.0, 1.0);
        glBegin(GL_LINES);
            glVertex3f(-2 * SUN_RADIUS, 0.0, 0.0);
            glVertex3f(2 * SUN_RADIUS, 0.0, 0.0);
        glEnd();
    }

    glPopMatrix();
    glFlush();
}

/*
 * Purpose:
 *      Utility function for drawCar()
 *      Draws the tire, rim and center of the wheel using GL_POLYGON Mode
 *      Draws the wheel spokes using GL_LINES
 *      Applies a careful rotation of car wheel using static variable 'wheel_rotation'
*/
void drawCarWheel() {
    glPushMatrix();
    glRotatef((GLfloat) wheel_rotation, 0.0, 0.0, 1.0);

    glBegin(GL_POLYGON);
        // Tire Color
        glColor3fv(BLACK_COLOR);
        for (double theta = 0.0; theta < 360.0; theta += 0.1) {
            glVertex3f(CAR_WHEEL_RADIUS * cos(theta), CAR_WHEEL_RADIUS * sin(theta), 0.0);
        }
    glEnd();

    glBegin(GL_POLYGON);
        // Rim Color
        glColor3fv(CAR_WHEEL_RIM_COLOR);
        for (double theta = 0.0; theta < 360.0; theta += 0.1) {
            glVertex3f(WHEEL_RIM_RADIUS * cos(theta), WHEEL_RIM_RADIUS * sin(theta), 1.0);
        }
    glEnd();

    glBegin(GL_POLYGON);
        // Center Color
        glColor3fv(BLACK_COLOR);
        for (double theta = 0.0; theta < 360.0; theta += 0.1) {
            glVertex3f(10.0 * cos(theta), 10.0 * sin(theta), 2.0);
        }
    glEnd();

    glLineWidth(1.5);
    for (double theta = 0.0; theta < 360.0; theta += 20.0) {
        glRotatef(20.0, 0.0, 0.0, 1.0);
        glBegin(GL_LINES);
            glVertex3f(-CAR_WHEEL_RADIUS, 0.0, 3.0);
            glVertex3f(CAR_WHEEL_RADIUS, 0.0, 3.0);
        glEnd();
    }

    glPopMatrix();
    glFlush();
}

/*
 * Purpose:
 *      Draws the car
 *      Draws the Body of the car
 *      Translates to wheel locations and draws wheels using drawCarWheel() function
 *      Applies a translation of the car using the static variable 'car_translateX'
*/
void drawCar() {
    glPushMatrix();
    glTranslatef(car_translateX, 0.0, 0.0);

    // Car Color
    glColor3fv(CAR_COLOR);
    glBegin(GL_POLYGON);
        glVertex3f(-CAR_WIDTH/2, 0, 0.0);
        glVertex3f(CAR_WIDTH/2, 0, 0.0);
        glVertex3f(CAR_WIDTH/2, CAR_HEIGHT/2, 0.0);
        glVertex3f(-CAR_WIDTH/2, CAR_HEIGHT/2, 0.0);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3f(-CAR_WIDTH/2, CAR_HEIGHT/2, 0.0);
        glVertex3f(CAR_WIDTH/2, CAR_HEIGHT/2, 0.0);
        glVertex3f(CAR_WIDTH/2 - 70, CAR_HEIGHT, 0.0);
        glVertex3f(-CAR_WIDTH/2, CAR_HEIGHT, 0.0);
    glEnd();

    // draw car front window
    glColor3fv(CAR_GLASS_COLOR);
    glBegin(GL_POLYGON);
        glVertex3f(CAR_WIDTH/15, CAR_HEIGHT/2, 0.0);
        glVertex3f(CAR_WIDTH/2 - 20, CAR_HEIGHT/2, 0.0);
        glVertex3f(CAR_WIDTH/2 - 10 - 70, CAR_HEIGHT - 10, 0.0);
        glVertex3f(CAR_WIDTH/15, CAR_HEIGHT - 10, 0.0);
    glEnd();

    // draw car rear window
    glBegin(GL_POLYGON);
        glVertex3f(0.0, CAR_HEIGHT/2, 0.0);
        glVertex3f(-CAR_WIDTH/2 + 20, CAR_HEIGHT/2, 0.0);
        glVertex3f(-CAR_WIDTH/2 + 20, CAR_HEIGHT - 10, 0.0);
        glVertex3f(0.0, CAR_HEIGHT - 10, 0.0);
    glEnd();

    glPushMatrix();
    glTranslatef(-CAR_WIDTH/4, 0.0, 1.0);
    // Draw the Wheels
    drawCarWheel();

    glTranslatef(CAR_WIDTH/2, 0.0, 0.0);
    // Draw the Wheels
    drawCarWheel();
    glPopMatrix();

    glPopMatrix();
    glFlush();
}

/*
 * +-----------------------------+
 * |       Some aesthetics       |
 * +-----------------------------+
*/
/*
 * Purpose: 
 *      Draws leaves of the tree
 *      Uses GL_TRIANGLES to draw the leaves 
*/
void drawLeaves(){
    glPushMatrix();
    glBegin(GL_TRIANGLES);
        glColor3fv(TREE_LEAF_COLOR);
        glVertex3f(-TREE_HEIGHT/4, 0.0, 0.0);
        glVertex3f(TREE_HEIGHT/4, 0.0, 0.0);
        glVertex3f(0.0, TREE_HEIGHT/3, 0.0);
    glEnd();
    glPopMatrix();
    glFlush();
}

/*
 * Purpose:
 *      Draws the tree trunk using GL_LINES
 *      Uses utility function drawLeaves() to draw the leaves
*/
void drawTree(){
    glPushMatrix();
    // Draw The Trunk 
    glLineWidth(10.0);
    glBegin(GL_LINES);
        glColor3fv(BROWN_COLOR);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, TREE_HEIGHT, 0.0);
    glEnd();
    
    // Draw The Leaves
    glTranslatef(0.0, TREE_HEIGHT, 0.0);
    for(int i=0; i<3; ++i){
        glTranslatef(0.0, -TREE_HEIGHT/5, 0.0);
        drawLeaves();
    }

    glPopMatrix();
    glFlush();
}

/*
 * Purpose: Display function for rendering the animation scene
*/
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT) ;

    // Draw Sky
    drawSky();

    // Draw Ground
    drawGround();

    // Draw Road
    drawRoad();

    // Draw House
    drawHouse();

    // Set Initial Position of Sun
    glPushMatrix();
    glTranslatef(3 * WINDOW_X / 10, 3 * WINDOW_Y / 10, -FAR / 4);
    // Draw Sun
    drawSun();
    glPopMatrix();


    glPushMatrix();
    // Set Initial Position of Tree
    glTranslatef(-WINDOW_X/3, -WINDOW_Y / 10, -FAR / 4 + 1);
    // Draw Tree
    drawTree();
    glTranslatef(2*WINDOW_X/3, 0.0, 0.0);
    // Draw Tree
    drawTree();
    glPopMatrix();


    // Set Initial Position of Car
    glPushMatrix();
    glTranslatef(-WINDOW_X / 2, -15 * WINDOW_Y / 50, -FAR / 4 + 1);
    // Draw Car
    drawCar();
    glPopMatrix();

    glutSwapBuffers();
}


/*
 * Reshape function for defining viewport, setting up orthographic projection etc.
*/
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Get a Flat view
    glOrtho((double) - WINDOW_X / 2, (double)WINDOW_X / 2, (double) - WINDOW_Y / 2, (double)WINDOW_Y / 2, NEAR, FAR);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/*
 * Purpose:
 *      GLUT Timer Function for the animation
 *      Updates the static variables in every `MSEC` duration for a smooth animated scene
*/
void timer(int value) {
    sun_rotation = (sun_rotation - 1) % 360;
    car_translateX = (car_translateX + CAR_VELOCITY);
    if (car_translateX > WINDOW_X + CAR_WIDTH) {
        car_translateX = -CAR_WIDTH / 2;
    }
    wheel_rotation = (int)(wheel_rotation - (int)(360.0 * CAR_VELOCITY) / (2 * PI * CAR_WHEEL_RADIUS)) % 360;

    glutPostRedisplay();
    glutTimerFunc(MSEC, timer, 1);
}

// Main function
int main(int argc, char** argv)
{
    // Initializing GLUT
    glutInit(&argc, argv) ;

    // Set the display mode
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Define the window width x height
    glutInitWindowSize((int)WINDOW_X, (int)WINDOW_Y);

    // Define the window position
    glutInitWindowPosition(100, 100) ;

    // Creating a GLUT window
    glutCreateWindow("A simple animation of a Cartoon scene") ;

    // Setting Intial Parameters
    init() ;

    // Setting a display function
    glutDisplayFunc(display) ;
    glutReshapeFunc(reshape) ;
    glutTimerFunc(MSEC, timer, 1) ;

    // Calling the main loop
    glutMainLoop() ;
}

/**
 * Important Note for Self:
 * You have to enable GL_DEPTH_BUFFER_BIT if you wish to draw based on depth of z co-ordinates
 * Otherwise, next element will get drawn over the previous one
 * also you have to change the z-coordinates of the objects to get the desired effect
*/