/* Rotates a solid cube around it's center */

#include <math.h>
#include <stdlib.h>
#ifdef __APPLE__
  #include <GLUT/glut.h>
#else 
  #include <GL/glut.h>
#endif

GLfloat xRotated, yRotated, zRotated;


void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0,0.0,-4.0);
	glRotatef(xRotated,1.0,0.0,0.0);
	glRotatef(yRotated,0.0,1.0,0.0);
	glRotatef(zRotated,0.0,0.0,1.0);
	glScalef(2.0,1.0,1.0);
	glutSolidCube(1.0);
	glFlush();
	glutSwapBuffers();
}

void Reshape(int x, int y)
{
	if (y == 0 || x == 0) return; 
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();
	
	gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0,0,x,y);  //Use the whole window for rendering
}

void Idle(void)
{
	xRotated += 0.3;
	yRotated += 0.1;
	zRotated += -0.4;
	Display();
}


int main (int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  //For animations you should use double buffering
	glutInitWindowSize(300,300);
	glutCreateWindow("Rotating cube");
	xRotated = yRotated = zRotated = 0.0;
	glClearColor(0.0,0.0,0.0,0.0);
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Idle);
	glutMainLoop();
	return 0;
}
