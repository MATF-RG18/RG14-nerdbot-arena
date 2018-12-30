#ifndef _ENDGAME_H_
#define _ENDGAME_H_

extern int X, Z, bot_rotation, Teleporting, Zoom, trail_ID;
extern int XA, ZA, mvXA, mvZA, mirror_image, setMirrors;
extern float HammerTime, TeleClp;
extern int keyStates[256];
extern int window_width, window_height;
extern GLuint names[2];
extern GLfloat light_position[];

void endgame(void);

#endif