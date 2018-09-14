#include "stdafx.h"
#include "StalkerTest.h"



StalkerTest::StalkerTest()
{
}


StalkerTest::~StalkerTest()
{
}

bool StalkerTest::Init()
{
	_skr1.angle = PI / 2.f;
	_skr1.x = static_cast<float>(WINSIZEX) / 2.f - 100;
	_skr1.y = static_cast<float>(WINSIZEY) / 2.f;
	_skr1.endx = _skr1.x;
	_skr1.endy = _skr1.y;
	_skr1.length = 10.f;
	_skr1.rc = RectMakeCenter(_skr1.x, _skr1.y, 50, 50);
	_skr1.speed = 4.f;

	_skr2.angle = PI / 2.f;
	_skr2.x = static_cast<float>(WINSIZEX) / 2.f + 200.f;
	_skr2.y = static_cast<float>(WINSIZEY) / 2.f;
	_skr2.endx = _skr2.x;
	_skr2.endy = _skr2.y;
	_skr2.rc = RectMakeCenter(_skr2.x, _skr2.y, 50, 50);
	_skr2.speed = 1.f;

	return true;
}

void StalkerTest::Release()
{
}

void StalkerTest::Update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_skr1.angle += 0.04f;
		_skr1.x -= _skr1.speed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_skr1.angle -= 0.04f;
		_skr1.x += _skr1.speed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{		
		_skr1.y -= _skr1.speed;
		//_skr1.speed++;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_skr1.y += _skr1.speed;
		//_skr1.speed--;
	}

	_skr1.x += cosf(_skr1.angle) * 1.1f;
	_skr1.y += -sinf(_skr1.angle) * 1.1f;

	_skr1.endx = _skr1.x + cosf(_skr1.angle) * 25;
	_skr1.endy = _skr1.y + -sinf(_skr1.angle) * 25;

	_skr1.rc = RectMakeCenter(_skr1.x, _skr1.y, 50, 50);

	_skr2.angle = UTIL::getAngle(_skr2.x,_skr2.y,_skr1.x,_skr1.y); // 
	_skr2.x += cosf(_skr2.angle) * _skr2.speed;
	_skr2.y += -sinf(_skr2.angle) * _skr2.speed;
	_skr2.rc = RectMakeCenter(_skr2.x, _skr2.y, 30, 30);
}

void StalkerTest::Render(HDC hdc)
{
	EllipseMakeCenter(hdc, _skr1.x, _skr1.y, 50, 50);
	lineMake(hdc, _skr1.x, _skr1.y, _skr1.endx, _skr1.endy);
	EllipseMakeCenter(hdc, _skr2.x, _skr2.y, 50, 50);
}
