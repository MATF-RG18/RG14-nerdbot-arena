#include<stdio.h>
#include<stdlib.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>

static int window_width, window_height;

//promenljive za pomeranje po x i z osi
static int mv_Nx=0,mv_Px=0,mv_Nz=0,mv_Pz=0,mv_Py=0;

//deklaracija callback funkcija
static void on_display(void);
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv){

	//standardna inicijalizacija kazemo da koristimo sistem boja RGB, dva buffera i prepoznaje se dubina 
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);


    //inicijalizacija prozora
    glutInitWindowPosition(100,100);
    glutInitWindowSize(600,600);
    glutCreateWindow("CRINGE-BOT-ARENA");

    //pozivanje callback funkcija
    glutDisplayFunc(on_display);
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);

    //postavljenje boje koju zelimo da koristimo za ciscenje
    glClearColor(0,0,0,0);


    //palimo test dubine?
    glEnable(GL_DEPTH_TEST);

    //malo udebljavamo crtanje linija
    glLineWidth(3);


    //upadamo u glavnu petlju
    glutMainLoop();


    //Vracamo nulu :D
	return 0;
}

void on_display(void){

	//cistimo buffere boje i dubine
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//namestamo sta se vidi
    glViewport(0, 0,window_width, window_height);

    //namestamo ugao pod kojim vidimo, razmeru sirine i duzine vidnog polja,
    // pozicije near i far clipping ravni
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, window_width/(float)window_height, 1, 1500);

    //namestamo kameru gde je na sta gleda i pod kojim uglom
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(10, 10, 10,
    	     0, 0, 0,
    	     0, 1, 0);


    //iscrtavam koordinatni sistem da se lakse snadjem u svetu
    glBegin(GL_LINES);
       glColor3f(1,0,0);
       glVertex3f(100,0,0);
       glVertex3f(0,0,0);
       
       glColor3f(0,1,0);
       glVertex3f(0,100,0);
       glVertex3f(0,0,0);
       
       glColor3f(0,0,1);
       glVertex3f(0,0,100);
       glVertex3f(0,0,0);
    glEnd();

    glColor3f(0.7, 0.7, 1);
     
    //pravim pod Arene(od kocke skalirane (po x i z) i malo translirane na dole) 
    glPushMatrix();
        glTranslatef(0, -0.5, 0);
        glScalef(100,0,100);
        glutSolidCube(1);
    glPopMatrix();
   
   
    glColor3f(0.4, 0.5, 1);
    glPushMatrix();
    //Nacin pomeranja igraca, za sad u cetiri pravca 
    //Nx - negativnom stranom x ose, Px pozitivnom, analogno za z
    glTranslatef(0-mv_Nx+mv_Px, 0, 0-mv_Nz+mv_Pz);
    //trenutni mini-bot (isprobavam oblike)
    glBegin(GL_LINE_STRIP);
        glVertex3f(0,0,0);                        
        glVertex3f(0,0,1);
        glVertex3f(1,1,1);                        
        glVertex3f(1,1,0);
        glVertex3f(0,0,0);
        glVertex3f(2,0,0);
        glVertex3f(2,0,1);
        glVertex3f(2,1,1);
        glVertex3f(2,1,0);
        glVertex3f(2,0,0);
        glVertex3f(2,0,1);
        glVertex3f(0,0,1);
        glVertex3f(1,1,1); 
        glVertex3f(2,1,1); 
        glVertex3f(2,1,0);                                                
        glVertex3f(1,1,0);                       
    glEnd();
    //glutWireTorus(0.3,0.5,10,10);
    //glutSolidCube(0.7);
    glPopMatrix();
    //ovo je zid napravljen od torusa 
    glColor3f(0.3764, 0.3764, 0.3764);  
    glRotatef(90, 1, 0, 0);
    glutSolidTorus(40,1,10,10);

    // razmenjujemo sadrzaje nasa dva buffera
    glutSwapBuffers();
}

			

//desava se kad se prozoru promeni razmera
static void on_reshape(int width, int height){
     window_width = width;
     window_height = height;
}

//desava se klikom na neku dugme na testaturi
static void on_keyboard(unsigned char key, int x, int y){
	switch(key){
		case 27:
		   exit(0);
		   break;
		case 'w': //Move using W-A-S-D
		case 'W':
			{
			mv_Nx +=1;
			glutPostRedisplay();
			break;
			}
		case 's':
		case 'S':
			{
			mv_Px +=1;
			glutPostRedisplay();
			break;
			}
		case 'a':
		case 'A':
			{
			mv_Pz +=1;
			glutPostRedisplay();
			break;
			}
		case 'd':
		case 'D':
			{
			mv_Nz +=1;
			glutPostRedisplay();
			break;
			}

	}
}