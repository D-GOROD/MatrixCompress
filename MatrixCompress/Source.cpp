#include <Windows.h>
#include "SoftwareDefinition.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	WNDCLASS SoftwareMainClass = NewWinsowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInstance, LoadIcon(NULL, IDI_WARNING), 
		L"MainWindowClass", SoftwareMainProcedure);

	if (!RegisterClassW(&SoftwareMainClass)) { return -1; }

	MSG SoftwareMainMassage = { 0 };
	CreateWindow(L"MainWindowClass", L"Test1", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 200, 200, 600, 300, NULL, NULL, NULL, NULL);
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
			MessageBoxA(hWnd, filename, "work", MB_OK);
			break;
		case OnMenuAction2:
			GetWindowRect(hWnd, &rect);
			width = rect.right - rect.left;
			height = rect.bottom - rect.top;
			stroka = "width = " + std::to_string(width) + " height = " + std::to_string(height);
			MessageBoxA(hWnd, stroka.c_str(), "WinsiwSize", MB_OK);
			break;
		case OnButtonClicked1:
			if (~VisibleFlag1) {
				ShowWindow(hSizeY, 1);
				ShowWindow(hSetVisibleY, 1);
				VisibleFlag1 =~VisibleFlag1;
			}
			else {
				ShowWindow(hSizeY, 0);
				ShowWindow(hSetVisibleY, 0);
				VisibleFlag1 = ~VisibleFlag1;
			}
			break;
		case OnButtonClicked2:
			if (~VisibleFlag2) {
				ShowWindow(hSaveFileEdit, 1);
				ShowWindow(hSaveFileStatic, 1);
				ShowWindow(hSaveFileButton, 1);
				VisibleFlag2 = ~VisibleFlag2;
			}
			else {
				ShowWindow(hSaveFileEdit, 0);
				ShowWindow(hSaveFileStatic, 0);
				ShowWindow(hSaveFileButton, 0);
				VisibleFlag2 = ~VisibleFlag2;
			}
			break;
		case OnButtonClicked3:
			GetSaveFileNameA(&ofn);
			break;
		case OnButtonClicked4:

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
		SetOpenFileParam(hWnd);
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
	AppendMenu(SubSubMenu, MF_STRING, OnMenuAction2, L"WinsiwSize");

	AppendMenu(SubMenu, MF_POPUP, (UINT_PTR)SubSubMenu, L"Action");
	AppendMenu(SubMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(SubMenu, MF_STRING, OnExitSofrware, L"Exit");

	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu, L"Menu");
	SetMenu(hWnd, RootMenu);
}

void MainWndAddWidgets(HWND hWnd)
{
	CreateWindowA("static", "Ширина:", WS_VISIBLE | WS_CHILD, 10, 10, 55, 30, hWnd, NULL, NULL, NULL);
	hSizeX = CreateWindowA("edit", "10", WS_VISIBLE | WS_CHILD, 70, 10, 50, 20, hWnd, NULL, NULL, NULL);

	CreateWindowA("button", "Матрица не квадратична", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 10, 40, 200, 20, hWnd, (HMENU)OnButtonClicked1, NULL, NULL);

	hSetVisibleY = CreateWindowA("static", "Высота:",  WS_CHILD, 10, 70, 55, 20, hWnd, NULL, NULL, NULL);
	hSizeY = CreateWindowA("edit", "10",  WS_CHILD, 70, 70, 50, 20, hWnd, NULL, NULL, NULL);

	CreateWindowA("static", "D_MIN:", WS_VISIBLE | WS_CHILD, 10, 100, 55, 20, hWnd, NULL, NULL, NULL);
	hDMin = CreateWindowA("edit", "10", WS_VISIBLE | WS_CHILD, 70, 100, 20, 20, hWnd, NULL, NULL, NULL);

	CreateWindowA("button", "Сохранить в файл?", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 10, 130, 200, 20, hWnd, (HMENU)OnButtonClicked2, NULL, NULL);

	hSaveFileStatic = CreateWindowA("static", "Размер буфера", WS_CHILD, 10, 160, 55, 20, hWnd, NULL, NULL, NULL);
	hSaveFileEdit = CreateWindowA("edit", "100", WS_CHILD, 70, 160, 50, 20, hWnd, NULL, NULL, NULL);

	hSaveFileButton = CreateWindowA("button", "Сохранить", WS_CHILD, 150, 160, 100, 20, hWnd, (HMENU)OnButtonClicked4, NULL, NULL);

	CreateWindowA("button", "Расчитать", WS_VISIBLE | WS_CHILD, 10, 190, 100, 30, hWnd, NULL, NULL, NULL);

}

void SaveData(LPCSTR path)
{
	HANDLE FileToSave = CreateFileA(
		path,
		GENERIC_WRITE,
		NULL,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

}

void SetOpenFileParam(HWND hWnd)
{
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = filename;
	ofn.nMaxFile = sizeof(filename);
	ofn.lpstrFilter = ".txt";
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
}

void MainProcedure(HWND hWnd, int SIZE_X, int SIZE_Y, int LENGHT_RESULT_VECTOR, float D_MIN)
{

}