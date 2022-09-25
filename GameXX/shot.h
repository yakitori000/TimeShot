#pragma once


#include "DxLib.h"
#include "Player.h"
#include "enemy.h"
#include "collision.h"
#include "function.h"

#define SHOT			20		//�V���b�g�ő吔
#define SHOT_SPEED		20		//�ʏ�V���b�g�X�s�[�h
#define SHOT_INTERVAL	3		//�ʏ�V���b�g���˃C���^�[�o��

class Player;
class Enemy;

class Shot
{
private:
	int graph;
	int x;
	int y;
	int w;
	int h;
	int dx;
	int dy;

	bool visibleFlag;

public:
	/// <summary>
	/// �v���C���[�e������
	/// </summary>
	void Init();

	/// <summary>
	/// �v���C���[�e�X�V
	/// </summary>
	void Update(Player& player, Enemy& enemy);

	/// <summary>
	/// �v���C���[�e�`��
	/// </summary>
	void Draw(Player& player);

	/// <summary>
	/// �v���C���[�e�̍��W�Z�b�g
	/// </summary>
	void OnShot(float PlayerX, float PlayerY, float PlayerW, float PlayerH);

	bool IsVisibleFlag() { return visibleFlag; }
};