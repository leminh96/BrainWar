#pragma once

#include "resource.h"
UINT TimerID = 0;
UINT TimerID1 = 1;
int timer = 5;
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void OnPaint(HWND hwnd);
void OnDestroy(HWND hwnd);
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void Display_Countdown_Timer();
int a, b, c, kq, random_result,point = 0;
void Save_Window_Size(HWND hWnd);
void Restore_Window_Size(HWND hWnd);
HWND calculation, mypoint, buttonA, buttonB, start_hwnd, timer_hwnd;
void Set_Button_Result(int c);
int Check_Result(int c);
void Update_Point();
void Show_Message_Right();
void Show_Message_Wrong();