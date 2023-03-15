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

#define WINDOW_X        1200.0
#define WINDOW_Y        800.0 
#define FAR             600.0
#define NEAR           -600.0

#define SUN_RADIUS      50.0

#define MSEC            50

static int sun_rotation = 0;


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

    // The Road Markings
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
    glTranslatef(3*WINDOW_X/10, 3*WINDOW_Y/10, 0.0);
    glRotatef((GLfloat) sun_rotation, 0.0, 0.0, 1.0);
    // Sun Color
    glColor3f(1.0, 0.9, 0.0);
    
    glBegin(GL_POLYGON);
        for(double theta=0.0; theta < 360.0; theta+=0.1){
            glVertex3f(SUN_RADIUS*cos(theta), SUN_RADIUS*sin(theta), -FAR/4);
        }
    glEnd();

    glLineWidth(2.0);
        for(double theta=0.0; theta < 360.0; theta += 30.0){
            glRotatef(30.0, 0.0, 0.0, 1.0);
            glBegin(GL_LINES);
                glVertex3f(-2*SUN_RADIUS, 0.0, -FAR/4);
                glVertex3f(2*SUN_RADIUS, 0.0, -FAR/4);
            glEnd();
        }
    
    glPopMatrix();
    glFlush();
}

void drawCar(){
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

    // Draw Sun
    drawSun();

    // Draw Car
    drawCar();

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
    sun_rotation = (sun_rotation + 1) % 360;
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