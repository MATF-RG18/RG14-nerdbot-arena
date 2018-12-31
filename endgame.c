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

	//namestamo novu scenu koja zauzima ceo prozor
    glViewport(0, 0,window_width, window_height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, window_width/(float)window_height, 1, 1500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); 
  	gluLookAt(15, 15, 15,
  			   0, 0, 0,
  			   0, 1, 0);

  	//pod arene
    glBindTexture(GL_TEXTURE_2D, names[0]);
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

 	//zid arene
    glDisable(GL_LIGHTING);
    //ovo je zid napravljen od Sfere koju sece clipping ravan
    double clip_plane1_D[] = {0, -1, 0, 30};
    
    glClipPlane(GL_CLIP_PLANE3, clip_plane1_D);
    glEnable(GL_CLIP_PLANE3);
    glColor3f(0.5, 0.5, 0.5);
    
    glutSolidSphere(105, 20, 20);  

    glDisable(GL_CLIP_PLANE3);
       

    glEnable(GL_LIGHTING);

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


    if(HammerTime == 45 && HammerThrow == 0)
    {
    //cekici iza HB3
   	glPushMatrix();

   	glRotatef(-45, 0, 1, 0);

   	glTranslatef(-5, 5, -5);

    glPushMatrix();
    //the Hammer
    glTranslatef(0, 0, -5);
    glRotatef(45, 1, 0, 0);
    glRotatef(90, 0, 1, 0);
    glutSolidSphere(1,20,20);

    glPushMatrix();

    glTranslatef(0,3.5,0);
    glScalef(1,7,1);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();

    glTranslatef(0,7,0);
    glScalef(3,2,2);
    glutSolidCube(1);

    glPopMatrix();

    glPopMatrix();

    //the Hammer
    glPushMatrix();
    //glTranslatef(0, 0, +2);
    glRotatef(-45, 1, 0, 0);
 	glRotatef(90, 0, 1, 0);
    glutSolidSphere(1,20,20);

    glPushMatrix();

    glTranslatef(0,3.5,0);
    glScalef(1,7,1);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();

    glTranslatef(0,7,0);
    glScalef(3,2,2);
    glutSolidCube(1);

    glPopMatrix();


    glPopMatrix();
    glPopMatrix();
	}


    
	//pijedastal
    glPushMatrix();
  	glTranslatef(5, 0, -5);

  	glPushMatrix();
  	glScalef(2, 5, 2);
  	glutSolidCube(2);

  	glPopMatrix();


  	//HB3
  	glPushMatrix();
  	glRotatef(135, 0, 1, 0);
  	glTranslatef(-2, 5, -0.5);
  	draw_bot();

  	glPopMatrix();

  	glPopMatrix();


  	//gubitnik
  	glPushMatrix();

  	glTranslatef(-3, 1, 3);

  	glPushMatrix();
  	glTranslatef(0, 0, 5);

  	//lebdece sfere
  	glPushMatrix();
  	glTranslatef(-2, -1, -5);
  	glutSolidSphere(0.5,20,20);

  	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5, -1, 0);
  	glutSolidSphere(0.5,20,20);

  	glPopMatrix();

  	glPushMatrix();
  	glTranslatef(5, -1, 3);
  	glutSolidSphere(0.5,20,20);

  	glPopMatrix();

  	//anunaki

  	double clip_plane1_5[] = {-1, 0, 0, 1.5};
    
   	glClipPlane(GL_CLIP_PLANE5, clip_plane1_5);
   	glEnable(GL_CLIP_PLANE5);
  	glPushMatrix();
  	glRotatef(25, 0, 0, 1);
	glScalef(3,0.2,3);
    glutSolidSphere(1,20,20);
    glPopMatrix();

    glDisable(GL_CLIP_PLANE5);

   
    glutSolidSphere(1,20,20);

    glPopMatrix();

 
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 7);

    double clip_plane1_0[] = {1, 0, 0, -1.5};
    
   	glClipPlane(GL_CLIP_PLANE0, clip_plane1_0);
   	glEnable(GL_CLIP_PLANE0);

   		glPushMatrix();
  		glRotatef(25, 0, 0, 1);
		glScalef(3,0.2,3);
   	 	glutSolidSphere(1,20,20);
   		glPopMatrix();

    glDisable(GL_CLIP_PLANE0);

    glPopMatrix();
  }
  else if(HB3_HP <= 0)
  {



	//pijedastal
    glPushMatrix();
  	glTranslatef(5, 0, -5);

  	glPushMatrix();
  	glScalef(2, 5, 2);
  	glutSolidCube(2);

  	glPopMatrix();

  	//Anunaki
  	glPushMatrix();
  		glTranslatef(0, 9, 0);

  		draw_anunaki();

    glPopMatrix();


  	glPopMatrix();

  	//gubitnik
	glPushMatrix();
	glTranslatef(-5, 0, 5);
	glRotatef(135, 0, 1, 0);

	double clip_plane1_0[] = {1, -1, 0, 0};
    
   	glClipPlane(GL_CLIP_PLANE0, clip_plane1_0);
   	glEnable(GL_CLIP_PLANE0);
	draw_bot();

	glDisable(GL_CLIP_PLANE0);


	glPopMatrix();

	//the Hammer
	glPushMatrix();
  
    glTranslatef(1, 0, 5);
    glRotatef(90, 1, 0, 0);

    glScalef(0.3, 0.3, 0.3);
    glutSolidSphere(1,20,20);

    glPushMatrix();

    glTranslatef(0,3.5,0);
    glScalef(1,7,1);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();

    glTranslatef(0,7,0);
    glScalef(3,2,2);
    glutSolidCube(1);

    glPopMatrix();

    glPopMatrix();

    //the big hammer
	glPushMatrix();

    glTranslatef(-30, 0, -55);
    glRotatef(90, 1, 0, 0);
    

    glScalef(10, 10, 10);
    glutSolidSphere(1,20,20);

    glPushMatrix();

    glTranslatef(0,3.5,0);
    glScalef(1,7,1);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();

    glTranslatef(0,7,0);
    glScalef(3,2,2);
    glutSolidCube(1);

    glPopMatrix();

    glPopMatrix();



  }

}