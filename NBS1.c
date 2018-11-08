#include<stdio.h>
#include<stdlib.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

static int window_width, window_height;


//deklaracija callback funkcija
static void on_display(void);
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv){

	//standardna inicijalizacija kazemo da koristimo sistem boja RGB i dva buffera
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);


    //inicijalizacija prozora
    glutInitWindowPosition(100,100);
    glutInitWindowSize(600,600);
    glutCreateWindow("NERD-BOT-ARENA");

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
    gluPerspective(60, window_width/(float)window_height, 1, 25);

    //namestamo kameru gde je na sta gleda i pod kojim uglom
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(13, 13, 13,
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
	}
}