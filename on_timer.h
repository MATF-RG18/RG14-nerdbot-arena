#ifndef _ON___TIMER_H_
#define _ON___TIMER_H_

extern int mv_Nx,mv_Px,mv_Nz,mv_Pz,bot_rotation;
extern int mv_Nx_A,mv_Px_A,mv_Nz_A,mv_Pz_A;
extern float HammerTime;
extern int keyStates[256];
void on_timer(int value);

#endif