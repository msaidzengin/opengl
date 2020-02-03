#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

GLfloat tdist = 0.0;

enum { FILL, WIRE, BACKFACE };

int rendermode = FILL;

void menu(int selection)
{
    rendermode = selection;
    glutPostRedisplay();
}


/* geometry display list names */
enum { SPHERE = 1, FLOOR, WALLS };

void drawscene(void)
{
    GLfloat i;
    glPushMatrix();

    glTranslatef(10.f, -10.f, -400.f);
    //glRotatef(-10.0, 1.0, 0.0, 0.0);
    glRotatef(30.0, 1.0, 0.0, 0.0);
    glCallList(SPHERE);
    glPopMatrix();


}

void redraw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    switch (rendermode) {
    case FILL:
        drawscene();
        break;
    case WIRE: /* basic wireframe mode */
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        drawscene();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        break;
    case BACKFACE: /* use backface culling to clean things up */
        glEnable(GL_CULL_FACE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        drawscene();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDisable(GL_CULL_FACE);
        break;

    }


    glFlush();
}

void key(unsigned char key, int x, int y)
{
    switch (key) {
        cout << key << "\n";
    case 't':
        if (tdist < 140.0) {
            tdist = (tdist + 0.5);
            glutPostRedisplay();
        }
        break;
    case 'T':
        if (tdist > -50.0) {
            tdist = (tdist - 0.5);
            glutPostRedisplay();
        }
        break;
    case 'e':
        exit(0);
    }
}
int main(int argc, char** argv) {

    GLfloat* tex;
    static GLfloat lightpos[] = { -50.f, -50.f, -320.f, 1.f };
    static GLfloat sphere_mat[] = { 0.0, 1.0, 1.0, 1.0 };

    GLUquadricObj* sphere;

    glutInit(&argc, argv);
    glutInitWindowSize(700, 700);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
    (void)glutCreateWindow("Wireframe_Backface");

    glutDisplayFunc(redraw);
    glutKeyboardFunc(key);

    glutCreateMenu(menu);
    glutAddMenuEntry("Solid Fill", FILL);
    glutAddMenuEntry("Wireframe", WIRE);
    glutAddMenuEntry("Backface Culling", BACKFACE);

    glutAttachMenu(GLUT_RIGHT_BUTTON);


    /* draw a perspective scene */
    glMatrixMode(GL_PROJECTION);
    glFrustum(-100., 100., -100., 100., 320., 640.);
    glMatrixMode(GL_MODELVIEW);


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glClearColor(1.0, 0.0, 0.0, 1.0);


    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glNewList(SPHERE, GL_COMPILE);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sphere_mat);
    glutSolidSphere(80, 50, 50);
    glEndList();

    glutMainLoop();
    return 0;
}