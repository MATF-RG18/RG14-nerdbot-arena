#ifndef _DRAW___ANUNAKI_H_
#define _DRAW___ANUNAKI_H_

extern int el_rotate, AnuShoot;
extern int keyStates[256];
extern int HB3_HP, XA, ZA, X, Z, mvZA, mvXA, AnuShootMV;

void draw_anunaki(void);
void on_timer_EL(int value);
	
#endif