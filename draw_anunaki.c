#include<stdio.h>
#include<stdlib.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
#include<stdbool.h>
#include"draw_anunaki.h"


void draw_anunaki(void){

	glPushMatrix(); 
	glRotatef(90, 0, 0, 1);
	
	glPushMatrix();
	glRotatef(el_rotate, 0, 1, 0);
	glTranslatef(0,0,-3.5);
    glutSolidSphere(0.5,20,20);
	glPopMatrix();

    glPopMatrix();

	glPushMatrix();
	glRotatef(45, 0, 0, 1);
	
	glPushMatrix();
	glRotatef(el_rotate, 0, 1, 0);
	glTranslatef(3.5,0,0);
    glutSolidSphere(0.5,20,20);
    glPopMatrix();
   
    glPopMatrix();


	glPushMatrix();
	glRotatef(-45, 0, 0, 1);
		
	glPushMatrix();
	glRotatef(el_rotate, 0, 1, 0);
	glTranslatef(0,0,3.5);
    glutSolidSphere(0.5,20,20);
    glPopMatrix();
   
    glPopMatrix();
    
	glPushMatrix();
	glScalef(3,0.2,3);
    glutSolidSphere(1,20,20);
    glPopMatrix();
   
    glutSolidSphere(1,20,20);

   

}

//rotiramo sfere
void on_timer_EL(int value){
	el_rotate+=2;

	if(el_rotate==360)
		el_rotate=0;

	glutPostRedisplay();
	glutTimerFunc(10,on_timer_EL,0);
}