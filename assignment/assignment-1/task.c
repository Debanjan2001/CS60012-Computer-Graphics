/*
Name- Debanjan Saha
Roll- 19CS30014
Assignment- 1
Description- Trajectory of a Bouncing Ball

#ifdef __APPLE__
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

int main(int argc, char **argv){

}
*/

/* This program spins a square around itself in 2D */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

// static GLfloat spin = 0.0 ;


// Center of the cicle = (320, 240)
int xc = 0, yc = 0;

// Plot eight points using circle's symmetrical property
void plot_point(int x, int y)
{
  glBegin(GL_POINTS);
    glVertex2i(xc+x, yc+y);
    glVertex2i(xc+x, yc-y);
    glVertex2i(xc+y, yc+x);
    glVertex2i(xc+y, yc-x);
    glVertex2i(xc-x, yc-y);
    glVertex2i(xc-y, yc-x);
    glVertex2i(xc-x, yc+y);
    glVertex2i(xc-y, yc+x);
  glEnd();
}


// Function to draw a circle using bresenham's
// circle drawing algorithm
void bresenham_circle(int r)
{
  int x=0,y=r;
  float pk=(5.0/4.0)-r;

  /* Plot the points */
  /* Plot the first point */
  plot_point(x,y);
  int k;
  /* Find all vertices till x=y */
  while(x < y)
  {
    x = x + 1;
    if(pk < 0)
      pk = pk + 2*x+1;
    else
    {
      y = y - 1;
      pk = pk + 2*(x - y) + 1;
    }
    plot_point(x,y);
  }
  glFlush();
}

static GLfloat xTranslate = 0.0, yTranslate=300.0;
static float horizontalVelocity = 1;
static float velocity = 0.0;
static float accelaration = 0.05;
const float loss = 0.8;
static int upwardMotion = 0;
static int hitGround = 0;
static float EPS = 1e-6;

GLfloat getMax(GLfloat a, GLfloat b){
  if(a>b){
    return a;
  }
  return b;
}

float getMaxf(float a, float b){
  if(a>b){
    return a;
  }
  return b;
}

void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glShadeModel(GL_FLAT);
}


void DrawEllipse(float cx, float cy, float rx, float ry, int num_segments) 
{ 
    float theta = 2 * 3.1415926 / (float)(num_segments); 
    float c = cosf(theta);//precalculate the sine and cosine
    float s = sinf(theta);
    float t;

    float x = 1;//we start at angle = 0 
    float y = 0; 

    glBegin(GL_LINE_LOOP); 
    for(int ii = 0; ii < num_segments; ii++) 
    { 
        //apply radius and offset
        glVertex2f(x * rx + cx, y * ry + cy);//output vertex 

        //apply the rotation matrix
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    } 
    glEnd(); 
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT) ;

  // Draw sample Axes for better visualization
  glColor3f(0.0, 0.0, 0.0) ;
  glBegin(GL_LINES);
    glVertex2f(-5, -5);
    glVertex2f(160, -5);
    glVertex2f(-5, -5);
    glVertex2f(-5, 80);
  glEnd();


  glPushMatrix() ;

  // glTranslatef(0, 0, -20);
  // glRotatef(spin, 1.0, 0.5, 0.5) ;
  glTranslatef(xTranslate, yTranslate, -40.0);

  glColor3f(0.0, 0.0, 0.0) ;
  
  // glutWireSphere(25, 20, 20);
  
  if(yTranslate > 0 && yTranslate < 10000*EPS){
    // printf("yes\n");
    // bresenham_circle(15);
    DrawEllipse(xc, yc, 40, 20, 10);
  }else{
    bresenham_circle(30);
  }

  // bresenham_circle(30);

  glPopMatrix() ;
  glutSwapBuffers();
}

void translateDisplay(void)
{
  
  // if(velocity < EPS && horizontalVelocity < EPS){
  //   return;
  // }

  xTranslate = xTranslate + horizontalVelocity ;

  hitGround = 0;

  if(upwardMotion){
    velocity -= accelaration;
    yTranslate = yTranslate + velocity;
    if(velocity <= 0){
      upwardMotion = 0;
    }
  } else {
    velocity += accelaration;
    yTranslate = getMax(yTranslate - velocity, 0.0);
    if(yTranslate == 0){
      upwardMotion = 1;
      velocity = getMaxf(velocity-loss, 0.0);
    }

    // if(abs(yTranslate) <= EPS){
    //   hitGround = 1;
    // }
  }

  horizontalVelocity = getMaxf(0.0, horizontalVelocity - 0.004*loss);
  // printf("v=%f, a=%f\n", velocity, accelaration);

  glutPostRedisplay() ;
}


void reshape(int w, int h)
{
  float aspectRatio = (float)w / (float)h;
  glViewport(0,0,(GLsizei) w,(GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Get a Flat view
  glOrtho(-100.0, 800.0, -100.0, 500.0, -50.0, 50.0);

  // Get a 3d View
  // glFrustum (-10.0, 50.0, -10.0, 50.0, 10, 100);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
  switch (button) {
    case GLUT_LEFT_BUTTON:
      if (state == GLUT_DOWN)
        glutIdleFunc(translateDisplay) ;
      break ;
    case GLUT_RIGHT_BUTTON:
      if (state == GLUT_DOWN)
        glutIdleFunc(NULL) ;
      break ;
    default:
    break ;
  }
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv) ;
  glutInitDisplayMode(GLUT_DOUBLE) ;
  glutInitWindowSize(900, 600);
  glutInitWindowPosition(100,100) ;
  glutCreateWindow("Trajectory of a bouncing ball") ;
  init() ;
  glutDisplayFunc(display) ;
  glutReshapeFunc(reshape) ;
  glutMouseFunc(mouse) ;
  glutMainLoop() ;
}

