#include "stdafx.h"
#include "TrigonometricTest.h"



TrigonometricTest::TrigonometricTest()
{
}


TrigonometricTest::~TrigonometricTest()
{
}

bool TrigonometricTest::Init()
{
	// Cannon Init
	_cannon.angle = PI / 2;
	_cannon.length = 80;
	_cannon.radius = 50;

	//_bullet->angle = PI / 2;

	_cannon.center.x = WINSIZEX / 2;
	_cannon.center.y = WINSIZEY;


	_cannon.end.x = _cannon.center.x;
	_cannon.end.y = _cannon.center.y;

	// Bullet Init
	for (int i = 0; i < MAX_BULLET; i++)
	{
		_bullet[i].radius = 15;
		_bullet[i].speed = 3.f;
		_bullet[i].fire = false;
		_bullet[i].gravity = 0.f;
	}

	// Player Init
	_player.x = WINSIZEX / 2 + 100;
	_player.y = WINSIZEY / 2;
	_player.radius = 40.f;
	_player.angle = PI;
	_player.speed = 5.f;
	_player.gunEndX = _player.x;
	_player.gunEndY = _player.y;
	_player.gunLength = 50.f;

	return true;
}

void TrigonometricTest::Release()
{

}

void TrigonometricTest::Update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _cannon.angle < 3.03f)
	{
		_cannon.angle += 0.04f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _cannon.angle > 0.1f)
	{
		_cannon.angle -= 0.04f;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		BulletFire();
	}

	_cannon.end.x = _cannon.center.x + (cosf(_cannon.angle) * _cannon.length); // 생긴 x와 y의 각을 이용해서 그려줌...... 각도x길이로 값을 구함
	_cannon.end.y = _cannon.center.y + (-sinf(_cannon.angle) * _cannon.length);	


	//========================= 총알 ============================================

	BulletMove();
	BulletCollision();


	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_player.angle += 0.04f;
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_player.angle -= 0.04f;
	}

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_player.x += cosf(_player.angle) * _player.speed;
		_player.y += -sinf(_player.angle) * _player.speed;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		_player.x -= cosf(_player.angle) * _player.speed;
		_player.y -= -sinf(_player.angle) * _player.speed;
	}

	_player.gunEndX = _player.x + cosf(_player.angle) * 50;
	_player.gunEndY = _player.y + -sinf(_player.angle) * 50;

	for (int i = 0; i < MAX_BULLET; i++)           // 총알과 케논의 충돌처리
	{
		if (CollisionCircleAndCircle(_bullet[i].radius, _bullet[i].x, _bullet[i].y, _player.radius, _player.x, _player.y)) // 블랫i와 플레이어의 충돌 체크
		{
			_bullet[i] = { 0,0,0,0 };			// 충돌했을때 처리.. 지금은 없애는걸로 처리했다.
		}
	}

//============================================================================

}

void TrigonometricTest::Render(HDC hdc)
{
	// Cannon Render
	EllipseMakeCenter(hdc, _cannon.center.x, _cannon.center.y,
		_cannon.radius * 2, _cannon.radius * 2);
	lineMake(hdc, _cannon.center.x, _cannon.center.y, _cannon.end.x, _cannon.end.y);

	// Bullet Render
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (!_bullet[i].fire)
			continue;

		EllipseMakeCenter(hdc, _bullet[i].x, _bullet[i].y,
			_bullet[i].radius * 2, _bullet[i].radius * 2);
	}

	// Player Render
	EllipseMakeCenter(hdc, _player.x, _player.y, _player.radius * 2, _player.radius * 2);
	lineMake(hdc, _player.x, _player.y, _player.gunEndX, _player.gunEndY);


}



//==========================================================================================
//==========================================================================================


void TrigonometricTest::BulletFire()
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (_bullet[i].fire)
			continue;

		_bullet[i].fire = true;
		_bullet[i].x += _cannon.center.x + (cosf(_cannon.angle)* (_cannon.length + 10));
		_bullet[i].y += _cannon.center.y + (-sinf(_cannon.angle)* (_cannon.length + 10));
		_bullet[i].angle = _cannon.angle;
		break;
	}
}

void TrigonometricTest::BulletMove()
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (!_bullet[i].fire)
			continue;

		_bullet[i].x += cosf(_bullet[i].angle) * _bullet[i].speed;
		_bullet[i].y += -sinf(_bullet[i].angle) * _bullet[i].speed;

		if (_bullet[i].x - _bullet[i].radius < 0)
			_bullet[i].angle = PI - _bullet[i].angle;
		if (_bullet[i].y - _bullet[i].radius < 0)
			_bullet[i].angle = PI2 - _bullet[i].angle;

		if (_bullet[i].x + _bullet[i].radius > WINSIZEX)
			_bullet[i].angle = PI - _bullet[i].angle;
		if (_bullet[i].y + _bullet[i].radius > WINSIZEY)
			_bullet[i].angle = PI2 - _bullet[i].angle;
	}
}

void TrigonometricTest::BulletCollision()
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		for (int j = i + 1; j < MAX_BULLET; j++)
		{
			if (_bullet[i].radius * 2 < UTIL::getDistance(_bullet[i].x, _bullet[i].y, _bullet[j].x, _bullet[j].y))
			{
				continue;
			}

			_bullet[i].angle = UTIL::getAngle(_bullet[j].x, _bullet[j].y, _bullet[i].x, _bullet[i].y); // 충돌했을때 i의 각을 바꿔줌 .. getAngle 함수는 x,y값을 가지고 각을 구하는 함수.
			_bullet[j].angle = UTIL::getAngle(_bullet[i].x, _bullet[i].y, _bullet[j].x, _bullet[j].y); // 충돌했을때 j의 각을 바꿔줌
		}
	}
}
