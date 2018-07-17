#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "gameFuncs.h"

#define size_w_x 850
#define size_w_y 600

GLint idMiner, center_x, center_y;

int main (int argc, char **argv){

	glutInit (&argc,argv);
	glutInitDisplayMode (GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	glutInitWindowSize (size_w_x,size_w_y);
	//positioning the window at center	
	center_x = (glutGet(GLUT_SCREEN_WIDTH)-size_w_x)/2;
	center_y = (glutGet(GLUT_SCREEN_HEIGHT)-size_w_y)/2;
	glutInitWindowPosition (center_x,center_y);
	// end positioning
	
	idMiner = glutCreateWindow ("O robo minerador");
	
	// call back functions
	glutDisplayFunc (gameDraw);
	glutReshapeFunc (resize_window);
	glutKeyboardFunc (get_keyboard);
	glutSpecialFunc (get_keyboard_special);
	
	glutMainLoop();
	return 0;
}
