//ova funkcija je trebala samo da iscrtava Anunakija tako je bila inicijalno zamisljena... stvari su se otrgle kontroli
#include<stdio.h>
#include<stdlib.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
#include<stdbool.h>
#include"draw_anunaki.h"

//razni indikatori za razlicita stanja sfera, iteracije itd... 
static int AnuBullet1 = 0,AnuBullet2 = 0,AnuBullet3 = 0, br_iter = 0, AnuExplosion1 = 0,AnuExplosion2 = 0,AnuExplosion3 = 0;
static int NotFired1 = 1, NotFired2 = 1, NotFired3 = 1, TIME_INT = 20, SF_HITind = 0;
static int laserIter = 0, LS_Hitind = 0;



void draw_anunaki(void){


	if(laserTime == 0 || AnuShoot == 1){
	//ako nije ispaljena vrti je po njenoj osi normalno
	if(NotFired1 == 1)
	{
	glPushMatrix();
	//okrecem joj ptanju rotacije za 90 
	glRotatef(90, 0, 0, 1);
	
	glPushMatrix();
	//rotiram je po putanji
	glRotatef(el_rotate, 0, 1, 0);
	glTranslatef(0,0,-3.5);
	//rotiram je i oko sebe same ali to se bas i ne vidi :D
    glRotatef(el_rotate, 0, 1, 0);
    glutSolidSphere(0.5,20,20);
	glPopMatrix();
	glPopMatrix();
    }
    //ispaljivanje sfere 1
    else if(AnuExplosion1 == 0)
    {
    	glPushMatrix(); 
    	//pomera se malo njen pravac
    	glRotatef(-15, 0,1,0);
    	//horizontalni hitac, taman kad pomislis da ti fizika iz srednje nikad u zivotu nece trbati izgooglas formulu :D
	  	glTranslatef(AnuBullet1,3.5-(AnuBullet1*AnuBullet1)*9.81/6000, 3.5);
    	glutSolidSphere(0.5,20,20);
    	glPopMatrix();
    }
    else if(AnuExplosion1 == 1 && br_iter <=160)
    {
    	glPushMatrix(); 
    	glRotatef(-15, 0,1,0);
    	//pomeri na koordinate gde se sudarilo sa zemljom
	  	glTranslatef(64,-4, 0);
	  	//skaliranje sfere preko AnuBullet-a - 48 regulise velicinu eksplozje
	  	glScalef(AnuBullet1-48, AnuBullet1-48, AnuBullet1-48);
    	glutSolidSphere(0.5,20,20);
    	glPopMatrix();
    }

  

   

	
	if(NotFired2 == 1)
	{
	glPushMatrix();
	glRotatef(45, 0, 0, 1);
	
	glPushMatrix();
	glRotatef(el_rotate, 0, 1, 0);
	glTranslatef(3.5,0,0);
	glRotatef(el_rotate, 0, 1, 0);
	glutSolidSphere(0.5,20,20);
	glPopMatrix();
	glPopMatrix();
	}
	else if(AnuExplosion2 == 0)
	{
		glPushMatrix();	
		glTranslatef(AnuBullet2,3.5-(AnuBullet2*AnuBullet2)*9.81/6000,-3.5);
		glutSolidSphere(0.5,20,20);
    	glPopMatrix();
	}
	else if(AnuExplosion2 == 1 && br_iter <=195)
    {
    	glPushMatrix(); 
	  	glTranslatef(64,-4, 0);
	  	glScalef(AnuBullet2-48, AnuBullet2-48, AnuBullet2-48);
    	glutSolidSphere(0.5,20,20);
    	glPopMatrix();
    }


	if(NotFired3 == 1)
	{
	glPushMatrix();
	glRotatef(-45, 0, 0, 1);
		
	glPushMatrix();
	glRotatef(el_rotate, 0, 1, 0);
	glTranslatef(0,0,3.5);
	glRotatef(el_rotate, 0, 1, 0);
	glutSolidSphere(0.5,20,20);
    glPopMatrix();
      glPopMatrix();
	}
	else if(AnuExplosion3 == 0)
	{
		glPushMatrix();
		glRotatef(15, 0,1,0);
		glTranslatef(AnuBullet3,3.5-(AnuBullet3*AnuBullet3)*9.81/6000,0);
		glutSolidSphere(0.5,20,20);
    	glPopMatrix();
	}
	else if(AnuExplosion3 == 1 && br_iter <=230)
    {
    	glPushMatrix(); 
    	glRotatef(15, 0,1,0);
	  	glTranslatef(64,-4, 0);
	  	glScalef(AnuBullet3-48, AnuBullet3-48, AnuBullet3-48);
    	glutSolidSphere(0.5,20,20);
    	glPopMatrix();
    }
	}
	//animacija lasera 
	else if(laserTime == 1 && AnuShoot == 0)
	{	

		//laserov sistem(par sfera neke linije i jedna ravan) prvo rotiramo oko Z ose da bi laser isao od dole na gore
		glPushMatrix();

		 glTranslatef(0, 4, 0);
		
		 glRotatef(laserIter*2-45,  0, 0, 1);

		//ravan koju laser napravi malo isecena da ne bi izgledalo ko da Anunaki ubija samog sebe
		glDisable(GL_LIGHTING);
		double clip_plane1_4[] = {1, 1, 0, -1};
    
   	 	glClipPlane(GL_CLIP_PLANE4, clip_plane1_4);
   	 	glEnable(GL_CLIP_PLANE4);
		glPushMatrix();
			glColor3f(0.2, 0, 0.2);

		  	glTranslatef(100, -100, 0);
		  	glScalef(200, 200, 0.1);
		  	glutSolidCube(1);

		glPopMatrix();

		glDisable(GL_CLIP_PLANE4);
		glEnable(GL_LIGHTING);

		glTranslatef(0, -4, 0);

		glTranslatef(0, 4, 0);
		//posle laserov sistem rotiramo oko X ose da bi izgledalo kul
		glRotatef(laserIter*10, 1, 0, 0);
		glTranslatef(0, -4, 0);

		//zraci energije 
		glDisable(GL_LIGHTING);
		glColor3f(0.2, 0, 0.2);
		glLineWidth(2);
		glBegin(GL_LINES);
			glVertex3f(0, 5, 0);
			glVertex3f(1, 4, 0);

			glVertex3f(0, 3, +1);
			glVertex3f(1, 4, 0);


			glVertex3f(0, 3, -1);
			glVertex3f(1, 4, 0);

		glEnd();
		glLineWidth(1);
		glEnable(GL_LIGHTING);

		//Anunakijeve standardne tri sfere
		glPushMatrix();

		glTranslatef(0, 5, 0);
	
		glutSolidSphere(0.4,20,20);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, 3, 1);
		
		glutSolidSphere(0.4,20,20);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, 3, -1);

		glutSolidSphere(0.4,20,20);
		glPopMatrix();

		glPopMatrix();

	}

    
  
    //A evo i razlga sto se prvobitno funkcija zvala draw_anunaki
	glPushMatrix();
	glScalef(3,0.2,3);
    glutSolidSphere(1,20,20);
    glPopMatrix();
   
    glutSolidSphere(1,20,20);

   

}

//rotiramo sfere
void on_timer_EL(int value){

	//parametar animacije za rotiranje sfera
	el_rotate+=2;

	if(el_rotate==360)
		el_rotate=0;

	
	//ako je pritisnuto p pokrece se animacija ispaljivanja sfera
	if(AnuShoot == 1)
	{
		//iteracije predstavljaju vreme i implementiraju cooldown za "Napad"
		br_iter += 1;

		//posto smo zapoceli animaciju ugasi rotiranje sfera i ispali ih jednu po jednu, sa br_iter ogranici koliko ce sfera da raste kad eksplodira
		if( br_iter >= 1 && br_iter <= 80){
			NotFired1 = 0;
			AnuBullet1 += 1;
		}
		if( br_iter >= 35 && br_iter <= 115){
			NotFired2 = 0;
			AnuBullet2 += 1;
		}
		if( br_iter >= 70 && br_iter <= 150){
			NotFired3 = 0;
			AnuBullet3 += 1;
		}

		//kad sfera lupi o pod zapocni eksploziju
		if(3.5-(AnuBullet1*AnuBullet1)*9.81/6000 <= -4 && AnuExplosion1 == 0)
		{
			AnuExplosion1 = 1;
		}

		if(3.5-(AnuBullet2*AnuBullet2)*9.81/6000 <= -4 && AnuExplosion2 == 0)
		{
			AnuExplosion2 = 1;
		}

		if(3.5-(AnuBullet3*AnuBullet3)*9.81/6000 <= -4 && AnuExplosion3 == 0)
		{
			AnuExplosion3 = 1;
		}

		

		//da se zna da sam retardiran umesto da gledam HB3 ko0rdinate i da li se one nalaze u koordinatama eksplozije
		// ja sam pokusavao da nadjem kad je uksplozija usla u njegove koordinate... pokusavao sam to danima....

			//SF_HITind regulise da se samo jednom HB3-u smanji HP, kada je u unutrasnjosti eksplozije stalno mu se oduzima HP u suprotnom
			if(SF_HITind == 0){

			//kada Sfera padne (prva padne u 64-toj iteraciji) krece da se siri napravio sam "pravugaonik" koji obuhvata celu tu eksploziju
			//tom pravugaoniku gledam Xmin i Xmax koji se smanjuje odnosno povecava u tom rastucem intervalu gledam da li je HB3_X koordinata, analogno za Z
			//br_iter regulise da se u tacnom trenutku trazi kolizija	
			if(X + 25 >= XA - 25 - AnuBullet1 + 128 && X + 25 <= XA - 25 + AnuBullet1  && Z >= ZA + 17 - AnuBullet1 + 64 && Z  <= ZA + 17 + AnuBullet1 - 64 && br_iter >= 64 && br_iter <= 80)
			{
				SF_HITind = 1;
				HB3_HP -=1;
				printf("EXPLOSION NOISES\n");
			}
			//sve je isto kao za prvu koliziju samo je Z kordinata pomerena zato sto ova sfera pada pravo i gleda se u drugom trenutku
			if(X + 25 >= XA - 25 - AnuBullet2 + 128 && X + 25 <= XA - 25 + AnuBullet2  && Z >= ZA - AnuBullet2 + 64 && Z  <= ZA + AnuBullet2 - 64 && br_iter >= 99 && br_iter <= 115)
			{
				SF_HITind = 1;
				HB3_HP -=1;
				printf("EXPLOSION NOISES\n");
			}
			if(X + 25 >= XA - 25 - AnuBullet3 + 128 && X + 25 <= XA - 25 + AnuBullet3  && Z >= ZA - 17 - AnuBullet3 + 64 && Z  <= ZA - 17 + AnuBullet3 - 64 && br_iter >= 134 && br_iter <= 150)
			{
				SF_HITind = 1;
				HB3_HP -=1;
				printf("EXPLOSION NOISES\n");
			}
			}	

		if(br_iter == 230){
			AnuShootMV = 0;
		}
		
		//posle nekog vremena sve vrati na staro
		if(br_iter >= 800)
		{
			AnuShoot = 0;
			NotFired1 = 1;
			NotFired2 = 1;
			NotFired3 = 1;
			AnuBullet1 = 0;
			AnuExplosion1 = 0;
			AnuBullet2 = 0;
			AnuExplosion2 = 0;
			AnuExplosion3 = 0;
			AnuBullet3 = 0;
			br_iter = 0;
			SF_HITind = 0;
		}


	}

	//aktiviran je laser
	if(laserTime == 1)
		{
			//ne mrdaj dok se ispaljuje laser, recikliram movement blocker iz AnuShoot
			AnuShootMV = 1;

			//ako je ukljucena animacija AnuShoot iskljuci laser i move blockera
			if(AnuShoot == 1)
			{
				laserTime = 0;
				laserIter -= 2;
				AnuShootMV = 0;
			}

			//uvecava se parametar animacije
			laserIter += 2;

			//kolizija za HB3 i zrak lasera, da li im se poklapaju koordinate po Z i da li je HB3 ispred Anunakija po X-osi 
			if(Z <= ZA + 2 && Z >= ZA - 2 && X + 25 >= XA -25 && laserIter >= 6)
			{
				if(LS_Hitind == 0)
				{
					LS_Hitind = 1;
					HB3_HP -= 1;
				printf("LASER NOISES\n");
				}
			}

			//resetovanje svega
			if(laserIter == 80)
			{
				laserTime = 0;
				laserIter = 0;
				el_rotate = 0;
				AnuShootMV = 0;
				LS_Hitind = 0;
			}
		}

	glutPostRedisplay();
	glutTimerFunc(TIME_INT,on_timer_EL,0);
}