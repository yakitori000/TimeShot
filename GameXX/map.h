//#pragma once
//#include <DxLib.h>
//#include "collision.h"
//
///// <summary>
///// マップデータ構造体
///// </summary>
//class sMapLayer
//{
//public:
//	int** mapData;	//マップチップの二次元配列
//	int   mapXNum;	//マップチップが横方向に並んでいる数
//	int   mapYNum;	//マップチップが縦方向に並んでいる数
//
//	
//
//	/// <summary>
///// マップ初期化
///// </summary>
//	void Init();
//
//	/// <summary>
//	/// マップ描画
//	/// </summary>
//	void Draw();
//
//	/// <summary>
//	/// マップ後始末
//	/// </summary>
//	void Finalize();
//
//	/// <summary>
//	/// マップ後始末
//	/// </summary>
//	/// <param name ="checkRect">マップと当たっているか調査したい矩形</param>
//	/// <returns>マップと衝突したかをtrue/falseで返す</returns>
//	bool HitCalc(sHitRect& checkRect);
//
//	/// <summary>
//	/// マップのインデックス位置からブロック番号を返す
//	/// </summary>
//	/// <param name ="ix">マップのインデックス番号x</param>
//	/// <param name ="iy">マップのインデックス番号y</param>
//	/// <returns>マップのブロック番号を返す</returns>
//	unsigned char GetBlockType(int ix, int iy);
//
//	/// <summary>
//	/// 座標位置からブロック番号を返す
//	/// </summary>
//	/// <param name ="ix">x座標</pram>
//	/// <param name ="iy".y座標</pram>
//	/// <returns>マップのブロック番号を返す</returns>
//	unsigned char GetBlockTypeXY(int x, int y);
//
//	/// <summary>
///// マップローダー
///// </summary>
///// <param name="dst">初期化したいマップデータ</param>
///// <param name="mapCSVFileName">マップファイル名</param>
///// <returns>読み込みに成功したかをtrue falseで返却</returns>
//	bool LayerLoader(sMapLayer& dst, const char* mapCSVFileName);
//
//	/// <summary>
//	/// マップの破棄
//	/// </summary>
//	/// <param name="dst">メモリ開放したいマップデータ</param>
//	void Unloader(sMapLayer& dst);
//
//	/// <summary>
//	/// マップのレイヤーを描画
//	/// </summary>
//	/// <param name="layer">描画したいレイヤー</param>
//	void LayerDraw(sMapLayer& layer);
//};

#pragma once
#include <DxLib.h>
#include "collision.h"

/// <summary>
/// マップデータ構造体
/// </summary>
class sMapLayer
{
public:
	int** mapData; // マップチップの2次元配列
	int   mapXNum; // マップチップが横方向に並んでいる数
	int   mapYNum; // マップチップが縦方向に並んでいる数

	/// <summary>
/// マップ初期化
/// </summary>
	void Init();

	/// <summary>
	/// マップ描画
	/// </summary>
	void Draw(int scrollOffsetX, int scrollOffsetY);

	/// <summary>
	/// マップ後始末
	/// </summary>
	void Finalize();

	/// <summary>
	/// マップ後始末
	/// </summary>
	/// <param name ="checkRect">マップと当たっているか調査したい矩形</param>
	/// <returns>マップと衝突したかをtrue/falseで返す</returns>
	bool HitCalc(sHitRect& checkRect);

	/// <summary>
	/// 座標位置からブロック番号を返す
	/// </summary>
	/// <param name ="ix">x座標</param>
	/// <param name ="iy">y座標</param>
	/// <returns>マップのブロック番号を返す</returns>
	unsigned char GetBlockTypeXY(int x, int y);

	/// <summary>
	/// マップローダー
	/// </summary>
	/// <param name="dst">初期化したいマップデータ</param>
	/// <param name="mapCSVFileName">マップファイル名</param>
	/// <returns>読み込みに成功したかをtrue falseで返却</returns>
	bool LayerLoader(sMapLayer& dst, const char* mapCSVFileName);

	/// <summary>
	/// マップの破棄
	/// </summary>
	/// <param name="dst">メモリ開放したいマップデータ</param>
	void Unloader(sMapLayer& dst);

	/// <summary>
	/// マップのレイヤーを描画
	/// </summary>
	/// <param name="layer">描画したいレイヤー</param>
	void LayerDraw(sMapLayer& layer, int scrollOffsetX, int scrollOffsetY);
};

