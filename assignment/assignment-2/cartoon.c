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

#define WINDOW_X       1024.0
#define WINDOW_Y       768.0 
#define FAR           600.0
#define NEAR         -600.0

#define MSEC            10

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
    
    // Calling the main loop
    glutMainLoop() ;
}