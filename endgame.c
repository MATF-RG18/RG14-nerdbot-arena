#include<stdio.h>
#include<stdlib.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
#include<stdbool.h>
#include "endgame.h"
#include "on_display.h"
#include "draw_bot.h"
#include "draw_trail.h"
#include "draw_anunaki.h"
#include "collision.h"
#include "image.h"

void endgame(void)
{

	 light_position[0] = -1;
	 light_position[2] =  1;

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	//namestamo sta se vidi
    glViewport(0, 0,window_width, window_height);

    //namestamo ugao pod kojim vidimo, razmeru sirine i duzine vidnog polja,
    // pozicije near i far clipping ravni
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, window_width/(float)window_height, 1, 1500);

    //namestamo kameru gde je na sta gleda i pod kojim uglom, sad cak i prati igraca
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); 
  	gluLookAt(-15, 8, 15,
  			 0, 0, 0,
  			  0, 1, 0);

  	//pod arene

    glBindTexture(GL_TEXTURE_2D, names[1]);
    glBegin(GL_POLYGON);
        glNormal3f(0,1,0); 

        glTexCoord2f(0, 0);
        glVertex3f(-100, -1, 100);

        glTexCoord2f(50, 0);
        glVertex3f(100, -1, 100);

        glTexCoord2f(50, 50);
        glVertex3f(100, -1, -100);      

        glTexCoord2f(0, 50);                  
        glVertex3f(-100, -1, -100);
    glEnd();

    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, names[0]);
    //TODO napravi zid
     glBegin(GL_QUADS);

        glNormal3f(1, 0, 0);

         glTexCoord2f(0, 0);
         glVertex3f(-100, -1, -50);

         glTexCoord2f(8, 0);
         glVertex3f(-100, -1, 50);

         glTexCoord2f(8, 4);
         glVertex3f(-100, 30, 50);

         glTexCoord2f(0, 4);
         glVertex3f(-100, 30, -50);

        glNormal3f(1, 0, -1);

         glTexCoord2f(0, 0);
         glVertex3f(-100, -1, 50);

         glTexCoord2f(8, 0);
         glVertex3f(-50, -1, 100);

         glTexCoord2f(8, 4);
         glVertex3f(-50, 30, 100);

         glTexCoord2f(0, 4);
         glVertex3f(-100, 30, 50);

        glNormal3f(0, 0, -1);

         glTexCoord2f(0, 0);
         glVertex3f(50, -1, 100);

         glTexCoord2f(8, 0);
         glVertex3f(-50, -1, 100);

         glTexCoord2f(8, 4);
         glVertex3f(-50, 30, 100);

         glTexCoord2f(0, 4);
         glVertex3f(50, 30, 100);

       glNormal3f(1, 0, 1);

         glTexCoord2f(0, 0);
         glVertex3f(-100, -1, -50);

         glTexCoord2f(8, 0);
         glVertex3f(-50, -1, -100);

         glTexCoord2f(8, 4);
         glVertex3f(-50, 30, -100);

         glTexCoord2f(0, 4);
         glVertex3f(-100, 30, -50);

       glNormal3f(-1, 0, 0);

         glTexCoord2f(0, 0);
         glVertex3f(100, -1, -50);

         glTexCoord2f(8, 0);
         glVertex3f(100, -1, 50);

         glTexCoord2f(8, 4);
         glVertex3f(100, 30, 50);

         glTexCoord2f(0, 4);
         glVertex3f(100, 30, -50);

       //krivi 
       glNormal3f(-1, 0, 1);

         glTexCoord2f(0, 0);
         glVertex3f(100, -1, -50);

         glTexCoord2f(8, 0);
         glVertex3f(50, -1, -100);

         glTexCoord2f(8, 4);
         glVertex3f(50, 30, -100);

         glTexCoord2f(0, 4);
         glVertex3f(100, 30, -50);

        glNormal3f(0, 0, 1);

         glTexCoord2f(0, 0);
         glVertex3f(-50, -1, -100);

         glTexCoord2f(8, 0);
         glVertex3f(50, -1, -100);

         glTexCoord2f(8, 4);
         glVertex3f(50, 30, -100);

         glTexCoord2f(0, 4);
         glVertex3f(-50, 30, -100);

           //krivi 
       glNormal3f(-1, 0, -1);

         glTexCoord2f(0, 0);
         glVertex3f(100, -1, 50);

         glTexCoord2f(8, 0);
         glVertex3f(50, -1, 100);

         glTexCoord2f(8, 4);
         glVertex3f(50, 30, 100);

         glTexCoord2f(0, 4);
         glVertex3f(100, 30, 50);
    glEnd();

    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);

  	if(Anu_HP <= 0){


    //materijali
    GLfloat ambient_coeffs_Cube[] = { 1, 0.3, 1, 1};
    GLfloat diffuse_coeffs_Cube[] = { 0.7, 0.7, 0.7, 1};
    GLfloat specular_coeffs_Cube[] = { 0.5, 0.5, 0.5, 1};
    GLfloat shininess_Cube = 10;
    glMaterialfv(GL_BACK, GL_AMBIENT, ambient_coeffs_Cube);
    glMaterialfv(GL_BACK, GL_DIFFUSE, diffuse_coeffs_Cube);
    glMaterialfv(GL_BACK, GL_SPECULAR, specular_coeffs_Cube);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess_Cube);


    glPushMatrix();
  	glTranslatef(-3, 0, -5);

  	glPushMatrix();
  	glScalef(2, 5, 2);
  	glutSolidCube(2);

  	glPopMatrix();

  	glPushMatrix();
  	glTranslatef(-2, 5, 0);
  	draw_bot();

  	glPopMatrix();

  	glPopMatrix();

  	glPushMatrix();

  	glTranslatef(5, 1, 5);


  	//lebdece sfere
  	glPushMatrix();
  	glTranslatef(0, 0, 5);
  	glutSolidSphere(0.5,20,20);

  	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5, 0, 0);
  	glutSolidSphere(0.5,20,20);

  	glPopMatrix();

  	glPushMatrix();
  	glTranslatef(5, 0, 0);
  	glutSolidSphere(0.5,20,20);

  	glPopMatrix();

  	//anunaki
  	glRotatef(25, 0, 0, 1);


  	glPushMatrix();
	glScalef(3,0.2,3);
    glutSolidSphere(1,20,20);
    glPopMatrix();
   
    glutSolidSphere(1,20,20);




    glPopMatrix();












  }



     // Test koordinatni sistem

    glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(100,0,0);
        
        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,100,0);
        
        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,100);
    glEnd();



}