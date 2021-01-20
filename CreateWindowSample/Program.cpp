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
	// �E�B���h�E���b�Z�[�W�ɂ�镪��
	switch (uMessage)
	{
	case WM_DESTROY:			// �E�B���h�E�̔j���v��
		// ���b�Z�[�W�L���[��WM_QUIT���b�Z�[�W���|�X�g����
		::PostQuitMessage(0);
		break;
	default:					// �f�t�H���g����
		// �f�t�H���g�̃��b�Z�[�W�����ɗ���
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
	wcx.cbSize = sizeof(WNDCLASSEX);								// �\���̂̃T�C�Y
	wcx.style = CS_HREDRAW | CS_VREDRAW;							// �E�B���h�E�X�^�C��
	wcx.lpfnWndProc = WndProc;										// �E�B���h�E�̃��b�Z�[�W����������R�[���o�b�N�֐�
	wcx.cbClsExtra = 0;												// �E�B���h�E�N���X�\���̂̌��Ɋ��蓖�Ă�⑫�o�C�g��
	wcx.cbWndExtra = 0;												// �E�B���h�E�C���X�^���X�̌��Ɋ��蓖�Ă�⑫�o�C�g��
	wcx.hInstance = hInstance;										// ���̃N���X�̂��߂̃E�B���h�E�v���V�[�W��������C���X�^���X�n���h��
	wcx.hIcon = ::LoadIcon(NULL, IDI_APPLICATION);					// �A�C�R���̃n���h��
	wcx.hIconSm = ::LoadIcon(NULL, IDI_WINLOGO);					// �������T�C�Y�̃A�C�R���̃n���h��
	wcx.hCursor = ::LoadCursor(NULL, IDC_ARROW);					// �}�E�X�J�[�\���̃n���h��
	wcx.hbrBackground = (HBRUSH)::GetStockObject(WHITE_BRUSH);		// �E�B���h�E�w�i�F
	wcx.lpszMenuName = NULL;										// �f�t�H���g���j���[��
	wcx.lpszClassName = szWindowClass;								// ���̃E�B���h�E�N���X�ɂ��閼�O

	// �E�B���h�E�N���X�o�^�G���[
	if (!::RegisterClassEx(&wcx))
	{
		return 0;
	}

	// �E�B���h�E����
	hWnd = ::CreateWindow(
		szWindowClass,							// �E�B���h�E�N���X��
		szTitle,								// �E�B���h�E�^�C�g��
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,		// �E�B���h�E�X�^�C��
		CW_USEDEFAULT,							// X���W
		CW_USEDEFAULT,							// Y���W
		CW_USEDEFAULT,							// ��
		CW_USEDEFAULT,							// ����
		NULL,									// �e�E�B���h�E�̃n���h��
		NULL,									// ���j���[�n���h��
		hInstance,								// �E�B���h�E�C���X�^���X
		NULL);									// WM_CREATE��LPARAM�ɓn�������l

	// �E�B���h�E�����G���[
	if (!hWnd)
	{
		return 0;
	}

	// ���b�Z�[�W���[�v
	while (::GetMessage(&msg, NULL, 0, 0) != 0)
	{
		// ���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�ɕϊ����A�Ăяo�����X���b�h�̃��b�Z�[�W�L���[�Ƀ|�X�g����
		::TranslateMessage(&msg);
		// �E�B���h�E�v���V�[�W���փ��b�Z�[�W���f�B�X�p�b�`����
		::DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}
