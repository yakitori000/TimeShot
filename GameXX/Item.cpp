#include "Item.h"

void Item::Init(Music& music)
{
	BoxGraph = LoadGraph("data/image/box.png");
	OpenBoxGraph = LoadGraph("data/image/OpenBox.png");
	Graph = LoadGraph("dat/image/now.png");
	DropGraph = LoadGraph("data/image/dropShot.png");
	

	x = 10;
	y = 800;
	dropX = x - 50;
	dropY = 500;

	/*x = 880;
	y = 158;
	dropX = x - 50;
	dropY = 500;*/

	OpenFlag = false;
	HitFlag = false;

	int boxW, boxH;
	GetGraphSize(BoxGraph, &boxW, &boxH);
	w = boxW;
	h = boxH;

	ItemNowType = Graph;     // アイテム種類

	music.BoxSoundInit();
}

void Item::Updata(Player& player, Music &music)
{
	// 箱のあたり判定
		// 空でない箱の場合のみ次の処理に移る
	if (!OpenFlag)
	{
		// プレイヤーとの当たり判定
		if (((x > player.px && x < player.px + player.w) ||
			(player.px > x && player.px < x + w)) &&
			((y > player.py && y < player.py + player.h) ||
				(player.py > y && player.py < y + h)))
		{
			// 接触している場合獲得出来るようにする
			player.GetFlag = true;
			HitFlag = true;
			ItemNowType = DropGraph;
		}
		else
		{
			HitFlag = false;
		}
	}
	if (OpenFlag) 
	{
		HitFlag = false;
		
		if (player.animGetDown == false)
		{
			ItemNowType = Graph;
		}
	}
	
}

void Item::Draw()
{
	if (OpenFlag == true)
	{
		DrawGraph(x, y, OpenBoxGraph, TRUE);
		DrawGraph(dropX, dropY, Graph, TRUE);
	}
	else
	{
		DrawGraph(x, y, BoxGraph, TRUE);
	}
	
}


