#include "stdafx.h"
#include "Brain War.h"
#include "windows.h"
#include <windowsX.h>
#include <winuser.h>
#include <commctrl.h>
#include <cstdlib>
#include <ctime>

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")
#define MAX_LOADSTRING 100
#define BUFFERSIZE 255
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// The title bar text
// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_BRAINWAR, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BRAINWAR));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BRAINWAR));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_BRAINWAR);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(NULL, IDI_ERROR);
	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance; // Store instance handle in our global variable
	hWnd = CreateWindowEx(0, szWindowClass, L"Brain War",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 600, 500, NULL, NULL, hInstance, NULL);
	if (!hWnd)
	{
		return FALSE;
	}
	// set up our timer


	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	Restore_Window_Size(hWnd);
	INITCOMMONCONTROLSEX icc;
	icc.dwSize = sizeof(icc);
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);

	HFONT mFont = CreateFont(-35, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, L"Segoe UI");
	HFONT pFont = CreateFont(-25, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, L"Segoe UI");
	HFONT kFont = CreateFont(-15, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, L"Segoe UI");
	HFONT hFont = CreateFont(-15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L"Segoe UI");
	start_hwnd = CreateWindowEx(0, L"BUTTON", L"Start", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 270, 270, 100, 40, hWnd, (HMENU)IDC_BUTTON1, hInst, NULL);
	SendMessage(start_hwnd, WM_SETFONT, WPARAM(kFont), TRUE);
	HWND hwnd = CreateWindowEx(0, L"STATIC", L"BRAIN WAR", WS_CHILD | WS_VISIBLE | SS_CENTER, 170, 20, 300, 40, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(mFont), TRUE);
	calculation = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_LEFT, 270, 100, 100, 40, hWnd, NULL, hInst, NULL);
	SendMessage(calculation, WM_SETFONT, WPARAM(pFont), TRUE);
	mypoint = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_LEFT, 620, 70, 50, 40, hWnd, NULL, hInst, NULL);
	SendMessage(mypoint, WM_SETFONT, WPARAM(hFont), TRUE);
	buttonA = CreateWindowEx(0, L"BUTTON", L"", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 200, 170, 100, 40, hWnd, (HMENU)IDC_BUTTON2, hInst, NULL);
	SendMessage(buttonA, WM_SETFONT, WPARAM(hFont), TRUE);
	buttonB = CreateWindowEx(0, L"BUTTON", L"", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 350, 170, 100, 40, hWnd, (HMENU)IDC_BUTTON3, hInst, NULL);
	SendMessage(buttonB, WM_SETFONT, WPARAM(hFont), TRUE);
	hwnd = CreateWindowEx(0, L"STATIC", L"Point", WS_CHILD | WS_VISIBLE | SS_LEFT, 600, 40, 50, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(kFont), TRUE);
	timer_hwnd = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_LEFT, 310, 340, 50, 60, hWnd, NULL, hInst, NULL);
	SendMessage(timer_hwnd, WM_SETFONT, WPARAM(mFont), TRUE);
	return true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
	case WM_TIMER:
	{
		switch (wParam)
		{
		case ID_5SECONDS:
		{
			KillTimer(hWnd, TimerID);
			KillTimer(hWnd, TimerID1);
			int msgboxID = MessageBox(
				NULL,
				(LPCWSTR)L"Time up",
				(LPCWSTR)L"Game over",
				MB_ICONINFORMATION | MB_RETRYCANCEL | MB_DEFBUTTON2
			);
			if (msgboxID == IDRETRY)
			{
				HFONT hFont = CreateFont(-15, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, L"Segoe UI");
				start_hwnd = CreateWindowEx(0, L"BUTTON", L"Start", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 270, 270, 100, 40, hWnd, (HMENU)IDC_BUTTON1, hInst, NULL);
				SendMessage(start_hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
				SetWindowText(calculation, NULL);
				SetWindowText(buttonA, NULL);
				SetWindowText(buttonB, NULL);
				point = 0;
				Update_Point();
				TimerID = SetTimer(hWnd, ID_5SECONDS, 5 * 1000, NULL);
				timer = 5;
			}
			else
				PostQuitMessage(0);
			break;
		}
		case ID_1SECONDS:
			timer--;
			WCHAR *temp;
			temp = new WCHAR[5];
			swprintf(temp, 5, L"%d", timer);
			SetWindowText(timer_hwnd, temp);
			break;
		}
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void Set_Button_Result(int c)
{
	WCHAR *buffer = NULL;
	buffer = new WCHAR[255];
	switch (c)
	{
	case 0:
		kq = a + b;
		swprintf(buffer, 255, L"%d + %d", a, b);
		break;
	case 1:
		kq = a - b;
		swprintf(buffer, 255, L"%d - %d", a, b);
		break;
	case 2:
		kq = a*b;
		swprintf(buffer, 255, L"%d * %d", a, b);
		break;
	}
	SetWindowText(calculation, buffer);
	if (random_result == 0)
	{
		swprintf(buffer, 255, L"%d", kq);
		SetWindowText(buttonA, buffer);
		swprintf(buffer, 255, L"%d", kq - 10);
		SetWindowText(buttonB, buffer);
	}
	else
	{
		swprintf(buffer, 255, L"%d", kq);
		SetWindowText(buttonB, buffer);
		swprintf(buffer, 255, L"%d", kq + 10);
		SetWindowText(buttonA, buffer);
	}
}

int Check_Result(int c)
{
	int result_size = 10;
	int temp = 0;
	WCHAR *buffer = NULL;
	buffer = new WCHAR[result_size + 1];
	if (1 == c)
	{
		result_size = GetWindowTextLength(buttonA);
		GetWindowText(buttonA, buffer, result_size + 1);
		temp = _wtof(buffer);
	}
	else
	{
		result_size = GetWindowTextLength(buttonB);
		GetWindowText(buttonB, buffer, result_size + 1);
		temp = _wtof(buffer);
	}
	return temp;
}

void Update_Point()
{
	WCHAR buffer_point[5];
	swprintf(buffer_point, 5, L"%d", point);
	SetWindowText(mypoint, buffer_point);
}

void Show_Message_Right()
{
	int msgboxID = MessageBox(
		NULL,
		(LPCWSTR)L"Right, +100 points",
		(LPCWSTR)L"Congratulation",
		MB_ICONINFORMATION | MB_OK | MB_DEFBUTTON2);
}

void Show_Message_Wrong()
{
	int msgboxID = MessageBox(
		NULL,
		(LPCWSTR)L"Wrong, -100 points",
		(LPCWSTR)L"Sorry",
		MB_ICONINFORMATION | MB_OK | MB_DEFBUTTON2);
}

void Display_Countdown_Timer()
{
	WCHAR *temp;
	temp = new WCHAR[5];
	swprintf(temp, 5, L"%d", timer);
	SetWindowText(timer_hwnd, temp);
}

void OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	srand(time(NULL));
	a = rand() % 50 + 1;
	c = rand() % 3;
	b = rand() % 50 + 1;
	random_result = rand() % 2;
	switch (id)
	{
	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		break;
	case IDM_EXIT:
		DestroyWindow(hWnd);
		break;
	case IDC_BUTTON1:
		SetWindowText(start_hwnd, L"Next");
		Set_Button_Result(c);
		TimerID = SetTimer(hWnd, ID_5SECONDS, 6 * 1000, NULL);
		TimerID1 = SetTimer(hWnd, ID_1SECONDS, 1 * 1000, NULL);
		DestroyWindow(start_hwnd);
		Display_Countdown_Timer();
		break;
	case IDC_BUTTON2:
		KillTimer(hWnd, TimerID);
		KillTimer(hWnd, TimerID1);
		if (Check_Result(1) == kq)
		{
			point += 100;
			Update_Point();
			Show_Message_Right();
		}
		else
		{
			point -= 100;
			Update_Point();
			Show_Message_Wrong();
		}
		Set_Button_Result(c);
		TimerID = SetTimer(hWnd, ID_5SECONDS, 6 * 1000, NULL);
		timer = 5;
		TimerID1 = SetTimer(hWnd, ID_1SECONDS, 1 * 1000, NULL);
		Display_Countdown_Timer();
		break;
	case IDC_BUTTON3:
		KillTimer(hWnd, TimerID);
		KillTimer(hWnd, TimerID1);
		if (Check_Result(2) == kq)
		{
			point += 100;
			Update_Point();
			Show_Message_Right();
		}
		else
		{
			point -= 100;
			Update_Point();
			Show_Message_Wrong();
		}
		Set_Button_Result(c);
		TimerID = SetTimer(hWnd, ID_5SECONDS, 6 * 1000, NULL);
		timer = 5;
		TimerID1 = SetTimer(hWnd, ID_1SECONDS, 1 * 1000, NULL);
		Display_Countdown_Timer();
		break;
	}
}

void OnPaint(HWND hWnd)
{
	Save_Window_Size(hWnd);
	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(hWnd, &ps);
	EndPaint(hWnd, &ps);
}

void OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
}

void Save_Window_Size(HWND hWnd)
{
	LPRECT main = new RECT;
	LPPOINT app = new POINT;
	WCHAR *curpath = new WCHAR[BUFFERSIZE];
	WCHAR *buff = new WCHAR[BUFFERSIZE];
	long int width, height;

	GetCurrentDirectory(BUFFERSIZE, curpath);
	wcscat_s(curpath, BUFFERSIZE, L"\\config.ini");

	GetWindowRect(hWnd, main);
	width = main->right - main->left;
	height = main->bottom - main->top;
	
	app->x = main->left;
	app->y = main->top;

	ClientToScreen(NULL, app);

	swprintf(buff, BUFFERSIZE, L"%d", app->x);
	WritePrivateProfileString(L"app", L"x", buff, curpath);

	swprintf(buff, BUFFERSIZE, L"%d", app->y);
	WritePrivateProfileString(L"app", L"y", buff, curpath);

	swprintf(buff, BUFFERSIZE, L"%d", width);
	WritePrivateProfileString(L"app", L"width", buff, curpath);

	swprintf(buff, BUFFERSIZE, L"%d", height);
	WritePrivateProfileString(L"app", L"height", buff, curpath);
}

void Restore_Window_Size(HWND hWnd)
{
	WCHAR *curpath = new WCHAR[BUFFERSIZE];
	WCHAR *buffer = new WCHAR[BUFFERSIZE];
	long int width, height, x, y;

	GetCurrentDirectory(BUFFERSIZE, curpath);
	wcscat_s(curpath, BUFFERSIZE, L".\\config.ini");
	
	GetPrivateProfileString(L"app", L"x", L"100", buffer, BUFFERSIZE, curpath);
	x = _wtoi(buffer);
	GetPrivateProfileString(L"app", L"y", L"100", buffer, BUFFERSIZE, curpath);
	y = _wtoi(buffer);
	GetPrivateProfileString(L"app", L"width", L"400", buffer, BUFFERSIZE, curpath);
	width = _wtoi(buffer);
	GetPrivateProfileString(L"app", L"height", L"300", buffer, BUFFERSIZE, curpath);
	height = _wtoi(buffer);
	SetWindowPos(hWnd, NULL, x, y, width, height, NULL);
}