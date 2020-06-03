// C2.cpp : Определяет точку входа для приложения.
//
#include "framework.h"
#include "C2.h"
#include <iostream>
#include <fstream>
#include <comdef.h>

#define MAX_LOADSTRING 100
#define RGB(r, g, b) ((COLORREF)(((BYTE)(r) | ((WORD)(g) << 8)) | ((DWORD)(BYTE)(b)) << 16)))
// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
static HDC hdc;



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
	LoadStringW(hInstance, IDC_C2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_C2));

	MSG msg;

	// Цикл основного сообщения:
	// Цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;


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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_C2));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(255, 255, 255);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_C2);
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

	HWND hWnd = CreateWindowW(szWindowClass, _T("База данных"), WS_OVERLAPPEDWINDOW,
		700, 250, 500, 600, nullptr, nullptr, hInstance, nullptr);

	hdc = GetDC(hWnd);

	if (!hWnd)
	{
		return FALSE;
	}
	HMENU WINAPI a;
	HMENU Menu = CreateMenu();
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
static char M[25];
static wchar_t L[25];
static int C;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	static HWND hWndStatic;
	static HWND hWndEdit;
	static HWND hWndList;
	static HWND hWndRedact;
	static HWND hWndDelete;
	static HWND hWndAdd;
	static HWND hWndSave;


	//MultiByteToWideChar(CP_ACP, 0, M, -1, L, 5);

	switch (message)
	{
	case WM_COMMAND:
	{
		C = HIWORD(wParam);
		switch (C)
		{
		//case LBN_DBLCLK:
		//	C = SendMessage(hWndList, LB_GETCURSEL, 0, 0);
		//	SendMessage(hWndList, LB_GETTEXT, C, (LPARAM)L);
		//	//	ShowWindow(hWndStatic2, SW_HIDE);
		//	break;

		case LBN_SELCHANGE:
			C = SendMessage(hWndList, LB_GETCURSEL, 0, 0);
			SendMessage(hWndList, LB_GETTEXT, C, (LPARAM)L);
			SetWindowText(hWndEdit, L);
			EnableWindow(hWndRedact, 1);
			EnableWindow(hWndDelete, 1);
			EnableWindow(hWndAdd, 0);
			break;

		case BN_CLICKED:
			C = SendMessage(hWndList, LB_GETCURSEL, 0, 0);
			int R;

			if (lParam == (LPARAM)hWndRedact)
			{
				GetWindowText(hWndEdit, L, 25);
				R = SendMessage(hWndList, LB_FINDSTRINGEXACT, 0, (LPARAM)L);
				if (R == -1)
				{
					if (L[0] != NULL)
					{
						SendMessage(hWndList, LB_DELETESTRING, C, 0L);
						SendMessage(hWndList, LB_INSERTSTRING, C, (LPARAM)L);
					}
					else
					{
						MessageBox(hWnd, TEXT("Пустой ввод!"), TEXT("!!!"), MB_OK);
						SendMessage(hWndList, LB_SETCURSEL, -1, 0);
					}
				}
				else
				{
					MessageBox(hWnd, TEXT("Такой элемент уже есть!"), TEXT("!!!"), MB_OK);
					SendMessage(hWndList, LB_SETCURSEL, -1, 0);
				}
			}
			else if (lParam == (LPARAM)hWndAdd)
			{
				GetWindowText(hWndEdit, L, 25);
				R = SendMessage(hWndList, LB_FINDSTRINGEXACT, 0, (LPARAM)L);
				if (L[0] != NULL)
				{
					if (R == -1)
					{
						SendMessage(hWndList, LB_ADDSTRING, 0, (LPARAM)L);
					}
					else
					{
						MessageBox(hWnd, TEXT("Такой элемент уже есть!"), TEXT("!!!"), MB_OK);
					}
				}
				else
				{
					MessageBox(hWnd, TEXT("Пустой ввод!"), TEXT("!!!"), MB_OK);
				}
			}
			else if (lParam == (LPARAM)hWndDelete)
			{
				SendMessage(hWndList, LB_DELETESTRING, C, 0L);
			}
			else if (lParam == (LPARAM)hWndSave)
			{
				R = SendMessage(hWndList, LB_GETCOUNT, 0, 0);
				int length;
				std::filebuf fb;
				fb.open("D:\\bd.txt", std::ios::out);
				std::ostream thr(&fb);
				for (int i = 0; i < R; i++)
				{
					length = SendMessage(hWndList, LB_GETTEXT, i, (LPARAM)L);
					_bstr_t b = (L);
					const char *M = b;
					thr.write(M, length);
					if (i != R - 1)
					{
						thr << std::endl;
					}
				}
				fb.close();
			}

			EnableWindow(hWndRedact, 0);
			EnableWindow(hWndDelete, 0);
			EnableWindow(hWndAdd, 1);
			SetWindowText(hWndEdit, _T(""));
			break;
		}
	}

	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	}

	case WM_CREATE:
	{
		hWndStatic = CreateWindow(
			_T("static"),
			_T("Список"),
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT,
			10,
			10,
			70,
			20,
			hWnd,
			0,
			NULL,
			NULL);

		hWndList = CreateWindow(
			_T("listbox"),
			NULL,
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | LBS_NOTIFY,
			10,
			30,
			200,
			500,
			hWnd,
			0,
			NULL,
			NULL);

		hWndEdit = CreateWindow(
			_T("edit"),
			_T(""),
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT,
			270,
			30,
			200,
			25,
			hWnd,
			0,
			NULL,
			NULL);

		hWndRedact = CreateWindow(
			_T("button"),
			_T("Редактировать"),
			WS_DISABLED | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER,
			270,
			60,
			120,
			25,
			hWnd,
			0,
			NULL,
			NULL);

		hWndDelete = CreateWindow(
			_T("button"),
			_T("Удалить"),
			WS_DISABLED | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER,
			270,
			90,
			120,
			25,
			hWnd,
			0,
			NULL,
			NULL);

		hWndAdd = CreateWindow(
			_T("button"),
			_T("Добавить"),
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER,
			270,
			120,
			120,
			25,
			hWnd,
			0,
			NULL,
			NULL);

		hWndSave = CreateWindow(
			_T("button"),
			_T("Сохранить"),
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER,
			270,
			200,
			120,
			25,
			hWnd,
			0,
			NULL,
			NULL);

		std::ifstream thr;
		thr.open("D:\\bd.txt");
		if (!thr.is_open())
		{
			MessageBox(hWnd, TEXT("Файл базы не найден!"), TEXT("!!!"), MB_OK);
			SendMessage(hWnd, WM_DESTROY, wParam, lParam);
		}
		while (thr.getline(M, 25))
		{
			MultiByteToWideChar(CP_ACP, 0, M, -1, L, 25);
			SendMessage(hWndList, LB_ADDSTRING, 0, (LPARAM)L);
		}
		thr.close();
	//	SendMessage(hWndList, LB_ADDSTRING, 0, (LPARAM)_T("Аникин Филипп"));
	//	SendMessage(hWndList, LB_ADDSTRING, 0, (LPARAM)_T("Абдуллаев Тимур"));
	//	SendMessage(hWndList, LB_ADDSTRING, 0, (LPARAM)_T("Якубов Артём"));
		break;
	}
	/*case WM_LBUTTONDOWN:
	{
		break;
	}*/
	case WM_RBUTTONDOWN:
	{
		SendMessage(hWndList, LB_SETCURSEL, -1, 0);
		EnableWindow(hWndRedact, 0);
		EnableWindow(hWndDelete, 0);
		EnableWindow(hWndAdd, 1);
		SetWindowText(hWndEdit, _T(""));
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