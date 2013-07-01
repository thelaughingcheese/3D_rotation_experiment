#include <windows.h>
#include <iostream>
#include <process.h>

extern unsigned long buffer1[];
extern unsigned long buffer2[];
extern unsigned long *buffer_f;
extern unsigned long *buffer_b;

extern HWND *g_hwnd;
extern bool mouseButton[];
extern int mousePos[];
extern bool keyboard[];

extern float axisAngle;
extern float cubeAxisx;
extern float cubeAxisy;
extern float cubeAxisz;