#include <Windows.h>
#include <windowsx.h>
#include "resource.h"
#include "winres.h"

//Chức năng giao tiếp với Windows, toàn bộ thông diệp đều được gửi qua hàm này
//Hàm này đã được khai báo phía dưới
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK AboutBox(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


//the entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
					LPSTR lpCmdLine, int nCmdShow) {
	HWND hWnd;

	WNDCLASSEXW wc;

	//Clear bộ nhớ trước khi tạo cửa sổ
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	//Thông số của cửa sổ
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"WindowClass1";
	//Load icon
	wc.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
	wc.hIconSm = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
	//Load menu 
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	

	RegisterClassEx(&wc);

	//Tạo cửa sổ
	hWnd = CreateWindowEx(NULL, L"WindowClass1", L"Dream of Dragon", WS_OVERLAPPEDWINDOW,
		300, 300, 500, 400, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	//Đợi thông báo tiếp theo trong hàng đợi, và lưu trữ kết quả vào biến msg
	while (GetMessage(&msg, NULL, 0, 0)) {
		// dịch thông báo gõ phím sang định dạng phù hợp
		TranslateMessage(&msg);
		// gửi tin nhắn đến hàm WindowProc
		DispatchMessage(&msg);
	}
	// return this part of the WM_QUIT message to Windows
	return msg.wParam;
}

//Thủ tục để Vận hành một cửa sổ
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	// sort through and find what code to run for the message given
	switch (message){
		// this message is read when the window is closed
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_FILE_EXIT:
			PostQuitMessage(0);
			break;
		case ID_HELP_ABOUT:
			DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, AboutBox);
			break;
		}
	case WM_DESTROY:{
		// close the application entirely
		PostQuitMessage(0);
		return 0;
	} break;
	}

	// Handle any messages the switch statement didn't
	return DefWindowProc(hWnd, message, wParam, lParam);
}

BOOL CALLBACK AboutBox(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
	case WM_INITDIALOG:
		return 1;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hWnd, IDOK);
			break;
		case IDCANCEL:
			EndDialog(hWnd, IDCANCEL);
			break;
		}
		break;
	default:
		return 0;
	}
	return 1;
	}