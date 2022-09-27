#pragma once

#include "DxLib.h"
#include "Player.h"
#include "Music.h"
#include "map.h"
#include "function.h"
#include "collision.h"

#define ENEMY_LIFE		10
#define ENEMY_NUM		5
#define ENEMY_MAXX		1900
#define ENEMY_MAXY		600


class Player;
class Music;
struct sHitRect;



// エネミー.
class Enemy
{
private:
	/*float x[ENEMY_NUM];
	float y[ENEMY_NUM];*/
	float	x;
	float	y;
	int		w;
	int		h;
	float	vx, vy;
	int		graph;

	int num[ENEMY_NUM];


	float PosX[ENEMY_NUM] = {};
	float PosY[ENEMY_NUM] = {};

	bool	damageFlag;									// ダメージ食らってるか
	int		damageCounter;								// ダメージ数
	int		damageGraph;								// ダメージ画像

	bool	LivFlag;									// 生きているか
	int		LivCounter;									// 生存者数
	int		LivGraph;									// 
	
	int		Score;

	bool	isRightMove;								// 画面外にださない
	int		drawOffsetX;								// 当たり判定からの横方向ずらし量
	int		drawOffsetY;								// 当たり判定からの縦方向ずらし量

	const int		imageSizeX				= 64;       // 画像横サイズ
	const int		imageSizeY				= 128;      // 画像縦サイズ
	const int		hitSizeX				= 50;       // 当たり判定サイズ幅
	const int		hitSizeY				= 100;       // 当たり判定サイズ高さ

	const float		moveSpeed				= 200.0f;   // 移動速度 (ここで指定した値分のピクセル/秒進む) 
	const float		maxMoveSpeed			= 300.0f;   // 最大横移動速度
	const float		moveAccell				= 1.5f;     // 移動加速度
	const float		frictionRatio			= 0.98f;    // 摩擦係数
	const float		brakeRatio				= 0.95f;    // 進行方向に対して入力逆方向に入れたときのブレーキ係数
	const float		inAirMoveAccelRatio		= 0.8f;     // 空中横移動加速率
	const float		jumpInitalVelocity		= 10.5f;     // ジャンプ初速度
	const float		jumpUpSpeed				= 9.0f;     // ジャンプ長押し中上昇速度

	const int		colliderOffset			= 10;		// コライダー左右ずらし量
	const float		gravity					= 15.0f;	// 重力
	const float		maxFallSpeed			= 300.0f;	// 最大落下速度
	const float		hitHeadBrakeRatio		= -0.1f;    // 頭上衝突時の減速率

	bool  jumpFlag;										// ジャンプフラグ
	bool  onGround;										// 地面に立っているか
	bool  hitHead;										// 頭が当たったか	
	bool  hitWool;										// 壁に当たったか
	bool  hitPlayerFlag;								// プレイヤーに当たったか
	bool  Reverse;										//反転

public:

	int		life;										// 体力

	// 初期化.
	void Init();

	// アップデート.
	void Update(Player player, Music music, float deltaTime);

	// 描画.
	void Draw();
	void OnHitShot(int shotX, int shotY, int shotW, int shotH, bool visibleFlag);
	void setPosition(float x, float y, int num);

	bool GetPosX()const { return PosX; }
	bool GetPosY()const { return PosY; }
	bool GetScore()const { return Score; }
	bool GetLife()const { return life; }

	/// <summary>
	/// エネミーの当たり判定矩形を返す
	/// </summary>
	/// <returns>当たり判定矩形</returns>
	sHitRect getHitRect();

	/// <summary>
	/// 当たり判定矩形から位置を修正する
	/// </summary>
	/// <param name="hitRect">当たり判定矩形</param>
	void fixColPosition(sHitRect& hitRect);

	/// <summary>
	/// 地面に立っているか？
	/// </summary>
	/// <param name="groundFlg">足元の当たり判定結果</param>
	void SetGroundFlag(bool groundFlag);

	/// <summary>
	/// 頭を壁にぶつけたか
	/// </summary>
	/// <param name="headHitFlg">頭の当たり判定結果</param>
	void SetHeadHitFlag(bool headHitFlag);

	/// <summary>
	/// 足元コライダーのゲット
	/// </summary>
	/// <returns>足元コライダーの矩形情報</returns>
	sHitRect GetGroundCollider();

	/// <summary>
	/// 頭上コライダーのゲット
	/// </summary>
	/// <returns>頭上コライダーの矩形情報</returns>
	sHitRect GetHeadCollider();

};


