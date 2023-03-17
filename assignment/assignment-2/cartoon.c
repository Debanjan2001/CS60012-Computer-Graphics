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

#define WINDOW_X            1200.0
#define WINDOW_Y            800.0 
#define FAR                 600.0
#define NEAR                -600.0

#define SUN_RADIUS          50.0

#define PI                  acos(-1.0)

#define CAR_HEIGHT          100.0
#define CAR_WIDTH           250.0
#define CAR_WHEEL_RADIUS    40.0
#define WHEEL_RIM_RADIUS    33.0
#define CAR_VELOCITY        3

#define HOUSE_WINDOW_SIDE   80.0
#define HOUSE_DOOR_HEIGHT   130.0
#define HOUSE_DOOR_WIDTH    100.0

#define MSEC                30

static int sun_rotation     = 0;
static int car_translateX   = 0;
static int wheel_rotation   = 0;

GLfloat const WHITE_COLOR[] = {1.0, 1.0, 1.0};
GLfloat const BLACK_COLOR[] = {0.0, 0.0, 0.0};
GLfloat const BROWN_COLOR[] = {0.34, 0.05, 0.06};

GLfloat const SKY_COLOR[] = {0.06, 0.71, 0.94};
GLfloat const GRASS_COLOR[] = {0.04, 0.9, 0.16};
GLfloat const ROAD_COLOR[] = {0.24, 0.27, 0.28};
GLfloat const SUN_COLOR[] = {1.0, 0.9, 0.0};
GLfloat const HOUSE_OUTER_WALL_COLOR[] = {0.81, 0.16, 0.16};
GLfloat const HOUSE_DOOR_INNER_WALL_COLOR[] = {0.85, 0.63, 0.08};
GLfloat const HOUSE_WINDOW_INNER_WALL_COLOR[] = {0.7, 0.33, 0.49};
GLfloat const CAR_COLOR[] = {0.13, 0.08, 0.76};
GLfloat const CAR_WHEEL_RIM_COLOR[] = {0.56, 0.61, 0.67};


// Initial parameters: Clear the screen, set shading...
void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_FLAT);
}

void drawSky(){
    glBegin(GL_POLYGON);
        // Sky Color
        glColor3fv(SKY_COLOR);
        glVertex3f(-WINDOW_X/2, -WINDOW_Y/10, -FAR/2);
        glVertex3f(WINDOW_X/2, -WINDOW_Y/10, -FAR/2);
        glVertex3f(WINDOW_X/2, WINDOW_Y/2, -FAR/2);
        glVertex3f(-WINDOW_X/2, WINDOW_Y/2, -FAR/2);
    glEnd();
    glFlush();
}

void drawGround(){
    glBegin(GL_POLYGON);
        // Grass Color
        glColor3fv(GRASS_COLOR);
        glVertex3f(WINDOW_X/2, -WINDOW_Y/10, -FAR/2);
        glVertex3f(-WINDOW_X/2, -WINDOW_Y/10, -FAR/2);
        glVertex3f(-WINDOW_X/2, -WINDOW_Y/2, -FAR/2);
        glVertex3f(WINDOW_X/2, -WINDOW_Y/2, -FAR/2);
    glEnd();
    glFlush();
}

void drawRoad(){
    // The Road
    glBegin(GL_POLYGON);
        // Road Color
        glColor3fv(ROAD_COLOR);
        glVertex3f(-WINDOW_X/2, -2*WINDOW_Y/5, -FAR/4);
        glVertex3f(WINDOW_X/2, -2*WINDOW_Y/5, -FAR/4);
        glVertex3f(WINDOW_X/2, -WINDOW_Y/5, -FAR/4);
        glVertex3f(-WINDOW_X/2, -WINDOW_Y/5, -FAR/4);
    glEnd();

    // The Road Markings/Divider
    glBegin(GL_POLYGON);
        // Road Color
        glColor3fv(WHITE_COLOR);
        glVertex3f(-WINDOW_X/2, -8*WINDOW_Y/25, -FAR/4);
        glVertex3f(WINDOW_X/2, -8*WINDOW_Y/25, -FAR/4);
        glVertex3f(WINDOW_X/2, -7*WINDOW_Y/25, -FAR/4);
        glVertex3f(-WINDOW_X/2, -7*WINDOW_Y/25, -FAR/4);
    glEnd();
    glFlush();
}

void drawHouseWindow(){
    // The Window
    glBegin(GL_POLYGON);
        // Window Color
        glColor3fv(BROWN_COLOR);
        glVertex3f(-HOUSE_WINDOW_SIDE/2, -HOUSE_WINDOW_SIDE/2, 0.0);
        glVertex3f(HOUSE_WINDOW_SIDE/2, -HOUSE_WINDOW_SIDE/2, 0.0);
        glVertex3f(HOUSE_WINDOW_SIDE/2, HOUSE_WINDOW_SIDE/2, 0.0);
        glVertex3f(-HOUSE_WINDOW_SIDE/2, HOUSE_WINDOW_SIDE/2, 0.0);
    glEnd();

    // Draw the visible inner side of the house
    glBegin(GL_POLYGON);
        glColor3fv(HOUSE_WINDOW_INNER_WALL_COLOR);
        glVertex3f(-HOUSE_WINDOW_SIDE/2 + 10, -HOUSE_WINDOW_SIDE/2 + 5, 0.0);
        glVertex3f(HOUSE_WINDOW_SIDE/2 - 5, -HOUSE_WINDOW_SIDE/2 + 5, 0.0);
        glVertex3f(HOUSE_WINDOW_SIDE/2 - 5, HOUSE_WINDOW_SIDE/2 - 5, 0.0);
        glVertex3f(-HOUSE_WINDOW_SIDE/2 + 10, HOUSE_WINDOW_SIDE/2 - 5, 0.0);
    glEnd();

    // Put 2 bars on the windows
    glLineWidth(5.0);
    glBegin(GL_LINES);
        glColor3fv(BROWN_COLOR);
        glVertex3f(-HOUSE_WINDOW_SIDE/6, -HOUSE_WINDOW_SIDE/2, 0.0);
        glVertex3f(-HOUSE_WINDOW_SIDE/6, HOUSE_WINDOW_SIDE/2, 0.0);

        glVertex3f(HOUSE_WINDOW_SIDE/6, -HOUSE_WINDOW_SIDE/2, 0.0);
        glVertex3f(HOUSE_WINDOW_SIDE/6, HOUSE_WINDOW_SIDE/2, 0.0);
    glEnd();
    glFlush();
}

void drawHouseDoor(){
    // Draw the inner side of the house
    glBegin(GL_POLYGON);
        glColor3fv(HOUSE_DOOR_INNER_WALL_COLOR);
        glVertex3f(-HOUSE_DOOR_WIDTH/2, -HOUSE_DOOR_HEIGHT/2, 0.0);
        glVertex3f(HOUSE_DOOR_WIDTH/2, -HOUSE_DOOR_HEIGHT/2, 0.0);
        glVertex3f(HOUSE_DOOR_WIDTH/2, HOUSE_DOOR_HEIGHT/2, 0.0);
        glVertex3f(-HOUSE_DOOR_WIDTH/2, HOUSE_DOOR_HEIGHT/2, 0.0);
    glEnd();

    // Draw the door covering the inner walls of the house
    glBegin(GL_POLYGON);
        glColor3fv(BROWN_COLOR);
        glVertex3f(-HOUSE_DOOR_WIDTH/2, -HOUSE_DOOR_HEIGHT/2, 0.0);
        glVertex3f(HOUSE_DOOR_WIDTH/4 , -HOUSE_DOOR_HEIGHT/3, 0.0);
        glVertex3f(HOUSE_DOOR_WIDTH/4, HOUSE_DOOR_HEIGHT/3, 0.0);
        glVertex3f(-HOUSE_DOOR_WIDTH/2, HOUSE_DOOR_HEIGHT/2, 0.0);
    glEnd();
    glFlush();
}

void drawHouse(){
    glPushMatrix();
    glTranslatef(0.0, -WINDOW_Y/25, 0.0);
    // Draw wall
    glBegin(GL_POLYGON);
        // House Color
        glColor3fv(HOUSE_OUTER_WALL_COLOR);
        glVertex3f(-WINDOW_X/6, -WINDOW_Y/7, -FAR/4);
        glVertex3f(WINDOW_X/6, -WINDOW_Y/7, -FAR/4);
        glVertex3f(WINDOW_X/6, WINDOW_Y/6, -FAR/4);
        glVertex3f(-WINDOW_X/6, WINDOW_Y/6, -FAR/4);
    glEnd();

    // Draw roof
    glBegin(GL_POLYGON);
        // Roof Color
        glColor3fv(BROWN_COLOR);
        glVertex3f(-WINDOW_X/6 - 10, WINDOW_Y/6 + 50, -FAR/4);
        glVertex3f(WINDOW_X/6 + 10, WINDOW_Y/6 + 50, -FAR/4);
        glVertex3f(WINDOW_X/6 + 10, WINDOW_Y/6 - 50, -FAR/4);
        glVertex3f(-WINDOW_X/6 - 10, WINDOW_Y/6 - 50, -FAR/4);
    glEnd();

    glPushMatrix();
    glTranslatef(-WINDOW_X/12 - 20, 0.0, -FAR/4);
    // Draw window
    drawHouseWindow();
    glTranslatef(WINDOW_X/6 + 40, 0.0, 0.0);
    // Draw window
    drawHouseWindow();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, -WINDOW_Y/7 + HOUSE_DOOR_HEIGHT/2, -FAR/4);
    // Draw Door
    drawHouseDoor();
    glPopMatrix();

    glPopMatrix();
    glFlush();
}

void drawSun(){
    glPushMatrix();
    glRotatef((GLfloat) sun_rotation, 0.0, 0.0, 1.0);
    // Sun Color
    glColor3fv(SUN_COLOR);
    
    glBegin(GL_POLYGON);
        for(double theta=0.0; theta < 360.0; theta+=0.1){
            glVertex3f(SUN_RADIUS*cos(theta), SUN_RADIUS*sin(theta), 0.0);
        }
    glEnd();

    glLineWidth(2.0);
    for(double theta=0.0; theta < 360.0; theta += 30.0){
        glRotatef(30.0, 0.0, 0.0, 1.0);
        glBegin(GL_LINES);
            glVertex3f(-2*SUN_RADIUS, 0.0, 0.0);
            glVertex3f(2*SUN_RADIUS, 0.0, 0.0);
        glEnd();
    }
    
    glPopMatrix();
    glFlush();
}

void drawCarWheel(){
    glPushMatrix();
    glRotatef((GLfloat) wheel_rotation, 0.0, 0.0, 1.0);
    
    glBegin(GL_POLYGON);
        // Tire Color
        glColor3fv(BLACK_COLOR);
        for(double theta=0.0; theta < 360.0; theta+=0.1){
            glVertex3f(CAR_WHEEL_RADIUS*cos(theta), CAR_WHEEL_RADIUS*sin(theta), 0.0);
        }
    glEnd();

    glBegin(GL_POLYGON);
        // Rim Color
        glColor3fv(CAR_WHEEL_RIM_COLOR);
        for(double theta=0.0; theta < 360.0; theta+=0.1){
            glVertex3f(WHEEL_RIM_RADIUS*cos(theta), WHEEL_RIM_RADIUS*sin(theta), 1.0);
        }
    glEnd();

    glBegin(GL_POLYGON);
        // Center Color
        glColor3fv(BLACK_COLOR);
        for(double theta=0.0; theta < 360.0; theta+=0.1){
            glVertex3f(10.0*cos(theta), 10.0*sin(theta), 2.0);
        }
    glEnd();

    glLineWidth(1.5);
    for(double theta=0.0; theta < 360.0; theta += 20.0){
        glRotatef(20.0, 0.0, 0.0, 1.0);
        glBegin(GL_LINES);
            glVertex3f(-CAR_WHEEL_RADIUS, 0.0, 3.0);
            glVertex3f(CAR_WHEEL_RADIUS, 0.0, 3.0);
        glEnd();
    }

    glPopMatrix();
    glFlush();
}

void drawCar(){
    glPushMatrix();
    glTranslatef(car_translateX, 0.0, 0.0);
    
    // Car Color
    glColor3fv(CAR_COLOR);
    glBegin(GL_POLYGON);
        glVertex3f(-CAR_WIDTH/2, 0, 0.0);
        glVertex3f(CAR_WIDTH/2, 0, 0.0);
        glVertex3f(CAR_WIDTH/2, CAR_HEIGHT, 0.0);
        glVertex3f(-CAR_WIDTH/2, CAR_HEIGHT, 0.0);
    glEnd();

    glPushMatrix();
    glTranslatef(-60, 0.0, 1.0);
    // Draw the Wheels 
    drawCarWheel();
    
    glTranslatef(+120, 0.0, 0.0);
    // Draw the Wheels 
    drawCarWheel();
    glPopMatrix();

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
    glTranslatef(3*WINDOW_X/10, 3*WINDOW_Y/10, -FAR/4);
    // Draw Sun
    drawSun();
    glPopMatrix();

    // Set Initial Position of Car
    glPushMatrix();
    glTranslatef(-WINDOW_X/2, -15*WINDOW_Y/50, -FAR/4 + 1);
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
    glOrtho((double)-WINDOW_X/2, (double)WINDOW_X/2, (double)-WINDOW_Y/2, (double)WINDOW_Y/2, NEAR, FAR);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void timer(int value){
    sun_rotation = (sun_rotation - 1) % 360;
    car_translateX = (car_translateX + CAR_VELOCITY);
    if(car_translateX > WINDOW_X + CAR_WIDTH){
        car_translateX = -CAR_WIDTH / 2;
    }
    wheel_rotation = (int)(wheel_rotation - (int)(360.0*CAR_VELOCITY)/(2*PI*CAR_WHEEL_RADIUS)) % 360;

    glutPostRedisplay();
    glutTimerFunc(MSEC, timer, 1);
}


int main(int argc, char** argv)
{
    // Initializing GLUT
    glutInit(&argc, argv) ;
    
    // Set the display mode
    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
    
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