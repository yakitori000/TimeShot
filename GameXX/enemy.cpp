
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

	x = GetRand(ENEMY_MAXX);		//敵のX座標
	y = GetRand(ENEMY_MAXY);		//敵のY座標
	
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
	if (isRightMove == true)
	{
		x += 3;
		Reverse = true;
	}
	else
	{
		x -= 3;
		Reverse = false;
	}

	//壁に当たったらジャンプする
	if (x == hitrect.worldLX)
	{
		// 方向転換
		if (vx > 0.0f)
		{
			vx *= brakeRatio;
		}
		// 地上加速度
		vx += -moveAccell * deltaTime;
	}
	else
	{
		//空中加速度
		vy += -moveAccell * inAirMoveAccelRatio * deltaTime;
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
	x += vx;
	y += vy;

	// エネミーが画面端からでそうになっていたら画面内の座標に戻してあげ、移動する方向も反転する
	if (x > SCREEN_W - w)
	{
		x = SCREEN_W - w;
		isRightMove = false;
	}
	else if (x < 0)
	{
		x = 0;
		isRightMove = true;
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

	//プレイヤーに当たっているか
	if (player.GetHitPoint() > 0)
	{
		player.OnHitEnemy(x, y, w, h);
		hitPlayerFlag = true;
		//music.playEnemy(hitPlayerFlag);
	}

	// 当たり判定位置更新
	updateWorldRect(enemyHit, x, y);
	updateWorldRect(enemyFootCollider, x + colliderOffset / 2, y + enemyHit.h);
	updateWorldRect(enemyHeadCollider, x + colliderOffset / 2, y + enemyHeadCollider.h);
}

// 描画.
void Enemy::Draw()
{

	if (life > 0)
	{
		// ダメージを受けている場合はダメージ時のグラフィックを描画する
		if (damageFlag == true)
		{
			DrawGraph(static_cast<int>(x) + drawOffsetX,
				static_cast<int>(y) + drawOffsetY, damageGraph, TRUE);
		}
		else if (Reverse)
		{
			DrawTurnGraph(static_cast<int>(x) + drawOffsetX,
				static_cast<int>(y) + drawOffsetY, graph, TRUE);
		}
		else
		{
			DrawGraph(static_cast<int>(x) + drawOffsetX,
				static_cast<int>(y) + drawOffsetY, graph, TRUE);
		}
	}
}

sHitRect Enemy::getHitRect()
{
	return enemyHit;
}

void Enemy::OnHitShot(int shotX, int shotY, int shotW, int shotH, bool visibleFlag)
{
	// エネミーとの当たり判定
	if (((shotX > x && shotX < x) ||
		(x > shotX && x < shotX + shotW)) &&
		((shotY > y && shotY < y + h) ||
			(y > shotY && y < shotY + shotH)))
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
		Score += 1;
	}

}

void Enemy::setPosition(float x, float y, int num)
{
	PosX[num] = x;
	PosY[num] = y;
}

void Enemy::fixColPosition(sHitRect& hitRect)
{
	x = hitRect.worldLX;
	y = hitRect.worldLY;

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

