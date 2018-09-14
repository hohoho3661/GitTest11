#include "stdafx.h"
#include "FrameRenderTest.h"
#include "Player.h"
#include "Monster.h"


FrameRenderTest::FrameRenderTest()
{
}


FrameRenderTest::~FrameRenderTest()
{
}


bool FrameRenderTest::Init()
{
	_background = new Image;
	_background->Init(TEXT("Image/background.bmp"), WINSIZEX, WINSIZEY);

	
	player = new Player;
	monster = new Monster;

	return true;
}

void FrameRenderTest::Release()
{
	SAFE_DELETE(_background);
	SAFE_DELETE(player);
	SAFE_DELETE(monster);
}

void FrameRenderTest::Update()
{
	player->Update();
	monster->Update();
	CheckRect();
}

void FrameRenderTest::Render(HDC hdc)
{
	_background->Render(hdc, 0, 0);
	monster->Render(hdc);
	player->Render(hdc);
}

void FrameRenderTest::CheckRect()
{
	RECT temp;
	if (IntersectRect(&temp, &player->_Runner, &monster->_Golem))
	{
		if (player->_Runner.right <= monster->_Golem.left + (monster->_Golem.right - monster->_Golem.left) / 2)
		{
			player->damageSivaR();
		}
		else
		{
			player->damageSivaL();
		}
	}

}