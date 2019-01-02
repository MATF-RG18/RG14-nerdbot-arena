#ifndef _ENDGAME_H_
#define _ENDGAME_H_

extern int X, Z, bot_rotation;
extern int XA, ZA, mvXA, mvZA;
extern float HammerTime;
extern int keyStates[256];
extern int window_width, window_height;
extern GLuint names[2];
extern GLfloat light_position[];

void endgame(void);

#endif