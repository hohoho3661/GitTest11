#include "stdafx.h"
#include "Monster.h"



Monster::Monster()
{
	_monster = new Image;
	_monster->Init(TEXT("SpriteImage/Monster.bmp"), 358, 632, 2, 4, true, RGB(255, 0, 255)); // 파일이름... 이미지전체 x,y크기 ... 그이미지의 갯수 x값, y값.
	_monster->SetX(WINSIZEX - 200);
	_monster->SetY(WINSIZEY - 200);

	_Golem = RectMake(WINSIZEX-200,WINSIZEY-200, 358/2, 632/4);

	_dir = 1;
	//_dir = 0; // 일단 멈춰놓기.. 테스트용
}


Monster::~Monster()
{
	SAFE_DELETE(_monster);
}

void Monster::Update()
{
	switch (_dir)
	{
	case 1:										// _dir의 초기값은 1이니까 X방향으로 --;
		{
			_monster->SetX(_monster->GetX() - 3);
			_dirChange = true;
			_monster->SetFrameX(0);
			OffsetRect(&_Golem, -3, 0);
		}
		break;
	case -1:
		{
			_monster->SetX(_monster->GetX() + 3);
			_dirChange = false;
			_monster->SetFrameX(1);
			OffsetRect(&_Golem, 3, 0);
		}
		break;
	}
	if (_Golem.right > WINSIZEX || _Golem.left <= 0) // 양쪽끝에 닿았을때.
		_dir *= -1;									 // 스위치문에 들어갈 매개변수 _dir을 바꿔줌.

	
	_nCount++;

	if (_nCount % 10 == 0) // 1/100초마다 하나씩 그려짐. (원래는 1/1000초인데.. 10당 1개니까) ..... 프레임 skiping.
	{
		if (_dirChange)
		{
			if (_iIndex <= 0)
				_iIndex = 4;

			_iIndex--;

			_monster->SetFrameY(_iIndex);
		}
		else
		{
			if (_iIndex >= _monster->GetMaxFrameY())
				_iIndex = 0;

			_iIndex++;

			_monster->SetFrameY(_iIndex);
		}

		_nCount = 0;
	}
}

void Monster::Render(HDC hdc)
{
//	Rectangle(hdc, _Golem.left, _Golem.top, _Golem.right, _Golem.bottom);  // 확인용! 나중에 주석처리!!!!!!!!!!!!

	_monster->FrameRender(hdc, _monster->GetX(), _monster->GetY(),
		_monster->GetFrameX(), _monster->GetFrameY());
}
