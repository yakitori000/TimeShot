#pragma once


#include "DxLib.h"
#include "Player.h"
#include "enemy.h"
#include "collision.h"
#include "function.h"

#define SHOT			20		//ショット最大数
#define SHOT_SPEED		20		//通常ショットスピード
#define SHOT_INTERVAL	3		//通常ショット発射インターバル

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
	/// プレイヤー弾初期化
	/// </summary>
	void Init();

	/// <summary>
	/// プレイヤー弾更新
	/// </summary>
	void Update(Player& player, Enemy& enemy);

	/// <summary>
	/// プレイヤー弾描画
	/// </summary>
	void Draw(Player& player);

	/// <summary>
	/// プレイヤー弾の座標セット
	/// </summary>
	void OnShot(float PlayerX, float PlayerY, float PlayerW, float PlayerH);

	bool IsVisibleFlag() { return visibleFlag; }
};