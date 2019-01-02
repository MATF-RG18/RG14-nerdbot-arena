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
  //pomocni parametar za sredjivanje traga
	int offset=0;
	
  //crtanje traga kada je rotacije 0, 180 ili -180	
	if(trail_ID == 1 || trail_ID == 4){
		
		
		glPushMatrix();
    //trag je primarno napravljen za rotaciju 0 kada je 180(-180) mora da se malo podesi bolje
		if(trail_ID == 4)
		{
		glTranslatef(-28,0,0);
    offset = 7;
		}
    //gomila poligona koji predstavljaju trag
		glBegin(GL_POLYGON);
             		  glNormal3f(0,1,0);
       				  glVertex3f(24+X+offset, 2.5, Z+0.25);                                               
      				  glVertex3f(24+X+offset, 2.5, Z+0.75);
       				  glVertex3f(50+X+offset, 2.5, Z+0.75);
      				  glVertex3f(50+X+offset, 2.5, Z+0.25);
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

    //ako je rotacija bila 90 ili -90 ista stvar
  	if(trail_ID == 2 || trail_ID == 3)
		{
		
	 glPushMatrix();
	 	if(trail_ID == 3)
		{
    glTranslatef(2,0,-2);
    offset = 0;
		}
		if(trail_ID == 2)
		{
		offset=1;
		glTranslatef(2,0,-35.5);
		}
          glBegin(GL_POLYGON);
                  glNormal3f(0,1,0);
                glVertex3f(24+X+0.25, 2.5, Z);                                               
                glVertex3f(24+X+0.75, 2.5, Z);
                glVertex3f(24+X+0.75, 2.5, 37+Z+offset);
                glVertex3f(24+X+0.25, 2.5, 37+Z+offset);
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