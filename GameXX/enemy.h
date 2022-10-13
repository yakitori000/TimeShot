#pragma once

#include "DxLib.h"


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
	float	x1;
	float	y1;
	int		w1;
	int		h1;
	float	vx1, vy1;

	float	x2;
	float	y2;
	int		w2;
	int		h2;
	float	vx2, vy2;

	float	x3;
	float	y3;
	int		w3;
	int		h3;
	float	vx3, vy3;
	
	/*int num[ENEMY_NUM];*/

	float PosX[ENEMY_NUM] = {};
	float PosY[ENEMY_NUM] = {};

	int		graph1;										// 通常画像
	int		damageGraph1;								// ダメージ画像
	
	int		graph2;										// 通常画像
	int		damageGraph2;								// ダメージ画像
	
	int		graph3;										// 通常画像
	int		damageGraph3;								// ダメージ画像

	bool	damageFlag1;								// ダメージ食らってるか
	int		damageCounter1;								// ダメージ数

	bool	damageFlag2;								// ダメージ食らってるか
	int		damageCounter2;								// ダメージ数

	bool	damageFlag3;								// ダメージ食らってるか
	int		damageCounter3;								// ダメージ数
	

	bool	LivFlag1;									// 生きているか
	int		LivCounter1;									// 生存者数
	int		LivGraph1;									// 

	bool	LivFlag2;									// 生きているか
	int		LivCounter2;									// 生存者数
	int		LivGraph2;									// 

	bool	LivFlag3;									// 生きているか
	int		LivCounter3;									// 生存者数
	int		LivGraph3;									// 
	
	int		Score;

	bool	isRightMove1;								// 画面外にださない
	int		drawOffsetX1;								// 当たり判定からの横方向ずらし量
	int		drawOffsetY1;								// 当たり判定からの縦方向ずらし量

	bool	isRightMove2;								// 画面外にださない
	int		drawOffsetX2;								// 当たり判定からの横方向ずらし量
	int		drawOffsetY2;								// 当たり判定からの縦方向ずらし量

	bool	isRightMove3;								// 画面外にださない
	int		drawOffsetX3;								// 当たり判定からの横方向ずらし量
	int		drawOffsetY3;								// 当たり判定からの縦方向ずらし量

	const int		imageSizeX1				= 64;       // 画像横サイズ
	const int		imageSizeY1				= 128;      // 画像縦サイズ
	const int		hitSizeX1				= 50;       // 当たり判定サイズ幅
	const int		hitSizeY1				= 100;       // 当たり判定サイズ高さ

	const int		imageSizeX2				= 64;       // 画像横サイズ
	const int		imageSizeY2				= 128;      // 画像縦サイズ
	const int		hitSizeX2				= 50;       // 当たり判定サイズ幅
	const int		hitSizeY2				= 100;       // 当たり判定サイズ高さ

	const int		imageSizeX3				= 64;       // 画像横サイズ
	const int		imageSizeY3				= 128;      // 画像縦サイズ
	const int		hitSizeX3				= 50;       // 当たり判定サイズ幅
	const int		hitSizeY3				= 100;       // 当たり判定サイズ高さ

	const float		moveSpeed1				= 200.0f;   // 移動速度 (ここで指定した値分のピクセル/秒進む) 
	const float		maxMoveSpeed1			= 300.0f;   // 最大横移動速度
	const float		moveAccell1				= 1.5f;     // 移動加速度
	const float		frictionRatio1			= 0.98f;    // 摩擦係数
	const float		brakeRatio1				= 0.95f;    // 進行方向に対して入力逆方向に入れたときのブレーキ係数
	const float		inAirMoveAccelRatio1	= 0.8f;     // 空中横移動加速率
	const float		jumpInitalVelocity1		= 10.5f;    // ジャンプ初速度
	const float		jumpUpSpeed1			= 9.0f;     // ジャンプ長押し中上昇速度

	const float		moveSpeed2				= 200.0f;   // 移動速度 (ここで指定した値分のピクセル/秒進む) 
	const float		maxMoveSpeed2			= 300.0f;   // 最大横移動速度
	const float		moveAccell2				= 1.5f;     // 移動加速度
	const float		frictionRatio2			= 0.98f;    // 摩擦係数
	const float		brakeRatio2				= 0.95f;    // 進行方向に対して入力逆方向に入れたときのブレーキ係数
	const float		inAirMoveAccelRatio2	= 0.8f;     // 空中横移動加速率
	const float		jumpInitalVelocity2		= 10.5f;     // ジャンプ初速度
	const float		jumpUpSpeed2			= 9.0f;     // ジャンプ長押し中上昇速度

	const float		moveSpeed3				= 200.0f;   // 移動速度 (ここで指定した値分のピクセル/秒進む) 
	const float		maxMoveSpeed3			= 300.0f;   // 最大横移動速度
	const float		moveAccell3				= 1.5f;     // 移動加速度
	const float		frictionRatio3			= 0.98f;    // 摩擦係数
	const float		brakeRatio3				= 0.95f;    // 進行方向に対して入力逆方向に入れたときのブレーキ係数
	const float		inAirMoveAccelRatio3	= 0.8f;     // 空中横移動加速率
	const float		jumpInitalVelocity3		= 10.5f;     // ジャンプ初速度
	const float		jumpUpSpeed3			= 9.0f;     // ジャンプ長押し中上昇速度

	const int		colliderOffset1			= 10;		// コライダー左右ずらし量
	const float		gravity1				= 15.0f;	// 重力
	const float		maxFallSpeed1			= 300.0f;	// 最大落下速度
	const float		hitHeadBrakeRatio1		= -0.1f;    // 頭上衝突時の減速率

	const int		colliderOffset2			= 10;		// コライダー左右ずらし量
	const float		gravity2				= 15.0f;	// 重力
	const float		maxFallSpeed2			= 300.0f;	// 最大落下速度
	const float		hitHeadBrakeRatio2		= -0.1f;	// 頭上衝突時の減速率

	const int		colliderOffset3			= 10;		// コライダー左右ずらし量
	const float		gravity3				= 15.0f;	// 重力
	const float		maxFallSpeed3			= 300.0f;	// 最大落下速度
	const float		hitHeadBrakeRatio3		= -0.1f;    // 頭上衝突時の減速率

	bool  jumpFlag1;									// ジャンプフラグ
	bool  onGround1;									// 地面に立っているか
	bool  hitHead1;										// 頭が当たったか
	bool  hitWool1;										// 壁に当たったか	
	bool  hitPlayerFlag1;								// プレイヤーに当たったか	
	bool  Reverse1;										//反転	
	
	bool  jumpFlag2;									// ジャンプフラグ
	bool  onGround2;									// 地面に立っているか
	bool  hitHead2;										// 頭が当たったか
	bool  hitWool2;										// 壁に当たったか
	bool  hitPlayerFlag2;								// プレイヤーに当たったか
	bool  Reverse2;										//反転

	bool  jumpFlag3;									// ジャンプフラグ
	bool  onGround3;									// 地面に立っているか
	bool  hitHead3;										// 頭が当たったか	
	bool  hitWool3;										// 壁に当たったか
	bool  hitPlayerFlag3;								// プレイヤーに当たったか
	bool  Reverse3;										//反転

public:

	int		life1;										// 敵１の体力
	int		life2;										// 敵２の体力
	int		life3;										// 敵３の体力

	// 初期化
	void Init1();
	void Init2();
	void Init3();

	// アップデート
	void Update1(Player player, Music music, float deltaTime);
	void Update2(Player player, Music music, float deltaTime);
	void Update3(Player player, Music music, float deltaTime);

	// 描画
	void Draw1();
	void Draw2();
	void Draw3();
	
	void OnHitShot1(int shotX, int shotY, int shotW, int shotH, bool visibleFlag);
	void OnHitShot2(int shotX, int shotY, int shotW, int shotH, bool visibleFlag);
	void OnHitShot3(int shotX, int shotY, int shotW, int shotH, bool visibleFlag);
	
	//void setPosition(float x, float y, int num);

	bool GetPosX()const { return PosX; }
	bool GetPosY()const { return PosY; }
	bool GetScore()const { return Score; }
	bool GetLife1()const { return life1; }
	bool GetLife2()const { return life2; }
	bool GetLife3()const { return life3; }

	/// <summary>
	/// エネミーの当たり判定矩形を返す
	/// </summary>
	/// <returns>当たり判定矩形</returns>
	sHitRect getHitRect1();

	/// <summary>
	/// エネミーの当たり判定矩形を返す
	/// </summary>
	/// <returns>当たり判定矩形</returns>
	sHitRect getHitRect2();

	/// <summary>
	/// エネミーの当たり判定矩形を返す
	/// </summary>
	/// <returns>当たり判定矩形</returns>
	sHitRect getHitRect3();


	/// <summary>
	/// 当たり判定矩形から位置を修正する
	/// </summary>
	/// <param name="hitRect">当たり判定矩形</param>
	void fixColPosition1(sHitRect& hitRect);

	/// <summary>
	/// 当たり判定矩形から位置を修正する
	/// </summary>
	/// <param name="hitRect">当たり判定矩形</param>
	void fixColPosition2(sHitRect& hitRect);

	/// <summary>
	/// 当たり判定矩形から位置を修正する
	/// </summary>
	/// <param name="hitRect">当たり判定矩形</param>
	void fixColPosition3(sHitRect& hitRect);

	/// <summary>
	/// 地面に立っているか？
	/// </summary>
	/// <param name="groundFlg">足元の当たり判定結果</param>
	void SetGroundFlag1(bool groundFlag);

	/// <summary>
	/// 地面に立っているか？
	/// </summary>
	/// <param name="groundFlg">足元の当たり判定結果</param>
	void SetGroundFlag2(bool groundFlag);

	/// <summary>
	/// 地面に立っているか？
	/// </summary>
	/// <param name="groundFlg">足元の当たり判定結果</param>
	void SetGroundFlag3(bool groundFlag);

	/// <summary>
	/// 頭を壁にぶつけたか
	/// </summary>
	/// <param name="headHitFlg">頭の当たり判定結果</param>
	void SetHeadHitFlag1(bool headHitFlag);

	/// <summary>
	/// 頭を壁にぶつけたか
	/// </summary>
	/// <param name="headHitFlg">頭の当たり判定結果</param>
	void SetHeadHitFlag2(bool headHitFlag);

	/// <summary>
	/// 頭を壁にぶつけたか
	/// </summary>
	/// <param name="headHitFlg">頭の当たり判定結果</param>
	void SetHeadHitFlag3(bool headHitFlag);

	/// <summary>
	/// 足元コライダーのゲット
	/// </summary>
	/// <returns>足元コライダーの矩形情報</returns>
	sHitRect GetGroundCollider1();

	/// <summary>
	/// 足元コライダーのゲット
	/// </summary>
	/// <returns>足元コライダーの矩形情報</returns>
	sHitRect GetGroundCollider2();

	/// <summary>
	/// 足元コライダーのゲット
	/// </summary>
	/// <returns>足元コライダーの矩形情報</returns>
	sHitRect GetGroundCollider3();

	/// <summary>
	/// 頭上コライダーのゲット
	/// </summary>
	/// <returns>頭上コライダーの矩形情報</returns>
	sHitRect GetHeadCollider1();

	/// <summary>
	/// 頭上コライダーのゲット
	/// </summary>
	/// <returns>頭上コライダーの矩形情報</returns>
	sHitRect GetHeadCollider2();

	/// <summary>
	/// 頭上コライダーのゲット
	/// </summary>
	/// <returns>頭上コライダーの矩形情報</returns>
	sHitRect GetHeadCollider3();
};


