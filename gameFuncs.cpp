#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "gameFuncs.h"
#include <time.h>
#include <math.h>
#include "image.h"

#define WIDTH 850
#define HEIGHT 600
#define duration 60

//########################################################################################
//########################################################################################
//########################################################################################
GLint pnt=0,w,h,sng,an_rot=0;
GLuint idTexture;
GLfloat mov_x=0,mov_y=0.5,mov_z=0,tol;
GLint dia_x=3,dia_z=1;
GLfloat angle=40;
GLfloat theta=0;
GLfloat radius=16;
bool finish, enter=false;
GLint dir[2] = {0,0};
GLfloat obs[3]={0.0,7.0,0.0};
GLfloat eyes[3]={0.0,3.0,0.0};
time_t initial, current;
//########################################################################################
//########################################################################################
//########################################################################################

void init_light (void){ 
	GLfloat ambient_light[4]={0.2,0.2,0.2,1.0}; 
	GLfloat difused_light[4]={0.7,0.7,0.7,1.0};
	GLfloat specular_light[4]={1.0, 1.0, 1.0, 1.0};
	GLfloat position_light[4]={80.0, 40.0, 80.0, 1.0};
	GLfloat specularity[4]={0,0,0,1}; 
	GLint specMaterial = 60;

	glClearColor(0,0.7,1,1);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT,GL_SPECULAR,specularity);
	glMateriali(GL_FRONT,GL_SHININESS,specMaterial);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difused_light );
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light );
	glLightfv(GL_LIGHT0, GL_POSITION, position_light );
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);  
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void init_texture (){
	glEnable(GL_TEXTURE_2D);
		
		char *path = (char*) "terra.jpg";
		Image texture_arena = load_img(path);	
	
		glGenTextures(1,&idTexture);
		glBindTexture(GL_TEXTURE_2D,idTexture);
		gluBuild2DMipmaps(GL_TEXTURE_2D,3,texture_arena.dim.x,texture_arena.dim.y,GL_RGB,GL_UNSIGNED_BYTE,texture_arena.img);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);				

		glColor4f(0.47,0.29,0.08,1);
		glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_BLEND);
		glBindTexture(GL_TEXTURE_2D,idTexture);
   
		glBegin(GL_QUADS);
			glTexCoord2f(0,0);  glVertex3f(-5.08,0.28,6.03);
			glTexCoord2f(0,1);  glVertex3f(5.08,0.28,6.03);
			glTexCoord2f(1,0);  glVertex3f(5.08,0.28,-6.03);
			glTexCoord2f(1,1);  glVertex3f(-5.08,0.28,-6.03);
		glEnd();
	
	glDisable(GL_TEXTURE_2D);		
}

void reset (){
	mov_x=0; mov_y=0.5; mov_z=0;
	dia_x=3; dia_z=1;
	finish = false;
	radius=16; theta=0;
	pnt = 0; enter=false;
	initial= time(NULL);
}

void write_string(void *font,char *txt){
	while (*txt)
	glutBitmapCharacter(font, *txt++); 
}

void write_start (){
	glColor3f(1,0,0);
	glRasterPos3f(-10,7,4.5);        
	char* p = (char*) "Aperte Enter para iniciar o jogo";
	write_string (GLUT_BITMAP_HELVETICA_18,p);
}

void write_points(){         
	glColor3f(1,0,0);
	glRasterPos3f(-10,7,4.5);        
	char* p = (char*) "### O TEMPO ACABOU ####";
	write_string (GLUT_BITMAP_HELVETICA_18,p);
}

void write_points2(){         
	glColor3f(1,0,0);
	glRasterPos3f(-10,6,5.7);        
	char* p = (char*) "O numero de diamantes coletados foram:";
	if (pnt <= 1)
		p = (char*) "O numero de diamantes coletados foi:";
		
	write_string (GLUT_BITMAP_HELVETICA_18,p);
}

void write_points_value(){
	glColor3f(1,0,0);
	glRasterPos3f(-10,5,0.5);        
	char spnt[10];  
	sprintf(spnt,"%d",pnt);
	write_string (GLUT_BITMAP_HELVETICA_18,spnt);	
}

void draw_arena (){
  	glPushMatrix();
	  	glColor3f(0.47,0.29,0.08);
  		glScalef (10.0, 0.5, 12.0);
  		glutSolidCube (1.0);
  	glPopMatrix();
  	init_texture ();
}

void draw_miner(){
  	glPushMatrix();
	  	glColor3f(0.1,0.1,0.1);
	  	glTranslatef(mov_x,mov_y,mov_z);
	  	glScalef (1,0.5,1);
  		glutSolidCube (1.0);
  	glPopMatrix();
  	// draw the head
  	glPushMatrix();
	  	glColor3f(0.1,0.1,0.1);
	  	glTranslatef(mov_x,mov_y+0.2,mov_z);
	  	glScalef (0.4,0.7,0.4);
  		glutSolidCube (1.0);
  	glPopMatrix();	 
  	// draw the arms
  	glPushMatrix();
	  	glColor3f(0.1,0.1,0.1);
	  	if ((dir[0] == 0 && dir[1] == 0) || (dir[0] == 1 && dir[1] == 0)){ 
	  		glTranslatef(mov_x,mov_y,mov_z+0.5);
	  	}else{
	  		glTranslatef(mov_x+0.5,mov_y,mov_z);
	  	}
	  	glScalef (0.3,0.3,0.3);
  		glutSolidCube (1.0);
  	glPopMatrix();  	 	
  	glPushMatrix();
	  	glColor3f(0.1,0.1,0.1);
	  	if ((dir[0] == 0 && dir[1] == 0) || (dir[0] == 1 && dir[1] == 0)){ 
		  	glTranslatef(mov_x,mov_y,mov_z-0.5);
		}else{
			glTranslatef(mov_x-0.5,mov_y,mov_z);
		}
	  	glScalef (0.3,0.3,0.3);
  		glutSolidCube (1.0);
  	glPopMatrix();  	 	  	
  	// Draw the eyes
  	glPushMatrix();
	  	glColor3f(1,1,1);
	  	if (dir[0] == 0 && dir[1] == 0){
		  	glTranslatef(mov_x+0.19,mov_y+0.4,mov_z+0.1);
		}else if (dir[0] == 1 && dir[1] == 0){
			glTranslatef(mov_x-0.19,mov_y+0.4,mov_z+0.1);
		}else if (dir[0] == 1 && dir[1] == 1){
			glTranslatef(mov_x-0.1,mov_y+0.4,mov_z+0.19);
		}else{
			glTranslatef(mov_x-0.1,mov_y+0.4,mov_z-0.19);
		}
	  	glScalef (0.1,0.1,0.1);
  		glutSolidCube (1.0);
  	glPopMatrix();  	 	  	  	
  	glPushMatrix();
	  	glColor3f(1,1,1);
	  	if (dir[0] == 0 && dir[1] == 0){
		  	glTranslatef(mov_x+0.19,mov_y+0.4,mov_z-0.1);
		}else if (dir[0] == 1 && dir[1] == 0){
			glTranslatef(mov_x-0.19,mov_y+0.4,mov_z-0.1);
		}else if (dir[0] == 1 && dir[1] == 1){
			glTranslatef(mov_x+0.1,mov_y+0.4,mov_z+0.19);
		}else{
			glTranslatef(mov_x+0.1,mov_y+0.4,mov_z-0.19);
		}	  	
	  	glScalef (0.1,0.1,0.1);
  		glutSolidCube (1.0);
  	glPopMatrix();
}

void locate_draw_diamond (){
		volta:
		srand (rand());
		dia_x = rand()%5;
		dia_z = rand()%5;
		sng = rand()%2;
		an_rot = rand()%90;

		if (dia_x == 0 || dia_z == 0){
			goto volta;
		}else{
			if (sng){
				dia_x = -dia_x;
			}
			sng = rand()%2;
			if (sng){
				dia_z = -dia_z;
			}
		}
}

bool time (){
	current = time (NULL);
	if (difftime(current,initial) >= duration)
		return true;
	else
		return false;	
}

void draw_diamond (){
  	glPushMatrix();
	  	glColor3f(0.76,0.31,0.8);
	  	glTranslatef(dia_x,mov_y,dia_z);
	  	glScalef (1,0.5,1);
		glRotatef(an_rot,0,0,1);	  	
  		glutSolidIcosahedron();
  	glPopMatrix();	
}

bool catch_diamond (){
	tol = 1;
	if ((mov_x >= dia_x-tol && mov_x <= dia_x+tol) && (mov_z >= dia_z-tol && mov_z <= dia_z+tol)){
		pnt++;
		return true;
	}else{
		return false;
	}
}

void cam (){
  	glPushMatrix();
 		obs[0]=radius*cos(2*M_PI*theta/360);
 		obs[2]=radius*sin(2*M_PI*theta/360);
  		gluLookAt(obs[0],obs[1],obs[2],eyes[0],eyes[1],eyes[2],0.0,1.0,0.0);
}

void gameDraw (){
	glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	init_light();
		if (enter){ 
				finish = time ();
			if (!finish){
				cam (); // update cam
				draw_arena ();
				draw_miner();
				draw_diamond ();		
				if (catch_diamond ()){
					locate_draw_diamond ();
				}	
			}else if (finish){
				radius=16; theta=0;
				cam (); // update cam
				write_points();
				write_points2();
				write_points_value();
				draw_arena ();
				draw_miner();
				draw_diamond ();		
			}
		}else{
				cam (); // update cam
				write_start();		
				draw_arena ();
				draw_miner();
				draw_diamond ();					
		}
		
	glPopMatrix();
	glutSwapBuffers();	
}

void resize_window (GLint w, GLint h){
	glViewport (0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(angle,(GLfloat)WIDTH/(GLfloat)HEIGHT,0.1,30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void get_keyboard (unsigned char key, GLint x, GLint y){
	switch (key){
		case 27: exit(0); break;
		case 'w': if (!finish && enter && radius <= 20) radius++; break;
		case 's': if (!finish && enter && radius >= 14) radius--; break;
		case 'a': if (!finish && enter) theta+=2; break;
		case 'd': if (!finish && enter) theta-=2; break;
		case 'r': radius=16; theta=0; break;
		case ' ': reset (); break;
		case  13: enter=true; initial= time(NULL); break;
	}
	glutPostRedisplay();
}

void get_keyboard_special (GLint key, GLint x, GLint y){
	switch (key){
		case GLUT_KEY_RIGHT:
			if ((mov_z > -5.4) && (!finish) && enter) mov_z -=0.1;
			dir[0] = 0;
			dir[1] = 1;
		break;
		case GLUT_KEY_LEFT:
			if ((mov_z < 5.4) && (!finish) && enter) mov_z+=0.1;
			dir[0] = 1;
			dir[1] = 1;			
		break;		
		case GLUT_KEY_UP:
			if ((mov_x > -4.4) && (!finish) && enter) mov_x-=0.1;
			dir[0] = 1;
			dir[1] = 0;			
		break;					
		case GLUT_KEY_DOWN: 
			if ((mov_x < 4.4) && (!finish) && enter) mov_x+=0.1; 
			dir[0] = 0;
			dir[1] = 0;			
		break;	
	}
	glutPostRedisplay();
}

