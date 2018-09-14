#include "stdafx.h"
#include "Player.h"



Player::Player()
{
	_siva = new Image;
	_siva->Init(TEXT("SpriteImage/시바달리기.bmp"), 440, 108, 8, 2, true, RGB(255, 0, 255)); // 파일이름... 이미지전체 x,y크기 ... 그이미지의 갯수 x값, y값.
	_siva->SetX(WINSIZEX / 2);
	_siva->SetY(WINSIZEY - 100);

	//_Runner = RectMake(WINSIZEX /2, WINSIZEY - 100, 440/8, 108/2);

	// 점프
	_x = (WINSIZEX / 2) + 440 / 16;
	_y = (WINSIZEY - 100) + 108 / 4; // 727

	_Runner = RectMakeCenter(_x, _y, 440 / 8, 108 / 2);

	_jumpPower = _gravity = 0.f;
	_jumpDistX = 1.0f;
	_isJump = false;
	_crash = false;
	_crashDir = 1;
}


Player::~Player()
{
	SAFE_DELETE(_siva);
}

void Player::Update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (_x-27 > 0)
		{
			_siva->SetX(_siva->GetX() - SIVASPEED);
			_dirChange = true;
			_siva->SetFrameY(1);
			//OffsetRect(&_Runner, -3, 0);
			_x -= SIVASPEED;
		}

	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (_x+27 < WINSIZEX)
		{
			_siva->SetX(_siva->GetX() + SIVASPEED);
			_dirChange = false;
			_siva->SetFrameY(0);
			//OffsetRect(&_Runner, 3, 0);
			_x += SIVASPEED;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)&&(_isJump == false))
	{
		_gravity = 0.5f;
		_jumpPower = 15.0f;     // 점프 수치. 조정
		//_jumpDistX = 5.0f;
		_isJump = true;
	}
	//========================= 점 프 ===========================================
	if (_isJump)
	{
		_y -= _jumpPower;		// _y는 현재 대상의 위치.
		_siva->SetY(_siva->GetY() - _jumpPower);
		//_x += _jumpDistX * _dirX;
		_jumpPower -= _gravity; // 그 값만큼을 뺴고 다시 위치시킴.	

		
		//if (_Runner.bottom >= 754)
		if (_y >= 727) // 바닥값 계산한것.
		{
			_Runner.bottom = 754;
			_isJump = false;
			_crash = false;
		}
	}

	if (_crash)
	{
		_jumpDistX = 5.0f;
		_x -= _jumpDistX * _crashDir;

		_siva->SetX(_siva->GetX() - _jumpDistX * _crashDir);
	}

	_nCount++;

	if (_nCount % 10 == 0) // 1/100초마다 하나씩 그려짐. (원래는 1/1000초인데.. 10당 1개니까) ..... 프레임 skiping.
	{
		if (_dirChange)
		{
			if (_iIndex <= 0)
				_iIndex = 5;

			_iIndex--;

			_siva->SetFrameX(_iIndex);
		}
		else
		{
			if (_iIndex >= _siva->GetMaxFrameX())
				_iIndex = 2;

			_iIndex++;

			_siva->SetFrameX(_iIndex);
		}

		_nCount = 0;
	}

	_Runner = RectMakeCenter(_x, _y, 440 / 8, 108 / 2);
}

void Player::Render(HDC hdc)
{
//	Rectangle(hdc, _Runner.left, _Runner.top, _Runner.right, _Runner.bottom); // 확인용.. 나중에 잊지말고 주석처리하자

	_siva->FrameRender(hdc, _siva->GetX(), _siva->GetY(),
		_siva->GetFrameX(), _siva->GetFrameY());
}

//========================
// 시바가 맞았을때 함수 ... 피격 이미지를 추가하면 좋을듯

void Player::damageSivaR() // 오른쪽에서 부딪혔을때.. 왼쪽으로 튕겨나가는경우
{
//	_x -= SIVAPUSH;
//	_siva->SetX(_siva->GetX() - SIVAPUSH);
	
	_gravity = 0.3f;
	_jumpPower = 5.0f;
	_isJump = true; // 점프는 update에서. 점점 가감하는 효과로 깔끔하게 나오도록.

	_y -= _jumpPower;
	_siva->SetY(_siva->GetY() - _jumpPower);
	
	_crash = true; // 이걸 Update()에서 처리해야 생각했던대로 깔끔하게 나옴.
	_crashDir = 1; // 편의상 방향정하기.
}
void Player::damageSivaL()
{
//	_x += SIVAPUSH;
//	_siva->SetX(_siva->GetX() + SIVAPUSH);


	_gravity = 0.3f;
	_jumpPower = 5.0f;
	_isJump = true;

	_y -= _jumpPower;
	_siva->SetY(_siva->GetY() - _jumpPower);

	_crash = true;
	_crashDir = -1;
}
