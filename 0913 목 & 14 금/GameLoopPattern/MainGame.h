#pragma once
#include "GameNode.h"

//class RenderTest;
//class ImageCropTest;
//class FrameRenderTest;
//class TrigonometricTest;
class StalkerTest;

class MainGame : public GameNode
{
private:
#if defined(_RENDER_TEST)
	RenderTest*	renderTest;
#elif defined(_CROP_TEST)
	ImageCropTest* cropTest;
#elif defined(_FRAME_TEST)
	FrameRenderTest* frameTest;
#elif defined(_TRIFUNC_TEST)
	TrigonometricTest* trritest;
#elif defined(_STALKER_TEST)
	StalkerTest* stalkertest;
#endif //

public:
	MainGame();
	virtual ~MainGame();
	//==========================================


	//==========================================

	virtual bool Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};
