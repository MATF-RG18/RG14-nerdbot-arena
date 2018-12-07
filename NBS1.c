#include<stdio.h>
#include<stdlib.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
#include<stdbool.h>
#include "draw_bot.h"
#include "on_timer.h"
#include "on_display.h"

int window_width, window_height;
//boolean promenljva koja prati tastere
int keyStates[256];

//promenljive za pomeranje po x i z osi
int mv_Nx=0,mv_Px=0,mv_Nz=0,mv_Pz=0,bot_rotation=0,Teleporting=0,Zoom=0,trail_ID=1;
//promenljive za pomeranje Anunakija
int mv_Nx_A=0,mv_Px_A=0,mv_Nz_A=0,mv_Pz_A=0;
//The Hammer Is Bangin'
float HammerTime=45, HammerThrow=0, HammerSpin=0,HammerLift=0,HammerMeme=0,TeleClp=1;

//deklaracija callback funkcija
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);
static void keyUp(unsigned char key, int x, int y);
static void on_timer_2(int value);
static void on_timer_3(int value);

int main(int argc, char** argv){

    //incijalizujemo niz kljuceva koji predstavljaju testaturu
    int i;
    for(i=0;i<256;i++)
        keyStates[i]=0;
	
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
    keyStates[(int)key] = 0;
}


//Ovu 'moc' mi je predlozila Sanja kad je rekla: "I onda ces da bacis Cekic?"
static void on_timer_2(int value){
    if(value == 0)
    {
        //ako se pomeri za sto ili se priblizi kraju arene zove se funkcija za vracanje cekica
        if(abs(HammerThrow)>abs(abs(15-mv_Nx+mv_Px)-100)){
            glutTimerFunc(20,on_timer_2,1);
            return;
        }
        //kretanje cekica po x osi
        HammerThrow=HammerThrow-1;
        //malo odizemo cekic da se trtlja po podu
        HammerLift=3;
        //promenljiva za rotiranje cekica
        HammerSpin+=20;
        //ovim pomeram cekic na dole da bi se rotirao oko centra drske
        HammerMeme=-3.5;
        glutPostRedisplay();
        //vracamo se u u nasu tajmer funkciju
        glutTimerFunc(20,on_timer_2,0);
    }
    //sve isto ko malopre samo unazad
    if(value == 1)
    {
        if(HammerThrow==0){
            //vracanje svega u normalu i izlazak iz timer_2 funkcije
            HammerLift=0;
            HammerMeme=0;
            glutPostRedisplay();
            return;
        }
        HammerThrow=HammerThrow+1;
        HammerSpin-=20;
        glutPostRedisplay();
        glutTimerFunc(20,on_timer_2,1);
    }
}

//Moc teleportovanja za sad u 4D
static void on_timer_3(int value){
        if(value == 0){
            if(TeleClp<-7){
                
                    if(bot_rotation==0)
                    {
                    trail_ID=1;
                    mv_Nx+=30;
                    }
                    else if(bot_rotation == 90)
                    {
                    trail_ID=2;
                    mv_Pz+=30;  
                    }
                    if(bot_rotation==-90)
                    {
                    trail_ID=3;
                    mv_Nz+=30;
                    }
                    else if(bot_rotation == 180 || bot_rotation == -180)
                    {
                    trail_ID=4;
                    mv_Px+=30;  
                    }
                    glutTimerFunc(0,on_timer_3,1);
                    glutPostRedisplay();
                    return;
            }
            Teleporting=1;
            TeleClp-=0.4;

            glutPostRedisplay();
            glutTimerFunc(35,on_timer_3,0);
        }
        if(value == 1){
            if(TeleClp>1){
                Zoom=0;
                Teleporting=0;
                TeleClp=1;
                glutPostRedisplay();
                return;
        }
            TeleClp+=0.5;
            glutPostRedisplay();
            Zoom=1;
            glutTimerFunc(20,on_timer_3,1);
        }

}


    
//desava se klikom na neko dugme na tastaturi
static void on_keyboard(unsigned char key, int x, int y){
    keyStates[(int)key] = 1;
    glutTimerFunc(10, on_timer, 3);
    glutTimerFunc(10, on_timer, 5);

    
    switch(key){
        case 27:
           exit(0);
           break;
        case 32:{
            glutTimerFunc(20, on_timer, 0);
            break;
            }
        case 'a':
        case 'A':
        {
            glutTimerFunc(20, on_timer, 4);
            break;
        }
        case 'd':
        case 'D':
        {
            glutTimerFunc(20, on_timer, 4);
            break;
        }
        case 'w':
        case 'W':
        {
            glutTimerFunc(20, on_timer, 4);
            break;
        }
        case 's':
        case 'S':
        {
            glutTimerFunc(20, on_timer, 4);
            break;
        }
        //bacanje cekica na f
        case 'f':
        case 'F':
             {
            glutTimerFunc(20, on_timer_2, 0);
            break;
            }
        //teleportovnje na t
        case 't':
        case 'T':{
            glutTimerFunc(20, on_timer_3, 0);
            break;
        }

    }
}       
			
//desava se kad se prozoru promeni razmera
static void on_reshape(int width, int height){
     window_width = width;
     window_height = height;
}


