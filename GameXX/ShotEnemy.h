#pragma once

#include "enemy.h"

#define ESHOT			100		//エネミーショット最大数
#define ESHOT_SPEED		20		//通常ショットスピード
#define ESHOT_INTERVAL	3		//通常ショット発射インターバル

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
	/// エネミー弾初期化
	/// </summary>
	void InitShotEnemy();

	/// <summary>
	/// エネミー弾更新
	/// </summary>
	void UpdateShotEnemy(Player& player, Enemy& enemy);

	/// <summary>
	/// エネミー弾描画
	/// </summary>
	void DrawShotEnemy(Enemy& enemy);

	/// <summary>
	/// エネミー弾の座標セット
	/// </summary>
	void OnShotEnemy(float EnemyX, float EnemyY, float EnemyW, float EnemyH);

	bool IsEVisibleFlag() { return EVisibleFlag; }
};