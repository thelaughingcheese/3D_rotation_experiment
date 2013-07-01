#include "common.h"
#include "consoleLoop.h"
#include "mainLoop.h"

unsigned long buffer1[480000];
unsigned long buffer2[480000];
unsigned long *buffer_f;
unsigned long *buffer_b;

HWND *g_hwnd;

bool mouseButton[3] = {false,false,false};
int mousePos[2] = {0,0};
bool keyboard[0xff] = {};

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	switch(msg){
		case WM_CLOSE:{	//user clicks close button, has default but we specify it anyways
			DestroyWindow(hwnd);
			break;
		}
		case WM_DESTROY:{	//window is destroyed
			PostQuitMessage(0);
			break;
		}
		case WM_LBUTTONDOWN:{
			mouseButton[0] = true;
			break;
		}
		case WM_LBUTTONUP:{
			mouseButton[0] = false;
			break;
		}
		case WM_MBUTTONDOWN:{
			mouseButton[1] = true;
			break;
		}
		case WM_MBUTTONUP:{
			mouseButton[1] = false;
			break;
		}
		case WM_RBUTTONDOWN:{
			mouseButton[2] = true;
			break;
		}
		case WM_RBUTTONUP:{
			mouseButton[2] = false;
			break;
		}
		case WM_MOUSEMOVE:{
			mousePos[0] = LOWORD(lParam);
			mousePos[1] = 600 - HIWORD(lParam);
			break;
		}
		case WM_KEYDOWN:{
			keyboard[wParam] = true;
			break;
		}
		case WM_KEYUP:{
			keyboard[wParam] = false;
			break;
		}
		case WM_PAINT:{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			HDC hdcMem = CreateCompatibleDC(hdc);

			HBITMAP hbuffer;

			hbuffer = CreateBitmap(800,600,1,32,&buffer_f);
			//OutputDebugString("derp");

			HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hbuffer);

			BitBlt(hdc, 0, 0, 800,600, hdcMem,0,0,SRCCOPY);

			SelectObject(hdcMem, hbmOld);
			DeleteDC(hdcMem);
			DeleteObject(hbuffer);
			EndPaint(hwnd, &ps);

			break;
		}
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);		//if we don't handle the messages, let windows perform the default routines
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	/*----------
	hInstance - handle for the instance of the process
	hPrevInstance - previous instance, obsolete, used in older versions of windows, still needed for legacy
	lpCmdLine - string of parameters specified when run, usually set through shortcut
	nShowCmd - whether or not to start program with window showing or minimized
	----------*/

	WNDCLASSEX wc;		//creates a preset window configuration that can be reused later on to create similar type windows
	HWND hwnd;				//creates a handle for the window object
	MSG msg;					//container for windows messages
	const char g_szClassName[] = "myWindowClass";	//name used to identify the window class we will be creating

	//specifies properties of the window to create
	wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;		//window class identifier here
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

	//registers the window class so that we can use it when actually creating a window(s)
    if(!RegisterClassEx(&wc)){
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

	//re-adjust so you get the canvase size we want
	RECT rc = {0,0,800,600};

	AdjustWindowRectEx(&rc,WS_OVERLAPPEDWINDOW,false,WS_OVERLAPPEDWINDOW);

	//creates the window
	hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,			//window class identifier here
        "The title of my window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, rc.right-rc.left+6, rc.bottom-rc.top+6,
        NULL, NULL, hInstance, NULL);

	if(hwnd == NULL){
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

	g_hwnd = &hwnd;
	buffer_f = buffer1;
	buffer_b = buffer2;

	ShowWindow(hwnd, nCmdShow);		//specifies how the window should be shown
	UpdateWindow(hwnd);						//tells the window to update and paint any changes to window area

	AllocConsole();		//allocates a new console process and attaches it to this one
	freopen("CONIN$","rb", stdin);	//redirects cout stream to the console so it displays things
	freopen("CONOUT$","wb", stdout);

	_beginthread(consoleLoop,0,0);
	_beginthread(mainLoop,0,0);

	while(true){
		int msgStatus = PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE);
		if(msgStatus > 0){
			if(GetMessage(&msg, NULL, 0, 0) > 0){
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else{
				break;
			}
		}
		else{
			//stuff
			InvalidateRect(*g_hwnd, NULL, false);
		}
	}
    return msg.wParam;
}