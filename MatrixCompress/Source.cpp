#include "SoftwareDefinition.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	WNDCLASS SoftwareMainClass = NewWinsowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInstance, LoadIcon(NULL, IDI_WARNING), 
		L"MainWindowClass", SoftwareMainProcedure);

	if (!RegisterClassW(&SoftwareMainClass)) { return -1; }

	MSG SoftwareMainMassage = { 0 };
	CreateWindow(L"MainWindowClass", L"MatrixCompress", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 50, 50, 600, 300, NULL, NULL, NULL, NULL);
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
		case Help:
		{
			break;
		}
		case Save:
		{
			GetSaveFileNameA(&ofn);
			ofstream fout;
			fout.open(filename);
			Result[0].print_matrix_to_file(fout);
			fout.close();
			break;
		}
		case IsMatrixQuadratic:
		{
			if (~VisibleFlag1) {
				ShowWindow(hSizeY, 1);
				ShowWindow(hSetVisibleY, 1);
				VisibleFlag1 = ~VisibleFlag1;
			}
			else {
				ShowWindow(hSizeY, 0);
				ShowWindow(hSetVisibleY, 0);
				VisibleFlag1 = ~VisibleFlag1;
			}
			break;
		}
		case SaveToFileCheckbox:
		{
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
		}
		case SaveToFile:
		{
			GetSaveFileNameA(&ofn);
			break;
		}
		case Submit:
		{
			ShowWindow(Procent, 1);
			GetValue(hWnd);
			CompressThread = CreateThread(NULL, 0, MainProcedure, NULL, 0, NULL);
			break;
		}
		case OnExitSofrware:
		{
			PostQuitMessage(0);
			break;
		}
		default: break;
		}
		break;
	case WM_CREATE:
	{
		MainWndAddMenus(hWnd);
		MainWndAddWidgets(hWnd);
		SetOpenFileParam(hWnd);
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	default: return DefWindowProc(hWnd, msg, wp, lp);
	}
}

void MainWndAddMenus(HWND hWnd)
{
	HMENU RootMenu = CreateMenu();
	HMENU SubMenu = CreateMenu();

	AppendMenu(SubMenu, MF_STRING, Save, L"Сохранить");
	AppendMenu(SubMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(SubMenu, MF_STRING, OnExitSofrware, L"Выход");

	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu, L"Файл");
	AppendMenu(RootMenu, MF_STRING, Help, L"Справка");
	SetMenu(hWnd, RootMenu);
}

void MainWndAddWidgets(HWND hWnd)
{
	/*Поле ввода X*/
	CreateWindowA("static", "Ширина:", WS_VISIBLE | WS_CHILD, 10, 10, 55, 30, hWnd, NULL, NULL, NULL);
	hSizeX = CreateWindowA("edit", "10", WS_VISIBLE | WS_CHILD | ES_NUMBER, 70, 10, 50, 20, hWnd, (HMENU)GetXIndex, NULL, NULL);
	/*ЧекБокс, если матрица не квадратична*/
	CreateWindowA("button", "Матрица не квадратична", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 10, 40, 200, 20, hWnd, (HMENU)IsMatrixQuadratic, NULL, NULL);
	/*Поле ввода Y*/
	hSetVisibleY = CreateWindowA("static", "Высота:",  WS_CHILD, 10, 70, 55, 20, hWnd, NULL, NULL, NULL);
	hSizeY = CreateWindowA("edit", "10",  WS_CHILD | ES_NUMBER, 70, 70, 50, 20, hWnd, (HMENU)GetYIndex, NULL, NULL);
	/*Поле ввода D*/
	CreateWindowA("static", "D_MIN:", WS_VISIBLE | WS_CHILD, 10, 100, 55, 20, hWnd, NULL, NULL, NULL);
	hDMin = CreateWindowA("edit", "0.7", WS_VISIBLE | WS_CHILD, 70, 100, 50, 20, hWnd, (HMENU)GetDIndex, NULL, NULL);
	/*ЧекБокс, сохранить в файл?*/
	CreateWindowA("button", "Сохранить в файл?", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 10, 130, 200, 20, hWnd, (HMENU)SaveToFileCheckbox, NULL, NULL);
	/*Поле буфера сохранения в файл*/
	hSaveFileStatic = CreateWindowA("static", "Размер буфера", WS_CHILD, 10, 160, 55, 20, hWnd, NULL, NULL, NULL);
	hSaveFileEdit = CreateWindowA("edit", "100", WS_CHILD | ES_NUMBER, 70, 160, 50, 20, hWnd, (HMENU)GetLenghtResultIndex, NULL, NULL);
	/*Кнопка сохранения в файл*/
	hSaveFileButton = CreateWindowA("button", "Сохранить", WS_CHILD, 130, 157, 100, 25, hWnd, (HMENU)SaveToFile, NULL, NULL);
	/*Кнопка расчитать*/
	hSubmit = CreateWindowA("button", "Рассчитать", WS_VISIBLE | WS_CHILD, 10, 190, 100, 30, hWnd, (HMENU)Submit, NULL, NULL);
	/*Проценты*/
	Procent = CreateWindowA("static", "0%", WS_CHILD, 115, 197, 100, 30, hWnd, (HMENU)SetProcent, NULL, NULL);
	/*Окно вывода*/
	ResultEdit = CreateWindowA("edit", NULL, WS_VISIBLE | WS_CHILD | ES_MULTILINE, 235, 10, 335, 215/*215*/, hWnd, NULL, NULL, NULL);
}

void SetOpenFileParam(HWND hWnd)
{
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = filename;
	ofn.nMaxFile = sizeof(filename);
	ofn.lpstrFilter = ".txt";
	ofn.lpstrDefExt = ".txt";
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
}

DWORD WINAPI MainProcedure(LPVOID lpParameter)
{
	auto start = chrono::high_resolution_clock::now();
	long long N = (pow(2, ((SIZE_X - 2) + (SIZE_Y - 2)))) - 1;
	long long oneProcent = N / 100;
	long long procentPosition = N;
	int procent = 0;
	int M = (SIZE_X - 2) + (SIZE_Y - 2);
	int halfM = SIZE_Y - 2;
	vector<int> X, Y;
	vector<int> X_min, Y_min;
	vector<int> Summ_count, Summ_count_min;;
	//vector<Matrix> Result;
	float K_min = 100;
	float D_max = 0;
	bool flag = true;
	for (N; N > 0; N--)
	{
		if (N == procentPosition)
		{
			PrintProcent(procent);
			procent++;
			procentPosition -= oneProcent;
		}
		X.clear();
		Y.clear();
		Summ_count.clear();
		for (int i = 0; i < SIZE_X; i++) {
			X.push_back(i);
		}
		for (int i = 0; i < SIZE_Y; i++) {
			Y.push_back(i);
		}
		Summ_count.resize(X.back() + Y.back() + 1);
		int K = Summ_count.capacity();
		for (int i = 0; i < M; i++) {
			if (N & (static_cast<long long>(1) << i)) {
				if (i < halfM)
					EraseFoo(Y, (SIZE_Y - i - 2));
				else
				{
					EraseFoo(X, (SIZE_X + SIZE_Y - i - 4));
				}
			}
		}
		int z;
		for (int x : X)
		{
			for (int y : Y)
			{
				z = x + y;
				Summ_count[z]++;
			}
		}
		int multi = 1;
		for (int z : Summ_count)
		{
			multi *= z;
		}
		if (multi != 0)
		{
			float D;
			D = static_cast<float>(X.size()) / Y.size();
			if (D > 1)
				D = static_cast<float>(Y.size()) / X.size();
			if (D >= D_MIN)
			{
				if (LENGHT_RESULT_VECTOR != 0)
				{
					Matrix matrix(X, Y, Summ_count, D);
					Result.push_back(matrix);
					sort(Result.begin(), Result.end());
					if (Result.size() > LENGHT_RESULT_VECTOR) Result.pop_back();
				}
				else
				{
					float K = K = static_cast<float>(X.size() * Y.size()) / static_cast<float>(Summ_count.capacity());
					if (K < K_min)
					{
						K_min = K;
						D_max = D;
						X_min = X;
						Y_min = Y;
						Summ_count_min = Summ_count;
					}
				}
			}
		}
	}
	if (LENGHT_RESULT_VECTOR == 0)
	{
		Result.push_back(Matrix(X_min, Y_min, Summ_count_min, D_max));
	}
	ofstream fout;
	fout.open(filename);
	int i = 1;
	for (Matrix mat : Result)
	{
		fout << "/*" << i << "*\\" << endl;
		mat.print_matrix_to_file(fout);
		fout << endl;
		i++;
	}
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<float> duration = end - start;
	string result = Result[0].GetMatrixString() + "\r\n  Время выполнения - " + to_string(duration.count()) + "с";
	SetWindowTextA(ResultEdit, result.c_str());
	fout << "Time - " << duration.count() << endl;
	fout.close();

	return 0;
}

bool EraseFoo(vector<int>& vec, int a)
{
	if (a == 0 || a >= vec.size() - 1)
	{
		return false;
	}
	vector<int>::iterator it = vec.begin();
	advance(it, a);
	vec.erase(it);
	return true;
}

void GetValue(HWND hWnd)
{
	SIZE_X = GetDlgItemInt(hWnd, GetXIndex, NULL, false);
	if (~VisibleFlag1)
		SIZE_Y = SIZE_X;
	else
	{
		SIZE_Y = GetDlgItemInt(hWnd, GetYIndex, NULL, false);
	}
	if (~VisibleFlag2)
		LENGHT_RESULT_VECTOR = 0;
	else
	{
		LENGHT_RESULT_VECTOR = GetDlgItemInt(hWnd, GetLenghtResultIndex, NULL, false);
	}
	GetDlgItemText(hWnd, GetDIndex, D_MIN_CHAR, 255);
	wstring ws(D_MIN_CHAR);
	D_MIN = std::stod(ws);
}

void PrintProcent(int procent)
{
	string str = to_string(procent) + "%";
	SetWindowTextA(Procent, str.c_str());
}