#pragma once
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include <clocale>
#include <Windows.h>
#include <algorithm>
#include <fstream>
#include "Matrix.h"

#define Help 1
#define Save 2
//#define OnMenuAction3 3
#define OnExitSofrware 4
#define IsMatrixQuadratic 5
#define SaveToFileCheckbox 6
#define SaveToFile 7
#define Submit 8
#define GetXIndex 9
#define GetYIndex 10
#define GetDIndex 11
#define GetLenghtResultIndex 12
#define SetProcent 13
//#define ResultEdit 13

HANDLE CompressThread;
char filename[260];
char buff[255];
OPENFILENAMEA ofn;

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
HWND ResultEdit;
HWND Test;
HWND Procent;
HWND hSubmit;

BOOL VisibleFlag1 = false;
BOOL VisibleFlag2 = false;
BOOL IsWork = false;

int SIZE_X;
int SIZE_Y;
int LENGHT_RESULT_VECTOR = 0;
wchar_t D_MIN_CHAR[255] = {0};
float D_MIN;

vector<Matrix> Result;

string help = "Данное программное обеспечение служит для поиска оптимального решения задачи расположения каналов управления позиционного гидропривода\n\nВ полях \"Ширина\" и \"Высота\" указываются размеры исходной матрцы\nВ поле \"D_MIN\" устанавливается нижняя граница коэффициента D\nВ поле \"Размер\" устанавливается длина результирующего вектора.";

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASS NewWinsowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInstance, HICON Icon, LPCWSTR Name, WNDPROC Procedure);
void MainWndAddMenus(HWND hWnd);
void MainWndAddWidgets(HWND hWnd);
void SetOpenFileParam(HWND hWnd);
DWORD WINAPI MainProcedure(LPVOID lpParameter);
void GetValue(HWND hWnd);
bool EraseFoo(vector<int>& vec, int a);
void PrintProcent(int procent);