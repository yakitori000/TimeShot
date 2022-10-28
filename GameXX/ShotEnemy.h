#pragma once

#include "enemy.h"

#define ESHOT			100		//�G�l�~�[�V���b�g�ő吔
#define ESHOT_SPEED		20		//�ʏ�V���b�g�X�s�[�h
#define ESHOT_INTERVAL	3		//�ʏ�V���b�g���˃C���^�[�o��

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