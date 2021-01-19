#include <windows.h>

/// <summary>
/// �E�B���h�E�v���V�[�W��
/// </summary>
/// <param name="hWnd">�E�B���h�E�n���h��</param>
/// <param name="uMessage">�E�B���h�E���b�Z�[�W</param>
/// <param name="wParam">�p�����[�^1</param>
/// <param name="lParam">�p�����[�^2</param>
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
/// Windows�v���O�����̃A�v���P�[�V�����G���g���|�C���g
/// </summary>
/// <param name="hInstance">�C���X�^���X�n���h��</param>
/// <param name="hPrevInstance">���̃C���X�^���X�n���h��</param>
/// <param name="lpCmdLine">�R�}���h���C������</param>
/// <param name="nCmdShow">�����\�����@</param>
/// <returns></returns>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcx;
	MSG msg;
	HWND hWnd;
	LPCWSTR szTitle = TEXT("�T���v�� �A�v���P�[�V����");
	LPCWSTR szWindowClass = TEXT("SampleApp");

	// �E�B���h�E�N���X�ݒ�
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

	// �E�B���h�E�N���X�o�^�G���[
	if (!RegisterClassEx(&wcx))
	{
		return 0;
	}

	// �E�B���h�E����
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

	// �E�B���h�E�����G���[
	if (!hWnd)
	{
		return 0;
	}

	// ���b�Z�[�W���[�v
	while (::GetMessage(&msg, NULL, 0, 0) != 0)
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}
