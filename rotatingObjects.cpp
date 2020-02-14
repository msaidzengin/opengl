#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <iostream>
#include <cmath>
using namespace std;

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include<GL/gl.h>
#include <GL/glut.h>

//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);
}

//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

float _angle = 0.0;
float _cameraAngle = 0.0;
float _ang_tri = 0.0;

//Draws the 3D scene
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
	glRotatef(-_cameraAngle, 0.0, 1.0, 0.0); //Rotate the camera
	glTranslatef(0.0, 0.0, -7.0); //Move forward 5 units

	glColor3ub(255, 255, 0);
	glPushMatrix();
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glRotatef(_angle, 0.0, 0.0, 1.0);
	glutWireSphere(0.9, 30, 30);
	glPopMatrix();

	glPushMatrix();
	//glScalef(1.5, 1.5, 0.0);
	//glTranslatef(0.0, -1.5, 0.0);
	glRotatef(-20, 1.0, 0.0, 0.0);

	glColor3ub(128, 200, 0);
	glPushMatrix();
	glRotatef(-90, 1.0, 0.0, 0.0);
	glRotatef(_angle, 0.0, 0.0, 1.0);
	glutWireCone(1.0, 2.0, 20, 20);
	glPopMatrix();

	glColor3ub(138, 10, 150);
	glPushMatrix();
	glTranslatef(0.0, 1.2, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glRotatef(_angle, 0.0, 0.0, -1.0);
	glutWireTorus(0.2, 0.5, 80, 80);
	glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();
}

void update(int value) {
	_angle += 2.0f;
	if (_angle > 360) {
		_angle -= 360;
	}
	_ang_tri += 2.0f;
	if (_ang_tri > 360) {
		_ang_tri -= 360;
	}

	glutPostRedisplay(); //Tell GLUT that the display has changed

	//Tell GLUT to call update again in 25 milliseconds
	glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(200, 100);

	//Create the window
	glutCreateWindow("Transformations");
	initRendering();

	//Set handler functions
	glutDisplayFunc(drawScene);

	glutReshapeFunc(handleResize);

	glutTimerFunc(25, update, 0); //Add a timer

	glutMainLoop();
	return 0;
}