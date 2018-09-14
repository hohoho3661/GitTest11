#pragma once
#include "GameNode.h"

struct Stalker
{
	float x, y;
	float angle;
	float endx, endy;
	float length;
	float speed;

	RECT rc;
};

class StalkerTest : GameNode
{
	Stalker _skr1;
	Stalker _skr2;


public:
	StalkerTest();
	virtual ~StalkerTest();

	virtual bool Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};

// 과제
// 4방향에서 적 출현.. 적은 따라오는걸로
//
// 충돌처리
// 플레이어는 총알 발사, 에너미는 플레이어와 충돌했을때 ....처리
// 
// 