#include<stdio.h>
#include<stdlib.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
#include<stdbool.h>
#include "collision.h"


int collision(int IND){

	//Hammer bot bounding box
	int HB3Xmin = 26+X-3;
	int HB3Xmax = 26+X+3;
	int HB3Zmin = Z-1;
	int HB3Zmax = Z+2;


	//Anunaki bonding box
	int AXmin = -25 + XA - 3;
	int AXmax = -25 + XA + 3;
	int AZmin = ZA - 3;
	int AZmax = ZA + 3;

	//colizija sa zidom arene

	//za HB3
	if(HB3Xmax*HB3Xmax + HB3Zmax*HB3Zmax - 10000 >=0)
	{
		if(HB3Xmax>=0 && HB3Zmax>=0){
	 		X -= 1;
	 		Z -= 1;
	 		return 1;
	 	}
	 	else if(HB3Xmax>=0 && HB3Zmax<=0){
	 		X -= 1;
	 		Z += 1;
	 		return 1;
	 	}
	 	else if(HB3Xmax<=0 && HB3Zmax>=0){
	 		X += 1;
	 		Z -= 1;
	 		return 1;
	 	}
	 	else if(HB3Xmax<=0 && HB3Zmax<=0){
	 		X +=1;
	 		Z +=1;
	 		return 1;
	 	}
	} 
	//za Anunakija
	if(AXmax*AXmax + AZmax*AZmax - 10000 >=0)
	{
		if(AXmax>=0 && AZmax>=0){
	 		XA -= 1;
	 		ZA -= 1;
	 		return 1;
	 	}
	 	else if(AXmax>=0 && AZmax<=0){
	 		XA -= 1;
	 		ZA += 1;
	 		return 1;
	 	}
	 	else if(AXmax<=0 && AZmax>=0){
	 		XA += 1;
	 		ZA -= 1;
	 		return 1;
	 	}
	 	else if(AXmax<=0 && AZmax<=0){
	 		XA +=1;
	 		ZA +=1;
	 		return 1;
	 	}
	}

	//sudar anunakija i HB3

	//HB3 sa anunakijem
	if(IND == 1)
	{
	if(((AXmin <= HB3Xmax &&  HB3Xmax <= AXmax) && (AZmin <= HB3Zmax &&  HB3Zmax  <= AZmax)) || ((AXmin <= HB3Xmin &&  HB3Xmin <= AXmax) && (AZmin <= HB3Zmin &&  HB3Zmin <= AZmax)))
	{
		if(keyStates[(int)'a'] || keyStates[(int)'A'])
        {
            Z -= 2;
        }
        else if(keyStates[(int)'d'] || keyStates[(int)'D'])
        {
            Z += 2;
        }
        else if(keyStates[(int)'w'] || keyStates[(int)'W'])
        {
            X += 2;
        }
        else if(keyStates[(int)'s'] || keyStates[(int)'S'])
        {
           X -= 2;
        }
	 	
	}
	}	
	//Anunaki sa HB3
	else if(IND == 2)
	{
	if(((HB3Xmin <= AXmax &&  AXmax <= HB3Xmax) && (HB3Zmin-2 <= AZmax &&  AZmax  <= HB3Zmax+2)) || ((HB3Xmin <= AXmin &&  AXmin <= HB3Xmax) && (HB3Zmin - 2 <= AZmin &&  AZmin  <= HB3Zmax + 2)))
	{

		printf("doslo je do kolizije \n");
	
		
		if(keyStates[(int)'l'] || keyStates[(int)'L'])
        {
            ZA -= 2;
        }
        else if(keyStates[(int)'j'] || keyStates[(int)'J'])
        {
            ZA += 2;
        }
        else if(keyStates[(int)'k'] || keyStates[(int)'K'])
        {
            XA += 2;
        }
        else if(keyStates[(int)'i'] || keyStates[(int)'I'])
        {
           XA -= 2;
        }
	 	
	}
	}

	//kolizija cekica i anunakija
    if(((AXmin <= (int)(HB3Xmax+HammerThrow) && (int)(HB3Xmax+HammerThrow) <= AXmax) && (AZmin+1 <= HB3Zmax + 2 &&  HB3Zmax + 2 <= AZmax+1)))
	{
		//TODO namesti da se nesto desi pri ovoj koliziji
		printf("Prvi %d\n", (AXmin <= (int)(HB3Xmax+HammerThrow) && (int)(HB3Xmax+HammerThrow) <= AXmax));
		printf("Drugi %d\n", (AZmin+1 <= HB3Zmax + 2 &&  HB3Zmax + 2 <= AZmax+1));
		printf("Da li sam usao ovde?!\n");
		printf("HammerThrow %lf int HammerThrow %d HB3Xmax %d\n", HammerThrow, (int)HammerThrow, HB3Xmax);
		printf("HB3Xmax + HT %d HB3Xmin + HT %lf HB3Zmax %d HB3Zmin %d AXmax %d AXmin %d AZmax %d AZmin %d \n", (int)(HB3Xmax+HammerThrow), HB3Xmin + HammerThrow, HB3Zmax + 2, HB3Zmin + 2, AXmax, AXmin, AZmax+2, AZmin+2);
	}

	 return 0;
}
