#ifndef _ON___TIMER_H_
#define _ON___TIMER_H_

extern int mvX, mvZ, X, Z, HammerUp, rot, bot_rotation, HB3mv, HTGO, HTB, Teleporting, Jump, Zoom, trail_ID, rotate, HITind, Tenken;
extern int XA, ZA, mvXA, mvZA, mirror_image, MIter, setMirrors, AnuShootMV;
extern float HammerTime, HammerThrow, HammerSpin, HammerLift, HammerMeme, TeleClp;
extern int keyStates[256];
void on_timer(int value);

#endif