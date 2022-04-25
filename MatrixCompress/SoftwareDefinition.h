#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include <clocale>
#include <Windows.h>
#include <algorithm>
#include <fstream>
#include "Matrix.h"

#define OnMenuAction1 1
#define OnMenuAction2 2
#define OnMenuAction3 3
#define OnExitSofrware 4
#define OnButtonClicked1 5
#define OnButtonClicked2 6
#define OnButtonClicked3 7
#define OnButtonClicked4 8

char filename[260];
OPENFILENAMEA ofn;

std::string stroka;
RECT rect;
LONG width;
LONG height;

HWND hSizeX;
HWND hSizeY;
HWND hDMin;

HWND hSetVisibleY;
HWND hSaveFileStatic;
HWND hSaveFileEdit;
HWND hSaveFileButton;

BOOL VisibleFlag1 = false;
BOOL VisibleFlag2 = false;

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASS NewWinsowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInstance, HICON Icon, LPCWSTR Name, WNDPROC Procedure);
void MainWndAddMenus(HWND hWnd);
void MainWndAddWidgets(HWND hWnd);
void SaveData(LPCSTR path);
void SetOpenFileParam(HWND hWnd);
void MainProcedure(HWND hWnd, int SIZE_X, int SIZE_Y, int LENGHT_RESULT_VECTOR, float D_MIN);
