#include <windows.h>
#include <stdio.h>
#include<cstdlib>

HWND textF ,button_plus,button_minus,button_multiply,button_divide,infonumber_one,infonumber_two;
/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_CREATE:
			textF = CreateWindow("STATIC","Please input two numbers",WS_VISIBLE | WS_CHILD | WS_BORDER,25, 10,180,25,hwnd ,NULL,NULL,NULL);
			button_plus = CreateWindow("BUTTON","+",WS_VISIBLE | WS_CHILD | WS_BORDER,25, 120,25,25,hwnd ,(HMENU) 1,NULL,NULL);
			button_minus = CreateWindow("BUTTON","-",WS_VISIBLE | WS_CHILD | WS_BORDER,75, 120,25,25,hwnd ,(HMENU) 2,NULL,NULL);
			button_multiply = CreateWindow("BUTTON","*",WS_VISIBLE | WS_CHILD | WS_BORDER,125, 120,25,25,hwnd ,(HMENU) 3,NULL,NULL);
			button_divide = CreateWindow("BUTTON","/",WS_VISIBLE | WS_CHILD | WS_BORDER,175, 120,25,25,hwnd ,(HMENU) 4,NULL,NULL);
			infonumber_one = CreateWindow("EDIT","",WS_VISIBLE | WS_CHILD | WS_BORDER,25, 50,180,25,hwnd ,NULL,NULL,NULL);
			infonumber_two = CreateWindow("EDIT","",WS_VISIBLE | WS_CHILD | WS_BORDER,25, 80,180,25,hwnd ,NULL,NULL,NULL);
			break;

		case WM_COMMAND:
			switch (LOWORD(wParam)){
				char number_one[20],number_two[20],t[100];
				double x,y,z;
				case 1:
					x=0,y=0,z=0;
					GetWindowText(infonumber_one,number_one,20);
					GetWindowText(infonumber_two,number_two,20);
					x = atof(number_one);
					y = atof(number_two);
					z = x+y;
					sprintf(t, "%f", z);
					::MessageBeep(MB_ICONERROR);
					::MessageBox (hwnd, t , "Result",MB_OK);
					break;
				case 2:
					x=0,y=0,z=0;
					GetWindowText(infonumber_one,number_one,20);
					GetWindowText(infonumber_two,number_two,20);
					x = atof(number_one);
					y = atof(number_two);
					z = x-y;
					sprintf(t, "%f", z);
					::MessageBeep(MB_ICONERROR);
					::MessageBox (hwnd, t , "Result",MB_OK);
					break;
				case 3:
					x=0,y=0,z=0;
					GetWindowText(infonumber_one,number_one,20);
					GetWindowText(infonumber_two,number_two,20);
					/*std::cout << number_one << std::endl;
					std::cout << number_two << std::endl;*/
					x = atof(number_one);
					y = atof(number_two);
					/*std::cout << x << std::endl;
					std::cout << y << std::endl;*/
					z = x*y;
					sprintf(t, "%f", z);
					::MessageBeep(MB_ICONERROR);
					::MessageBox (hwnd, t , "Result",MB_OK);
					break;
				case 4:
					x=0,y=0,z=0;
					GetWindowText(infonumber_one,number_one,20);
					GetWindowText(infonumber_two,number_two,20);
					x = atof(number_one);
					y = atof(number_two);
					z = x/y;
					sprintf(t, "%f", z);
					::MessageBeep(MB_ICONERROR);
					::MessageBox (hwnd, t , "Result",MB_OK);
					break;
				
			}


		break;
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+22);
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
