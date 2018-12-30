#include<stdio.h>
#include<stdlib.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
#include<stdbool.h>
#include "collision.h"

//Hammer bot bounding box
	int HB3Xmin;
	int HB3Xmax;
	int HB3Zmin;
	int HB3Zmax;


//Anunaki bonding box
	int AXmin;
	int AXmax;
	int AZmin;
	int AZmax;


int collision(int IND){

	HB3Xmin = 25+X-3;
	HB3Xmax = 25+X+3;
	HB3Zmin = Z-1;
	HB3Zmax = Z+2;


	AXmin = -25 + XA - 3;
	AXmax = -25 + XA + 3;
	AZmin = ZA - 3;
	AZmax = ZA + 3;


	//colizija sa zidom arene

	//za HB3
	if(HB3Xmax*HB3Xmax + HB3Zmax*HB3Zmax - 8400 >=0)
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
	if(AXmax*AXmax + AZmax*AZmax - 8400 >=0)
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


	//gledam gde se po X koordinati nalzi HB3
	// i na tu koordinatu dodajem pola hammerThrow(ne znam zasto tako najpribliznije radi :D) i gledam da li se poklopi za X koordianatam Anunakija
	if((X + 25 + (int)HammerThrow/2 >= AXmin && X + 25 +(int)HammerThrow/2 <= AXmax)  && (AZmin <= Z &&  Z <= AZmax))
	{
		//smanjuje se HP anunakiju ako ga strefi cekic
		if(HITind == 1)
		{
		Anu_HP -= 1;
		HITind = 0;
		}
	}


	 return 0;
}
