
#include "collision.h"

void initRect(sHitRect& dstRect, float w, float h)
{
	dstRect.w = w;
	dstRect.h = h;

	dstRect.worldLX = 0.0f;
	dstRect.worldRX = w;
	dstRect.worldLY = 0.0f;
	dstRect.worldRY = h;
}

void updateWorldRect(sHitRect& dstRect, float x, float y)
{
	dstRect.worldLX = x;
	dstRect.worldRX = x + dstRect.w;
	dstRect.worldLY = y;
	dstRect.worldRY = y + dstRect.h;
}

bool isHitRect(const sHitRect& rect1, const sHitRect& rect2)
{
	// 二つの矩形の当たり判定の公式より
	return (rect1.worldLX < rect2.worldRX&&
			rect2.worldLX < rect1.worldRX&&
			rect1.worldLY < rect2.worldRY&&
			rect2.worldLY < rect1.worldRY);
}

void calcFixHitRectPosition(sHitRect& movableRect, const sHitRect& staticRect)
{
	//上下左右の押し戻し距離を計算
	float left	= staticRect.worldLX - movableRect.worldRX;
	float right = staticRect.worldRX - movableRect.worldLX;
	float up	= staticRect.worldLY - movableRect.worldRY;
	float down  = staticRect.worldRY - movableRect.worldLY;

	// fabs() はカッコ内の変数の絶対値を求める関数
	// dx は x方向の最短押し戻し移動量
	// dy は y方向の最短押し戻し移動を求める
	float dx = (fabs(left) < fabs(right)) ? left : right;		//絶対値を求める関数
	float dy = (fabs(up) < fabs(down)) ? up : down;

	// x方向、y方向の最短押し戻し距離を比較し、最短で戻せる方で戻す
	if (fabs(dx) < fabs(dy))
	{
		movableRect.worldLX += dx;
		movableRect.worldRX += dx;
	}
	else
	{
		movableRect.worldLY += dy;
		movableRect.worldRY += dy;
	}
}


void calcFixHitRectPosition(sHitRect& movableRect, const sHitRect& staticRect, BlockInfo blockinfo)
{
	// ブロック情報から壁が存在しないとき、わざと大きな押し戻し量を設定し以降の最小値を選ぶ候補から外されるようにする。
	//上下左右の押し戻し距離を計算
	float left	 = staticRect.worldLX - movableRect.worldRX;
	float right	 = staticRect.worldRX - movableRect.worldLX;
	float up	 = staticRect.worldLY - movableRect.worldRY;
	float down	 = staticRect.worldRY - movableRect.worldLY;

	if (!(blockinfo & BLOCK_LEFT))
	{
		left = -staticRect.w;
	}
	if (!(blockinfo & BLOCK_RIGHT))
	{
		right = staticRect.w;
	}
	if (!(blockinfo & BLOCK_UP))
	{
		up = -staticRect.h;
	}
	if (!(blockinfo & BLOCK_DOWN))
	{
		down = staticRect.h;
	}

	// fabs() はカッコ内の変数の絶対値を求める関数
	// dx は x方向の最短押し戻し移動量
	// dy は y方向の最短押し戻し移動を求める
	float dx = (fabs(left) < fabs(right)) ? left : right;		//絶対値を求める関数
	float dy = (fabs(up) < fabs(down)) ? up : down;

	//エラー時、両方とも壁がないときの衝突をした？
	if (fabs(dx) == fabs(dy))
	{
		return;
	}

	//x方向　Y方向の最短押し戻し距離を比較、最短で戻せる方法で戻す
	if (fabs(dx) < fabs(dy))
	{
		movableRect.worldLX += dx;
		movableRect.worldRX += dx;
	}
	else
	{
		movableRect.worldLY += dy;
		movableRect.worldRY += dy;
	}
}
