#include<stdio.h>
#include<stdlib.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
#include<stdbool.h>
#include "on_timer.h"

void on_timer(int value)
{
    //udaranje cekica o pod 
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
    //rotiranje bota pri kretanju na razlicite strane fali kad idemo po dijagonali
    else if(value == 4 && (keyStates[(int)'a'] || keyStates[(int)'A']))
    {
    	if(bot_rotation==-180)
    			bot_rotation=bot_rotation*(-1);

    	if(bot_rotation<=-90)
    		bot_rotation-=5;
    	if(bot_rotation>90 && bot_rotation<=180)
    		bot_rotation-=5;
    	if(bot_rotation<90 && bot_rotation>-90)
    		bot_rotation+=5;
    	glutPostRedisplay();
    	if(bot_rotation==90)
        {
        	glutTimerFunc(20, on_timer, 3);
        }
        else
        {
        glutTimerFunc(10, on_timer, 4);
    	} 	
    }
    else if(value == 4 && (keyStates[(int)'d'] || keyStates[(int)'d']))
    {



    	if(bot_rotation==180)
    			bot_rotation=bot_rotation*(-1);
    	if(bot_rotation>=90 && bot_rotation<180)
    		bot_rotation+=5;
    	if(bot_rotation<-90 && bot_rotation>=-180)
    		bot_rotation+=5;
    	if(bot_rotation<90 && bot_rotation>0)
    		bot_rotation-=5;
    	if(bot_rotation>-90 && bot_rotation<=0)
    		bot_rotation-=5;
    	glutPostRedisplay();
        
    	if(bot_rotation==-90)
        {
        	glutTimerFunc(20, on_timer, 3);
        }
        else
        {
        glutTimerFunc(10, on_timer, 4);
    	} 
    }
    else if(value == 4 && (keyStates[(int)'w'] || keyStates[(int)'W']))
    {	

    	if(bot_rotation>0 && bot_rotation<=180)
    		bot_rotation-=5;	
    	if(bot_rotation<0 && bot_rotation>=-180)
    		bot_rotation+=5;
    	glutPostRedisplay();
    	if(bot_rotation==0)
        {
        	glutTimerFunc(20, on_timer, 3);
        }
        else
        {
        glutTimerFunc(10, on_timer, 4);
    	}
    }
    else if(value == 4 && (keyStates[(int)'s'] || keyStates[(int)'S']))
    {	
    	if(bot_rotation>0 && bot_rotation<180)
    		bot_rotation+=5;	
    	if(bot_rotation<=0 && bot_rotation>-180)
    		bot_rotation-=5;
    	glutPostRedisplay();
    	if(abs(bot_rotation)==180)
        {
        	glutTimerFunc(20, on_timer, 3);
        }
        else
        {
        glutTimerFunc(10, on_timer, 4);
    	}
    }
    //kretanje za Hammer-bot-3000
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
    //kretanje za Anunaki
    else if(value == 5){
    	if((keyStates[(int)'i'] || keyStates[(int)'I']))
    {
        mv_Nx_A+=1;
        glutPostRedisplay();
    }
    if((keyStates[(int)'j'] || keyStates[(int)'J']))
    {	
        mv_Pz_A+=1;
        glutPostRedisplay();
    }
     if((keyStates[(int)'k'] || keyStates[(int)'K']))
    {
        mv_Px_A+=1;
        glutPostRedisplay();
    }
    if((keyStates[(int)'l'] || keyStates[(int)'L']))
    {

        mv_Nz_A+=1;
        glutPostRedisplay();
    }
    }	
        else
            return;
}