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
#include "draw_anunaki.h"
#include "collision.h"

//razmere prozora
int window_width, window_height;

//boolean promenljva koja prati tastere
int keyStates[256];

//promenljive za pomeranje po x i z osi za HB3
int mvX=0, X=0, mvZ=0, Z=0, bot_rotation=0, rot=0, HB3mv=0;

//promenljive za HB3 sposobnosti
int Teleporting=0, Jump=0, Zoom=0, trail_ID=1;
float TeleClp = 1;

//promenljive za pomeranje Anunakija
int XA=0, ZA=0, mvXA=0, mvZA=0, Amv=0;

//promenljive za Anunakijeve sposobosti
int el_rotate=0, mirror_image=1;

//The Hammer Is Bangin'
float HammerTime=45, HammerThrow=0, HammerSpin=0,HammerLift=0,HammerMeme=0;
int HammerUp=1,HTGO=0, HTB=0;


//deklaracija callback funkcija
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);
static void keyUp(unsigned char key, int x, int y);

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
    glutInitWindowSize(400,400);
    glutCreateWindow("CRINGE-BOT-ARENA");

    //pozivanje callback funkcija
    glutDisplayFunc(on_display);
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutTimerFunc(20, on_timer, 0);
    glutTimerFunc(50,on_timer_EL,0);
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

    
//desava se klikom na neko dugme na tastaturi
static void on_keyboard(unsigned char key, int x, int y){
    //collision(1);
    keyStates[(int)key] = 1;
 
    switch(key){
        case 27:
           exit(0);
           break;
        case 32:{
            HammerUp=0;
            break;
            }
        case 'a':
        case 'A':
        {
            collision(1);
            HB3mv=1;
            mvX = 0;
            mvZ = 1;
            if(bot_rotation == 0 || bot_rotation == -90){
                rot = 5;
                HB3mv=0;
            }
            else if(bot_rotation == -180){
                bot_rotation=180;
                rot = 0;
                HB3mv=0;
            }
            else if(bot_rotation == 180)
            {
                rot = -5;
                HB3mv=0;  
            }
            else if(bot_rotation == 90){
                rot = 0;
            }
            break;
        }
        case 'd':
        case 'D':
        {
            HB3mv=1;
            collision(1);
            mvX = 0;
            mvZ = -1;
            if(bot_rotation == 0 || bot_rotation == 90){
                rot = -5;
                HB3mv=0;
            }
            else if(bot_rotation == 180){
                bot_rotation=-180;
                rot = 0;
                HB3mv=0;
            }
            else if(bot_rotation == -180)
            {
                rot = 5;
                HB3mv=0;  
            }
            else if(bot_rotation == 90){
                rot = 0;
            }
            break;
        }
        case 'w':
        case 'W':
        {
            HB3mv=1;
            collision(1);
            mvX = -1;
            mvZ = 0;
            if(bot_rotation == 180 || bot_rotation == 90){
                rot = -5;
                HB3mv=0;
            }
            else if(bot_rotation == -180){
                bot_rotation = 180;
                rot = 0;
                HB3mv=0;
            }
            else if(bot_rotation == -90)
            {
                rot = 5;
                HB3mv=0;  
            }
            else if(bot_rotation == 0){
                rot = 0;
            }
            break;
        }
        case 's':
        case 'S':
        {
            HB3mv=1;
            collision(1);
            mvX = 1;
            mvZ = 0;
            if(bot_rotation == 0 || bot_rotation == -90){
                rot = -5;
                HB3mv=0;
            }
            else if(bot_rotation == 90)
            {
                rot = 5;
                HB3mv=0;  
            }
            else if(bot_rotation == 180 || bot_rotation == -180){
                rot = 0;
            }
            break;
        }
        //bacanje cekica na f
        case 'f':
        case 'F':
             {
                HTGO=1;
                //malo odizemo cekic da se ne trtlja po podu
                HammerLift=3; 
                break;
            }
        //teleportovnje na t
        case 't':
        case 'T':
        {
            Teleporting = 1;
            break;
        }
        case 'i':
        case 'I':
        {
            Amv = 1;
            collision(2);
            mvXA = 1;
            mvZA = 0;
            break;
        }
        case 'k':
        case 'K':
        {
            Amv = 1;
            collision(2);
            mvXA = -1;
            mvZA = 0;
            break;
        } 
        case 'j':
        case 'J':
        {
            Amv = 1;
            collision(2);            
            mvXA = 0;
            mvZA = -1;
            break;
        } 
        case 'l':
        case 'L':
        {
            Amv = 1;
            collision(2);
            mvXA = 0;
            mvZA = 1;
            break;
        }    

    }
    //collision(1);
}       
			
//desava se kad se prozoru promeni razmera
static void on_reshape(int width, int height){
     window_width = width;
     window_height = height;
}


