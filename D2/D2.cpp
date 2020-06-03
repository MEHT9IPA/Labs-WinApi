// D2.cpp : Определяет точку входа для приложения.
//
#include "framework.h"
#include "D2.h"
#define RGB(r, g, b) ((COLORREF)(((BYTE)(r) | ((WORD)(g) << 8)) | ((DWORD)(BYTE)(b)) << 16)))

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HDC hdc;
// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Разместите код здесь.

	// Инициализация глобальных строк
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_D2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_D2));

	MSG msg;

	// Цикл основного сообщения:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_D2));
	wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_D2);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

	HWND hWnd = CreateWindowW(szWindowClass, _TEXT("D2"), WS_OVERLAPPEDWINDOW,
		650, 250, 600, 600, nullptr, nullptr, hInstance, nullptr);

	hdc = GetDC(hWnd);
	if (!hWnd)
	{
		return FALSE;
	}
	HMENU WINAPI a;
	HMENU Menu = CreateMenu();
	HMENU hPopupMenu1 = CreatePopupMenu();
	AppendMenu(Menu, MF_STRING | MF_POPUP, (UINT)hPopupMenu1, L"Включить");
	{
		AppendMenu(hPopupMenu1, MF_STRING, 100, L"Курсор");
		AppendMenu(hPopupMenu1, MF_STRING, 200, L"Круг");
	}
	SetMenu(hWnd, Menu);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//

/*
xPos = LOWORD(lParam);
		yPos = HIWORD(lParam);
		hdc = GetDC(hWnd);
		nSize = wsprintf(szBuf, TEXT("(%d, %d)"), xPos, yPos);
		TextOut(hdc, 0, 0, szBuf, nSize);
		ReleaseDC(hWnd, hdc);
*/
HWND static1;
POINT coords;
static HWND Static1;
static HWND Static2;
HANDLE hThread1;
HANDLE hThread2;
DWORD WINAPI Thread1(LPVOID th1);
DWORD WINAPI Thread2(LPVOID th2);
BOOL thread1_working = false;
BOOL thread2_working = false;
HWND hWnd;
LPARAM lParam;
int tSize1, tSize2;
static PAINTSTRUCT ps;



DWORD WINAPI Thread1(LPVOID th1)
{
	RECT rect3 = { 0, 0, 200 ,80 };
	wchar_t t1[20];
	wchar_t t2[20];
	int x, y;
	while (true)
	{
		//TextOut(hdc, 50, 50, TEXT("DFDFD"), 5)
		GetCursorPos(&coords);
		x = coords.x;
		y = coords.y;
		//int counter1 = x;
		/*for (int i = 0; i < 4; i++)
		{
			if ((counter1 / 10) > 0)
			{
				xc++;
				counter1 = counter1 / 10;
			}
		}*/

		tSize1 = wsprintf(t1, L"Координата X: %d", x);
		tSize2 = wsprintf(t2, L"Координата Y: %d", y);
		//_itoa_s(test1, t1, 5, 10);
		//MultiByteToWideChar(CP_ACP, 0, t1, -1, t2, 10);
		//SetWindowText(Static1, t2);
		hdc = GetDC(HWND(th1));
		SetTextColor(hdc, RGB(rand() % 155, rand() % 155, rand() % 155);
		TextOut(hdc, 20, 20, t1, tSize1);//xc);
		TextOut(hdc, 20, 40, t2, tSize2);
		ReleaseDC(HWND(th1), hdc);
		Sleep(200);
		InvalidateRect(HWND(th1), &rect3, TRUE);
		UpdateWindow(HWND(th1));

		//Sleep(200);
	}
	return 0;
}
DWORD WINAPI Thread2(LPVOID th2)
{
	RECT rect3 = { 110, 140, 460, 490 };
	RECT rectl = { 110, 140, 285, 490 };
	RECT rectr = { 285, 140, 460, 490 };
	InvalidateRect(HWND(th2), &rect3, TRUE);
	UpdateWindow(HWND(th2));
	Sleep(1000);
	while (true)
	{
		hdc = GetDC(HWND(th2));
		FillRect(hdc, &rectl, (HBRUSH)RGB(255, 255, 255);
		ReleaseDC(HWND(th2), hdc);
		Sleep(1000);
		InvalidateRect(HWND(th2), &rect3, TRUE);
		UpdateWindow(HWND(th2));
		hdc = GetDC(HWND(th2));
		FillRect(hdc, &rectr, (HBRUSH)RGB(255, 255, 255);
		ReleaseDC(HWND(th2), hdc);
		Sleep(1000);
		InvalidateRect(HWND(th2), &rect3, TRUE);
		UpdateWindow(HWND(th2));
	}
	return 0;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{


	switch (message)
	{
	case WM_CREATE:
	{
		break;
	}
	case WM_LBUTTONDOWN:
	{

		/*RECT rect3 = { 0, 0, 500 ,500 };
		InvalidateRect(hWnd, &rect3, TRUE);
		UpdateWindow(hWnd);
		hdc = GetDC(hWnd);
		char t1[5];
		wchar_t t2[10];
		GetCursorPos(&coords);
		int test1 = coords.x;
		int test2 = coords.y;
		int xc = 1;
		int yc = 0;
		int counter1 = test1;
		for (int i = 0; i < 4; i++)
		{
			if ((counter1 / 10) > 0)
			{
				xc++;
				counter1 = counter1 / 10;
			}
		}
		//nSize = wsprintf(t2, TEXT("(%d, %d)"), test1, test2);
		_itoa_s(test1, t1, 5, 10);
		MultiByteToWideChar(CP_ACP, 0, t1, -1, t2, 10);
		//SetWindowText(Static1, t2);
		SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255);
		//TextOut(hdc, 100, 100, TEXT("    "), 5);
		TextOut(hdc, 50, 50, t2, xc);
		ReleaseDC(hWnd, hdc);
		*/

		break;
	}

	case WM_PAINT:
	{
		hdc = GetDC(hWnd);
		hdc = BeginPaint(hWnd, &ps);
		if (thread2_working)
		{
			HBRUSH hbr = CreateSolidBrush(RGB(0, 0, 0);           //285;315
			HPEN hpn = CreatePen(PS_NULL, 0, RGB(255, 0, 0);
			int color_c = 0;
			SelectObject(hdc, hbr);
			SelectObject(hdc, hpn);
			for (int i = 150; i > 0; i = i - 10)
			{
				hbr = CreateSolidBrush(RGB(color_c, color_c, color_c);
				Ellipse(hdc, 285 - i, 315 - i, 285 + i, 315 + i);
				color_c = color_c + 15;
				SelectObject(hdc, hbr);
			}
			
		}

		EndPaint(hWnd, &ps);
		ReleaseDC(hWnd, hdc);
		break;
	}

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case 100: //курсор
		{
			if (!thread1_working)
			{
				hThread1 = CreateThread(NULL, 0, Thread1, hWnd, 0, NULL);
			}
			thread1_working = true;
			break;

		}
		case 200: //круг
		{
			if (!thread2_working)
			{
				hThread2 = CreateThread(NULL, 0, Thread2, hWnd, 0, NULL);
			}
			thread2_working = true;
			break;
		}
		}
		break;
	}

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

/* Обработчик сообщений для окна "О программе".
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
}*/