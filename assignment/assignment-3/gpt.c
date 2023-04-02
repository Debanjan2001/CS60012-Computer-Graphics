#include <stdio.h>
#include <GL/glut.h>

// Define variables for teapot and light sources
GLfloat teapotSpecular[] = {1.0, 1.0, 1.0, 0.5};
GLfloat teapotShininess[] = {50.0};
GLfloat light0_position[] = {0.0, 0.0, 10.0, 1.0};
GLfloat light0_diffuse[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light1_position[] = {-10.0, 0.0, 0.0, 1.0};
GLfloat light1_diffuse[] = {1.0, 0.0, 0.0, 1.0};
GLfloat light2_position[] = {0.0, 10.0, 0.0, 1.0};
GLfloat light2_diffuse[] = {0.0, 1.0, 0.0, 1.0};
GLfloat light3_position[] = {10.0, 0.0, 0.0, 1.0};
GLfloat light3_diffuse[] = {0.0, 0.0, 1.0, 1.0};
GLfloat ambientLight[] = {0.2, 0.2, 0.2, 1.0};
GLfloat viewpointLight[] = {1.0, 1.0, 1.0, 0.0};
GLfloat lightIntensity = 1.0;

// Define variables for mouse interaction
int mouseDown = 0;
int lastMouseX = 0;
int lastMouseY = 0;
float rotateX = 0.0;
float rotateY = 0.0;

// Define function to draw the teapot
void drawTeapot() {
    glutSolidTeapot(1.0);
}

// Define function to draw a colored sphere for the light sources
void drawSphere(GLfloat* position, GLfloat* diffuse) {
    glPushMatrix();
    glTranslatef(position[0], position[1], position[2]);
    glColor3f(diffuse[0], diffuse[1], diffuse[2]);
    glutSolidSphere(0.2, 20, 20);
    glPopMatrix();
}

// Define function to set up the lights
void setupLights() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
    glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
    glMaterialfv(GL_FRONT, GL_SPECULAR, teapotSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, teapotShininess);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, viewpointLight);
}

// Define function to draw the scene
void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
    glRotatef(rotateX, 1.0, 0.0, 0.0);
    glRotatef(rotateY, 0.0, 1.0, 0.0);
    drawTeapot();
    drawSphere(light1_position, light1_diffuse);
    drawSphere(light2_position, light2_diffuse);
    drawSphere(light3_position, light3_diffuse);
    glutSwapBuffers();
}

// Define function to handle mouse interaction
void handleMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            mouseDown = 1;
            lastMouseX = x;
            lastMouseY = y;
        }
        else {
            mouseDown = 0;
        }
    }
}

// Define function to handle mouse motion
void handleMouseMove(int x, int y) {
    if (mouseDown) {
        rotateX += (y - lastMouseY) * 0.5;
        rotateY += (x - lastMouseX) * 0.5;
        lastMouseX = x;
        lastMouseY = y;
        glutPostRedisplay();
    }
}

// Define function to handle keyboard input
void handleKeyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '1':
            lightIntensity += 0.1;
            if (lightIntensity > 1.0) {
                lightIntensity = 1.0;
            }
            glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, lightIntensity);
            break;
        case '2':
            lightIntensity -= 0.1;
            if (lightIntensity < 0.0) {
                lightIntensity = 0.0;
            }
            glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, lightIntensity);
            break;
        case 'r':
            light1_diffuse[0] = 1.0 - light1_diffuse[0];
            glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
            break;
        case 'g':
            light2_diffuse[1] = 1.0 - light2_diffuse[1];
            glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
            break;
        case 'b':
            light3_diffuse[2] = 1.0 - light3_diffuse[2];
            glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

// Define main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Multiple Light Sources");
    glutDisplayFunc(drawScene);
    glutMouseFunc(handleMouse);
    glutMotionFunc(handleMouseMove);
    glutKeyboardFunc(handleKeyboard);
    setupLights();
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
