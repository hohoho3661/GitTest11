#include "stdafx.h"
#include "Player.h"



Player::Player()
{
	_siva = new Image;
	_siva->Init(TEXT("SpriteImage/�ùٴ޸���.bmp"), 440, 108, 8, 2, true, RGB(255, 0, 255)); // �����̸�... �̹�����ü x,yũ�� ... ���̹����� ���� x��, y��.
	_siva->SetX(WINSIZEX / 2);
	_siva->SetY(WINSIZEY - 100);

	//_Runner = RectMake(WINSIZEX /2, WINSIZEY - 100, 440/8, 108/2);

	// ����
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
		_jumpPower = 15.0f;     // ���� ��ġ. ����
		//_jumpDistX = 5.0f;
		_isJump = true;
	}
	//========================= �� �� ===========================================
	if (_isJump)
	{
		_y -= _jumpPower;		// _y�� ���� ����� ��ġ.
		_siva->SetY(_siva->GetY() - _jumpPower);
		//_x += _jumpDistX * _dirX;
		_jumpPower -= _gravity; // �� ����ŭ�� ���� �ٽ� ��ġ��Ŵ.	

		
		//if (_Runner.bottom >= 754)
		if (_y >= 727) // �ٴڰ� ����Ѱ�.
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

	if (_nCount % 10 == 0) // 1/100�ʸ��� �ϳ��� �׷���. (������ 1/1000���ε�.. 10�� 1���ϱ�) ..... ������ skiping.
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
//	Rectangle(hdc, _Runner.left, _Runner.top, _Runner.right, _Runner.bottom); // Ȯ�ο�.. ���߿� �������� �ּ�ó������

	_siva->FrameRender(hdc, _siva->GetX(), _siva->GetY(),
		_siva->GetFrameX(), _siva->GetFrameY());
}

//========================
// �ùٰ� �¾����� �Լ� ... �ǰ� �̹����� �߰��ϸ� ������

void Player::damageSivaR() // �����ʿ��� �ε�������.. �������� ƨ�ܳ����°��
{
//	_x -= SIVAPUSH;
//	_siva->SetX(_siva->GetX() - SIVAPUSH);
	
	_gravity = 0.3f;
	_jumpPower = 5.0f;
	_isJump = true; // ������ update����. ���� �����ϴ� ȿ���� ����ϰ� ��������.

	_y -= _jumpPower;
	_siva->SetY(_siva->GetY() - _jumpPower);
	
	_crash = true; // �̰� Update()���� ó���ؾ� �����ߴ���� ����ϰ� ����.
	_crashDir = 1; // ���ǻ� �������ϱ�.
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
