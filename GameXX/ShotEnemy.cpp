#include "DxLib.h"
#include "Player.h"
#include "ShotEnemy.h"
#include "collision.h"
#include "function.h"

void ShotEnemy::InitShotEnemy()
{
	// �V���b�g�̑��݂�����������
	int shotEnemyGraph;
	shotEnemyGraph = LoadGraph("data/image/HADOU1.png");
	EGraph = shotEnemyGraph;

	//�e����ʏ�ɑ��݂��Ă��Ȃ�
	EVisibleFlag = false;

	//�e�̃O���t�B�b�N�̃T�C�Y���擾
	int shotEnemyW, shotEnemyH;
	GetGraphSize(shotEnemyGraph, &shotEnemyW, &shotEnemyH);
	ew = shotEnemyW;
	eh = shotEnemyH;
}

void ShotEnemy::UpdateShotEnemy(Player& player, Enemy& enemy)
{
	//�G�l�~�[�e�̈ړ����[�`��
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

	// �e�̂����蔻��
	// �e�����݂��Ă���ꍇ�̂ݎ��̏����ɉf��
	if (EVisibleFlag == true && player.HitPoint > 0)
	{
		player.OnHitShot(ex, ey, ew, eh, EVisibleFlag);
	}
}

void ShotEnemy::DrawShotEnemy(Enemy& enemy)
{
	if (EVisibleFlag == true)
	{
		//�e�̕`�������
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
	// �e�̈ʒu���Z�b�g�A�ʒu�̓v���C���[�̒��S�ɂ���
	ex = (EnemyW - ew) / 40 + EnemyX;
	ey = (EnemyH - eh) / -1.5 + EnemyY;

	// �e�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ���true��������
	EVisibleFlag = true;
}
