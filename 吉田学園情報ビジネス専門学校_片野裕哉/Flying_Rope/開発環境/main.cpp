//=========================================================================================================================
//
// DirectX_Sample [main.cpp]
// Author:team 11
//
//=========================================================================================================================
#include "main.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "input.h"
#include "player.h"
#include "block.h"
#include "BG.h"
#include "wire.h"
#include "fade.h"
#include "sound.h"
#include "tutorial.h"
#include "StageSelect.h"

//=========================================================================================================================
// �}�N����`
//=========================================================================================================================
#define CLASS_NAME "WindowClass"		// �E�B���h�E�N���X�̖��O
#define WINDOW_NAME "�t���C���O���[�v"	// �E�B���h�E�̖��O
#define WINDOW_COLOR_R	(0)				// �E�B���h�E�̐F(��)
#define WINDOW_COLOR_G	(0)				// �E�B���h�E�̐F(��)
#define WINDOW_COLOR_B	(0)				// �E�B���h�E�̐F(��)
#define WINDOW_COLOR_A	(0)				// �E�B���h�E�̐F(�����x)

//=========================================================================================================================
// �v���g�^�C�v�錾
//=========================================================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// �E�B���h�E�v���V�[�W��
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);							// ����������
void Uninit(void);																	// �I������
void Update(void);																	// �X�V����
void Draw(void);																	// �`�揈��
void DrawFPS(void);																	// fps�\��

//=========================================================================================================================
// �O���[�o���ϐ�
//=========================================================================================================================
LPDIRECT3D9 g_pD3D = NULL;					// Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;		// Direct3D�f�o�C�X�ւ̃|�C���^(�`�揈���ɕK�v)
LPD3DXFONT g_pFont = NULL;					// �t�H���g�ւ̃|�C���^
int g_nCountFPS;							// FPS�J�E���^
MODE g_mode = MODE_TITLE;					// ���[�h�̎��

//=========================================================================================================================
// ���C���֐�
//=========================================================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstace, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL, IDI_APPLICATION)
	};

	HWND hWnd;		// �E�B���h�E�n���h��(���ʎq)
	MSG  msg;		// ���b�Z�[�W���i�[����


	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	RECT rect = { SCREEN_WIDTH_L, SCREEN_HEIGHT_T, SCREEN_WIDTH_R, SCREEN_HEIGHT_U };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	

	// �E�B���h�E�̐���
	hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rect.right,
		rect.bottom,
		NULL,
		NULL,
		hInstance,
		NULL);

	// ����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	// �E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	DWORD dwExecLastTime;	// �������s�ŏI����
	DWORD dwFPSLastTime;	// FPS�v���ŏI����
	DWORD dwCurrentTime;	// ���ݎ���
	DWORD dwFrameCount;		// �t���[���J�E���g

	dwExecLastTime = 
	dwFPSLastTime = 
	dwCurrentTime = timeGetTime();	// ���ݎ�����ݒ�
	dwFrameCount = 0;

	//���b�Z�[�W���[�v
	while (1)
	{	// Windows�̏���
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// ���b�Z�[�W���擾���Ȃ������ꍇ "0" ��Ԃ�
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{// DirectX�̏���
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5�b�o��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) > (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// �X�V����
				Update();

				// �`�揈��
				Draw();

				dwFrameCount++;
			}
		}
	}

	// �I������
	Uninit();

	// �E�B���h�E�N���X�̓o�^����
	UnregisterClass(
		CLASS_NAME,
		wcex.hInstance);

	return (int)msg.wParam;
	return 0;
}

//=========================================================================================================================
// �E�B���h�E�v���V�[�W��
//=========================================================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	const RECT rect = { SCREEN_WIDTH_L, SCREEN_HEIGHT_T, SCREEN_WIDTH_R, SCREEN_HEIGHT_U };

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);	// WM_QUIT���b�Z�[�W��Ԃ�
		break;
	case WM_CLOSE:
		// �~�{�^���̐ݒ�
		nID = MessageBox(NULL, "�E�B���h�E����܂����H", "�m�F", (MB_YESNO | MB_ICONEXCLAMATION));
		if (nID == IDYES)
		{
			DestroyWindow(hWnd);	// WM_DESTROY���b�Z�[�W��Ԃ�
		}
		else
		{
			return 0;
		}
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			//// ESCAPE�L�[�̐ݒ�
			//nID = MessageBox(NULL, "�E�B���h�E����܂����H", "�m�F", (MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST));
			//if (nID == IDYES)
			//{
				DestroyWindow(hWnd);	// WM_DESTROY���b�Z�[�W��Ԃ�
			//}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=========================================================================================================================
// ����������
//=========================================================================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	// DIrect3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// �f�B�X�v���C���[�h�̎擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH_R;		// �X�N���[���̕�
	d3dpp.BackBufferHeight = SCREEN_HEIGHT_U;		// �X�N���[���̍���
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	// Direct3D�f�o�C�X�̐���
	if (FAILED(g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// �J�����O�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h(���l�̍���)�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);			// �\�[�X(�`�挳)�̍������@�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// �f�X�e�B�l�[�V����(�`���)�̍������@�̐ݒ�

	// �T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �k���� ���
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �g�厞 ���
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// U�l �J��Ԃ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// V�l �J��Ԃ�

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// ���l�̍���
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// ���l�̍���
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ���l�̍���

	// ���͂̏�����
	InitKeyboard(hInstance, hWnd);

	// �t�F�[�h�̏���������
	InitFade(MODE_TITLE);



	D3DXCreateFont(
		g_pD3DDevice,
		30,
		0,
		0,
		0,
		FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Terminal",
		&g_pFont);

	// �T�E���h�̏���������
	InitSound(hWnd);

	// ���[�h�̃Z�b�g����
	SetMode(g_mode);


	return S_OK;
}

//=========================================================================================================================
// �I������
//=========================================================================================================================
void Uninit(void)
{	
	// �L�[���͂̏I������
	UninitKeyboard();

	// �t�F�[�h�̏I������
	UninitFade();

	switch (g_mode)
	{
	case MODE_TITLE:
		// �^�C�g����ʂ̏I������
		UninitTitle();
		break;

	case MODE_TUTORIAL:
		// �`���[�g���A����ʂ̏I������
		UninitTutorial();
		break;

	case MODE_STAGESELECT:
		// �`���[�g���A����ʂ̏I������
		UninitStageSelect();
		break;

	case MODE_GAME:
		// �Q�[����ʂ̏I������
		UninitGame();
		break;

	case MODE_RESULT:
		// ���U���g��ʂ̏I������
		UninitResult();
		break;
	}

	// �T�E���h�̏I������
	UninitSound();

	// Direct3D�f�o�C�X�̊J��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	// Direct3D�I�u�W�F�N�g�̊J��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	// �t�H���g�̊J��
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
}

//=========================================================================================================================
// �X�V����
//=========================================================================================================================
void Update(void)
{
	// ���͂̍X�V
	UpdateKeyboard();

	switch (g_mode)
	{
	case MODE_TITLE:
		// �^�C�g����ʂ̍X�V����
		UpdateTitle();
		break;

	case MODE_TUTORIAL:
		// �`���[�g���A����ʂ̍X�V����
		UpdateTutorial();
		break;

	case MODE_STAGESELECT:
		// �X�e�[�W�Z���N�g��ʂ̍X�V����
		UpdateStageSelect();
		break;

	case MODE_GAME:
		// �Q�[����ʂ̍X�V����
		UpdateGame();
		break;

	case MODE_RESULT:
		// ���U���g��ʂ̍X�V����
		UpdateResult();
		break;
	}

	// �t�F�[�h�̍X�V����
	UpdateFade();

}

//=========================================================================================================================
// �`�揈��
//=========================================================================================================================
void Draw(void)
{
	// �o�b�N�o�b�t�@&Z�o�b�t�@�̃N���A(��ʃN���A)
	g_pD3DDevice->Clear(
		0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(WINDOW_COLOR_R, WINDOW_COLOR_G, WINDOW_COLOR_B, WINDOW_COLOR_A),
		1.0f,
		0);

	// �`��̊J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (g_mode)
		{
		case MODE_TITLE:
			// �^�C�g����ʂ̕`�揈��
			DrawTitle();
			break;

		case MODE_TUTORIAL:
			// �`���[�g���A����ʂ̕`�揈��
			DrawTutorial();
			break;

		case MODE_STAGESELECT:
			// �X�e�[�W�Z���N�g��ʂ̕`�揈��
			DrawStageSelect();
			break;

		case MODE_GAME:
			// �Q�[����ʂ̕`�揈��
			DrawGame();
			break;

		case MODE_RESULT:
			// ���U���g��ʂ̕`�揈��
			DrawResult();
			break;
		}

		//
		DrawFade();
#ifdef _DEBUG
		//
		DrawFPS();
#endif

		// �`��̏I��
		g_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=========================================================================================================================
// �f�o�C�X�̎擾
//=========================================================================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=========================================================================================================================
// FPS�̕`��
//=========================================================================================================================
void DrawFPS(void)
{
	RECT rect = { SCREEN_WIDTH_L, SCREEN_HEIGHT_T, SCREEN_WIDTH_R, SCREEN_HEIGHT_U };
	char aStr[256];

	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	// �e�L�X�g�̕`��
	g_pFont->DrawText(
		NULL,
		&aStr[0],
		-1,
		&rect,
		DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));
}

//=========================================================================================================================
// ���[�h�̐ݒ�
//=========================================================================================================================
void SetMode(MODE mode)
{
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;

	case MODE_TUTORIAL:
		// �`���[�g���A����ʂ̏I������
		UninitTutorial();
		break;

	case MODE_STAGESELECT:
		// �X�e�[�W�Z���N�g��ʂ̏I������
		UninitStageSelect();
		break;

	case MODE_GAME:
		UninitGame();
		break;

	case MODE_RESULT:
		UninitResult();
		break;
	}

	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;

	case MODE_TUTORIAL:
		// �`���[�g���A����ʂ̏���������
		InitTutorial();
		break;

	case MODE_STAGESELECT:
		// �X�e�[�W�Z���N�g��ʂ̏���������
		InitStageSelect();
		break;

	case MODE_GAME:
		InitGame();
		break;

	case MODE_RESULT:
		InitResult();
		break;
	}

	g_mode = mode;
}

//=========================================================================================================================
// ���[�h�̎擾
//=========================================================================================================================
MODE GetMode(void)
{
	return g_mode;
}