#pragma once

// ����� ���� ���� ����

//#define _RENDER_TEST
//#define _CROP_TEST
//#define _FRAME_TEST
//#define _TRIFUNC_TEST
#define _STALKER_TEST


// �ùٷ�
#define SIVASPEED	7
#define SIVAPUSH	50


// �޸� ���� ��ũ��
// Backbuffer
#define SAFE_DELETE(p)	{if(p) {delete(p);(p) = NULL;}}
#define SAFE_RELEASE(p)	{if(p) {(p)->Release(); (p) = NULL;}}

// ������ ������ ���� ��ũ��
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

#define WINSIZEX	1000
#define WINSIZEY	800
#define WINSTARTX	100
#define WINSTARTY	100

// �̱��� ��ü ��ũ��
#define RAND		RandomFunction::getSingleton()
#define KEYMANAGER	KeyManager::getSingleton()

//
//#define PI			3.141592f
//#define PI2			PI*2