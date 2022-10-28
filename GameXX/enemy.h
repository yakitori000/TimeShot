#pragma once

#include "DxLib.h"


#define ENEMY_LIFE		10
#define ENEMY_NUM		5
#define ENEMY_MAXX		1900
#define ENEMY_MAXY		600
#define ENEMY_SPEED		3
#define ENEMY_SHOTTIME  60

class Player;
class Music;
class ShotEnemy;
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
	int		count1;						//残り弾数カウント
	int		ShotTimeCount1;				//発射時間カウント

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

	/*float PosX[ENEMY_NUM] = {};
	float PosY[ENEMY_NUM] = {};*/

	int		graph1;										// 通常画像
	int		damageGraph1;								// ダメージ画像
	bool	damageFlag1;								// ダメージ食らってるか
	int		damageCounter1;								// ダメージ数

	int		graph3;										// 通常画像
	int		damageGraph3;								// ダメージ画像
	bool	damageFlag3;								// ダメージ食らってるか
	int		damageCounter3;								// ダメージ数

	int		graph2;										// 通常画像
	int		damageGraph2;								// ダメージ画像
	bool	damageFlag2;								// ダメージ食らってるか
	int		damageCounter2;								// ダメージ数

	bool	LivFlag1;									// 生きているか
	int		LivCounter1;									// 生存者数
	int		LivGraph1;									// 

	bool	LivFlag2;									// 生きているか
	int		LivCounter2;									// 生存者数
	int		LivGraph2;									// 

	bool	LivFlag3;									// 生きているか
	int		LivCounter3;									// 生存者数
	int		LivGraph3;									// 
	
	bool	isRightMove1;								// 画面外にださない
	int		drawOffsetX1;								// 当たり判定からの横方向ずらし量
	int		drawOffsetY1;								// 当たり判定からの縦方向ずらし量

	bool	isRightMove2;								// 画面外にださない
	int		drawOffsetX2;								// 当たり判定からの横方向ずらし量
	int		drawOffsetY2;								// 当たり判定からの縦方向ずらし量

	bool	isRightMove3;								// 画面外にださない
	int		drawOffsetX3;								// 当たり判定からの横方向ずらし量
	int		drawOffsetY3;								// 当たり判定からの縦方向ずらし量

	const int		imageSizeX1				= 64;		// 画像横サイズ
	const int		imageSizeY1				= 128;		// 画像縦サイズ
	const int		hitSizeX1				= 50;		// 当たり判定サイズ幅
	const int		hitSizeY1				= 100;		// 当たり判定サイズ高さ

	const int		imageSizeX2				= 64;		// 画像横サイズ
	const int		imageSizeY2				= 128;		// 画像縦サイズ
	const int		hitSizeX2				= 50;		// 当たり判定サイズ幅
	const int		hitSizeY2				= 100;		// 当たり判定サイズ高さ

	const int		imageSizeX3				= 64;		// 画像横サイズ
	const int		imageSizeY3				= 128;		// 画像縦サイズ
	const int		hitSizeX3				= 50;		// 当たり判定サイズ幅
	const int		hitSizeY3				= 100;		// 当たり判定サイズ高さ

	const float		jumpInitalVelocity1		= 10.5f;	// ジャンプ初速度
	const int		colliderOffset1			= 10;		// コライダー左右ずらし量
	const float		gravity1				= 15.0f;	// 重力
	const float		maxFallSpeed1			= 300.0f;	// 最大落下速度
	const float		hitHeadBrakeRatio1		= -0.1f;	// 頭上衝突時の減速率
	
	const float		jumpInitalVelocity2		= 11.0f;	// ジャンプ初速度
	const int		colliderOffset2			= 10;		// コライダー左右ずらし量
	const float		gravity2				= 15.0f;	// 重力
	const float		maxFallSpeed2			= 300.0f;	// 最大落下速度
	const float		hitHeadBrakeRatio2		= -0.1f;	// 頭上衝突時の減速率

	const float		jumpInitalVelocity3		= 11.5f;	// ジャンプ初速度
	const int		colliderOffset3			= 10;		// コライダー左右ずらし量
	const float		gravity3				= 15.0f;	// 重力
	const float		maxFallSpeed3			= 300.0f;	// 最大落下速度
	const float		hitHeadBrakeRatio3		= -0.1f;    // 頭上衝突時の減速率


	bool  jumpFlag1;									// ジャンプフラグ
	bool  onGround1;									// 地面に立っているか
	bool  hitHead1;										// 頭が当たったか
	bool  hitPlayerFlag1;								// プレイヤーに当たったか
	bool  ShotFlag1;									// 発射しているか
	bool  ShotCounter;									// 発射タイミング
	bool  Reverse1;										//反転	
	
	bool  jumpFlag2;									// ジャンプフラグ
	bool  onGround2;									// 地面に立っているか
	bool  hitHead2;										// 頭が当たったか
	bool  hitPlayerFlag2;								// プレイヤーに当たったか
	bool  Reverse2;										//反転

	bool  jumpFlag3;									// ジャンプフラグ
	bool  onGround3;									// 地面に立っているか
	bool  hitHead3;										// 頭が当たったか	
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
	void Update1(Player player, Music music, ShotEnemy shot[], int shotnum, float deltaTime);
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

	//bool GetPosX()const { return PosX; }
	//bool GetPosY()const { return PosY; }
	//bool GetScore()const { return Score; }
	
	bool GetLife1()const { return life1; }
	bool GetLife2()const { return life2; }
	bool GetLife3()const { return life3; }

	bool GetX1() const { return x1; }
	bool GetY1() const { return y1; }
	bool GetW1() const { return w1; }
	bool GetH1() const { return h1; }

	bool GetReverse1() const { return Reverse1; }

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


