
#include "Shot.h"

//������
void Shot::Init()
{
	// �V���b�g�̑��݂�����������
	int shotGraph;
	shotGraph = LoadGraph("data/SuperShot.png");
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
		if (x < 0 - w || x > SCREEN_W)
		{
			visibleFlag = false;
		}
	}
	

		// �e�̂����蔻��
		// �e�����݂��Ă���ꍇ�̂ݎ��̏����ɉf��
		if (visibleFlag == true && enemy.GetLife() > 0)
		{
			enemy.OnHitShot(x, y, w, h, visibleFlag);
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
	// �ei�̈ʒu���Z�b�g�A�ʒu�̓v���C���[�̒��S�ɂ���
	x = (PlayerW - w) / 40 + PlayerX;
	y = (PlayerH - h) / -1.5 + PlayerY;
	
	// �ei�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ���true��������
	visibleFlag = true;
}
