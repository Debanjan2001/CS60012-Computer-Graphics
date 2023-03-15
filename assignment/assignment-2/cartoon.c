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

#define CAR_HEIGHT          100.0
#define CAR_WHEEL_RADIUS    40.0
#define WHEEL_RIM_RADIUS    33.0
#define CAR_VELOCITY        3

#define MSEC                30

static int sun_rotation     = 0;
static int car_translateX   = 0;
static int wheel_rotation   = 0;


// Initial parameters: Clear the screen, set shading...
void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_FLAT);
}

void drawSky(){
    glBegin(GL_POLYGON);
        // Sky Color
        glColor3f(0.06, 0.71, 0.94);
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
        glColor3f(0.04, 0.9, 0.16);
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
        glColor3f(0.24, 0.27, 0.28);
        glVertex3f(-WINDOW_X/2, -2*WINDOW_Y/5, -FAR/4);
        glVertex3f(WINDOW_X/2, -2*WINDOW_Y/5, -FAR/4);
        glVertex3f(WINDOW_X/2, -WINDOW_Y/5, -FAR/4);
        glVertex3f(-WINDOW_X/2, -WINDOW_Y/5, -FAR/4);
    glEnd();

    // The Road Markings/Divider
    glBegin(GL_POLYGON);
        // Road Color
        glColor3f(1.0, 1.0, 1.0);
        glVertex3f(-WINDOW_X/2, -8*WINDOW_Y/25, -FAR/4);
        glVertex3f(WINDOW_X/2, -8*WINDOW_Y/25, -FAR/4);
        glVertex3f(WINDOW_X/2, -7*WINDOW_Y/25, -FAR/4);
        glVertex3f(-WINDOW_X/2, -7*WINDOW_Y/25, -FAR/4);
    glEnd();
    glFlush();
}

void drawHouse(){

}

void drawSun(){
    glPushMatrix();
    glRotatef((GLfloat) sun_rotation, 0.0, 0.0, 1.0);
    // Sun Color
    glColor3f(1.0, 0.9, 0.0);
    
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
        glColor3f(0.0, 0.0, 0.0);
        for(double theta=0.0; theta < 360.0; theta+=0.1){
            glVertex3f(CAR_WHEEL_RADIUS*cos(theta), CAR_WHEEL_RADIUS*sin(theta), 0.0);
        }
    glEnd();

    glBegin(GL_POLYGON);
        // Rim Color
        glColor3f(0.38, 0.4, 0.43);
        for(double theta=0.0; theta < 360.0; theta+=0.1){
            glVertex3f(WHEEL_RIM_RADIUS*cos(theta), WHEEL_RIM_RADIUS*sin(theta), 0.0);
        }
    glEnd();

    glBegin(GL_POLYGON);
        // Center Color
        glColor3f(0.0, 0.0, 0.0);
        for(double theta=0.0; theta < 360.0; theta+=0.1){
            glVertex3f(10.0*cos(theta), 10.0*sin(theta), 0.0);
        }
    glEnd();

    glLineWidth(1.5);
    for(double theta=0.0; theta < 360.0; theta += 20.0){
        glRotatef(20.0, 0.0, 0.0, 1.0);
        glBegin(GL_LINES);
            glVertex3f(-CAR_WHEEL_RADIUS, 0.0, 0.0);
            glVertex3f(CAR_WHEEL_RADIUS, 0.0, 0.0);
        glEnd();
    }

    glPopMatrix();
    glFlush();
}

void drawCar(){
    glPushMatrix();
    glTranslatef(car_translateX, 0.0, 0.0);
    
    // Car Color
    glColor3f(0.13, 0.1, 0.87);
    glBegin(GL_POLYGON);
        glVertex3f(-WINDOW_X/10, 0, 0.0);
        glVertex3f(WINDOW_X/10, 0, 0.0);
        glVertex3f(WINDOW_X/10, CAR_HEIGHT, 0.0);
        glVertex3f(-WINDOW_X/10, CAR_HEIGHT, 0.0);
    glEnd();

    // Draw the Wheels 
    glTranslatef(-60, 0.0, -50.0);
    drawCarWheel();
    glTranslatef(+120, 0.0, 0.0);
    drawCarWheel();

    glPopMatrix();
    glFlush();
}

/*
 * Purpose: Display function for rendering the ball
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
    glTranslatef(-5*WINDOW_X/20, -15*WINDOW_Y/50, -FAR/4);
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
    if(car_translateX > WINDOW_X){
        car_translateX = -WINDOW_X/2 + 50;
    }
    wheel_rotation = (int)(wheel_rotation - (int)(36.0*CAR_VELOCITY*MSEC)/(20*3.14*CAR_WHEEL_RADIUS)) % 360;

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