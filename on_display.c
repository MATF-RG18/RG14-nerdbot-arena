#include<stdio.h>
#include<stdlib.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
#include<stdbool.h>
#include "on_display.h"
#include "draw_bot.h"
#include "draw_trail.h"
#include "draw_anunaki.h"
#include "collision.h"

void on_display(void){


	//cistimo buffere boje i dubine
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    //inicijalizacija izvora svetlosti
    GLfloat light_position[] = {0, 1, 0, 0};
    GLfloat light_ambient[] = {0.0, 0.0, 0.0, 1};
    GLfloat light_diffuse[] = {1, 1, 1, 1};
    GLfloat light_specular[] = {0.9, 0.9, 0.9, 1};
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

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
    gluLookAt(40+X, 8, Z,
    	     X, 0, Z,
    	     0, 1, 0);


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
    glBegin(GL_POLYGON);
        glNormal3f(0,1,0); 
        glVertex3f(-110,-1,110);                       
        glVertex3f(110,-1,110);
        glVertex3f(110,-1,-110);                        
        glVertex3f(-110,-1,-110);
    glEnd();


    GLfloat ambient_coeffs2[] = { 0.1, 0.1, 0.1, 1 };
    GLfloat diffuse_coeffs2[] = { 0.2, 0.3, 0.7, 1 };
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs2);


     //crtam Hammer-Bot-3000
    glPushMatrix();
    //Nacin pomeranja igraca
    //Nx - negativnom stranom x ose, Px pozitivnom, analogno za z
    glTranslatef(25+X, 0, Z);
    glRotatef(bot_rotation,0,1,0);  
    //podestio sam se P2 sad koristimo vise c fajlova za ovaj projekat
    draw_bot();
            
    glPopMatrix();


    //Crtam Anunaki
    glPushMatrix();
    glTranslatef(-25+XA, 4+sin(XA/4.0)+sin(ZA/4.0), ZA);
   
    draw_anunaki();

    glPopMatrix();

    //Anunakijeva sposobnost Mirror image
    if(mirror_image == 1)
    {
        //prva kopija
        glPushMatrix();
        glTranslatef(-25+XA+15, 4+sin(XA/4.0)+sin(ZA/4.0), ZA-10);
   
        draw_anunaki();

        glPopMatrix();

        //druga kopija
        glPushMatrix();
        glTranslatef(-25+XA+15, 4+sin(XA/4.0)+sin(ZA/4.0), ZA+10);
   
        draw_anunaki();

        glPopMatrix();
    }

     //iscrtavanje sfera pri teleportovanju i traga
    if(Teleporting == 1){
            
            GLfloat ambient_coeffs2[] = { 0.1, 0.1, 0.1, 1 };
            GLfloat diffuse_coeffs2[] = { 0.2, 0.3, 0.7, 1 };
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


    //materijal zida arene nisam siguran da ovo radi ono sto zelim
    GLfloat ambient_coeffs_Wall[] = { 0.0, 0.0, 1.0, 1};
    GLfloat diffuse_coeffs_Wall[] = { 0.7, 0.7, 1, 1};
    GLfloat specular_coeffs_Wall[] = { 0, 0, 0, 1};
    glMaterialfv(GL_BACK, GL_AMBIENT, ambient_coeffs_Wall);
    glMaterialfv(GL_BACK, GL_DIFFUSE, diffuse_coeffs_Wall);
    glMaterialfv(GL_BACK, GL_SPECULAR, specular_coeffs_Wall);

    //ovo je zid napravljen od Sfere koju sece clipping ravan
    double clip_plane0[] = {0, -1, 0, 25};
    
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
    gluLookAt(-40 + XA, 8, ZA,
               XA, 0,  ZA,
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
    glBegin(GL_POLYGON);
        glNormal3f(0,1,0); 
        glVertex3f(-110,-1,110);                       
        glVertex3f(110,-1,110);
        glVertex3f(110,-1,-110);                        
        glVertex3f(-110,-1,-110);
    glEnd();

    //materijal mini-bota
    GLfloat ambient_coeffs2_D[] = { 0.1, 0.1, 0.1, 1 };
    GLfloat diffuse_coeffs2_D[] = { 0.2, 0.3, 0.7, 1 };
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs2_D);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs2_D);

    //crtam Hammer-Bot-3000
    glPushMatrix();

    //Nacin pomeranja HB3
    glTranslatef(25 + X, 0, 0+Z);
    //rotiranje bota u pravcu kretanja
    glRotatef(bot_rotation, 0, 1, 0);  

    //iscrtava se HB3
    draw_bot();

    glPopMatrix();

    //Crtam Anunaki
    glPushMatrix();
    glTranslatef(-25+XA,4+sin(XA/4.0)+sin(ZA/4.0),0+ZA);
   
    draw_anunaki();

    glPopMatrix();

    //mirror image
    if(mirror_image == 1)
    {
        //prva kopija
        glPushMatrix();
        glTranslatef(-25+XA+15, 4+sin(XA/4.0)+sin(ZA/4.0), ZA-10);
   
        draw_anunaki();

        glPopMatrix();

        //druga kopija
        glPushMatrix();
        glTranslatef(-25+XA+15, 4+sin(XA/4.0)+sin(ZA/4.0), ZA+10);
   
        draw_anunaki();

        glPopMatrix();
    }


     //iscrtavanje sfera pri teleportovanju i traga
    if(Teleporting == 1){
            
            GLfloat ambient_coeffs2[] = { 0.1, 0.1, 0.1, 1 };
            GLfloat diffuse_coeffs2[] = { 0.2, 0.3, 0.7, 1 };
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


    //materijal zida arene nisam siguran da ovo radi ono sto zelim
    GLfloat ambient_coeffs_Wall_D[] = { 0.0, 0.0, 1.0, 1};
    GLfloat diffuse_coeffs_Wall_D[] = { 0.7, 0.7, 1, 1};
    GLfloat specular_coeffs_Wall_D[] = { 0, 0, 0, 1};

    glMaterialfv(GL_BACK, GL_AMBIENT, ambient_coeffs_Wall_D);
    glMaterialfv(GL_BACK, GL_DIFFUSE, diffuse_coeffs_Wall_D);
    glMaterialfv(GL_BACK, GL_SPECULAR, specular_coeffs_Wall_D);

    //ovo je zid napravljen od Sfere koju sece clipping ravan
    double clip_plane1_D[] = {0, -1, 0, 25};
    
    glClipPlane(GL_CLIP_PLANE3, clip_plane1_D);
    glEnable(GL_CLIP_PLANE3);
    
    glutSolidSphere(105, 20, 20);  

    glDisable(GL_CLIP_PLANE3);


    glPopMatrix();

     glutSwapBuffers();

}