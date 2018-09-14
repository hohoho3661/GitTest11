#pragma once
#include "GameNode.h"

#define MAX_BULLET	20

struct Bullet
{
	float	x, y;
	float	speed;
	float	angle;
	float	radius; // 반지름
	float	gravity;
	bool	fire;
};

struct Cannon
{
	POINT	center;			// 포대의 중심
	POINT	end;			// 포신의 끝
	float	angle;			// 포신의 각도
	int		radius;			// 포대의 반지름
	int		length;			// 포신의 길이
};

struct Player
{
	float x, y;
	float radius;
	float angle;
	float speed;
	float gunEndX;
	float gunEndY;
	float gunLength;
};


class TrigonometricTest : public GameNode
{
	Cannon	_cannon;
	Bullet	_bullet[MAX_BULLET];

	Player _player;
	
public:
	TrigonometricTest();
	virtual ~TrigonometricTest();

	virtual bool Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void BulletFire();
	void BulletMove();

	void BulletCollision();
};

