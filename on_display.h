#ifndef _ON___DISPLAY_H_
#define _ON___DISPLAY_H_

extern int mv_Nx,mv_Px,mv_Nz,mv_Pz,bot_rotation,Teleporting,Zoom,trail_ID;
extern int mv_Nx_A,mv_Px_A,mv_Nz_A,mv_Pz_A;
extern float HammerTime, TeleClp;
extern int keyStates[256];
extern int window_width, window_height;
void on_display(void);

#endif