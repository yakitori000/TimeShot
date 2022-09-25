#pragma once
#include"DxLib.h"
#include "shot.h"
#include "Item.h"
#include "map.h"
#include "Music.h"
#include "collision.h"

class Shot;
class Item;
class Music;

//プレイヤー
class Player
{
public:

	const int animDown					= 0;		// 下方向
	const int animLeft					= 1;		// 左方向
	const int animRight					= 2;		// 右方向
	const int animShotDown				= 3;		// 射撃下方向
	const int animShotLeft				= 4;		// 射撃左方向
	const int animShotRight				= 5;		// 射撃右方向
	const int animStopShotLeft			= 6;		// 停止射撃左方向
	const int animStopShotRight			= 7;		// 停止射撃右方向
	const int animGetDown				= 8;		// 獲得ポーズ

	const float animationFPS			= 6.0f;		// 秒間 6コマのアニメーション
	const float moveSpeed				= 200.0f;	// 移動速度 (ここで指定した値分のピクセル/秒進む) 
	const float maxMoveSpeed			= 300.0f;	// 最大横移動速度
	const float moveAccell				= 1.5f;		// 移動加速度
	const float frictionRatio			= 0.98f;	// 摩擦係数
	const float brakeRatio				= 0.95f;	// 進行方向に対して入力逆方向に入れたときのブレーキ係数
	const float inAirMoveAccelRatio		= 0.8f;		// 空中横移動加速率
	const float jumpInitalVelocity		= 5.5f;		// ジャンプ初速度
	const float jumpUpSpeed				= 9.0f;		// ジャンプ長押し中上昇速度
	const float hitHeadBrakeRatio		= -0.1f;	// 頭上衝突時の減速率

	const int   imageSizeX				= 64;		// 画像横サイズ
	const int   imageSizeY				= 96;		// 画像縦サイズ
	const int   hitSizeX				= 40;		// 当たり判定サイズ幅
	const int   hitSizeY				= 60;		// 当たり判定サイズ高さ

	const int   colliderOffset			= 10;		// コライダー左右ずらし量
	const float gravity					= 15.0f;	// 重力
	const float maxFallSpeed			= 300.0f;	// 最大落下速度
	const float jumpButtonAcceptTime	= 0.95f;	// ジャンプ長押し受付時間

	int   HitPoint;									// プレイヤーの体力
	float animTimer;								// アニメーションタイマー
	int   animNowType;								// 現在のアニメ種類
	int   animNowPattern;							// 現在のアニメパターン
	int   animNowIndex;								// アニメーション画像配列の添え字 0～11までの数値
	int   drawOffsetX;								// 当たり判定からの横方向ずらし量
	int   drawOffsetY;								// 当たり判定からの縦方向ずらし量

	bool sideFlag;									// 右向いているか
	bool GetFlag;									// アイテム獲得できるか
	bool DamegeFlag;								// ダメージを食らっているか
	int	 DamageCounter;								// ダメージ数
	int	 DamageGraph;								// ダメージ画像

	bool  jumpFlag;									// ジャンプフラグ
	bool  onGround;									// 地面に立っているか
	bool  hitHead;									// 頭がぶつかっているか
	float jumpTimer;								// ジャンプ長押し時間タイマー

	float px, py;									// プレイヤーの座標
	float vx, vy;									// プレイヤーの速度
	int w;											// 画像の幅
	int h;											// 画像の高さ
	int count;										// 弾数カウント
	int ScoreCount;									// ゲームスコア
	int graph;										// 画像サイズ
	int ShotIntervalCount;							// 前フレームでショットされていたか

	//効果音
	int ShotSound;			//発射音
	int OutBulletSound;		//弾切れ音

	/// <summary>
	/// プレイヤー初期化
	/// </summary>
	void Init();

	/// <summary>
	/// プレイヤー更新
	/// </summary>
	/// <param name="deltaTime">1フレーム分の処理時間</param>
	void Update( Shot shot[], int shotnum, Item &item,Music &music, float deltaTime);

	/// <summary>
	/// プレイヤー描画
	/// </summary>
	void Draw();

	/// <summary>
	/// プレイヤー後始末
	/// </summary>
	void Finalize();

	void DrawShot(Shot shot);		//銃関連のサウンド再生

	/// <summary>
	/// プレイヤーの当たり判定矩形を返す
	/// </summary>
	/// <returns>プレイヤーの当たり判定矩形</returns>
	sHitRect getHitRect();

	/// <summary>
	/// 当たり判定矩形からプレイヤー位置を修正する
	/// </summary>
	/// <param name="hitRect">当たり判定矩形</param>
	void fixColPosition(sHitRect& hitRect);

	/// <summary>
	/// エネミーに当たっているか
	/// </summary>
	void OnHitEnemy(int enemyX, int enemyY, int enemyW, int enemyH);

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
	/// プレイヤーの足元コライダーのゲット
	/// </summary>
	/// <returns>足元コライダーの矩形情報</returns>
	sHitRect GetGroundCollider();

	/// <summary>
	/// プレイヤーの頭上コライダーのゲット
	/// </summary>
	/// <returns>頭上コライダーの矩形情報</returns>
	sHitRect GetHeadCollider();

	bool GetHitPoint()const { return HitPoint; }
	bool inputMove(float deltaTime);
};



