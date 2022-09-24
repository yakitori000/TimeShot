#pragma once
#include "DxLib.h"
#include <math.h>

/// <summary>
/// 当たり判定短形
/// </summary>
struct sHitRect
{
	float w;			//当たり短形幅ピクセル数
	float h;			//当たり短形高さピクセル数
	float worldLX;		//左上Ｘ座標
	float worldLY;		//左上Ｙ座標
	float worldRX;		//右上Ｘ座標
	float worldRY;		//右上Ｙ座標

};

//ブロック壁情報
#define BLOCK_LEFT	0x01	// 0001
#define BLOCK_RIGHT	0x02	// 0010
#define BLOCK_UP	0x04	// 0100
#define BLOCK_DOWN	0x08	// 1000

/// <summary>
/// ブロック壁情報型
/// </summary>
typedef unsigned char BlockInfo;

/// <summary>
/// 当たり判定初期化
/// </summary>
/// <param name="dstRect">初期化したい当たり判定変数</param>
/// <param name="W">当たり判定の幅</param>
/// <param name="W">当たり判定の高さ</param>
void initRect(sHitRect& dstRect, float w, float h);

/// <summary>
/// 当たり判定の移動更新処理
/// </summary>
/// <param name="dstRect">更新したい当たり判定変数</param>
/// <param name="X">当たり判定左上x座標</parma>
/// <param name="Y">当たり判定左上y座標</parma>
void updateWorldRect(sHitRect& dstRect, float x, float y);

/// <summary>
/// 当たり判定の短形の描画
/// </summary>
/// <param name="rect">描画したい当たり判定短形</param>
//void drawRect(const sHitRect& rect);

/// <summary>
/// 二つの矩形が衝突したかを返す
/// </summary>
/// <param name="rect1">矩形1</param>
/// <param name="rect2">矩形2</param>
/// <returns>矩形の二つが衝突したかをtrue/falseで返す</returns>
bool isHitRect(const sHitRect& rect1, const sHitRect& rect2);

///// <summary>
/// 2つの矩形の衝突めり込み量を計算し、mobableRect位置を変更する
/// </summary>
/// <param name="movableRect">移動可能矩形</param>
/// <param name="staticRect">静止矩形(動かないブロックなど)</param>
void calcFixHitRectPosition(sHitRect& movableRect, const sHitRect& staticRect);

/// <summary>
/// 2つの矩形の衝突めり込み量を計算し、mobableRect位置を変更する
/// </summary>
/// <param name="movableRect">移動可能矩形</param>
/// <param name="staticRect">静止矩形(動かないブロックなど)</param>
/// <param name="blockInfo">ブロック情報</param>
void calcFixHitRectPosition(sHitRect& movableRect, const sHitRect& staticRect, BlockInfo blockinfo);