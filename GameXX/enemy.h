#pragma once

#include "DxLib.h"

#define ENEMY_LIFE		80
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
	//float	x1;
	//float	y1;
	//int		w1;
	//int		h1;
	//float	vx1, vy1;
	//int		count1;						//残り弾数カウント
	//int		ShotTimeCount1;				//発射時間カウント

	//float	x2;
	//float	y2;
	//int		w2;
	//int		h2;
	//float	vx2, vy2;

	//float	x3;
	//float	y3;
	//int		w3;
	//int		h3;
	//float	vx3, vy3;

	float	x[ENEMY_NUM];
	float	y[ENEMY_NUM];
	int 	w[ENEMY_NUM];
	int 	h[ENEMY_NUM];
	float	vx[ENEMY_NUM], vy[ENEMY_NUM];
	int		count[ENEMY_NUM];							//残り弾数カウント
	int		ShotTimeCount[ENEMY_NUM];					//発射時間カウント

	int		Graph[ENEMY_NUM];							// 通常画像
	int		DamageGraph[ENEMY_NUM];						// ダメージ画像
	bool	DamageFlag[ENEMY_NUM];						// ダメージ受けたか
	int		DamageCounter[ENEMY_NUM];					// ダメージ数

	bool	LivFlag[ENEMY_NUM];							// 生きているか
	int		LivCounter[ENEMY_NUM];						// 生存者数
	int		LivGraph[ENEMY_NUM];						// 
	
	bool	IsRightMove[ENEMY_NUM];						// 画面外にださない
	int		DrawOffsetX[ENEMY_NUM];						// 当たり判定からの横方向ずらし量
	int		DrawOffsetY[ENEMY_NUM];						// 当たり判定からの縦方向ずらし量

	//int num[ENEMY_NUM];
	//float x[ENEMY_NUM];
	//float y[ENEMY_NUM];
	//float PosX[ENEMY_NUM] = {};
	//float PosY[ENEMY_NUM] = {};

	//int		Graph1;										// 通常画像
	//int		DamageGraph1;								// ダメージ画像
	//bool	DamageFlag1;								// ダメージ受けたか
	//int		DamageCounter1;								// ダメージ数

	//int		Graph2;										// 通常画像
	//int		DamageGraph2;								// ダメージ画像
	//bool	DamageFlag2;								// ダメージ受けたか
	//int		DamageCounter2;								// ダメージ数

	//int		Graph3;										// 通常画像
	//int		DamageGraph3;								// ダメージ画像
	//bool	DamageFlag3;								// ダメージ受けたか
	//int		DamageCounter3;								// ダメージ数

	//bool	LivFlag1;									// 生きているか
	//int		LivCounter1;								// 生存者数
	//int		LivGraph1;									// 

	//bool	LivFlag2;									// 生きているか
	//int		LivCounter2;								// 生存者数
	//int		LivGraph2;									// 

	//bool	LivFlag3;									// 生きているか
	//int		LivCounter3;								// 生存者数
	//int		LivGraph3;									// 
	//
	//bool	IsRightMove1;								// 画面外にださない
	//int		DrawOffsetX1;								// 当たり判定からの横方向ずらし量
	//int		DrawOffsetY1;								// 当たり判定からの縦方向ずらし量

	//bool	IsRightMove2;								// 画面外にださない
	//int		DrawOffsetX2;								// 当たり判定からの横方向ずらし量
	//int		DrawOffsetY2;								// 当たり判定からの縦方向ずらし量

	//bool	IsRightMove3;								// 画面外にださない
	//int		DrawOffsetX3;								// 当たり判定からの横方向ずらし量
	//int		DrawOffsetY3;								// 当たり判定からの縦方向ずらし量
	
	const int		imageSizeX	= 64;					// 画像横サイズ
	const int		imageSizeY	= 128;					// 画像縦サイズ
	const int		hitSizeX	= 50;					// 当たり判定サイズ幅
	const int		hitSizeY	= 100;					// 当たり判定サイズ高さ

	const float		jumpInitalVelocity	= 10.5f;		// ジャンプ初速度
	const int		colliderOffset		= 10;			// コライダー左右ずらし量
	const float		gravity				= 15.0f;		// 重力
	const float		maxFallSpeed		= 300.0f;		// 最大落下速度
	const float		hitHeadBrakeRatio	= -0.1f;		// 頭上衝突時の減速率

	bool  jumpFlag;							// ジャンプフラグ
	bool  onGround;							// 地面に立っているか
	bool  hitHead;							// 頭が当たったか
	bool  hitPlayerFlag;						// プレイヤーに当たったか
	bool  ShotFlag;							// 発射しているか
	bool  Reverse;							//反転	

	//bool  jumpFlag1;									// ジャンプフラグ
	//bool  onGround1;									// 地面に立っているか
	//bool  hitHead1;										// 頭が当たったか
	//bool  hitPlayerFlag1;								// プレイヤーに当たったか
	//bool  ShotFlag1;									// 発射しているか
	//bool  Reverse1;										//反転	
	//
	//bool  jumpFlag2;									// ジャンプフラグ
	//bool  onGround2;									// 地面に立っているか
	//bool  hitHead2;										// 頭が当たったか
	//bool  hitPlayerFlag2;								// プレイヤーに当たったか
	//bool  Reverse2;										//反転

	//bool  jumpFlag3;									// ジャンプフラグ
	//bool  onGround3;									// 地面に立っているか
	//bool  hitHead3;										// 頭が当たったか	
	//bool  hitPlayerFlag3;								// プレイヤーに当たったか
	//bool  Reverse3;										//反転

public:

	int		life;
	int		life1;										// 敵１の体力
	int		life2;										// 敵２の体力
	int		life3;										// 敵３の体力

	// 初期化
	void Init();
	/*void Init1();
	void Init2();
	void Init3();*/
	
	// アップデート
	void Update(Player player, Music music, ShotEnemy shot[], int shotnum, float deltaTime);
	/*void Update1(Player player, Music music, ShotEnemy shot[], int shotnum, float deltaTime);
	void Update2(Player player, Music music, float deltaTime);
	void Update3(Player player, Music music, float deltaTime);*/

	// 描画
	void Draw();
	/*void Draw1();
	void Draw2();
	void Draw3();
	*/
	void DrawHP(int life1, int MAXlife);

	void OnHitShot(int shotX, int shotY, int shotW, int shotH, bool visibleFlag);
	/*void OnHitShot1(int shotX, int shotY, int shotW, int shotH, bool visibleFlag);
	void OnHitShot2(int shotX, int shotY, int shotW, int shotH, bool visibleFlag);
	void OnHitShot3(int shotX, int shotY, int shotW, int shotH, bool visibleFlag);*/

	//bool GetPosX()const { return PosX; }
	//bool GetPosY()const { return PosY; }
	//bool GetScore()const { return Score; }


	bool GetLife()const { return life; }
	
	bool GetX() const { return x; }
	bool GetY() const { return y; }
	bool GetW() const { return w; }
	bool GetH() const { return h; }

	bool GetReverse() const { return Reverse; }

	/*bool GetLife1()const { return life1; }
	bool GetLife2()const { return life2; }
	bool GetLife3()const { return life3; }

	bool GetX1() const { return x1; }
	bool GetY1() const { return y1; }
	bool GetW1() const { return w1; }
	bool GetH1() const { return h1; }

	bool GetReverse1() const { return Reverse1; }*/


	//<summary>
	//エネミーの当たり判定矩形を返す
	//</summary>
	//<returns>当たり判定矩形</returns>
	sHitRect getHitRect();

	//<summary>
	//エネミーの当たり判定矩形を返す
	//</summary>
	//<returns>当たり判定矩形</returns>
	//sHitRect getHitRect1();

	//<summary>
	//エネミーの当たり判定矩形を返す
	//</summary>
	//<returns>当たり判定矩形</returns>
	//sHitRect getHitRect2();

	//<summary>
	//エネミーの当たり判定矩形を返す
	//</summary>
	//<returns>当たり判定矩形</returns>
	//sHitRect getHitRect3();

	//<summary>
//当たり判定の位置修正
//</summary>
//<param name="hitRect">当たり判定矩形</param>
	void fixColPosition(sHitRect& hitRect);

	//<summary>
	//当たり判定の位置修正
	//</summary>
	//<param name="hitRect">当たり判定矩形</param>
	//void fixColPosition1(sHitRect& hitRect);

	//<summary>
	//当たり判定の位置修正
	//</summary>
	//<param name="hitRect">当たり判定矩形</param>
	//void fixColPosition2(sHitRect& hitRect);

	//<summary>
	//当たり判定の位置修正
	//</summary>
	//<param name="hitRect">当たり判定矩形</param>
	//void fixColPosition3(sHitRect& hitRect);

	//<summary>
	//足元当たり判定
	//</summary>
	//<param name="groundFlg">足元の当たり判定結果</param>
	void SetGroundFlag(bool groundFlag);

	//<summary>
	//足元当たり判定
	//</summary>
	//<param name="groundFlg">足元の当たり判定結果</param>
	//void SetGroundFlag1(bool groundFlag);

	//<summary>
	//足元当たり判定
	//</summary>
	//<param name="groundFlg">足元の当たり判定結果</param>
	//void SetGroundFlag2(bool groundFlag);

	//<summary>
	//足元当たり判定
	//</summary>
	//<param name="groundFlg">足元の当たり判定結果</param>
	//void SetGroundFlag3(bool groundFlag);
	
	//<summary>
	//頭の当たり判定
	//</summary>
	//<param name="headHitFlg">頭の当たり判定結果</param>
	void SetHeadHitFlag(bool headHitFlag);

	//<summary>
	//頭の当たり判定
	//</summary>
	//<param name="headHitFlg">頭の当たり判定結果</param>
	//void SetHeadHitFlag1(bool headHitFlag);

	//<summary>
	//頭の当たり判定
	//</summary>
	//<param name="headHitFlg">頭の当たり判定結果</param>
	//void SetHeadHitFlag2(bool headHitFlag);

	// <summary>
	// 頭の当たり判定
	// </summary>
	// <param name="headHitFlg">頭の当たり判定結果</param>
	//void SetHeadHitFlag3(bool headHitFlag);


	//<summary>
	//足元コライダー取得
	//</summary>
	//<returns>足元コライダーの矩形情報</returns>
	sHitRect GetGroundCollider();

	//<summary>
	//足元コライダー取得
	//</summary>
	//<returns>足元コライダーの矩形情報</returns>
	//sHitRect GetGroundCollider1();

	//<summary>
	//足元コライダー取得
	//</summary>
	//<returns>足元コライダーの矩形情報</returns>
	//sHitRect GetGroundCollider2();

	//<summary>
	//足元コライダー取得
	//</summary>
	//<returns>足元コライダーの矩形情報</returns>
	//sHitRect GetGroundCollider3();

	//<summary>
	//頭上コライダー取得
	//</summary>
	//<returns>頭上コライダーの矩形情報</returns>
	sHitRect GetHeadCollider();

	//<summary>
	//頭上コライダー取得
	//</summary>
	//<returns>頭上コライダーの矩形情報</returns>
	//sHitRect GetHeadCollider1();

	//<summary>
	//頭上コライダー取得
	//</summary>
	//<returns>頭上コライダーの矩形情報</returns>
	//sHitRect GetHeadCollider2();

	//<summary>
	//頭上コライダー取得
	//</summary>
	//<returns>頭上コライダーの矩形情報</returns>
	//sHitRect GetHeadCollider3();
	
};