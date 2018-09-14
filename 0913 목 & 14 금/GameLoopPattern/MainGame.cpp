#include "stdafx.h"
#include "MainGame.h"

#include "ImageCropTest.h"
#include "RenderTest.h"
#include "FrameRenderTest.h"
#include "TrigonometricTest.h"
#include "StalkerTest.h"

// 루프랜더를 사용해서 
// 이미지 하나로.


MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}



bool MainGame::Init() // 초기화
{
	GameNode::Init();

	//===================================

#if defined(_RENDER_TEST)
	renderTest = new RenderTest;
	assert(renderTest != NULL);
	renderTest->Init();
#elif defined(_CROP_TEST)
	cropTest = new ImageCropTest;
	assert(cropTest != NULL);
	cropTest->Init();
#elif defined(_FRAME_TEST)
	frameTest = new FrameRenderTest;
	assert(frameTest != NULL);
	frameTest->Init();

#elif defined(_TRIFUNC_TEST)
	trritest = new TrigonometricTest; // 불완전한 형식 = 이름이 다를떄.
	assert(trritest != NULL);
	trritest->Init();

#elif defined(_STALKER_TEST)
	stalkertest = new StalkerTest; // 불완전한 형식 = 이름이 다를떄.
	assert(stalkertest != NULL);
	stalkertest->Init();
#endif //

	//===================================

	return true;
}

void MainGame::Release() // 해제
{
	GameNode::Release();
	//==================================
#if defined(_RENDER_TEST)
	renderTest->Release();
#elif defined(_CROP_TEST)
	cropTest->Release();
#elif defined(_FRAME_TEST)
	frameTest->Release();
#elif defined(_TRIFUNC_TEST)
	trritest->Release();
#elif defined(_STALKER_TEST)
	stalkertest->Release();
#endif //


	//==================================
}

void MainGame::Update() // 변동
{
	GameNode::Update();
	//==================================
#if defined(_RENDER_TEST)
	renderTest->Update();
#elif defined(_CROP_TEST)
	cropTest->Update();
#elif defined(_FRAME_TEST)
	frameTest->Update();
#elif defined(_TRIFUNC_TEST)
	trritest->Update();
#elif defined(_STALKER_TEST)
	stalkertest->Update();
#endif //
	//==================================

}

void MainGame::Render(HDC hdc) // 그리기 ( 화면 출력 ) // 랜더링작업을 백버퍼에 프래임단위로 1/10초마다 한번씩 화면에 뿌려줌
{
	//GameNode::Render(hdc);

	HDC	backDC = (this->GetBackBuffer())->GetMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//============================
	// 모든작업은 여기 안에서 작업.
#if defined(_RENDER_TEST)
	renderTest->Render(backDC);
#elif defined(_CROP_TEST)
	cropTest->Render(backDC);
#elif defined(_FRAME_TEST)
	frameTest->Render(backDC);
#elif defined(_TRIFUNC_TEST)
	trritest->Render(backDC);
#elif defined(_STALKER_TEST)
	stalkertest->Render(backDC);
#endif //
	//============================
	this->GetBackBuffer()->Render(hdc, 0, 0);
}