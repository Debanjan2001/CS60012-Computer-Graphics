/* Simple starter code to test if the openGL setup is working properly in your system  */
/* Opens a window and displays the Utah teapot */

#ifdef __APPLE__
  #include <GLUT/glut.h>
#else 
  #include <GL/glut.h>
#endif

void display ()
{
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    
    glBegin(GL_LINES);
        glColor3f(0,0,0);
        glVertex2f(20, 20);
        glVertex2f(400, 20);
        glVertex2f(20, 20);
        glVertex2f(20, 400);
    glEnd();


    glPointSize(5);
    glBegin(GL_POINTS);
        glVertex2f(100, 50);
        glVertex2f(100, 150);
        glVertex2f(200, 200);
    glEnd();

    glBegin(GL_TRIANGLES);
        glColor3f(0.1, 0.2, 0.3);
        glVertex2f(200, 100);
        glVertex2f(300, 100);
        glVertex2f(250, 200);
    glEnd();

    glColor3f(1,0,0);
    glRectf(250,250,350,350);

    glFlush();
}

int main ( int argc, char * argv[] )
{
    glutInit(&argc,argv);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_RGB);
    glutCreateWindow("My first openGL program!");
    glutDisplayFunc(display);
    glutMainLoop();
}