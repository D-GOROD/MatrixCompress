#include <Windows.h>
#include "SoftwareDefinition.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	WNDCLASS SoftwareMainClass = NewWinsowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInstance, LoadIcon(NULL, IDI_WARNING), 
		L"MainWindowClass", SoftwareMainProcedure);

	if (!RegisterClassW(&SoftwareMainClass)) { return -1; }

	MSG SoftwareMainMassage = { 0 };
	CreateWindow(L"MainWindowClass", L"Test1", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 250, NULL, NULL, NULL, NULL);
	while (GetMessage(&SoftwareMainMassage, NULL, NULL, NULL))
	{
		TranslateMessage(&SoftwareMainMassage);
		DispatchMessage(&SoftwareMainMassage);
	}
	return 0;
}

WNDCLASS NewWinsowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInstance, HICON Icon, LPCWSTR Name, WNDPROC Procedure)
{
	WNDCLASS NWC = { 0 };
	NWC.hCursor = Cursor;
	NWC.hIcon = Icon;
	NWC.hInstance = hInstance;
	NWC.lpszClassName = Name;
	NWC.hbrBackground = BGColor;
	NWC.lpfnWndProc = Procedure;
	return NWC;
}

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_COMMAND:
		switch (wp)
		{
		case OnMenuAction1:
			MessageBoxA(hWnd, "Menu 1 was clicked", "work", MB_OK);
			break;
		case OnMenuAction2:
			MessageBoxA(hWnd, "Menu 2 was clicked", "work", MB_OK);
			break;
		case OnButtonClicked1:
			MessageBoxA(hWnd, "Button was clicked", "work", MB_OK);
			break;
		case OnButtonClicked2:
			SetWindowTextA(hEditControl, "");
			break;
		case OnExitSofrware:
			PostQuitMessage(0);
			break;
		default:
			break;
		}
		break;
	case WM_CREATE:
		MainWndAddMenus(hWnd);
		MainWndAddWidgets(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, msg, wp, lp);
	}
}

void MainWndAddMenus(HWND hWnd)
{
	HMENU RootMenu = CreateMenu();
	HMENU SubMenu = CreateMenu();
	HMENU SubSubMenu = CreateMenu();
	AppendMenu(SubSubMenu, MF_STRING, OnMenuAction1, L"menu 1");
	AppendMenu(SubSubMenu, MF_STRING, OnMenuAction2, L"menu 2");

	AppendMenu(SubMenu, MF_POPUP, (UINT_PTR)SubSubMenu, L"Action");
	AppendMenu(SubMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(SubMenu, MF_STRING, OnExitSofrware, L"Exit");

	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu, L"Menu");
	SetMenu(hWnd, RootMenu);
}

void MainWndAddWidgets(HWND hWnd)
{
	CreateWindowA("static", "Test static WND", WS_VISIBLE | WS_CHILD | ES_CENTER, 0, 0, 490, 20, hWnd, NULL, NULL, NULL);
	hEditControl = CreateWindowA("edit", "Test edit WND", WS_VISIBLE | WS_CHILD | ES_CENTER, 0, 50, 490, 20, hWnd, NULL, NULL, NULL);
	CreateWindowA("button", "Test button WND", WS_VISIBLE | WS_CHILD, 0, 100, 150, 30, hWnd, (HMENU)OnButtonClicked1, NULL, NULL);
	CreateWindowA("button", "Clear edit box", WS_VISIBLE | WS_CHILD, 200, 100, 150, 30, hWnd, (HMENU)OnButtonClicked2, NULL, NULL);
}