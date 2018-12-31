#include<stdio.h>
#include<stdlib.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
#include<stdbool.h>
#include "on_timer.h"
#include "collision.h"

//da malo zadrzim cekic na podu
int Hammer_Pause = 0;

void on_timer(int value)
{

	if(mirror_image)
	{
		
		if(MIter <= 200)
		{
			MIter += 1;
		}
		else
		{
			MIter = 0;
			mirror_image = 0;	
    	}   
	}

    //Ovu 'moc' mi je predlozila Sanja kad je rekla: "I onda ces da bacis Cekic?"
    if(HTGO == 1)
    {
        collision(3);
		mvX = 0;
        mvZ = 0; 
        rot = 0;
        //pomera se za sto
        if(HammerThrow < -150){
            HTB = 1;
            HTGO = 0;
            HITind1 = 1;
        }
        //kretanje cekica po x osi
        HammerThrow -= 3;
        
        //promenljiva za rotiranje cekica
        HammerSpin += 30;

        //ovim pomeram cekic na dole da bi se rotirao oko centra drske
        HammerMeme=-3.5;
        glutPostRedisplay();
    }
    //sve isto ko malopre samo unazad
    else if(HTB == 1)
    {
        collision(3);
        if(HammerThrow==0)
        {
            //vracanje svega u normalu i izlazak iz timer_2 funkcije
            HammerLift = 0;
            HammerMeme = 0;

            HTB = 0;
            HTGO = 0;
            HB3mv = 1;
            HITind1 = 1;

            glutPostRedisplay();

        }
        else
        {

        mvX = 0;
        mvZ = 0;
        rot = 0;
        
        HammerThrow += 3;

        HammerSpin -= 30;

        glutPostRedisplay();
       }
    }

    //udaranje cekica o pod 
    if(HammerUp==0)
        {
        if(HammerTime < 90)
            {
                HammerTime += 3;
                glutPostRedisplay();
            }
        else if(HammerTime == 90)
        	{
            Hammer_Pause += 1;
        	}
        }
    if(Hammer_Pause == 12)
        {
        	Hammer_Pause = 0;
        	HammerUp = 1; 
            Tenken = 0;
        }

        else if(HammerUp == 1 && HammerTime != 45)
            {
                HammerTime -= 1;
                glutPostRedisplay();
            }
     	else if(HammerTime == 45)
     	{
     		Hammer_Pause = 0;
     		HITind2 = 1;
    	 }

    if(rotate == 1){
    	   if(bot_rotation > 180)
            bot_rotation = 180;
        if(bot_rotation < -180)
            bot_rotation = -180;

        //bot_rotation += rot;


        if(bot_rotation!=90 && (keyStates[(int)'a'] || keyStates[(int)'A']))
        {
            bot_rotation += rot;
        }
        else if(bot_rotation!=-90 && (keyStates[(int)'d'] || keyStates[(int)'D']))
        {
            bot_rotation += rot;
        }
        else if(bot_rotation!=0 && (keyStates[(int)'w'] || keyStates[(int)'W']))
        {
            bot_rotation += rot;
        }
        else if((bot_rotation!=180 && bot_rotation!=-180) && (keyStates[(int)'s'] || keyStates[(int)'S']))
        {
            bot_rotation += rot;
        }
        else {
        	rotate = 0;
        	HB3mv = 1;
        }
        	
    }

    //pomeranje Hammer-Bot-3000 na WASD
    if(((keyStates[(int)'w'] || keyStates[(int)'W']) || (keyStates[(int)'a'] || keyStates[(int)'A']) || (keyStates[(int)'s'] || keyStates[(int)'S']) || (keyStates[(int)'d'] || keyStates[(int)'D'])) && HB3mv == 1)
    {     
            X += mvX;
            Z += mvZ;
            glutPostRedisplay();
    }

    //kretanje za Anunaki na IJKL
        if((keyStates[(int)'k'] || keyStates[(int)'K']) || (keyStates[(int)'l'] || keyStates[(int)'L']) || (keyStates[(int)'i'] || keyStates[(int)'I']) || (keyStates[(int)'j'] || keyStates[(int)'J']))
    {
  			//dok se ne zavrsi poslednja eksplozija Anunaki ne moze da se pomera
    		if(AnuShootMV == 1)
    		{
    			mvZA = 0;
    			mvXA = 0;
    		}
            XA += mvXA;          
            ZA += mvZA;
            glutPostRedisplay();
    }



//Moc teleportovanja
if(Teleporting == 1){
            if(Jump == 0){
            if(TeleClp <- 7){                
                    if(bot_rotation==0)
                    {
                    trail_ID = 1;
                    X -= 30;
                    if(collision(1))
					{
						X += 30;
						Teleporting = 0;
                    	TeleClp = 1;
                    	Jump -= 1;
					}
                    }
                    else if(bot_rotation == 90)
                    {
                    trail_ID = 2;
                    Z += 30;
                    if(collision(1))
					{
						Z -= 30;
						Teleporting = 0;
                    	TeleClp = 1;
                    	Jump -= 1;
					}
                    }
                    else if(bot_rotation==-90)
                    {
                    trail_ID = 3;
                    Z -= 30;
                    if(collision(1))
					{
						Z += 30;
						Teleporting = 0;
                    	TeleClp = 1;
                    	Jump -= 1;
					}
                    }
                    else if(bot_rotation == 180 || bot_rotation == -180)
                    {
                    trail_ID = 4;
                    X += 30;
                    if(collision(1))
					{
						X -= 30;
						Teleporting = 0;
                    	TeleClp = 1;
                    	Jump -= 1;
					} 
                    }
                    else 
                    {
                    	Teleporting = 0;
                    	TeleClp = 1;
                    	Jump -= 1;
                    }
                    Jump +=1;
                    glutPostRedisplay();
            
            }
            else
            {
            TeleClp-=0.5;

            glutPostRedisplay();
            }
        }
        
         if(Jump == 1){
            if(TeleClp>1)
            {
                Zoom = 0;

                Teleporting = 0;
                TeleClp = 1;
                Jump = 0;
                glutPostRedisplay();
            }
            else{
            TeleClp+=0.5;

            glutPostRedisplay();

            Zoom = 1;
            }
        }

}


	collision(1);
    glutTimerFunc(30, on_timer, 0);

}