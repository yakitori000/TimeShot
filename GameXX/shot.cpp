
#include "Shot.h"

//������
void Shot::Init()
{
	// �V���b�g�̑��݂�����������
	int shotGraph;
	shotGraph = LoadGraph("data/image/SuperShot.png");
	graph = shotGraph;

	//�e����ʏ�ɑ��݂��Ă��Ȃ�
	visibleFlag = false;

	//�e�̃O���t�B�b�N�̃T�C�Y���擾
	int shotW, shotH;
	GetGraphSize(shotGraph, &shotW, &shotH);
	w = shotW;
	h = shotH;

}

//�A�b�v�f�[�g
void Shot::Update(Player& player, Enemy& enemy)
{
	//�v���C���[�e�̈ړ����[�`��
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
		if (x < SCREEN_WMIN - w || x > SCREEN_WMAX)
		{
			visibleFlag = false;
		}
	}
	

		// �e�̂����蔻��
		// �e�����݂��Ă���ꍇ�̂ݎ��̏����ɉf��
		if (visibleFlag == true && enemy.GetLife1() > 0)
		{
			enemy.OnHitShot1(x, y, w, h, visibleFlag);
		}

		if (visibleFlag == true && enemy.GetLife2() > 0)
		{
			enemy.OnHitShot2(x, y, w, h, visibleFlag);
		}

		if (visibleFlag == true && enemy.GetLife3() > 0)
		{
			enemy.OnHitShot3(x, y, w, h, visibleFlag);
		}
}

//�`��
void Shot::Draw(Player& player)
{
	if (visibleFlag == true)
	{
		//�e�̕`�������
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
	// �e�̈ʒu���Z�b�g�A�ʒu�̓v���C���[�̒��S�ɂ���
	x = (PlayerW - w) / 40 + PlayerX;
	y = (PlayerH - h) / -1.5 + PlayerY;
	
	// �e�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ���true��������
	visibleFlag = true;
}


