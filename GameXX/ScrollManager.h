#pragma once
#include "collision.h"


class Scroll
{
public:

    float scrollX;     // スクロールX方向値
    float scrollY;     // スクロールY方向値

    float screenXMax;  // スクリーン上の右スクロール開始境界値
    float screenYMin;  // スクリーン上の上スクロール開始境界値
    float screenYMax;  // スクリーン上の下スクロール開始境界値

    int screenWidth; // スクリーン幅
    int screenHeight;// スクリーン高さ

    float scrollXMax;   // ステージ全体のX方向最大値
    float scrollYMin;   // ステージ全体のY方向最小値
    float scrollYMax;   // ステージ全体のY方向最大値

    float dx;
    float dy;

    const float scrollSpeed = 5.0f;

    /// <summary>
    /// スクロールマネージャ初期化
    /// </summary>
    /// <param name="windowWidth">ウィンドウの幅ドット数</param>
    /// <param name="windowHeight">ウィンドウの高さドット数</param>
    /// <param name="worldRect">ステージ全体の矩形</param>
    void Init(int screenWidth, int screenHeight, const sHitRect& worldRect);

    /// <summary>
    /// スクロールの更新処理
    /// </summary>
    /// <param name="playerRect">スクロールの中心となるキャラクター矩形</param>
    /// <param name="deltaTime">ウィンドウ更新時間</param>
    void Update(const sHitRect& playerRect, float deltaTime);

    /// <summary>
    /// スクロールの描画オフセットXを取得
    /// </summary>
    /// <returns>x方向オフセット</returns>
    int GetDrawOffsetX();

    /// <summary>
    /// スクロールの描画オフセットYを取得
    /// </summary>
    /// <returns>y方向オフセット</returns>
    int GetDrawOffsetY();

    /// <summary>
    /// スクロールのデバッグ情報表示
    /// </summary>
    void DebugShow();
};

