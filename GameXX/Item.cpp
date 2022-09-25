#include "Item.h"

void Item::Init()
{
	BoxGraph = LoadGraph("data/image/box.png");
	OpenBoxGraph = LoadGraph("data/image/OpenBox.png");
	Graph = LoadGraph("dat/image/now.png");
	DropGraph = LoadGraph("data/image/dropShot.png");
	

	x = 880;
	y = 158;
	dropX = x - 50;
	dropY = 500;

	OpenFlag = false;
	HitFlag = false;

	int boxW, boxH;
	GetGraphSize(BoxGraph, &boxW, &boxH);
	w = boxW;
	h = boxH;

	ItemNowType = Graph;     // �A�C�e�����
}

void Item::Updata(Player& player)
{
	// ���̂����蔻��
		// ��łȂ����̏ꍇ�̂ݎ��̏����Ɉڂ�
	if (!OpenFlag)
	{
		// �v���C���[�Ƃ̓����蔻��
		if (((x > player.px && x < player.px + player.w) ||
			(player.px > x && player.px < x + w)) &&
			((y > player.py && y < player.py + player.h) ||
				(player.py > y && player.py < y + h)))
		{
			// �ڐG���Ă���ꍇ�l���o����悤�ɂ���
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


