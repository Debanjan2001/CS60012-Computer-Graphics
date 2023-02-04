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
    glutSolidTeapot(.5);
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