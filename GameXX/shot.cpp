
#include "Shot.h"

//初期化
void Shot::Init()
{
	// ショットの存在を初期化する
	int shotGraph;
	shotGraph = LoadGraph("data/SuperShot.png");
	graph = shotGraph;

	//弾が画面上に存在していない
	visibleFlag = false;

	//弾のグラフィックのサイズを取得
	int shotW, shotH;
	GetGraphSize(shotGraph, &shotW, &shotH);
	w = shotW;
	h = shotH;

}

//アップデート
void Shot::Update(Player& player, Enemy& enemy)
{
	//プレイヤー弾の移動ルーチン
	if (visibleFlag == true)
	{	
		if (player.sideFlag == true )
		{
			x -= SHOT_SPEED;
		}
		if (player.sideFlag == false)
		{
			if (x >= player.px || x <= player.px )
			{
				x += SHOT_SPEED;
			}
		}
		if (x < 0 - w || x > SCREEN_W)
		{
			visibleFlag = false;
		}
	}
	

		// 弾のあたり判定
		// 弾が存在している場合のみ次の処理に映る
		if (visibleFlag == true && enemy.GetLife() > 0)
		{
			enemy.OnHitShot(x, y, w, h, visibleFlag);
		}
}

//描画
void Shot::Draw(Player& player)
{
	if (visibleFlag == true)
	{
		//弾の描画をする
		if (player.sideFlag == true)
		{
			DrawRotaGraph(x, y, 1.0f, PI / 1, graph, TRUE, FALSE);
		}
		else
		{
			DrawRotaGraph(x, y, 1.0f, PI / 1, graph, TRUE, TRUE);
		}
	}

}

void Shot::OnShot(float PlayerX, float PlayerY, float PlayerW, float PlayerH)
{
	// 弾iの位置をセット、位置はプレイヤーの中心にする
	x = (PlayerW - w) / 40 + PlayerX;
	y = (PlayerH - h) / -1.5 + PlayerY;
	
	// 弾iは現時点を持って存在するので、存在状態を保持する変数にtrueを代入する
	visibleFlag = true;
}
