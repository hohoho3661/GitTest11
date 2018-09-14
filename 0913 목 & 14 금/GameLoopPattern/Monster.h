#pragma once

class Image;

class Monster
{
	Image*	_monster;

	int		_nCount;
	int		_iIndex;

	int		_dirChange;

	int		_dir; // 방향알려주는거

public:
	Monster();
	virtual ~Monster();

	virtual void Update();
	virtual void Render(HDC hdc);

	//========================
	RECT	_Golem;
};

