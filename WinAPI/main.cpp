#include<Windows.h>
#include"resource.h"
#include <commctrl.h> // Может понадобиться для EM_SETCUEBANNER, хотя обычно есть в Windows.h
#pragma comment(lib, "comctl32.lib") // Для поддержки общих элементов управления
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	/*MessageBox
	(
		NULL, 
		"Hello WinAPI!", 
		"MessageBox", 
		MB_YESNOCANCEL 
		| MB_ICONQUESTION 
		| MB_HELP
		| MB_SYSTEMMODAL
		| MB_RIGHT
	);*/

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL,(DLGPROC) DlgProc, 0);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
		SetFocus(GetDlgItem(hwnd, IDC_EDIT_LOGIN));

		HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
		SendMessage(hEditLogin, EM_SETCUEBANNER, TRUE, (LPARAM)L"Введите логин");
		SendMessage(hEditPassword, EM_SETCUEBANNER, TRUE, (LPARAM)L"Введите пароль");
	}
	break;
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
			case IDC_BUTTON_COPY:
			{
				CONST INT SIZE = 256;
				CHAR sz_buffer[SIZE] = {};
				HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
				HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
				SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
				SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			}
				break;
			case IDOK:
				MessageBox(NULL, "А чё 'ОК' то? Закрой окно.", "Info", MB_OK | MB_ICONINFORMATION);
				break;
			case IDCANCEL:
				EndDialog(hwnd, 0);
				break;
			}
			break;
		case WM_CLOSE:
			EndDialog(hwnd, 0);
	}
	return FALSE;
}