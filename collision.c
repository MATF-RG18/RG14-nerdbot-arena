//ako se dva objekata sudare prijavi i obradi taj sudar
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

	//za HB3 gledam arenu kao da je krug sa poluprecnikom 95, i bacujem koordinate HB3 u jednacinu tog kruga da ocenim da li je u unutrasnjosti
	if(HB3Xmax*HB3Xmax + HB3Zmax*HB3Zmax - 8400 >=0)
	{
		printf("It seems something is in your way!?\n");
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
		printf("Try flying over that.\n");
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


	//gledam gde se po X/Z koordinati nalzi HB3 i na tu koordinatu dodajem 1/3 HammerThrow(ispred translate-a sam primenio scale(0.3, 0.3, 0.3))
	//pomnozenu sa cos/sin ugla rotacije sto pravi krugove oko HB3 koji predstavljaju sve moguca mesta udarca u anunakija
	// i onda gledam da li se poklopi za bounding boxom Anunakija
	if((X + 25 + (int)(HammerThrow/3*cos(-bot_rotation*3.14/180)) >= AXmin && X + 25 + (int)(HammerThrow/3*cos(-bot_rotation*3.14/180)) <= AXmax) 
	 && (AZmin <= Z + (int)(HammerThrow/3*sin(-bot_rotation*3.14/180)) &&  Z + (int)(HammerThrow/3*sin(-bot_rotation*3.14/180)) <= AZmax))
	{
		//smanjuje se HP anunakiju ako ga strefi cekic
		if(HITind1 == 1)
		{
		HITind1 = 0;
		Anu_HP -= 1;
		printf("Anu: I can't believe you have done this...\n");
		}
	}


	//sudar Velikog cekica i Anunakija slicno kao za HammerThrow samo sad imam fiksan poluprecnik kruznice (50 - duzina cekica) 
	//proveravam gde je anunaki u odnosu na bounding box glave cekica
	if(HammerTime >= 85 && HammerTime <= 90 &&
		( XA - 25 <= (X + 38 - 50*cos(-bot_rotation*3.14/180)) && (XA - 25 >= (X + 12 - 50*cos(-bot_rotation*3.14/180))) )
		&&  ( ZA <= (Z + 20 - 50*sin(-bot_rotation*3.14/180)) && ZA >= (Z - 50*sin(-bot_rotation*3.14/180)) ) )
	{
		//da bi se samo jednom skinuo HP Anunakiju
		if(HITind2 == 1)
		{
		HITind2 = 0;
		Anu_HP -= 1;
		printf("HB3: KOKUJO TENKEN MJOO!\nAnu: oh noOoOo..\n");
		}
		
	}


	 return 0;
}
