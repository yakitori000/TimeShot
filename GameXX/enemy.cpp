
#include "Enemy.h"

sHitRect hitrect;
sHitRect enemyHit;                          // プレイヤー当たり判定
sHitRect enemyFootCollider;                 // 接地コライダー
sHitRect enemyHeadCollider;                 // 頭上コライダー

// 初期化
void Enemy::Init()
{
	// エネミーのグラフィックをメモリにロード＆表示座標を初期化
	
	graph = LoadGraph("data/image/Zonbi3.png");
	damageGraph = LoadGraph("data/image/Zonbi.png");
	GraphFilter(damageGraph, DX_GRAPH_FILTER_HSB, 120, 120, 120, 256);
	
	life = ENEMY_LIFE;				//敵の体力

	x[0] = GetRand(ENEMY_MAXX);		//敵のX座標
	y[0] = GetRand(ENEMY_MAXY);		//敵のY座標

	x[1] = GetRand(ENEMY_MAXX);		//敵のX座標
	y[1] = GetRand(ENEMY_MAXY);		//敵のY座標

	x[2] = GetRand(ENEMY_MAXX);		//敵のX座標
	y[2] = GetRand(ENEMY_MAXY);		//敵のY座標
	
	x[3] = GetRand(ENEMY_MAXX);		//敵のX座標
	y[3] = GetRand(ENEMY_MAXY);		//敵のY座標
	
	x[4] = GetRand(ENEMY_MAXX);		//敵のX座標
	y[4] = GetRand(ENEMY_MAXY);		//敵のY座標


	// 当たり判定初期化
	initRect(enemyHit, hitSizeX, hitSizeY);
	initRect(enemyFootCollider, hitSizeX - colliderOffset, 1);
	initRect(enemyHeadCollider, hitSizeX - colliderOffset, 1);

	// エネミーのグラフィックのサイズを得る
	GetGraphSize(graph, &w, &h);

	// 描画位置のオフセット値を計算
   // 左右から見てセンター、上下方向は底辺基準となるように計算
	drawOffsetX = (hitSizeX - imageSizeX) / 2;
	drawOffsetY = (hitSizeY - imageSizeY);

	jumpFlag = false;
	onGround = false;
	hitHead = false;
	Reverse = false;
	hitPlayerFlag = false;
	LivCounter = 0;

	// エネミーが顔を歪めているかどうかの変数に『歪めていない』を表すFALSEを代入
	damageFlag = false;	
}


// アップデート.
void Enemy::Update(Player player, Music music, float deltaTime)
{
	//接地してる？
	if (onGround)
	{
		jumpFlag = false;
		vy = 0.0f;	
	}
	else
	{
		jumpFlag = true;
	}

	//頭上に当たった？
	if (hitHead)
	{
		vy = hitHeadBrakeRatio * vy;
	}

	// エネミーの座標を移動している方向に移動する
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (isRightMove == true)
		{
			x[i] += 3;
			Reverse = true;
		}
		else
		{
			x[i] -= 3;	
			Reverse = false;
		}
	}
	
	if (!jumpFlag)
	{
		vy -= jumpInitalVelocity;
		jumpFlag = true;
		onGround = false;
	}

	// ジャンプ中なら重力を発生
	if (jumpFlag)
	{
		vy += gravity * deltaTime;
	}

	// 位置更新
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		x[i] += vx;
		y[i] += vy;
	}

	// エネミーが画面端からでそうになっていたら画面内の座標に戻してあげ、移動する方向も反転する
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (x[i] > SCREEN_W - w)
		{
			x[i] = SCREEN_W - w;
			isRightMove = false;
		}
		else if (x[i] < 0)
		{
			x[i] = 0;
		
			isRightMove = true;
		}
	}
	
	// エネミーを描画
	// ダメージを受けているかどうかで処理を分岐
	if (damageFlag == true)
	{
		damageCounter++;
		life--;

		if (damageCounter == 5)
		{
			//『ダメージをうけていない』を表すFALSEを代入
			damageFlag = false;
		}
		if (life <= 0)
		{
			LivCounter--;
		}
	}

	for (int i = 0; i < ENEMY_NUM; i++)
	{
		//プレイヤーに当たっているか
		if (player.GetHitPoint() >= 0)
		{
			player.OnHitEnemy(x[i], y[i], w, h);

			hitPlayerFlag = true;
			//music.playEnemy(hitPlayerFlag);
		}
	}
	

	// 当たり判定位置更新
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		updateWorldRect(enemyHit, x[i], y[i]);
		updateWorldRect(enemyFootCollider, x[i] + colliderOffset / 2, y[i] + enemyHit.h);
		updateWorldRect(enemyHeadCollider, x[i] + colliderOffset / 2, y[i] + enemyHeadCollider.h);
	}
}

// 描画.
void Enemy::Draw()
{

	if (life > 0)
	{
		// ダメージを受けている場合はダメージ時のグラフィックを描画する
		if (damageFlag == true)
		{
			for (int i = 0; i < ENEMY_NUM; i++)
			{
				DrawGraph(static_cast<int>(x[i]) + drawOffsetX,
					static_cast<int>(y[i]) + drawOffsetY, damageGraph, TRUE);
			}
		}
		else if (Reverse)
		{
			for (int i = 0; i < ENEMY_NUM; i++)
			{
				DrawTurnGraph(static_cast<int>(x[i]) + drawOffsetX,
					static_cast<int>(y[i]) + drawOffsetY, graph, TRUE);
			}
		}
		else
		{
			for (int i = 0; i < ENEMY_NUM; i++)
			{
				DrawGraph(static_cast<int>(x[i]) + drawOffsetX,
					static_cast<int>(y[i]) + drawOffsetY, graph, TRUE);
			}
			
		}
	}
}

sHitRect Enemy::getHitRect()
{
	return enemyHit;
}

void Enemy::OnHitShot(int shotX, int shotY, int shotW, int shotH, bool visibleFlag)
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		// エネミーとの当たり判定
		if (((shotX > x[i] && shotX < x[i]) ||
			(x[i] > shotX && x[i] < shotX + shotW)) &&
			((shotY > y[i] && shotY < y[i] + h) ||
				(y[i] > shotY && y[i] < shotY + shotH)))
		{
			//ヘッドショット判定
			/*if (true )
			{
				life -= 10;
			}*/

			// 接触している場合は当たった弾の存在を消す
			visibleFlag = false;

			// エネミーの顔を歪めているかどうかを保持する変数に『歪めている』を表すTRUEを代入
			damageFlag = true;

			// エネミーの顔を歪めている時間を測るカウンタ変数に０を代入
			damageCounter = 0;

			// ライフ減少＆スコア加算
			life -= 1;
		}
	}
}

void Enemy::setPosition(float x, float y, int num)
{
	PosX[num] = x;
	PosY[num] = y;
}

void Enemy::fixColPosition(sHitRect& hitRect)
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		x[i] = hitRect.worldLX;
		y[i] = hitRect.worldLY;
	}
	
	enemyHit = hitRect;
}

void Enemy::SetGroundFlag(bool groundFlag)
{
	onGround = groundFlag;
}

void Enemy::SetHeadHitFlag(bool headHitFlag)
{
	hitHead = headHitFlag;
}

sHitRect Enemy::GetGroundCollider()
{
	return enemyFootCollider;
}

sHitRect Enemy::GetHeadCollider()
{
	return enemyHeadCollider;
}

