// A1.cpp : Определяет точку входа для приложения.
//
#include "framework.h"
#include "A1.h"

#define MAX_LOADSTRING 100
#define RGB(r, g, b) ((COLORREF)(((BYTE)(r) | ((WORD)(g) << 8)) | ((DWORD)(BYTE)(b)) << 16)))
// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

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
	LoadStringW(hInstance, IDC_A1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_A1));

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_A1));
	wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);
	wcex.hbrBackground = CreateSolidBrush(RGB(66, 170, 255);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_A1);
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

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 700, 700, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

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
class PAINT_NODE
{
private:
	RECT element;
	int Color[3] = { 0, 0, 0 };
	PAINT_NODE* next;
public:
	PAINT_NODE()
	{
		next = NULL;
		element = { 0,0,0,0 };
	}
	void Set_element(RECT A)
	{
		element = A;
	}
	void Set_color(int R, int G, int B)
	{
		Color[0] = R;
		Color[1] = G;
		Color[2] = B;
	}
	void Set_next(PAINT_NODE* A)
	{
		next = A;
	}
	RECT Get_element()
	{
		return element;
	}
	int Get_red()
	{
		return Color[0];
	}
	int Get_blue()
	{
		return Color[2];
	}
	int Get_green()
	{
		return Color[1];
	}
	PAINT_NODE* Get_next()
	{
		return next;
	}
};

class PAINT_STACK
{
private:
	PAINT_NODE* top;
public:
	PAINT_STACK()
	{
		top = NULL;
	}
	bool Is_empty()
	{
		if (top == NULL)
		{
			return true;
		}
		return false;
	}
	void push(RECT A, int R, int G, int B)
	{
		PAINT_NODE* new_slot = new PAINT_NODE;
		(*new_slot).Set_next(top);
		(*new_slot).Set_element(A);
		(*new_slot).Set_color(R, G, B);
		top = new_slot;
	}
	void pop()
	{
		PAINT_NODE* temp = top;
		top = (*top).Get_next();
		delete temp;
	}
	PAINT_STACK(const PAINT_STACK& nStack)
	{
		top = NULL;
		PAINT_NODE* nSN = nStack.top;
		while (nSN != NULL)
		{
			PAINT_NODE* temp = new PAINT_NODE;
			(*temp).Set_next(top);
			(*temp).Set_element(nSN->Get_element());
			(*temp).Set_color(nSN->Get_red(), nSN->Get_green(), nSN->Get_blue());
			top = temp;
			temp = NULL;
			delete temp;
			nSN = nSN->Get_next();
		}
		//	this->push(temp->Get_element(), temp->Get_red(), temp->Get_green(), temp->Get_blue());
		//	temp->Get_next();
	}
		//while (temp != NULL)
		//{
		//	(*temp).Set_next(top);
		//	(*temp).Set_element(nStack.top->Get_element());
		//	(*temp).Set_color(nStack.top->Get_red(), nStack.top->Get_green(), nStack.top->Get_blue());
		//	top = temp;
		//	temp = temp->Get_next();
		//}
	RECT Get_top_element()
	{
		return (*top).Get_element();
	}
	~PAINT_STACK()
	{
		while (!Is_empty())
		{
			pop();
		}
	}
	void Do_paint(HDC hdc)
	{
		PAINT_STACK P(*this);
		PAINT_NODE* temp = P.top;
		while (temp != NULL)
		{
			FillRect(hdc, &temp->Get_element(), CreateSolidBrush(RGB(temp->Get_red(), temp->Get_green(), temp->Get_blue()));
			temp = temp->Get_next();
		}
	}
};

PAINT_STACK S;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	RECT custom;
	HDC hdc;
	RECT screen;
	GetWindowRect(hWnd, &screen);
	int x = screen.right - screen.left;
	int y = screen.bottom - screen.top;

	int x1 = rand() % x;
	int y1 = rand() % y;
	int x2 = rand() % x;
	int y2 = rand() % y;
	int r = rand() % 255;
	int g = rand() % 255;
	int b = rand() % 255;
	switch (message)
	{
	case WM_PAINT:
	{
	//	RECT rectangle = { x1, y1, x2, y2 };

		HDC hdc = BeginPaint(hWnd, &ps);

		//REDRAWING SEQUENCE
		S.Do_paint(hdc);
	//	RECT E = S.Get_top_element();
	//	while (!S.Is_empty())
	//	{
	//		FillRect(hdc, &S.Get_top_element(), CreateSolidBrush(RGB(5, 5, 5));
	//		S.pop();
	//	}
		EndPaint(hWnd, &ps);

	//	MessageBox(hWnd, TEXT("!!!!!"), TEXT("BRUH"), MB_OK);
	//	GetClientRect(hWnd, &custom);
	//	FillRect(hdc, &rectangle, CreateSolidBrush(RGB(r, g, b));
		break;
	}
	case WM_LBUTTONDOWN:
	{
		hdc = GetDC(hWnd);
		RECT rectangle = { x1, y1, x2, y2 };
		S.push(rectangle,r,g,b);                          //!!!!!
	//	GetClientRect(hWnd, &custom);
		FillRect(hdc, &rectangle, CreateSolidBrush(RGB(r, g, b));
		ReleaseDC(hWnd, hdc);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		MessageBox(hWnd, TEXT("Нажата правая кнопка мыши"), TEXT("!!!"), MB_OK);
	//	Sleep(30000);
		ShowWindow(hWnd, SW_MINIMIZE);
		while (!S.Is_empty())
		{
			S.pop();
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