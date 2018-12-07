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
		glTranslatef(-32,0,-1);
		}
		glBegin(GL_POLYGON);
             		  glNormal3f(0,1,0);
       				  glVertex3f(14-mv_Nx+mv_Px, 2.5, 0-mv_Nz+mv_Pz+0.25);                                               
      				  glVertex3f(14-mv_Nx+mv_Px, 2.5, 0-mv_Nz+mv_Pz+0.75);
       				  glVertex3f(45-mv_Nx+mv_Px, 2.5, 0-mv_Nz+mv_Pz+0.75);
      				  glVertex3f(45-mv_Nx+mv_Px, 2.5, 0-mv_Nz+mv_Pz+0.25);
   				glEnd();

   				glBegin(GL_POLYGON); 
   					  glNormal3f(0,1,0);
      				  glVertex3f(16-mv_Nx+mv_Px, 1, 0-mv_Nz+mv_Pz);                                                
      				  glVertex3f(16-mv_Nx+mv_Px, 1, 0-mv_Nz+mv_Pz+1);
       				  glVertex3f(45-mv_Nx+mv_Px, 1, 0-mv_Nz+mv_Pz+1);
      				  glVertex3f(45-mv_Nx+mv_Px, 1, 0-mv_Nz+mv_Pz);
  				glEnd();

             	glBegin(GL_POLYGON);
             		  glNormal3f(0,1,-1);
       				  glVertex3f(16-mv_Nx+mv_Px, 1, 0-mv_Nz+mv_Pz);                                                
      				  glVertex3f(16-mv_Nx+mv_Px, 0, 0-mv_Nz+mv_Pz-1);
       				  glVertex3f(45-mv_Nx+mv_Px, 0, 0-mv_Nz+mv_Pz-1);
      				  glVertex3f(45-mv_Nx+mv_Px, 1, 0-mv_Nz+mv_Pz);
   				glEnd();

   				glBegin(GL_POLYGON); 
   					  glNormal3f(0,1,1);
      				  glVertex3f(16-mv_Nx+mv_Px, 1, 0-mv_Nz+mv_Pz+1);                                                
      				  glVertex3f(16-mv_Nx+mv_Px, 0, 0-mv_Nz+mv_Pz+2);
       				  glVertex3f(45-mv_Nx+mv_Px, 0, 0-mv_Nz+mv_Pz+2);
      				  glVertex3f(45-mv_Nx+mv_Px, 1, 0-mv_Nz+mv_Pz+1);
  				glEnd();

  			glPopMatrix();

  }

  	if(trail_ID == 2 || trail_ID == 3)
		{
		
	 glPushMatrix();
	 	if(trail_ID == 3)
		{
		offset=-3;
		}
		if(trail_ID == 2)
		{
		offset=0;
		glTranslatef(1,0,-36);
		}
				glBegin(GL_POLYGON);
             		  glNormal3f(0,1,0);
       				  glVertex3f(14-mv_Nx+mv_Px+0.25, 2.5, 2-mv_Nz+mv_Pz+offset);                                               
      				  glVertex3f(14-mv_Nx+mv_Px+0.75, 2.5, 2-mv_Nz+mv_Pz+offset);
       				  glVertex3f(14-mv_Nx+mv_Px+0.75, 2.5, 37-mv_Nz+mv_Pz);
      				  glVertex3f(14-mv_Nx+mv_Px+0.25, 2.5, 37-mv_Nz+mv_Pz);
   				glEnd();

   				glBegin(GL_POLYGON); 
   					  glNormal3f(0,1,0);
      				  glVertex3f(14-mv_Nx+mv_Px, 1, 2-mv_Nz+mv_Pz);                                                
      				  glVertex3f(14-mv_Nx+mv_Px+1, 1, 2-mv_Nz+mv_Pz);
       				  glVertex3f(14-mv_Nx+mv_Px+1, 1, 35-mv_Nz+mv_Pz);
      				  glVertex3f(14-mv_Nx+mv_Px, 1, 35-mv_Nz+mv_Pz);
  				glEnd();

             	glBegin(GL_POLYGON);
             		  glNormal3f(0,1,-1);
       				  glVertex3f(14-mv_Nx+mv_Px, 1, 2-mv_Nz+mv_Pz);                                                
      				  glVertex3f(14-mv_Nx+mv_Px-1, 0, 2-mv_Nz+mv_Pz);
       				  glVertex3f(14-mv_Nx+mv_Px-1, 0, 35-mv_Nz+mv_Pz);
      				  glVertex3f(14-mv_Nx+mv_Px, 1, 35-mv_Nz+mv_Pz);
   				glEnd();

   				glBegin(GL_POLYGON); 
   					  glNormal3f(0,1,1);
      				  glVertex3f(14-mv_Nx+mv_Px+1, 1, 2-mv_Nz+mv_Pz);                                                
      				  glVertex3f(14-mv_Nx+mv_Px+2, 0, 2-mv_Nz+mv_Pz);
       				  glVertex3f(14-mv_Nx+mv_Px+2, 0, 35-mv_Nz+mv_Pz);
      				  glVertex3f(14-mv_Nx+mv_Px+1, 1, 35-mv_Nz+mv_Pz);
  				glEnd();

  			glPopMatrix();
	

}

}