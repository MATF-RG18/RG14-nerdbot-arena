#include<stdio.h>
#include<stdlib.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
#include<stdbool.h>

static int window_width, window_height;
//boolean promenljva koja prati tastere
static bool* keyStates[256];

//promenljive za pomeranje po x i z osi
static int mv_Nx=0,mv_Px=0,mv_Nz=0,mv_Pz=0,mv_Py=0;
//The Hammer Is Bangin'
static float HammerTime=45;

//deklaracija callback funkcija
static void on_display(void);
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);
static void on_timer(int value);
static void keyUp(unsigned char key, int x, int y);

int main(int argc, char** argv){

    int i;
    for(i=0;i<256;i++)
        keyStates[i]=false;
	
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
    glutKeyboardUpFunc(keyUp);

    //postavljenje boje koju zelimo da koristimo za ciscenje
    glClearColor(0,0.6,0.6,0);


    //palimo test dubine?
    glEnable(GL_DEPTH_TEST);

    //ukljucujemo normale na objekte zbog osvetljenja
    glEnable(GL_NORMALIZE);

    //malo udebljavamo crtanje linija
    glLineWidth(3);


    //upadamo u glavnu petlju
    glutMainLoop();


    //Vracamo nulu :D
	return 0;
}

//funkcija se poziva kada podignemo prst sa tastera
void keyUp (unsigned char key, int x, int y) {  
    keyStates[(int)key] = false;
}


    
//desava se klikom na neko dugme na tastaturi
static void on_keyboard(unsigned char key, int x, int y){
    keyStates[(int)key] = true;
    glutTimerFunc(10, on_timer, 3);
    
    switch(key){
        case 27:
           exit(0);
           break;
        case 32:{
            glutTimerFunc(20, on_timer, 0);
            break;
            }

    }
}       

//timer funkcija koja regulise pokrete igraca i lupanje cekica
static void on_timer(int value)
{

        if(value == 0){
        if(HammerTime < 90){
               
                HammerTime+=1;
                glutPostRedisplay();

                if(HammerTime == 90)
                    glutTimerFunc(20, on_timer, 1); 
                else
                    glutTimerFunc(20, on_timer, 0);  
             }
         }
        else if(value == 1){
        if(HammerTime != 45){
             HammerTime-=1;
             glutPostRedisplay();
             glutTimerFunc(20, on_timer, 1);

            }

        }
    else if(value == 3){
    if((keyStates[(int)'w'] || keyStates[(int)'W']) && (keyStates[(int)'d'] || keyStates[(int)'D']))
    {

        mv_Nz+=1;
        mv_Nx+=1;
        glutPostRedisplay();
    }
    if((keyStates[(int)'w'] || keyStates[(int)'W']) && (keyStates[(int)'a'] || keyStates[(int)'A']))
    {

        mv_Pz+=1;
        mv_Nx+=1;
        glutPostRedisplay();
    }
    if((keyStates[(int)'s'] || keyStates[(int)'S']) && (keyStates[(int)'d'] || keyStates[(int)'D']))
    {

        mv_Nz+=1;
        mv_Px+=1;
        glutPostRedisplay();
    }
    if((keyStates[(int)'s'] || keyStates[(int)'S']) && (keyStates[(int)'a'] || keyStates[(int)'A']))
    {

        mv_Pz+=1;
        mv_Px+=1;
        glutPostRedisplay();
    }
    if((keyStates[(int)'w'] || keyStates[(int)'W']))
    {
        mv_Nx+=1;
        glutPostRedisplay();
    }
    if((keyStates[(int)'a'] || keyStates[(int)'A']))
    {

        mv_Pz+=1;
        glutPostRedisplay();
    }
     if((keyStates[(int)'s'] || keyStates[(int)'S']))
    {
        mv_Px+=1;
        glutPostRedisplay();
    }
    if((keyStates[(int)'d'] || keyStates[(int)'D']))
    {

        mv_Nz+=1;
        glutPostRedisplay();
    }
        }
        else
            return;
}

void on_display(void){

    //donja clipping ravan koja mi odseca donji deo Sfere koja predstavlja zid arene
    double clip_plane0[] = {0, 1, 0, 2};
    glClipPlane(GL_CLIP_PLANE0, clip_plane0);
    glEnable(GL_CLIP_PLANE0);

    //inicijalizacija izvora svetlosti
    GLfloat light_position[] = {0, 10, 0, 0};
    GLfloat light_ambient[] = {0.0, 0.0, 0.0, 1};
    GLfloat light_diffuse[] = {1, 1, 1, 1};
    GLfloat light_specular[] = {0.9, 0.9, 0.9, 1};
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);


	//cistimo buffere boje i dubine
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//namestamo sta se vidi
    glViewport(0, 0,window_width, window_height);

    //namestamo ugao pod kojim vidimo, razmeru sirine i duzine vidnog polja,
    // pozicije near i far clipping ravni
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, window_width/(float)window_height, 1, 1500);

    //namestamo kameru gde je na sta gleda i pod kojim uglom, sad cak i prati igraca
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(10-mv_Nx+mv_Px, 7, 0-mv_Nz+mv_Pz,
    	     0-mv_Nx+mv_Px, 0, 0-mv_Nz+mv_Pz,
    	     0, 1, 0);

 
    //namestamo materijal poda arene
    GLfloat ambient_coeffs[] = { 0.0, 0.0, 1.0, 1};
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
        glVertex3f(-100,-1,100);                       
        glVertex3f(100,-1,100);
        glVertex3f(100,-1,-100);                        
        glVertex3f(-100,-1,-100);
    glEnd();

    //materijal mini-bota
    GLfloat ambient_coeffs2[] = { 0.1, 0.1, 0.1, 1 };
    GLfloat diffuse_coeffs2[] = { 0.2, 0.3, 0.7, 1 };
    GLfloat specular_coeffs2[] = { 0.5, 0.5, 0.5, 1 };
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs2);

    glPushMatrix();
    //Nacin pomeranja igraca
    //Nx - negativnom stranom x ose, Px pozitivnom, analogno za z
    glTranslatef(0-mv_Nx+mv_Px, 0, 0-mv_Nz+mv_Pz);
    
    //iscrtavanje mini-bota (isprobavam oblike)
    glColor3f(1,0,0);
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
    glTranslatef(1.5, 1, 1.75);
    glRotatef(HammerTime,0,0,1); 
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

    glPopMatrix();


    //materijal zida arene nisam siguran da ovo radi ono sto zelim
    GLfloat ambient_coeffs_Wall[] = { 0.0, 0.0, 1.0, 1};
    GLfloat diffuse_coeffs_Wall[] = { 0.7, 0.7, 1, 1};
    GLfloat specular_coeffs_Wall[] = { 0, 0, 0, 1};
    glMaterialfv(GL_BACK, GL_AMBIENT, ambient_coeffs_Wall);
    glMaterialfv(GL_BACK, GL_DIFFUSE, diffuse_coeffs_Wall);
    glMaterialfv(GL_BACK, GL_SPECULAR, specular_coeffs_Wall);

    //ovo je zid napravljen od Sfere koju sece clipping ravan
    double clip_plane1[] = {0, -1, 0, 12};
    
    glClipPlane(GL_CLIP_PLANE1, clip_plane1);
    glEnable(GL_CLIP_PLANE1);
    
    glutSolidSphere(100, 20, 20);  

    glDisable(GL_CLIP_PLANE0);
    glDisable(GL_CLIP_PLANE1);

    // razmenjujemo sadrzaje nasa dva buffera
    glutSwapBuffers();
}

			

//desava se kad se prozoru promeni razmera
static void on_reshape(int width, int height){
     window_width = width;
     window_height = height;
}


