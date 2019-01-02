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

//pomocni parametri za mirror image
int Xcopy1, Zcopy1, Ycopy1, Xcopy2, Zcopy2, Ycopy2;

//pozicija svetla
GLfloat light_position[] = {0, 1, 0, 0};

//random broj
int r;

GLuint names[2];

void on_display(void){


	//sve sto se nadje vezano za teksture je preslikano sa vezbi, mislim da nema potrebe da komentarisem, names ima dva mesta zato sto su bile predvidjene dve teksture, ali...
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


    //dok nekom od robota HP nije na nuli crtaj podeljeni ekran 
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
    GLfloat ambient_coeffs[] = { 0.1, 0.1, 0.1, 1 };
    GLfloat diffuse_coeffs[] = { 0.5, 0, 0, 1 };
    GLfloat specular_coeffs[] = { 0.5, 0.5, 0.5, 1};
    GLfloat shininess = 10;
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);


    //crtam Hammer-Bot-3000
    glPushMatrix();

    //Nacin pomeranja HB3
    glTranslatef(25+X, 0, Z);

    //rotiranje bota u pravcu kretanja morao sam malo da ga izmestim zato sto ga nisam crtao da stoji u koordinatnom pocetku
    glTranslatef(1.5,0,0.5);
    glRotatef(bot_rotation,0,1,0);
    glTranslatef(-1.5,0,-0.5);  

    draw_bot();
            
    glPopMatrix();

    //kada je pokrenuta animacija za Tenken sposobnost crta se Cekic
    if(Tenken == 1)
    { 
    //THE HAMMER uzet iz koda draw_bot.c i transformisan u skladu sa svojom funkcionalnoscu
    glPushMatrix();

    glTranslatef(35+X, 7, Z + 10);
 
    glRotatef(bot_rotation, 0, 1, 0);

    glScalef(8, 8, 8);
    glRotatef(HammerTime,0,0,1); 

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

    //iscrtavanje sfera pri teleportovanju i traga
    if(Teleporting == 1){
  
    		//iscrtavanje traga u pravom momentu za tacnu stranu
            if(Zoom == 1)
            {
            draw_trail(trail_ID);
            }
            
            //sfera za teleportovanje u odnosu na TeleClp se polako iscrtava na dole odnosno na gore
            double clip_plane1[] = {0, 1, 0, TeleClp};
    
            glClipPlane(GL_CLIP_PLANE1, clip_plane1);
            glEnable(GL_CLIP_PLANE1);

            glPushMatrix();
            glTranslatef(25+X+1, 1.5, Z+0.5);
            glutWireSphere(5, 20, 20);  
            glPopMatrix();
             
    
            glDisable(GL_CLIP_PLANE1);
    }

   	//postavljanje boje za Anunakija
    diffuse_coeffs[0] = 0.2;
    diffuse_coeffs[1] = 0.3;
    diffuse_coeffs[2] = 0.5;

    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);

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

    //Crtam Anunakija
    glPushMatrix();
    glTranslatef(-25+XA, 4+sin(XA/4.0)+sin(ZA/4.0), ZA);
    draw_anunaki();
    
    glPopMatrix();

    //matrijali zida
    ambient_coeffs[0] = 0.7;
    ambient_coeffs[1] = 0.7;
    ambient_coeffs[2] = 0.7;

    diffuse_coeffs[0] = 0.7;
    diffuse_coeffs[1] = 0.7;
    diffuse_coeffs[2] = 0.7;

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    
    //ovo je zid napravljen od Sfere koju sece clipping ravan
    double clip_plane0[] = {0, -1, 0, 30};
    
    glClipPlane(GL_CLIP_PLANE0, clip_plane0);
    glEnable(GL_CLIP_PLANE0);

    glutSolidSphere(105, 20, 20);  

    glDisable(GL_CLIP_PLANE0);

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

    //postavljanje boje za HB3
    diffuse_coeffs[0] = 0.5;
    diffuse_coeffs[1] = 0;
    diffuse_coeffs[2] = 0;

    ambient_coeffs[0] = 0.1;
    ambient_coeffs[1] = 0.1;
    ambient_coeffs[2] = 0.1;

    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);

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

    //Tenkoen sposobnost
    if(Tenken == 1)
    {
  	//THE HAMMER
    glPushMatrix();

    glTranslatef(35+X, 7, Z + 10);
    glRotatef(bot_rotation, 0, 1, 0);
    glScalef(8, 8, 8);
    glRotatef(HammerTime,0,0,1); 

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


    //sposobnost teleportovanje
    if(Teleporting == 1){

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


   	//postavljanje boje za Anunakija
    diffuse_coeffs[0] = 0.2;
    diffuse_coeffs[1] = 0.3;
    diffuse_coeffs[2] = 0.5;

    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);

    //Crtam Anunakija
    glPushMatrix();
    glTranslatef(-25+XA, 4+sin(XA/4.0)+sin(ZA/4.0), ZA);
   
    draw_anunaki();

    glPopMatrix();


    //matrijali zida
    ambient_coeffs[0] = 0.7;
    ambient_coeffs[1] = 0.7;
    ambient_coeffs[2] = 0.7;

    diffuse_coeffs[0] = 0.7;
    diffuse_coeffs[1] = 0.7;
    diffuse_coeffs[2] = 0.7;

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    
    //ovo je zid napravljen od Sfere koju sece clipping ravan
    double clip_plane_3[] = {0, -1, 0, 30};
    
    glClipPlane(GL_CLIP_PLANE3, clip_plane_3);
    glEnable(GL_CLIP_PLANE3);

    glutSolidSphere(105, 20, 20);  

    glDisable(GL_CLIP_PLANE3);
 

    glPopMatrix();

	}
	//kada jednom od robota HP padne ispod 0 iscrtava se Endgame scena
	else if(HB3_HP <= 0 || Anu_HP <= 0)
    {
    	endgame();
    }

     glutSwapBuffers();

}
