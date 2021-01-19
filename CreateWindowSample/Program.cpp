#include <windows.h>

/// <summary>
/// ウィンドウプロシージャ
/// </summary>
/// <param name="hWnd">ウィンドウハンドル</param>
/// <param name="uMessage">ウィンドウメッセージ</param>
/// <param name="wParam">パラメータ1</param>
/// <param name="lParam">パラメータ2</param>
/// <returns></returns>
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return ::DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}

/// <summary>
/// Windowsプログラムのアプリケーションエントリポイント
/// </summary>
/// <param name="hInstance">インスタンスハンドル</param>
/// <param name="hPrevInstance">他のインスタンスハンドル</param>
/// <param name="lpCmdLine">コマンドライン引数</param>
/// <param name="nCmdShow">初期表示方法</param>
/// <returns></returns>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcx;
	MSG msg;
	HWND hWnd;
	LPCWSTR szTitle = TEXT("サンプル アプリケーション");
	LPCWSTR szWindowClass = TEXT("SampleApp");

	// ウィンドウクラス設定
	::ZeroMemory(&wcx, sizeof(wcx));
	wcx.cbSize = sizeof(WNDCLASSEX);
	wcx.style = CS_HREDRAW | CS_VREDRAW;
	wcx.lpfnWndProc = WndProc;
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hInstance = hInstance;
	wcx.hIcon = ::LoadIcon(NULL, IDI_APPLICATION);
	wcx.hIconSm = ::LoadIcon(NULL, IDI_WINLOGO);
	wcx.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	wcx.hbrBackground = (HBRUSH)::GetStockObject(WHITE_BRUSH);
	wcx.lpszMenuName = NULL;
	wcx.lpszClassName = szWindowClass;

	// ウィンドウクラス登録エラー
	if (!RegisterClassEx(&wcx))
	{
		return 0;
	}

	// ウィンドウ生成
	hWnd = ::CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	// ウィンドウ生成エラー
	if (!hWnd)
	{
		return 0;
	}

	// メッセージループ
	while (::GetMessage(&msg, NULL, 0, 0) != 0)
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}
