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
	// ウィンドウメッセージによる分岐
	switch (uMessage)
	{
	case WM_DESTROY:			// ウィンドウの破棄要求
		// メッセージキューにWM_QUITメッセージをポストする
		::PostQuitMessage(0);
		break;
	default:					// デフォルト処理
		// デフォルトのメッセージ処理に流す
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
	wcx.cbSize = sizeof(WNDCLASSEX);								// 構造体のサイズ
	wcx.style = CS_HREDRAW | CS_VREDRAW;							// ウィンドウスタイル
	wcx.lpfnWndProc = WndProc;										// ウィンドウのメッセージを処理するコールバック関数
	wcx.cbClsExtra = 0;												// ウィンドウクラス構造体の後ろに割り当てる補足バイト数
	wcx.cbWndExtra = 0;												// ウィンドウインスタンスの後ろに割り当てる補足バイト数
	wcx.hInstance = hInstance;										// このクラスのためのウィンドウプロシージャがあるインスタンスハンドル
	wcx.hIcon = ::LoadIcon(NULL, IDI_APPLICATION);					// アイコンのハンドル
	wcx.hIconSm = ::LoadIcon(NULL, IDI_WINLOGO);					// 小さいサイズのアイコンのハンドル
	wcx.hCursor = ::LoadCursor(NULL, IDC_ARROW);					// マウスカーソルのハンドル
	wcx.hbrBackground = (HBRUSH)::GetStockObject(WHITE_BRUSH);		// ウィンドウ背景色
	wcx.lpszMenuName = NULL;										// デフォルトメニュー名
	wcx.lpszClassName = szWindowClass;								// このウィンドウクラスにつける名前

	// ウィンドウクラス登録エラー
	if (!::RegisterClassEx(&wcx))
	{
		return 0;
	}

	// ウィンドウ生成
	hWnd = ::CreateWindow(
		szWindowClass,							// ウィンドウクラス名
		szTitle,								// ウィンドウタイトル
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,		// ウィンドウスタイル
		CW_USEDEFAULT,							// X座標
		CW_USEDEFAULT,							// Y座標
		CW_USEDEFAULT,							// 幅
		CW_USEDEFAULT,							// 高さ
		NULL,									// 親ウィンドウのハンドル
		NULL,									// メニューハンドル
		hInstance,								// ウィンドウインスタンス
		NULL);									// WM_CREATEでLPARAMに渡したい値

	// ウィンドウ生成エラー
	if (!hWnd)
	{
		return 0;
	}

	// メッセージループ
	while (::GetMessage(&msg, NULL, 0, 0) != 0)
	{
		// 仮想キーメッセージを文字メッセージに変換し、呼び出し側スレッドのメッセージキューにポストする
		::TranslateMessage(&msg);
		// ウィンドウプロシージャへメッセージをディスパッチする
		::DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}
