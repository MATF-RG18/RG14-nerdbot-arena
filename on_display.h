#ifndef _ON___DISPLAY_H_
#define _ON___DISPLAY_H_

extern int X, Z, bot_rotation, Teleporting, Zoom, trail_ID, Tenken;
extern int XA, ZA, mvXA, mvZA, mirror_image, setMirrors;
extern float HammerTime, TeleClp;
extern int keyStates[256];
extern int window_width, window_height;

void on_display(void);

#endif