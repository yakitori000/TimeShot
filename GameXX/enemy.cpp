
#include "Enemy.h"
#include "Player.h"
#include "ShotEnemy.h"
#include "Music.h"
#include "map.h"
#include "function.h"
#include "collision.h"

//敵１
sHitRect hitrect1;
sHitRect enemyHit1;                          // 敵１当たり判定
sHitRect enemyFootCollider1;                 // 接地コライダー
sHitRect enemyHeadCollider1;                 // 頭上コライダー

//敵２
sHitRect hitrect2;
sHitRect enemyHit2;                          // 敵２当たり判定
sHitRect enemyFootCollider2;                 // 接地コライダー
sHitRect enemyHeadCollider2;                 // 頭上コライダー

//敵３
sHitRect hitrect3;
sHitRect enemyHit3;                          // 敵３当たり判定
sHitRect enemyFootCollider3;                 // 接地コライダー
sHitRect enemyHeadCollider3;                 // 頭上コライダー

// 初期化
void Enemy::Init1()
{
	// エネミーのグラフィックをメモリにロード＆表示座標を初期化
	
	Graph1 = LoadGraph("data/image/Zonbi1.png");
	DamageGraph1 = LoadGraph("data/image/Zonbi.png");
	GraphFilter(DamageGraph1, DX_GRAPH_FILTER_HSB, 120, 120, 120, 256);
	
	life1 = ENEMY_LIFE;				//敵1の体力

	x1 = GetRand(ENEMY_MAXX);		//敵1のX座標
	y1 = GetRand(ENEMY_MAXY);		//敵1のY座標
	
	if (x1 >= ENEMY_MAXX)
	{
		x1 == ENEMY_MAXX;
	}
	if (y1 >= ENEMY_MAXY)
	{
		y1 == ENEMY_MAXY;
	}

	// 当たり判定初期化　敵１
	initRect(enemyHit1, hitSizeX1, hitSizeY1);
	initRect(enemyFootCollider1, hitSizeX1 - colliderOffset1, 1);
	initRect(enemyHeadCollider1, hitSizeX1 - colliderOffset1, 1);
	
	// エネミーのグラフィックのサイズを取得
	GetGraphSize(Graph1, &w1, &h1);

	// 描画位置のオフセット値を計算
   // 左右から見てセンター、上下方向は底辺基準となるように計算
	DrawOffsetX1 = (hitSizeX1 - imageSizeX1) / 2;
	DrawOffsetY1 = (hitSizeY1 - imageSizeY1);

	jumpFlag1 = false;
	onGround1 = false;
	hitHead1 = false;
	Reverse1 = false;
	hitPlayerFlag1 = false;
	DamageFlag1 = false;
	ShotFlag1 = false;
	
	LivCounter1 = 0;
	ShotTimeCount1 = 0;
	count1 = ESHOT;
}

void Enemy::Init2()
{
	Graph2 = LoadGraph("data/image/Zonbi2.png");
	DamageGraph2 = LoadGraph("data/image/Zonbi.png");
	GraphFilter(DamageGraph2, DX_GRAPH_FILTER_HSB, 120, 120, 120, 256);

	life2 = ENEMY_LIFE;				//敵2の体力

	x2 = GetRand(ENEMY_MAXX);		//敵2のX座標
	y2 = GetRand(ENEMY_MAXY);		//敵2のY座標

	if (x2 >= ENEMY_MAXX)
	{
		x2 == ENEMY_MAXX;
	}
	if (y2 >= ENEMY_MAXY)
	{
		y2 == ENEMY_MAXY;
	}

	// 当たり判定初期化　敵２
	initRect(enemyHit2, hitSizeX2, hitSizeY2);
	initRect(enemyFootCollider2, hitSizeX2 - colliderOffset2, 1);
	initRect(enemyHeadCollider2, hitSizeX2 - colliderOffset2, 1);

	// エネミーのグラフィックのサイズを取得
	GetGraphSize(Graph2, &w2, &h2);

	// 描画位置のオフセット値を計算
   // 左右から見てセンター、上下方向は底辺基準となるように計算
	DrawOffsetX2 = (hitSizeX2 - imageSizeX2) / 2;
	DrawOffsetY2 = (hitSizeY2 - imageSizeY2);

	jumpFlag2 = false;
	onGround2 = false;
	hitHead2 = false;
	Reverse2 = false;
	hitPlayerFlag2 = false;
	DamageFlag2 = false;
	
	LivCounter2 = 0;
}

void Enemy::Init3()
{
	Graph3 = LoadGraph("data/image/Zonbi3.png");
	DamageGraph3 = LoadGraph("data/image/Zonbi.png");
	GraphFilter(DamageGraph3, DX_GRAPH_FILTER_HSB, 120, 120, 120, 256);

	life3 = ENEMY_LIFE;				//敵3の体力

	x3 = GetRand(ENEMY_MAXX);		//敵3のX座標
	y3 = GetRand(ENEMY_MAXY);		//敵3のY座標

	if (x3 >= ENEMY_MAXX)
	{
		x3 == ENEMY_MAXX;
	}
	if (y3 >= ENEMY_MAXY)
	{
		y3 == ENEMY_MAXY;
	}

	// 当たり判定初期化　敵３
	initRect(enemyHit3, hitSizeX3, hitSizeY3);
	initRect(enemyFootCollider3, hitSizeX3 - colliderOffset3, 1);
	initRect(enemyHeadCollider3, hitSizeX3 - colliderOffset3, 1);

	// エネミーのグラフィックのサイズを取得
	GetGraphSize(Graph3, &w3, &h3);

	// 描画位置のオフセット値を計算
   // 左右から見てセンター、上下方向は底辺基準となるように計算
	DrawOffsetX3 = (hitSizeX3 - imageSizeX3) / 2;
	DrawOffsetY3 = (hitSizeY3 - imageSizeY3);

	jumpFlag3 = false;
	onGround3 = false;
	hitHead3 = false;
	Reverse3 = false;
	hitPlayerFlag3 = false;
	DamageFlag3 = false;
	
	LivCounter3 = 0;
}


// 敵１アップデート
void Enemy::Update1(Player player, Music music, ShotEnemy shot[], int shotnum, float deltaTime)
{
	//接地してる？
	if (onGround1)
	{
		jumpFlag1 = false;
		vy1 = 0.0f;	
	}
	else
	{
		jumpFlag1 = true;
	}

	//頭上に当たった？
	if (hitHead1)
	{
		vy1 = hitHeadBrakeRatio1 * vy1;
	}

	// エネミーの座標を移動している方向に移動する
	
	if (IsRightMove1 == true)
	{
		x1 += ENEMY_SPEED;
		Reverse1 = true;
	}
	else
	{
		x1 -= ENEMY_SPEED;
		Reverse1 = false;
	}
	
	if (!jumpFlag1)
	{
		vy1 -= jumpInitalVelocity1;
		jumpFlag1 = true;
		onGround1 = false;
	}

	// ジャンプ中なら重力を発生
	if (jumpFlag1)
	{
		vy1 += gravity1 * deltaTime;
	}

	// 位置更新
	
	x1 += vx1;
	y1 += vy1;
	

	// エネミーが画面外にでそうなら押し戻す。（移動する方向も反転する）
	if (x1 > SCREEN_WMAX - w1)
	{
		x1 = SCREEN_WMAX - w1;
		IsRightMove1 = false;
	}
	else if (x1 < SCREEN_WMIN)
	{
		x1 = SCREEN_WMIN;
	
		IsRightMove1 = true;
	}

	if (life1 > 0)
	{
		//弾があるなら
		if (count1 > 0)
		{
			ShotTimeCount1++;
			music.playEnemyAtack(count1);
			if (ShotTimeCount1 >= ENEMY_SHOTTIME)
			{
				// 画面上にでていない弾があるか、弾の数だけ繰り返えす
				for (int i = 0; i < ESHOT; i++)
				{
					// 弾iが画面上にでていない場合はその弾を画面に出す
					if (shot[i].IsEVisibleFlag() == 0)
					{
						shot[i].OnShotEnemy(x1, (y1 + 50), w1, h1);
						count1--;
						ShotFlag1 = false;
						ShotTimeCount1 = 0;
						break;
					}
				}
			}
		}
	}

	// エネミーを描画
	// ダメージを受けているかどうかで処理を分岐
	if (DamageFlag1 == true)
	{
		DamageCounter1++;
		life1--;

		if (DamageCounter1 == 5)
		{
			//『ダメージをうけていない』を表すFALSEを代入
			DamageFlag1 = false;
		}
		if (life1 <= 0)
		{
			LivCounter1--;
		}
	}

	//プレイヤーに当たっているか
	if (player.GetHitPoint() >= 0)
	{
		player.OnHitEnemy(x1, y1, w1, h1);

		hitPlayerFlag1 = true;
		//music.playEnemy(hitPlayerFlag);
	}
	
	// 当たり判定位置更新
	updateWorldRect(enemyHit1, x1, y1);
	updateWorldRect(enemyFootCollider1, x1 + colliderOffset1 / 2, y1 + enemyHit1.h);
	updateWorldRect(enemyHeadCollider1, x1 + colliderOffset1 / 2, y1 + enemyHeadCollider1.h);
	
}

// 敵２アップデート
void Enemy::Update2(Player player, Music music, float deltaTime)
{
	//接地してる？
	if (onGround2)
	{
		jumpFlag2 = false;
		vy2 = 0.0f;
	}
	else
	{
		jumpFlag2 = true;
	}

	//頭上に当たった？
	if (hitHead2)
	{
		vy2 = hitHeadBrakeRatio2 * vy2;
	}

	// エネミーの座標を移動している方向に移動する
	if (IsRightMove2 == true)
	{
		x2 += ENEMY_SPEED;
		Reverse2 = true;
	}
	else
	{
		x2 -= ENEMY_SPEED;
		Reverse2 = false;
	}


	if (!jumpFlag2)
	{
		vy2 -= jumpInitalVelocity2;
		jumpFlag2 = true;
		onGround2 = false;
	}

	// ジャンプ中なら重力を発生
	if (jumpFlag2)
	{
		vy2 += gravity2 * deltaTime;
	}

	// 位置更新
	x2 += vx2;
	y2 += vy2;


	// エネミーが画面端からでそうになっていたら画面内の座標に戻してあげ、移動する方向も反転する
	if (x2 > SCREEN_WMAX - w2)
	{
		x2 = SCREEN_WMAX - w2;
		IsRightMove2 = false;
	}
	else if (x2 < SCREEN_WMIN)
	{
		x2 = SCREEN_WMIN;

		IsRightMove2 = true;
	}

	// エネミーを描画
	// ダメージを受けているかどうかで処理を分岐
	if (DamageFlag2 == true)
	{
		DamageCounter2++;
		life2--;

		if (DamageCounter2 == 5)
		{
			//『ダメージをうけていない』を表すFALSEを代入
			DamageFlag2 = false;
		}
		if (life2 <= 0)
		{
			LivCounter2--;
		}
	}

	//プレイヤーに当たっているか
	if (player.GetHitPoint() >= 0)
	{
		player.OnHitEnemy(x2, y2, w2, h2);

		hitPlayerFlag2 = true;
		//music.playEnemy(hitPlayerFlag);
	}

	// 当たり判定位置更新
	updateWorldRect(enemyHit2, x2, y2);
	updateWorldRect(enemyFootCollider2, x2 + colliderOffset2 / 2, y2 + enemyHit2.h);
	updateWorldRect(enemyHeadCollider2, x2 + colliderOffset2 / 2, y2 + enemyHeadCollider2.h);

}

// 敵３アップデート
void Enemy::Update3(Player player, Music music, float deltaTime)
{
	//接地してる？
	if (onGround3)
	{
		jumpFlag3 = false;
		vy3 = 0.0f;
	}
	else
	{
		jumpFlag3 = true;
	}

	//頭上に当たった？
	if (hitHead3)
	{
		vy3 = hitHeadBrakeRatio3 * vy3;
	}

	// エネミーの座標を移動している方向に移動する
	if (IsRightMove3 == true)
	{
		x3 += ENEMY_SPEED;
		Reverse3 = true;
	}
	else
	{
		x3 -= ENEMY_SPEED;
		Reverse3 = false;
	}

	if (!jumpFlag3)
	{
		vy3 -= jumpInitalVelocity3;
		jumpFlag3 = true;
		onGround3 = false;
	}

	// ジャンプ中なら重力を発生
	if (jumpFlag3)
	{
		vy3 += gravity3 * deltaTime;
	}

	// 位置更新
	x3 += vx3;
	y3 += vy3;

	// エネミーが画面端からでそうになっていたら画面内の座標に戻してあげ、移動する方向も反転する
	if (x3 > SCREEN_WMAX - w3)
	{
		x3 = SCREEN_WMAX - w3;
		IsRightMove3 = false;
	}
	else if (x3 < SCREEN_WMIN)
	{
		x3 = SCREEN_WMIN;

		IsRightMove3 = true;
	}

	// エネミーを描画
	// ダメージを受けているかどうかで処理を分岐
	if (DamageFlag3 == true)
	{
		DamageCounter3++;
		life3--;

		if (DamageCounter3 == 5)
		{
			//『ダメージをうけていない』を表すFALSEを代入
			DamageFlag3 = false;
		}
		if (life3 <= 0)
		{
			LivCounter3--;
		}
	}

	//プレイヤーに当たっているか
	if (player.GetHitPoint() >= 0)
	{
		player.OnHitEnemy(x3, y3, w3, h3);

		hitPlayerFlag3 = true;
		//music.playEnemy(hitPlayerFlag);
	}

	// 当たり判定位置更新
	updateWorldRect(enemyHit3, x3, y3);
	updateWorldRect(enemyFootCollider3, x3 + colliderOffset3 / 2, y3 + enemyHit3.h);
	updateWorldRect(enemyHeadCollider3, x3 + colliderOffset3 / 2, y3 + enemyHeadCollider3.h);

}

// 描画
void Enemy::Draw1()
{
	//enemy1
	if (life1 > 0)
	{
		// ダメージを受けている場合はダメージ時のグラフィックを描画する
		if (DamageFlag1 == true)
		{
			DrawGraph(static_cast<int>(x1) + DrawOffsetX1,
				static_cast<int>(y1) + DrawOffsetY1, Graph1, TRUE);
		}
		else if (Reverse1)
		{
			DrawTurnGraph(static_cast<int>(x1) + DrawOffsetX1,
				static_cast<int>(y1) + DrawOffsetY1, Graph2, TRUE);
		}
		else
		{
			DrawGraph(static_cast<int>(x1) + DrawOffsetX1,
				static_cast<int>(y1) + DrawOffsetY1, Graph3, TRUE);
		}
	}
}

void Enemy::Draw2()
{
	//enemy2
	if (life2 > 0)
	{
		// ダメージを受けている場合はダメージ時のグラフィックを描画する
		if (DamageFlag2 == true)
		{
			DrawGraph(static_cast<int>(x2) + DrawOffsetX2,
				static_cast<int>(y2) + DrawOffsetY2, DamageGraph2, TRUE);
		}
		else if (Reverse2)
		{
			DrawTurnGraph(static_cast<int>(x2) + DrawOffsetX2,
				static_cast<int>(y2) + DrawOffsetY2, Graph2, TRUE);
		}
		else
		{
			DrawGraph(static_cast<int>(x2) + DrawOffsetX2,
				static_cast<int>(y2) + DrawOffsetY2, Graph2, TRUE);
		}
	}
}


void Enemy::Draw3()
{
	//enemy3
	if (life3 > 0)
	{
		// ダメージを受けている場合はダメージ時のグラフィックを描画する
		if (DamageFlag3 == true)
		{
			DrawGraph(x3 + DrawOffsetX3,
				y3 + DrawOffsetY3, DamageGraph3, TRUE);
		}
		else if (Reverse3)
		{
			DrawTurnGraph(static_cast<int>(x3) + DrawOffsetX3,
				static_cast<int>(y3) + DrawOffsetY3, Graph3, TRUE);
		}
		else
		{
			DrawGraph(static_cast<int>(x3) + DrawOffsetX3,
				static_cast<int>(y3) + DrawOffsetY3, Graph3, TRUE);
		}
	}
}

sHitRect Enemy::getHitRect1()
{
	return enemyHit1;
}

sHitRect Enemy::getHitRect2()
{
	return enemyHit2;
}

sHitRect Enemy::getHitRect3()
{
	return enemyHit3;
}

void Enemy::OnHitShot1(int shotX, int shotY, int shotW, int shotH, bool visibleFlag)
{
	// エネミーとの当たり判定
	if (((shotX > x1 && shotX < x1) ||
		(x1 > shotX && x1 < shotX + shotW)) &&
		((shotY > y1 && shotY < y1 + h1) ||
			(y1 > shotY && y1 < shotY + shotH)))
	{
		//ヘッドショット判定
		/*if (true )
		{
			life1 -= 10;
		}*/

		// 接触している場合は当たった弾の存在を消す
		visibleFlag = false;

		// エネミーの顔を歪めているかどうかを保持する変数に『歪めている』を表すTRUEを代入
		DamageFlag1 = true;

		// エネミーの顔を歪めている時間を測るカウンタ変数に０を代入
		DamageCounter1 = 0;

		// ライフ減少＆スコア加算
		life1 -= 1;
	}
}

void Enemy::OnHitShot2(int shotX, int shotY, int shotW, int shotH, bool visibleFlag)
{
	// エネミーとの当たり判定
	if (((shotX > x2 && shotX < x2) ||
		(x2 > shotX && x2 < shotX + shotW)) &&
		((shotY > y2 && shotY < y2 + h2) ||
			(y2 > shotY && y2 < shotY + shotH)))
	{
		//ヘッドショット判定
		/*if (true )
		{
			life2 -= 10;
		}*/

		// 接触している場合は当たった弾の存在を消す
		visibleFlag = false;

		// エネミーの顔を歪めているかどうかを保持する変数に『歪めている』を表すTRUEを代入
		DamageFlag2 = true;

		// エネミーの顔を歪めている時間を測るカウンタ変数に０を代入
		DamageCounter2 = 0;

		// ライフ減少＆スコア加算
		life2 -= 1;
	}
}

void Enemy::OnHitShot3(int shotX, int shotY, int shotW, int shotH, bool visibleFlag)
{
	// エネミーとの当たり判定
	if (((shotX > x3 && shotX < x3) ||
		(x3 > shotX && x3 < shotX + shotW)) &&
		((shotY > y3 && shotY < y3 + h3) ||
			(y3 > shotY && y3 < shotY + shotH)))
	{
		//ヘッドショット判定
		/*if (true )
		{
			life3 -= 10;
		}*/

		// 接触している場合は当たった弾の存在を消す
		visibleFlag = false;

		// エネミーの顔を歪めているかどうかを保持する変数に『歪めている』を表すTRUEを代入
		DamageFlag3 = true;

		// エネミーの顔を歪めている時間を測るカウンタ変数に０を代入
		DamageCounter3 = 0;

		// ライフ減少＆スコア加算
		life3 -= 1;
	}
}

void Enemy::fixColPosition1(sHitRect& hitRect)
{
	x1 = hitRect.worldLX;
	y1 = hitRect.worldLY;

	enemyHit1 = hitRect;
}

void Enemy::fixColPosition2(sHitRect& hitRect)
{
	x2 = hitRect.worldLX;
	y2 = hitRect.worldLY;

	enemyHit2 = hitRect;
}

void Enemy::fixColPosition3(sHitRect& hitRect)
{
	x3 = hitRect.worldLX;
	y3 = hitRect.worldLY;

	enemyHit3 = hitRect;
}

void Enemy::SetGroundFlag1(bool groundFlag)
{
	onGround1 = groundFlag;
}

void Enemy::SetGroundFlag2(bool groundFlag)
{
	onGround2 = groundFlag;
}

void Enemy::SetGroundFlag3(bool groundFlag)
{
	onGround3 = groundFlag;
}

void Enemy::SetHeadHitFlag1(bool headHitFlag)
{
	hitHead1 = headHitFlag;
}

void Enemy::SetHeadHitFlag2(bool headHitFlag)
{
	hitHead2 = headHitFlag;
}

void Enemy::SetHeadHitFlag3(bool headHitFlag)
{
	hitHead3 = headHitFlag;
}

sHitRect Enemy::GetGroundCollider1()
{
	return enemyFootCollider1;
}

sHitRect Enemy::GetGroundCollider2()
{
	return enemyFootCollider2;
}

sHitRect Enemy::GetGroundCollider3()
{
	return enemyFootCollider3;
}

sHitRect Enemy::GetHeadCollider1()
{
	return enemyHeadCollider1;
}

sHitRect Enemy::GetHeadCollider2()
{
	return enemyHeadCollider2;
}

sHitRect Enemy::GetHeadCollider3()
{
	return enemyHeadCollider3;
}



