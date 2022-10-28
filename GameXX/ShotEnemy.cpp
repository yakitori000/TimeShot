#include "DxLib.h"
#include "Player.h"
#include "ShotEnemy.h"
#include "collision.h"
#include "function.h"

void ShotEnemy::InitShotEnemy()
{
	// ショットの存在を初期化する
	int shotEnemyGraph;
	shotEnemyGraph = LoadGraph("data/image/HADOU1.png");
	EGraph = shotEnemyGraph;

	//弾が画面上に存在していない
	EVisibleFlag = false;

	//弾のグラフィックのサイズを取得
	int shotEnemyW, shotEnemyH;
	GetGraphSize(shotEnemyGraph, &shotEnemyW, &shotEnemyH);
	ew = shotEnemyW;
	eh = shotEnemyH;
}

void ShotEnemy::UpdateShotEnemy(Player& player, Enemy& enemy)
{
	//エネミー弾の移動ルーチン
	if (EVisibleFlag == true)
	{
		if (enemy.GetReverse1() == true)
		{
			ex += ESHOT_SPEED;
		}
		if (enemy.GetReverse1() == false)
		{
			if (ex >= enemy.GetX1() || ex <= enemy.GetX1())
			{
				ex -= ESHOT_SPEED;
			}
		}
		if (ex < SCREEN_WMIN - ew || ex > SCREEN_WMAX)
		{
			EVisibleFlag = false;
		}
	}

	// 弾のあたり判定
	// 弾が存在している場合のみ次の処理に映る
	if (EVisibleFlag == true && player.HitPoint > 0)
	{
		player.OnHitShot(ex, ey, ew, eh, EVisibleFlag);
	}
}

void ShotEnemy::DrawShotEnemy(Enemy& enemy)
{
	if (EVisibleFlag == true)
	{
		//弾の描画をする
		if (enemy.GetReverse1() == true)
		{
			DrawRotaGraph(ex, ey, 1.0f, PI / 1, EGraph, TRUE, FALSE);
		}
		else
		{
			DrawRotaGraph(ex, ey, 1.0f, PI / 1, EGraph, TRUE, TRUE);
		}

	}
}

void ShotEnemy::OnShotEnemy(float EnemyX, float EnemyY, float EnemyW, float EnemyH)
{
	// 弾の位置をセット、位置はプレイヤーの中心にする
	ex = (EnemyW - ew) / 40 + EnemyX;
	ey = (EnemyH - eh) / -1.5 + EnemyY;

	// 弾は現時点を持って存在するので、存在状態を保持する変数にtrueを代入する
	EVisibleFlag = true;
}
