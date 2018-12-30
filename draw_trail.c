#include<stdio.h>
#include<stdlib.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
#include<stdbool.h>
#include "draw_trail.h"

//iscrtavanje trail-a koji nastaje pri teleportovanju
void draw_trail(int trail_ID)
{
	int offset=0;
		
	if(trail_ID == 1 || trail_ID == 4){
		
		
		glPushMatrix();
		if(trail_ID == 4)
		{
		glTranslatef(-28,0,0);
		}
		glBegin(GL_POLYGON);
             		  glNormal3f(0,1,0);
       				  glVertex3f(24+X, 2.5, Z+0.25);                                               
      				  glVertex3f(24+X, 2.5, Z+0.75);
       				  glVertex3f(55+X, 2.5, Z+0.75);
      				  glVertex3f(55+X, 2.5, Z+0.25);
   				glEnd();

   				glBegin(GL_POLYGON); 
   					  glNormal3f(0,1,0);
      				  glVertex3f(26+X, 1, Z);                                                
      				  glVertex3f(26+X, 1, Z+1);
       				  glVertex3f(55+X, 1, Z+1);
      				  glVertex3f(55+X, 1, Z);
  				glEnd();

             	glBegin(GL_POLYGON);
             		  glNormal3f(0,1,-1);
       				  glVertex3f(26+X, 1, Z);                                                
      				  glVertex3f(26+X, 0, Z-1);
       				  glVertex3f(55+X, 0, Z-1);
      				  glVertex3f(55+X, 1, Z);
   				glEnd();

   				glBegin(GL_POLYGON); 
   					  glNormal3f(0,1,1);
      				  glVertex3f(26+X, 1, Z+1);                                                
      				  glVertex3f(26+X, 0, Z+2);
       				  glVertex3f(55+X, 0, Z+2);
      				  glVertex3f(55+X, 1, Z+1);
  				glEnd();

  			glPopMatrix();

  }

  	if(trail_ID == 2 || trail_ID == 3)
		{
		
	 glPushMatrix();
	 	if(trail_ID == 3)
		{
		offset=-3;
    glTranslatef(2,0,-2);
		}
		if(trail_ID == 2)
		{
		offset=0;
		glTranslatef(2+offset,0,-35);
		}
				glBegin(GL_POLYGON);
             		  glNormal3f(0,1,0);
       				  glVertex3f(24+X+0.25, 2.5, 2+Z+offset);                                               
      				  glVertex3f(24+X+0.75, 2.5, 2+Z+offset);
       				  glVertex3f(24+X+0.75, 2.5, 37+Z);
      				  glVertex3f(24+X+0.25, 2.5, 37+Z);
   				glEnd();

   				glBegin(GL_POLYGON); 
   					  glNormal3f(0,1,0);
      				  glVertex3f(24+X, 1, 2+Z);                                                
      				  glVertex3f(24+X+1, 1, 2+Z);
       				  glVertex3f(24+X+1, 1, 35+Z);
      				  glVertex3f(24+X, 1, 35+Z);
  				glEnd();

             	glBegin(GL_POLYGON);
             		  glNormal3f(0,1,-1);
       				  glVertex3f(24+X, 1, 2+Z);                                                
      				  glVertex3f(24+X-1, 0, 2+Z);
       				  glVertex3f(24+X-1, 0, 35+Z);
      				  glVertex3f(24+X, 1, 35+Z);
   				glEnd();

   				glBegin(GL_POLYGON); 
   					  glNormal3f(0,1,1);
      				  glVertex3f(24+X+1, 1, 2+Z);                                                
      				  glVertex3f(24+X+2, 0, 2+Z);
       				  glVertex3f(24+X+2, 0, 35+Z);
      				  glVertex3f(24+X+1, 1, 35+Z);
  				glEnd();

  			glPopMatrix();
	

}

}