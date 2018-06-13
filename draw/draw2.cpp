// draw.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "draw2.h"
#include <vector>
#include <cstdio>


#define MAX_LOADSTRING 100
#define TMR_1 1

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

INT value;

// buttons
HWND hwndButton;
bool Zlap = false;
bool Zlapane = false;
bool puscilem = false;
double Pi = 3.14;
int Ramie = 100; //
int Alfa = 45;
int Beta = 0;
int numerek = 0;
// sent data
int col = 0;
int Ox = 250;
int Oy = 250;
int Ax; int Ay; int Bx; int By;

int warstwa[250] = { 0 };
int max = 0;
int numer_klockaX = 1;
int numer_klockaY = 0;

int klocek_1[13] = { 65,220,100,220,135,220,170,220,205,220,240,220 };


std::vector<Point> data;
RECT drawArea1 = { 0, 0, 150, 200 };
RECT drawArea2 = { 50, 400, 650, 422 };

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Buttons(HWND, UINT, WPARAM, LPARAM);


void MyOnPaint(HDC hdc)
{
	Graphics graphics(hdc);
	Pen pen(Color(255, 0, 0, 255));
	Pen pen2(Color(255, 255, 0, 0));

	graphics.DrawLine(&pen, 0, 250, 500, 250); //
	graphics.DrawLine(&pen, 250, 0, 250, 500);

	Ax = Ramie * cos(Alfa *Pi / 180) + Ox;
	Ay = -Ramie * sin(Alfa *Pi / 180) + Oy;

	graphics.DrawLine(&pen, Ox, Oy, Ax, Ay);

	Bx = Ramie * cos(Beta *Pi / 180) + Ax;
	By = -Ramie * sin(Beta *Pi / 180) + Ay;
	graphics.DrawLine(&pen, Ax, Ay, Bx, By);
	if (Zlap == true)
	{
		if (Bx >= klocek_1[numer_klockaY] && By >= klocek_1[numer_klockaX] && Bx <= (klocek_1[numer_klockaY] + 30) && By <= (klocek_1[numer_klockaX] + 30))
		{
			Zlapane = true;
		}
		if (Zlapane == true)
		{
			klocek_1[numer_klockaY] = Bx;
			klocek_1[numer_klockaX] = By;
		}

		graphics.DrawRectangle(&pen, klocek_1[0], klocek_1[1], 30, 30);
		graphics.DrawRectangle(&pen, klocek_1[2], klocek_1[3], 30, 30);
		graphics.DrawRectangle(&pen, klocek_1[4], klocek_1[5], 30, 30);
		graphics.DrawRectangle(&pen, klocek_1[6], klocek_1[7], 30, 30);
		graphics.DrawRectangle(&pen, klocek_1[8], klocek_1[9], 30, 30);
		graphics.DrawRectangle(&pen, klocek_1[10], klocek_1[11], 30, 30);
		graphics.DrawRectangle(&pen2, klocek_1[numer_klockaY], klocek_1[numer_klockaX], 30, 30);

	}
	else
	{
		if (numerek == 1) {
			for (int i = Bx - 250; i < Bx - 220; i++) {
				warstwa[i] ++;
			}

			for (int i = Bx - 250; i < Bx - 220; i++) {
				if (warstwa[i] > max) {
					max = warstwa[i];
				}

			}
			for (int i = Bx - 250; i < Bx - 220; i++) {

				warstwa[i] = max;


			}
			numerek = 0;
			klocek_1[numer_klockaX] = 220 - (max * 30);
			max = 0;
		}

		//klocek_1[numer_klockaX] = 220 - (max * 30);
		graphics.DrawRectangle(&pen, klocek_1[0], klocek_1[1], 30, 30);
		graphics.DrawRectangle(&pen, klocek_1[2], klocek_1[3], 30, 30);
		graphics.DrawRectangle(&pen, klocek_1[4], klocek_1[5], 30, 30);
		graphics.DrawRectangle(&pen, klocek_1[6], klocek_1[7], 30, 30);
		graphics.DrawRectangle(&pen, klocek_1[8], klocek_1[9], 30, 30);
		graphics.DrawRectangle(&pen, klocek_1[10], klocek_1[11], 30, 30);
		graphics.DrawRectangle(&pen2, klocek_1[numer_klockaY], klocek_1[numer_klockaX], 30, 30);
	}
}

void Klocek(int numerekX, int numerekY)
{
	for (int i = Bx - 250; i < Bx - 220; i++) {
		warstwa[Bx] ++;
	}

	for (int i = Bx - 250; i < Bx - 220; i++) {
		if (warstwa[i] > max) {
			max = warstwa[i];
		}
	}
	klocek_1[numerekX] = 220 - (max * 30);
	klocek_1[numerekY] = Bx;
}

void repaintWindow(HWND hWnd, HDC &hdc, PAINTSTRUCT &ps, RECT *drawArea)
{
	if (drawArea == NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
	hdc = BeginPaint(hWnd, &ps);
	MyOnPaint(hdc);
	EndPaint(hWnd, &ps);
}

// main function (exe hInstance)
int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	value = 0;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);



	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAW));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAW));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_DRAW);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;


	hInst = hInstance; // Store instance handle (of exe) in our global variable

					   // main window
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	// create button and store the handle                                                       

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Alfa minus"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		600, 30,                                  // the left and top co-ordinates
		100, 50,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON1,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Alfa plus"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		710, 30,                                  // the left and top co-ordinates
		100, 50,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON2,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                              // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Beta minus"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		600, 100,                                  // the left and top co-ordinates
		100, 50,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON3,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Beta plus"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		710, 100,                                  // the left and top co-ordinates
		100, 50,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON4,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Numer klocka plus"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		600, 170,                                  // the left and top co-ordinates
		150, 50,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON5,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Numer klocka minus"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		750, 170,                                  // the left and top co-ordinates
		150, 50,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON6,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Zlap mnie"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		600, 240,                                  // the left and top co-ordinates
		100, 50,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON7,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Mo¿esz ju¿ mnie puœciæ "),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		600, 310,                                  // the left and top co-ordinates
		300, 50,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON8,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("Kwadrat 1 "),
		WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
		460, 360, 100, 30, hWnd, (HMENU)ID_RBUTTON1, GetModuleHandle(NULL), NULL);
	/*
	hwndButton = CreateWindow(TEXT("button"), TEXT("Kwadrat 2 "),
	WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
	460, 360, 100, 30, hWnd, (HMENU)ID_RBUTTON2, GetModuleHandle(NULL), NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("Kwadrat 3 "),
	WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
	460, 360, 100, 30, hWnd, (HMENU)ID_RBUTTON3, GetModuleHandle(NULL), NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("Kwadrat 4 "),
	WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
	460, 360, 100, 30, hWnd, (HMENU)ID_RBUTTON4, GetModuleHandle(NULL), NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("Kwadrat 5 "),
	WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
	460, 360, 100, 30, hWnd, (HMENU)ID_RBUTTON5, GetModuleHandle(NULL), NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("Kwadrat 6 "),
	WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
	460, 360, 100, 30, hWnd, (HMENU)ID_RBUTTON6, GetModuleHandle(NULL), NULL);*/

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window (low priority)
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		// MENU & BUTTON messages
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_BUTTON1:
			if (Ay< Oy - 5 && By < Oy - 5)
				Alfa = Alfa - 5;
			if (Ax < Ox)
				Alfa = Alfa - 5;
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		case ID_BUTTON2:
			if (Ay< Oy - 5 && By < Oy - 5)
				Alfa = Alfa + 5;
			if (Ax > Ox)
				Alfa = Alfa + 5;
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		case ID_BUTTON3:
			if (By  < Oy - 5)
				Beta = Beta - 5;

			if (Bx < Ox && Bx != Ox)
				Beta = Beta - 5;
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		case ID_BUTTON4:
			if (By  < Oy - 5)
				Beta = Beta + 5;
			if (Bx > Ox && Bx != Ox)
				Beta = Beta + 5;
			repaintWindow(hWnd, hdc, ps, NULL);
			break;

		case ID_BUTTON5:
			if (numer_klockaX < 13)
				Zlapane = false;
			numer_klockaX += 2;
			numer_klockaY += 2;
			break;
		case ID_BUTTON6:
			if (numer_klockaX > 0)
				Zlapane = false;
			numer_klockaX -= 2;
			numer_klockaY -= 2;
			break;

		case ID_BUTTON7:
			if (Bx >= klocek_1[0] && Bx <= (klocek_1[0] + 30) && By >= klocek_1[1] && By <= (klocek_1[1] + 30))
			{
				Zlapane = true;

				klocek_1[0] = Bx;
				klocek_1[1] = By;
			}
			break;

		case ID_BUTTON8:
			//if (Bx == klocek_1[0] && By == klocek_1[1] )
			//{
			//puscilem = true;
			//klocek_1[0] = Bx;
			//klocek_1[1] = By;
			//	}
			Klocek(numer_klockaX, numer_klockaY);
			puscilem = true;
			//for (int i = Bx - 250; i < Bx - 220; i++) {
			//	warstwa[Bx] ++;
			//	}


			break;

		case ID_RBUTTON1:
			if (Zlap == true)
			{
				Zlapane = false;
				Zlap = false;
				numerek = 1;
			}
			else
				Zlap = true;
			Zlapane = false;
			break;
			/*
			case ID_RBUTTON2:
			if (Zlap == true)
			{
			Zlapane = false;
			Zlap = false;
			}
			else
			Zlap = true;
			break;

			case ID_RBUTTON3:
			if (Zlap == true)
			{
			Zlapane = false;
			Zlap = false;
			}
			else
			Zlap = true;
			break;

			case ID_RBUTTON4:
			if (Zlap == true)
			{
			Zlapane = false;
			Zlap = false;
			}
			else
			Zlap = true;
			break;

			case ID_RBUTTON5:
			if (Zlap == true)
			{
			Zlapane = false;
			Zlap = false;
			}
			else
			Zlap = true;
			break;

			case ID_RBUTTON6:
			if (Zlap == true)
			{
			Zlapane = false;
			Zlap = false;
			}
			else
			Zlap = true;
			break;*/
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here (not depend on timer, buttons)
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_TIMER:
		switch (wParam)
		{
		case TMR_1:
			//force window to repaint
			repaintWindow(hWnd, hdc, ps, &drawArea2);
			value++;
			break;
		}

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
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
