/* Simple starter code to test if the openGL setup is working properly in your system  */
/* Opens a window and displays the Utah teapot */

#ifdef __APPLE__
  #include <GLUT/glut.h>
#else 
  #include <GL/glut.h>
#endif

void display ()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,1.0,0.0);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, 1, 1, 0.0f, 0.0f, 1.0f);
    
    glBegin(GL_POLYGON);
    glVertex2f(0.25, 0.25);
    glVertex2f(0.75, 0.25);
    glVertex2f(0.75, 0.75);
    glVertex2f(0.25, 0.75);
    glEnd();
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
