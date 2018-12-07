#include<stdio.h>
#include<stdlib.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
#include<stdbool.h>
#include "draw_bot.h"

void draw_bot(void){

    glBegin(GL_POLYGON);
        glNormal3f(-1,1,0);
        glVertex3f(0,0,0);                        
        glVertex3f(1,1,0);
        glVertex3f(1,1,1);                        
        glVertex3f(0,0,1);
    glEnd();

    glBegin(GL_POLYGON);  
        glNormal3f(0,1,0);                      
        glVertex3f(1,1,0);
        glVertex3f(1,1,1);                        
        glVertex3f(2.5,1,1);
        glVertex3f(2.5,1,0);
    glEnd();


    glBegin(GL_POLYGON);
        glNormal3f(0,1,-1);                        
        glVertex3f(1,1,0);
        glVertex3f(1,0,-1);                        
        glVertex3f(2.5,0,-1);
        glVertex3f(2.5,1,0);
    glEnd();

    glBegin(GL_POLYGON); 
        glNormal3f(0,1,1);                                               
        glVertex3f(1,1,1);
        glVertex3f(1,0,2);
        glVertex3f(2.5,0,2);
        glVertex3f(2.5,1,1);
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3f(-1,1,-1);                                                
        glVertex3f(1,1,0);
        glVertex3f(0,0,0);
        glVertex3f(1,0,-1);
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3f(-1,1,1);                                                
        glVertex3f(1,1,1);
        glVertex3f(0,0,1);
        glVertex3f(1,0,2);
    glEnd();

    glBegin(GL_POLYGON); 
        glNormal3f(1,1,1);                                               
        glVertex3f(2.5,1,1);
        glVertex3f(2.5,0,2);
       glVertex3f(3.5,0,1);
    glEnd();

    glBegin(GL_POLYGON);    
        glNormal3f(1,1,-1);                                            
        glVertex3f(2.5,1,0);
        glVertex3f(2.5,0,-1);
        glVertex3f(3.5,0,0); 
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3f(1,1,0);
        glVertex3f(2.5,1,1);
        glVertex3f(2.5,1,0);
        glVertex3f(3.5,0,0);                        
        glVertex3f(3.5,0,1);
    glEnd();

    //THE HAMMER (two cubes and a sphere walk into a coordinate system...)
    glPushMatrix();

    glScalef(0.3,0.3,0.3);
    glTranslatef(1.5+HammerThrow, 1+HammerLift, 1.75);
    glRotatef(HammerTime+HammerSpin,0,0,1); 
    glTranslatef(0,HammerMeme,0);
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