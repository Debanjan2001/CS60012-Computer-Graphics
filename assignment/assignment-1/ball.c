/*
 * Name- Debanjan Saha
 * Roll- 19CS30014
 * Email- debanjansaha2001@gmail.com
 * Assignment- 1
 * Description- Trajectory of a Bouncing Ball
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif


// Circle Properties: Center of the cicle = (0, 0), Radius = 30
const int BALL_CENTER_X = 0;
const int BALL_CENTER_Y = 0;
const int BALL_RADIUS = 30;

// Ellipse Properties
const int ELLIPSE_MAJOR_AXIS_MAX = 35; // during maximum deformation when the ball hits ground
static int ELLIPSE_MAJOR_AXIS = 35; // initialize during maximum deformation

// static variables for my Design Choices
// The values were set after to some parameter tuning to get a suitable simulation of the ball dropping.

static GLfloat xTranslate = 0.0, yTranslate = 600.0; // set initial location to drop the ball
static float horizontalVelocity = 2; // Set initial horizontal velocity for the ball
static float verticalVelocity = 0.0; // Set initial vertical velocity for the ball
static float accelaration = 0.15; // Set accelaration due to gravity

/*
 * Set hypothetical loss function for recalculating velocity in both directions
 * horizontalLoss: for constantly updating the horizontalVelocity of ball as if there is a resistive force like wind against it
 * verticalLoss: My design is that the ball will go up again with new_velocity = (1-verticalLoss)*old_verticalVelocity after collision 
 * Instead of keeping friction, energy conservation etc, I used these parameters for keeping things simple.
 */
const float verticalLoss = 0.2;
const float horizontalLoss = 0.002;
static int upwardMotion = 0; // Track direction of motion
const float ELLIPSE_RESTORATION_RATE = 0.01; // Deformation restoration rate after collision in ground

/*
 * Purpose: Utility Function to calculate the maximum between two float/GLFloat variables 
 * Input: (a, b) are two floats
 * Output: max(a,b)
*/
float getMax(float a, float b) {
    if (a > b) {
        return a;
    }
    return b;
}

/*
 * Purpose: Plot eight points using circle's symmetrical property for forming the circle
 * 
 * Input: x:        x_value sent from Bresenham Circle Drawing Algo
 *        y:        Calculated y_value from Bresenham Circle Drawing Algo
 *        x_center: x co-ordinate of center of the circle
 *        y_center: y co-ordinate of center of the circle  
 * 
 * Output: Draw A set of 8 symmetrical points using OpenGL Library Functions
*/ 
void plotCirclePoint(int x, int y, int x_center, int y_center)
{
    glBegin(GL_POINTS);
      glVertex2i(x_center + x, y_center + y);
      glVertex2i(x_center + x, y_center - y);
      glVertex2i(x_center + y, y_center + x);
      glVertex2i(x_center + y, y_center - x);
      glVertex2i(x_center - x, y_center - y);
      glVertex2i(x_center - y, y_center - x);
      glVertex2i(x_center - x, y_center + y);
      glVertex2i(x_center - y, y_center + x);
    glEnd();
}

/*
 * Purpose: Function to draw a circle using Bresenham's circle drawing algorithm
 * 
 * Input: x_center:   x co-ordinate of the center of circle to be drawn
 *        y_center:   y co-ordinate of the center of circle to be drawn
 *        radius:     radius of the circle to be drawn
 * 
 * Output: A circle drawn using passed parameters
*/
void drawBresenhamCircle(int x_center, int y_center, int radius)
{
    int x = 0, y = radius;
    float p = 3.0 - 2 * radius;
    while (x <= y) {
        plotCirclePoint(x, y, x_center, y_center);
        if (p < 0) {
            p += 4 * x + 6;
        } else {
            y -= 1;
            p += 4 * (x - y) + 10;
        }
        x += 1;
    }
    glFlush();
}

/*
 * Purpose: Plot Four points using ellipse's symmetrical property for forming the ellipse
 * 
 * Input: x:        x_value sent from MidpointEllipse Drawing Algorithm
 *        y:        Calculated y_value from MidpointEllipse Drawing Algorithm
 *        x_center: x co-ordinate of center of the ellipse
 *        y_center: y co-ordinate of center of the ellipse  
 * 
 * Output: Draw A set of 4 symmetrical points using OpenGL Library Functions
*/ 
void plotEllipsePoint(int x, int y, int x_center, int y_center) {
    glBegin(GL_POINTS);
      glVertex2i(x_center + x, y_center + y);
      glVertex2i(x_center - x, y_center + y);
      glVertex2i(x_center + x, y_center - y);
      glVertex2i(x_center - x, y_center - y);
    glEnd();
}

/*
 * Purpose: Function to draw an ellipse using Midpoint Ellipse drawing algorithm
 * 
 * Input: x_center:       x co-ordinate of the center of ellipse to be drawn
 *        y_center:       y co-ordinate of the center of ellipse to be drawn
 *        major_radius:   major_radius of the ellipse to be drawn
 *        minor_radius:   minor_radius of the ellipse to be drawn
 * 
 * Output: An ellipse drawn using passed parameters
 * 
 * Reference/Citation: I have used GeeksforGeeks for learning how to draw an ellipse.
 * The link: https://www.geeksforgeeks.org/midpoint-ellipse-drawing-algorithm/ provides 
 * the access to my referred document. I give due credit of the function below to the author 
 * of this content and by the re-use of the function with my added modifications, 
 * I hereby declare that I am NOT the SOLE owner of the following Midpoint Ellipse Drawing algorithm implementation.
 * 
 * Note: This function will only be used for the Bonus part of this assignment
*/
void drawMidpointEllipse(int x_center, int y_center, int major_radius, int minor_radius) {
    long int dx, dy, d1, d2, x, y;
    x = 0;
    y = minor_radius;

    // Initial decision parameter of region 1
    d1 = (minor_radius * minor_radius) - (major_radius * major_radius * minor_radius) + (0.25 * major_radius * major_radius);
    dx = 2 * minor_radius * minor_radius * x;
    dy = 2 * major_radius * major_radius * y;

    // For region 1
    while (dx < dy) {
        // Plot the symmetric points 
        plotEllipsePoint(x, y, x_center, y_center);

        // Checking and updating value of decision parameter based on algorithm
        if (d1 < 0) {
            x += 1;
            dx = dx + (2 * minor_radius * minor_radius);
            d1 = d1 + dx + (minor_radius * minor_radius);
        } else {
            x += 1;
            y -= 1;
            dx = dx + (2 * minor_radius * minor_radius);
            dy = dy - (2 * major_radius * major_radius);
            d1 = d1 + dx - dy + (minor_radius * minor_radius);
        }
    }

    // Decision parameter of region 2
    d2 = ((minor_radius * minor_radius) * ((x + 0.5) * (x + 0.5))) +
         ((major_radius * major_radius) * ((y - 1) * (y - 1))) -
         (major_radius * major_radius * minor_radius * minor_radius);

    // Plotting points of region 2
    while (y >= 0) {
        // Plot the symmetric points 
        plotEllipsePoint(x, y, x_center, y_center);

        // Checking and updating parameter value based on algorithm
        if (d2 > 0) {
            y -= 1;
            dy = dy - (2 * major_radius * major_radius);
            d2 = d2 + (major_radius * major_radius) - dy;
        } else {
            y -= 1;
            x += 1;
            dx = dx + (2 * minor_radius * minor_radius);
            dy = dy - (2 * major_radius * major_radius);
            d2 = d2 + dx - dy + (major_radius * major_radius);
        }
    }
    glFlush();
}

// Initial parameters: Clear the screen, set shading...
void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_FLAT);
}


/*
 * Purpose: Display function for rendering the ball
*/
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT) ;

    // Draw sample Lines for better visualization
    glColor3f(0.0, 0.0, 0.0) ;
    glBegin(GL_LINES);

    // Draw a ground line
    for(int i=1;i<=3;i++){
        glVertex2f(-200, -30-i);
        glVertex2f(1500, -30-i);
    }
    
    glEnd();

    glPushMatrix() ;

    glTranslatef(xTranslate, yTranslate, 0.0);

    glColor3f(0.0, 0.0, 0.0) ;
    
    // If ball has just hit the ground and is about to go up, then deform the ball.
    // As long as the ball has enough verticalVelocity, keep it deforming, otherwise it will stay unchanged.
    if(upwardMotion == 1 && yTranslate < BALL_RADIUS && verticalVelocity > 1){
        // By conservation of volume,
        // pi*r*r = pi*a*b (during deformation) [where r= radius, a=major_exis, b=minor_axis]
        // then b = r*r/a;
        drawMidpointEllipse(BALL_CENTER_X, BALL_CENTER_Y, ELLIPSE_MAJOR_AXIS, (BALL_RADIUS * BALL_RADIUS) / ELLIPSE_MAJOR_AXIS);
    } else {
        drawBresenhamCircle(BALL_CENTER_X, BALL_CENTER_Y, 30);
    }

    glPopMatrix() ;
    glutSwapBuffers();
}

/*
 * Purpose: translateDisplay function for rendering/simulating the actual trajectory ball
 * Contains the actual logic of the trajectory of the ball.
*/
void translateDisplay(void)
{
    if ((verticalVelocity == 0.0) && (horizontalVelocity == 0.0) && (yTranslate == 0.0)) {
        // If the ball has stopped, stop translation
        return;
    }

    // Constantly Update the horizontal Velocity
    // Imagining as if there is a resistive force like wind which reduces its velocity
    horizontalVelocity = getMax(0.0, horizontalVelocity - horizontalLoss);

    // Update the xTranslation continuously
    xTranslate = xTranslate + horizontalVelocity ;

    if (upwardMotion == 1) {
        // when the ball is moving up,
        verticalVelocity = getMax(verticalVelocity - accelaration, 0.0);
        yTranslate = yTranslate + verticalVelocity;
        
        // constantly keep reducing the deformation when the ball is moving up 
        ELLIPSE_MAJOR_AXIS = getMax(ELLIPSE_MAJOR_AXIS - ELLIPSE_RESTORATION_RATE, BALL_RADIUS);

        // if max height reached, set upwardMotion to false
        if (verticalVelocity <= 0) {
            upwardMotion = 0;
        }
    } else {
        // when the ball is moving down,
        verticalVelocity += accelaration;
        yTranslate = getMax(yTranslate - verticalVelocity, 0.0);

        // when it has hit the ground,
        if (yTranslate <= 0) {
            // set upwardMotion to true,
            upwardMotion = 1;
            verticalVelocity = verticalVelocity * (1-verticalLoss);

            // Deform the ball to max possible amount
            ELLIPSE_MAJOR_AXIS = ELLIPSE_MAJOR_AXIS_MAX;
        }
    }

    glutPostRedisplay() ;
}

/*
 * Reshape function for defining viewport, setting up orthographic projection etc.
*/
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Get a Flat view --> Numbers generated according to window size
    glOrtho(-100.0, 1340.0, -100.0, 800.0, -50.0, 50.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/*
 * Function for handling mouse inputs 
*/
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
    // Initializing GLUT
    glutInit(&argc, argv) ;
    
    // Set the display mode
    glutInitDisplayMode(GLUT_DOUBLE) ;
    
    // Define the window width x height
    glutInitWindowSize(1440, 900);
    
    // Define the window position
    glutInitWindowPosition(100, 100) ;
    
    // Creating a GLUT window
    glutCreateWindow("Trajectory of a bouncing ball") ;

    // Setting Intial Parameters
    init() ;

    // Setting a display function
    glutDisplayFunc(display) ;
    glutReshapeFunc(reshape) ;
    glutMouseFunc(mouse) ;
    
    // Calling the main loop
    glutMainLoop() ;
}