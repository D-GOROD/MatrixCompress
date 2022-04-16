#pragma once

#define OnMenuAction1 1
#define OnMenuAction2 2
#define OnMenuAction3 3
#define OnExitSofrware 4
#define OnButtonClicked1 5
#define OnButtonClicked2 6

HWND hEditControl;
LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASS NewWinsowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInstance, HICON Icon, LPCWSTR Name, WNDPROC Procedure);
void MainWndAddMenus(HWND hWnd);
void MainWndAddWidgets(HWND hWnd);