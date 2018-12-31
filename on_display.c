#include<stdio.h>
#include<stdlib.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
#include<stdbool.h>
#include<time.h>
#include "on_display.h"
#include "draw_bot.h"
#include "draw_trail.h"
#include "draw_anunaki.h"
#include "collision.h"
#include "image.h"
#include "endgame.h"

int Xcopy1, Zcopy1, Ycopy1, Xcopy2, Zcopy2, Ycopy2;
GLfloat light_position[] = {0, 1, 0, 0};
int r;

GLuint names[2];

void on_display(void){



	Image * image;

	image = image_init(0, 0);


    image_read(image, "Gray.bmp");

    /* Generisu se identifikatori tekstura. */
    glGenTextures(2, names);

    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);

     glBindTexture(GL_TEXTURE_2D, names[0]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);

    /* Unistava se objekat za citanje tekstura iz fajla. */
    image_done(image);


	//cistimo buffere boje i dubine
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    //inicijalizacija izvora svetlosti
    GLfloat light_ambient[] = {0.3, 0.3, 0.3, 1};
    GLfloat light_diffuse[] = {0.7, 0.7, 0.7, 1};
    GLfloat light_specular[] = {0.9, 0.9, 0.9, 1};
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    if(HB3_HP > 0 && Anu_HP > 0){

	//namestamo sta se vidi
    glViewport(0, 0,window_width/2, window_height);

    //namestamo ugao pod kojim vidimo, razmeru sirine i duzine vidnog polja,
    // pozicije near i far clipping ravni
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (window_width/2)/(float)window_height, 1, 1500);

    //namestamo kameru gde je na sta gleda i pod kojim uglom, sad cak i prati igraca
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //40 20 
  	gluLookAt(40 + X, 15, Z,
  			 X+20, 5, Z,
  			  0, 1, 0);

    // gluLookAt(25+X+20*cos(-bot_rotation*3.145/1100), 10, Z+20*sin(-bot_rotation*3.145/1100),
   	//      	  25+X, 0, Z,
   	//      	  0, 1, 0);

  	 //namestamo materijal poda arene
    GLfloat ambient_coeffs[] = { 0.5, 0.5, 0.5, 1};
    GLfloat diffuse_coeffs[] = { 0.5, 0.5, 0.5, 1};
    GLfloat specular_coeffs[] = { 0.5, 0.5, 0.5, 1};
    GLfloat shininess = 10;
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

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

    //materijali robota
    GLfloat ambient_coeffs2[] = { 0.1, 0.1, 0.1, 1 };
    GLfloat diffuse_coeffs2[] = { 0.2, 0.3, 0.5, 1 };
  //   GLfloat diffuse_coeffs2[] = { 0.9, 0.3, 0.5, 1 };
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs2);

     //crtam Hammer-Bot-3000
    glPushMatrix();
    //Nacin pomeranja HB3
    glTranslatef(25+X, 0, Z);
    //rotiranje bota u pravcu kretanja
    glTranslatef(1.5,0,0.5);
    glRotatef(bot_rotation,0,1,0);
    glTranslatef(-1.5,0,-0.5);  

    draw_bot();
            
    glPopMatrix();

    //kada je pokrenura animacija za Tenken crta se Cekic
    if(Tenken == 1)
    {

    
    //THE HAMMER (two cubes and a sphere walk into a coordinate system...)
    glPushMatrix();

    glTranslatef(35+X, 7, Z + 10);
    //rotiranje bota u pravcu kretanja
    //glTranslatef(1.5,0,0.5);
    glRotatef(bot_rotation, 0, 1, 0);

    glScalef(8, 8, 8);
    glRotatef(HammerTime,0,0,1); 
    //glTranslatef(0,HammerMeme,0);
    //glutSolidSphere(0.8,20,20);

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


//Anunakijeva sposobnost Mirror image
    if(mirror_image == 1)
    {
    
    	if(setMirrors == 1)
    	{

    	setMirrors = 0;

    	//generisanje nasumicnog broja
    	srand(time(NULL));
    	r = rand()%100 + 1;
    	

    	//postavljanje koordinata mirror_images iste kao Anunakijeve koordinate ali malo izmestene
    	Xcopy1 = -25+XA+15;
    	Ycopy1 = 4+sin(XA/4.0)+sin(ZA/4.0);
    	Zcopy1 = ZA-10;

    	Xcopy2 = -25+XA+15;
    	Ycopy2 = 4+sin(XA/4.0)+sin(ZA/4.0);
    	Zcopy2 = ZA+10;
    
    	
    		//na osnovu random brojeva odredjujemo gde ce anunaki da se pojavi
    		if(r < 33)
    		{
    			XA = XA + 15;
    			ZA = ZA - 10;
 
    			Xcopy1 -= 15;
    			//uskladjivanje visina sva tri Anunakija
    			Ycopy1 = 4+sin(XA/4.0)+sin(ZA/4.0);
    			Ycopy2 = 4+sin(XA/4.0)+sin(ZA/4.0);
    			Zcopy1 += 10;
    		}
    		else if(r >= 33 && r < 66)
    		{
    			XA = XA + 15;
    			ZA = ZA + 10;			

    			Xcopy2 -= 15;
    			Ycopy1 = 4+sin(XA/4.0)+sin(ZA/4.0);
    			Ycopy2 = 4+sin(XA/4.0)+sin(ZA/4.0);
    			Zcopy2 -= 10;
    		}
    	

    
    	}
        //prva kopija
        glPushMatrix();
        glTranslatef(Xcopy1, Ycopy1, Zcopy1);
   
        draw_anunaki();

        glPopMatrix();

        //druga kopija
        glPushMatrix();
        glTranslatef(Xcopy2, Ycopy2, Zcopy2);
   
        draw_anunaki();

        glPopMatrix();

    }

    //Crtam Anunaki
    glPushMatrix();
    glTranslatef(-25+XA, 4+sin(XA/4.0)+sin(ZA/4.0), ZA);
    draw_anunaki();
    
    glPopMatrix();

     //iscrtavanje sfera pri teleportovanju i traga
    if(Teleporting == 1){
            
            GLfloat ambient_coeffs2[] = { 0.1, 0.1, 0.1, 1 };
            GLfloat diffuse_coeffs2[] = { 0.2, 0.3, 0.5, 1 };
            glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs2);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs2);

            if(Zoom == 1)
            {
            draw_trail(trail_ID);
            }
            
            double clip_plane1[] = {0, 1, 0, TeleClp};
    
            glClipPlane(GL_CLIP_PLANE1, clip_plane1);
            glEnable(GL_CLIP_PLANE1);

            


            glPushMatrix();
            glTranslatef(25+X+1, 1.5, Z+0.5);
            glutWireSphere(5, 20, 20);  
            glPopMatrix();
             
    
            glDisable(GL_CLIP_PLANE1);
    }

    glDisable(GL_LIGHTING);
     //ovo je zid napravljen od Sfere koju sece clipping ravan
    double clip_plane0[] = {0, -1, 0, 30};
    
    glClipPlane(GL_CLIP_PLANE0, clip_plane0);
    glEnable(GL_CLIP_PLANE0);
    glColor3f(0.5, 0.5, 0.5);
    glutSolidSphere(105, 20, 20);  

    glDisable(GL_CLIP_PLANE0);

    glEnable(GL_LIGHTING);

    glPushMatrix();

    //druga kamera koja prati drugog igraca dosta je slicno svemu sto se desava gore
    glViewport(window_width/2, 0,window_width/2, window_height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (window_width)/(float)window_height/2, 1, 1500);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(-40 + XA, 15, ZA,
               XA-20, 5,  ZA,
              0, 1, 0);


    //namestamo materijal poda arene
    GLfloat ambient_coeffs_D[] = { 0.5, 0.5, 0.5, 1};
    GLfloat diffuse_coeffs_D[] = { 0.5, 0.5, 0.5, 1};
    GLfloat specular_coeffs_D[] = { 0.5, 0.5, 0.5, 1};
    GLfloat shininess_D = 10;
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs_D);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs_D);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs_D);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess_D);

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

    //materijal mini-bota
    GLfloat ambient_coeffs2_D[] = { 0.1, 0.1, 0.1, 1 };
    GLfloat diffuse_coeffs2_D[] = { 0.2, 0.3, 0.5, 1 };
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs2_D);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs2_D);

    //crtam Hammer-Bot-3000
    glPushMatrix();

    //Nacin pomeranja HB3
    glTranslatef(25 + X, 0, Z);
    //rotiranje bota u pravcu kretanja
    glTranslatef(1.5,0,0.5);
    glRotatef(bot_rotation,0,1,0);
    glTranslatef(-1.5,0,-0.5);   

    //iscrtava se HB3
    draw_bot();

    glPopMatrix();

    if(Tenken == 1)
    {

  	//THE HAMMER (two cubes and a sphere walk into a coordinate system...)
    glPushMatrix();

    glTranslatef(35+X, 7, Z + 10);
    //rotiranje bota u pravcu kretanja
    //glTranslatef(1.5,0,0.5);
    glRotatef(bot_rotation, 0, 1, 0);

    glScalef(8, 8, 8);
    glRotatef(HammerTime,0,0,1); 
    //glTranslatef(0,HammerMeme,0);
    glutSolidSphere(0.8,20,20);

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


    //Crtam Anunaki
    glPushMatrix();
    glTranslatef(-25+XA, 4+sin(XA/4.0)+sin(ZA/4.0), ZA);
   
    draw_anunaki();

    glPopMatrix();

     //iscrtavanje sfera pri teleportovanju i traga
    if(Teleporting == 1){
            
            GLfloat ambient_coeffs2[] = { 0.1, 0.1, 0.1, 1 };
            GLfloat diffuse_coeffs2[] = { 0.2, 0.3, 0.5, 1 };
            glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs2);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs2);

            if(Zoom == 1)
            {
            draw_trail(trail_ID);
            }
            
            double clip_plane2[] = {0, 1, 0, TeleClp};
    
            glClipPlane(GL_CLIP_PLANE2, clip_plane2);
            glEnable(GL_CLIP_PLANE2);

            


            glPushMatrix();
            glTranslatef(25+X+1, 1.5, Z+0.5);
            glutWireSphere(5, 20, 20);  
            glPopMatrix();
             
    
            glDisable(GL_CLIP_PLANE2);
    }


    glDisable(GL_LIGHTING);
    //ovo je zid napravljen od Sfere koju sece clipping ravan
    double clip_plane1_D[] = {0, -1, 0, 30};
    
    glClipPlane(GL_CLIP_PLANE3, clip_plane1_D);
    glEnable(GL_CLIP_PLANE3);
    glColor3f(0.5, 0.5, 0.5);
    
    glutSolidSphere(105, 20, 20);  

    glDisable(GL_CLIP_PLANE3);
       

   glEnable(GL_LIGHTING);
 

    glPopMatrix();

	}
	else if(HB3_HP <= 0 || Anu_HP <= 0)
    {
    	endgame();
    }

     glutSwapBuffers();

}
