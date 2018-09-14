#pragma once

class Image;

class Player
{
	Image*	_siva;

	int		_nCount;
	int		_iIndex;

	int		_dirChange;

	//============ ���� ���� ===============
	float _x, _y;
	float _jumpPower, _gravity, _jumpDistX;
	bool _isJump;
	//=====================================
public:		
	Player();
	virtual ~Player();	

	virtual void Update();
	virtual void Render(HDC hdc);
	//========================
	RECT	_Runner;		// �ù�

	void	damageSivaR();
	void	damageSivaL();

	bool	_crash;
	int		_crashDir;
};

