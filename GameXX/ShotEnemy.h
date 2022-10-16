#pragma once

#include "DxLib.h"
#include "Player.h"
#include "enemy.h"
#include "collision.h"
#include "function.h"

#define ESHOT			100		//�G�l�~�[�V���b�g�ő吔
#define ESHOT_SPEED		20		//�ʏ�V���b�g�X�s�[�h

class Player;
class Enemy;

class ShotEnemy
{
private:

	int EGraph;
	int ex;
	int ey;
	int ew;
	int eh;
	int edx;
	int edy;

	bool EVisibleFlag;

public:

	/// <summary>
	/// �G�l�~�[�e������
	/// </summary>
	void InitShotEnemy();

	/// <summary>
	/// �G�l�~�[�e�X�V
	/// </summary>
	void UpdateShotEnemy(Player& player, Enemy& enemy);

	/// <summary>
	/// �G�l�~�[�e�`��
	/// </summary>
	void DrawShotEnemy(Enemy& enemy);

	/// <summary>
	/// �G�l�~�[�e�̍��W�Z�b�g
	/// </summary>
	void OnShotEnemy(float EnemyX, float EnemyY, float EnemyW, float EnemyH);

	bool IsEVisibleFlag() { return EVisibleFlag; }
};