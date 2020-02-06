/*
 * Copyright (c) 1993-1997, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 * Permission to use, copy, modify, and distribute this software for
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that
 * the name of Silicon Graphics, Inc. not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission.
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
 * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
 * THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
 * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * US Government Users Restricted Rights
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor
 * clauses in the FAR or the DOD or NASA FAR Supplement.
 * Unpublished-- rights reserved under the copyright laws of the
 * United States.  Contractor/manufacturer is Silicon Graphics,
 * Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
 *
 * OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
 */

 /*
  * smooth.c
  * This program demonstrates smooth shading.
  * A smooth shaded polygon is drawn in a 2-D projection.
  */

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include <stdlib.h>
  /* This program illustrates the use of the glut library for
 interfacing with a Window System */

 /* The program opens a window, clears it to black,
 then draws a box at the location of the mouse each time the
 left button is clicked. The right button exits the program

 The program also reacts correctly when the window is
 moved or resized by clearing the new window to black*/


#include <time.h>
#include <stdlib.h>


 /* globals */

GLsizei wh = 500, ww = 500; /* initial window size */
GLfloat size = 3.0;   /* half side length of square */

typedef struct {
	GLint x;
	GLint y;
} Point2D;

typedef struct {
	GLubyte r;
	GLubyte g;
	GLubyte b;
} Color;

typedef struct {
	Point2D center;
	Color color;
} Square;


Square squareArray[10000];
int numSquares = 0;

void makeSquare(int x, int y)
{

	y = wh - y;
	squareArray[numSquares].center.x = x;
	squareArray[numSquares].center.y = y;
	squareArray[numSquares].color.r = (GLubyte)rand() % 256;
	squareArray[numSquares].color.g = (GLubyte)rand() % 256;
	squareArray[numSquares++].color.b = (GLubyte)rand() % 256;

	glutPostRedisplay();
}


/* rehaping routine called whenever window is resized
or moved */

void myReshape(GLsizei w, GLsizei h)
{

	/* adjust clipping box */

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* adjust viewport and clear */

	glViewport(0, 0, w, h);

	/* set global size for use by drawing routine */

	ww = w;
	wh = h;
}

void myinit(void)
{

	glViewport(0, 0, ww, wh);

	/* Pick 2D clipping window to match size of screen window
	This choice avoids having to scale object coordinates
	each time window is resized */

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)ww, 0.0, (GLdouble)wh);

	/* set clear color to black and clear window */

	glClearColor(0.0, 0.0, 0.0, 1.0);


}

void myKeyboard(unsigned char key, int x, int y)
{
	if ((key == 'Q') || (key == 'q'))
		exit(0);
}


void myMouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		exit(0); /*terminate the program through OpenGL */
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		makeSquare(x, y);
}

/* display callback required by GLUT 3.0 */

void myDisplay(void)
{
	int i, x, y;
	glClear(GL_COLOR_BUFFER_BIT);
	for (i = 0; i < numSquares; i++) {
		x = squareArray[i].center.x;
		y = squareArray[i].center.y;
		glColor3ub(squareArray[i].color.r, squareArray[i].color.g, squareArray[i].color.b);
		glBegin(GL_POLYGON);
		glVertex2f(x + size, y + size);
		glVertex2f(x - size, y + size);
		glVertex2f(x - size, y - size);
		glVertex2f(x + size, y - size);
		glEnd();
	}
	glFlush();
}

void myMenu(int id) {
	if (id == 1)
		size = size * 2;
	else if (id == 2 && size > 1)
		size = size / 2;
	glutPostRedisplay();
}

int main(int argc, char** argv)
{


	int menu_id;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ww, wh);
	glutCreateWindow("square");
	myinit();
	glutReshapeFunc(myReshape);
	glutMouseFunc(myMouse);
	glutMotionFunc(makeSquare);
	glutDisplayFunc(myDisplay);
	glutKeyboardFunc(myKeyboard);

	menu_id = glutCreateMenu(myMenu);
	glutAddMenuEntry("Increase square size", 1);
	glutAddMenuEntry("Decrease square size", 2);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);

	srand(time(NULL));

	glutMainLoop();

}
