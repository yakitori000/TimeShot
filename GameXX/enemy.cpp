
#include "Enemy.h"
#include "Player.h"
#include "Music.h"
#include "map.h"
#include "function.h"
#include "collision.h"

//�G�P
sHitRect hitrect1;
sHitRect enemyHit1;                          // �G�P�����蔻��
sHitRect enemyFootCollider1;                 // �ڒn�R���C�_�[
sHitRect enemyHeadCollider1;                 // ����R���C�_�[

//�G�Q
sHitRect hitrect2;
sHitRect enemyHit2;                          // �G�Q�����蔻��
sHitRect enemyFootCollider2;                 // �ڒn�R���C�_�[
sHitRect enemyHeadCollider2;                 // ����R���C�_�[

//�G�R
sHitRect hitrect3;
sHitRect enemyHit3;                          // �G�R�����蔻��
sHitRect enemyFootCollider3;                 // �ڒn�R���C�_�[
sHitRect enemyHeadCollider3;                 // ����R���C�_�[

// ������
void Enemy::Init1()
{
	// �G�l�~�[�̃O���t�B�b�N���������Ƀ��[�h���\�����W��������
	
	graph1 = LoadGraph("data/image/Zonbi1.png");
	damageGraph1 = LoadGraph("data/image/Zonbi.png");
	GraphFilter(damageGraph1, DX_GRAPH_FILTER_HSB, 120, 120, 120, 256);
	
	life1 = ENEMY_LIFE;				//�G1�̗̑�

	x1 = GetRand(ENEMY_MAXX);		//�G1��X���W
	y1 = GetRand(ENEMY_MAXY);		//�G1��Y���W

	// �����蔻�菉�����@�G�P
	initRect(enemyHit1, hitSizeX1, hitSizeY1);
	initRect(enemyFootCollider1, hitSizeX1 - colliderOffset1, 1);
	initRect(enemyHeadCollider1, hitSizeX1 - colliderOffset1, 1);
	
	// �G�l�~�[�̃O���t�B�b�N�̃T�C�Y�𓾂�
	GetGraphSize(graph1, &w1, &h1);

	// �`��ʒu�̃I�t�Z�b�g�l���v�Z
   // ���E���猩�ăZ���^�[�A�㉺�����͒�ӊ�ƂȂ�悤�Ɍv�Z
	drawOffsetX1 = (hitSizeX1 - imageSizeX1) / 2;
	drawOffsetY1 = (hitSizeY1 - imageSizeY1);

	jumpFlag1 = false;
	onGround1 = false;
	hitHead1 = false;
	Reverse1 = false;
	hitPlayerFlag1 = false;
	LivCounter1 = 0;

	// �G�l�~�[�����c�߂Ă��邩�ǂ����̕ϐ��Ɂw�c�߂Ă��Ȃ��x��\��FALSE����
	damageFlag1 = false;	
}

void Enemy::Init2()
{
	graph2 = LoadGraph("data/image/panelu1.png");
	damageGraph2 = LoadGraph("data/image/Zonbi.png");
	GraphFilter(damageGraph2, DX_GRAPH_FILTER_HSB, 120, 120, 120, 256);

	life2 = ENEMY_LIFE;				//�G2�̗̑�

	x2 = GetRand(ENEMY_MAXX);		//�G2��X���W
	y2 = GetRand(ENEMY_MAXY);		//�G2��Y���W

	// �����蔻�菉�����@�G�Q
	initRect(enemyHit2, hitSizeX2, hitSizeY2);
	initRect(enemyFootCollider2, hitSizeX2 - colliderOffset2, 1);
	initRect(enemyHeadCollider2, hitSizeX2 - colliderOffset2, 1);

	// �G�l�~�[�̃O���t�B�b�N�̃T�C�Y�𓾂�
	GetGraphSize(graph2, &w2, &h2);

	// �`��ʒu�̃I�t�Z�b�g�l���v�Z
   // ���E���猩�ăZ���^�[�A�㉺�����͒�ӊ�ƂȂ�悤�Ɍv�Z
	drawOffsetX2 = (hitSizeX2 - imageSizeX2) / 2;
	drawOffsetY2 = (hitSizeY2 - imageSizeY2);

	jumpFlag2 = false;
	onGround2 = false;
	hitHead2 = false;
	Reverse2 = false;
	hitPlayerFlag2 = false;
	LivCounter2 = 0;

	// �G�l�~�[�����c�߂Ă��邩�ǂ����̕ϐ��Ɂw�c�߂Ă��Ȃ��x��\��FALSE����
	damageFlag2 = false;
}

void Enemy::Init3()
{
	graph3 = LoadGraph("data/image/Zonbi3.png");
	damageGraph3 = LoadGraph("data/image/Zonbi.png");
	GraphFilter(damageGraph3, DX_GRAPH_FILTER_HSB, 120, 120, 120, 256);

	life3 = ENEMY_LIFE;				//�G3�̗̑�

	x3 = GetRand(ENEMY_MAXX);		//�G3��X���W
	y3 = GetRand(ENEMY_MAXY);		//�G3��Y���W	

	// �����蔻�菉�����@�G�R
	initRect(enemyHit3, hitSizeX3, hitSizeY3);
	initRect(enemyFootCollider3, hitSizeX3 - colliderOffset3, 1);
	initRect(enemyHeadCollider3, hitSizeX3 - colliderOffset3, 1);

	// �G�l�~�[�̃O���t�B�b�N�̃T�C�Y�𓾂�
	GetGraphSize(graph3, &w3, &h3);

	// �`��ʒu�̃I�t�Z�b�g�l���v�Z
   // ���E���猩�ăZ���^�[�A�㉺�����͒�ӊ�ƂȂ�悤�Ɍv�Z
	drawOffsetX3 = (hitSizeX3 - imageSizeX3) / 2;
	drawOffsetY3 = (hitSizeY3 - imageSizeY3);

	jumpFlag3 = false;
	onGround3 = false;
	hitHead3 = false;
	Reverse3 = false;
	hitPlayerFlag3 = false;
	LivCounter3 = 0;

	// �G�l�~�[�����c�߂Ă��邩�ǂ����̕ϐ��Ɂw�c�߂Ă��Ȃ��x��\��FALSE����
	damageFlag3 = false;
}


// �G�P�A�b�v�f�[�g
void Enemy::Update1(Player player, Music music, float deltaTime)
{
	//�ڒn���Ă�H
	if (onGround1)
	{
		jumpFlag1 = false;
		vy1 = 0.0f;	
	}
	else
	{
		jumpFlag1 = true;
	}

	//����ɓ��������H
	if (hitHead1)
	{
		vy1 = hitHeadBrakeRatio1 * vy1;
	}

	// �G�l�~�[�̍��W���ړ����Ă�������Ɉړ�����
	
	if (isRightMove1 == true)
	{
		x1 += 3;
		Reverse1 = true;
	}
	else
	{
		x1 -= 3;	
		Reverse1 = false;
	}
	
	if (!jumpFlag1)
	{
		vy1 -= jumpInitalVelocity1;
		jumpFlag1 = true;
		onGround1 = false;
	}

	// �W�����v���Ȃ�d�͂𔭐�
	if (jumpFlag1)
	{
		vy1 += gravity1 * deltaTime;
	}

	// �ʒu�X�V
	
	x1 += vx1;
	y1 += vy1;
	

	// �G�l�~�[����ʒ[����ł����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă����A�ړ�������������]����
	if (x1 > SCREEN_WMAX - w1)
	{
		x1 = SCREEN_WMAX - w1;
		isRightMove1 = false;
	}
	else if (x1 < SCREEN_WMIN)
	{
		x1 = SCREEN_WMIN;
	
		isRightMove1 = true;
	}

	// �G�l�~�[��`��
	// �_���[�W���󂯂Ă��邩�ǂ����ŏ����𕪊�
	if (damageFlag1 == true)
	{
		damageCounter1++;
		life1--;

		if (damageCounter1 == 5)
		{
			//�w�_���[�W�������Ă��Ȃ��x��\��FALSE����
			damageFlag1 = false;
		}
		if (life1 <= 0)
		{
			LivCounter1--;
		}
	}

	//�v���C���[�ɓ������Ă��邩
	if (player.GetHitPoint() >= 0)
	{
		player.OnHitEnemy(x1, y1, w1, h1);

		hitPlayerFlag1 = true;
		//music.playEnemy(hitPlayerFlag);
	}
	
	// �����蔻��ʒu�X�V
	updateWorldRect(enemyHit1, x1, y1);
	updateWorldRect(enemyFootCollider1, x1 + colliderOffset1 / 2, y1 + enemyHit1.h);
	updateWorldRect(enemyHeadCollider1, x1 + colliderOffset1 / 2, y1 + enemyHeadCollider1.h);
	
}

// �G�Q�A�b�v�f�[�g
void Enemy::Update2(Player player, Music music, float deltaTime)
{
	//�ڒn���Ă�H
	if (onGround2)
	{
		jumpFlag2 = false;
		vy2 = 0.0f;
	}
	else
	{
		jumpFlag2 = true;
	}

	//����ɓ��������H
	if (hitHead2)
	{
		vy2 = hitHeadBrakeRatio2 * vy2;
	}

	// �G�l�~�[�̍��W���ړ����Ă�������Ɉړ�����
	if (isRightMove2 == true)
	{
		x2 += 6;
		Reverse2 = true;
	}
	else
	{
		x2 -= 6;
		Reverse2 = false;
	}


	if (!jumpFlag2)
	{
		vy2 -= jumpInitalVelocity2;
		jumpFlag2 = true;
		onGround2 = false;
	}

	// �W�����v���Ȃ�d�͂𔭐�
	if (jumpFlag2)
	{
		vy2 += gravity2 * deltaTime;
	}

	// �ʒu�X�V
	x2 += vx2;
	y2 += vy2;


	// �G�l�~�[����ʒ[����ł����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă����A�ړ�������������]����
	if (x2 > SCREEN_WMAX - w2)
	{
		x2 = SCREEN_WMAX - w2;
		isRightMove2 = false;
	}
	else if (x2 < SCREEN_WMIN)
	{
		x2 = SCREEN_WMIN;

		isRightMove2 = true;
	}

	// �G�l�~�[��`��
	// �_���[�W���󂯂Ă��邩�ǂ����ŏ����𕪊�
	if (damageFlag2 == true)
	{
		damageCounter2++;
		life2--;

		if (damageCounter2 == 5)
		{
			//�w�_���[�W�������Ă��Ȃ��x��\��FALSE����
			damageFlag2 = false;
		}
		if (life2 <= 0)
		{
			LivCounter2--;
		}
	}

	//�v���C���[�ɓ������Ă��邩
	if (player.GetHitPoint() >= 0)
	{
		player.OnHitEnemy(x2, y2, w2, h2);

		hitPlayerFlag2 = true;
		//music.playEnemy(hitPlayerFlag);
	}

	// �����蔻��ʒu�X�V
	updateWorldRect(enemyHit2, x2, y2);
	updateWorldRect(enemyFootCollider2, x2 + colliderOffset2 / 2, y2 + enemyHit2.h);
	updateWorldRect(enemyHeadCollider2, x2 + colliderOffset2 / 2, y2 + enemyHeadCollider2.h);

}

// �G�R�A�b�v�f�[�g
void Enemy::Update3(Player player, Music music, float deltaTime)
{
	//�ڒn���Ă�H
	if (onGround3)
	{
		jumpFlag3 = false;
		vy3 = 0.0f;
	}
	else
	{
		jumpFlag3 = true;
	}

	//����ɓ��������H
	if (hitHead3)
	{
		vy3 = hitHeadBrakeRatio3 * vy3;
	}

	// �G�l�~�[�̍��W���ړ����Ă�������Ɉړ�����
	if (isRightMove3 == true)
	{
		x3 += 9;
		Reverse3 = true;
	}
	else
	{
		x3 -= 9;
		Reverse3 = false;
	}


	if (!jumpFlag3)
	{
		vy3 -= jumpInitalVelocity3;
		jumpFlag3 = true;
		onGround3 = false;
	}

	// �W�����v���Ȃ�d�͂𔭐�
	if (jumpFlag3)
	{
		vy3 += gravity3 * deltaTime;
	}

	// �ʒu�X�V
	x3 += vx3;
	y3 += vy3;

	// �G�l�~�[����ʒ[����ł����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă����A�ړ�������������]����
	if (x3 > SCREEN_WMAX - w3)
	{
		x3 = SCREEN_WMAX - w3;
		isRightMove3 = false;
	}
	else if (x3 < SCREEN_WMIN)
	{
		x3 = SCREEN_WMIN;

		isRightMove3 = true;
	}

	// �G�l�~�[��`��
	// �_���[�W���󂯂Ă��邩�ǂ����ŏ����𕪊�
	if (damageFlag3 == true)
	{
		damageCounter3++;
		life3--;

		if (damageCounter3 == 5)
		{
			//�w�_���[�W�������Ă��Ȃ��x��\��FALSE����
			damageFlag3 = false;
		}
		if (life3 <= 0)
		{
			LivCounter3--;
		}
	}

	//�v���C���[�ɓ������Ă��邩
	if (player.GetHitPoint() >= 0)
	{
		player.OnHitEnemy(x3, y3, w3, h3);

		hitPlayerFlag3 = true;
		//music.playEnemy(hitPlayerFlag);
	}

	// �����蔻��ʒu�X�V
	updateWorldRect(enemyHit3, x3, y3);
	updateWorldRect(enemyFootCollider3, x3 + colliderOffset3 / 2, y3 + enemyHit3.h);
	updateWorldRect(enemyHeadCollider3, x3 + colliderOffset3 / 2, y3 + enemyHeadCollider3.h);

}

// �`��
void Enemy::Draw1()
{
	//enemy1
	if (life1 > 0)
	{
		// �_���[�W���󂯂Ă���ꍇ�̓_���[�W���̃O���t�B�b�N��`�悷��
		if (damageFlag1 == true)
		{
			DrawGraph(static_cast<int>(x1) + drawOffsetX1,
				static_cast<int>(y1) + drawOffsetY1, damageGraph1, TRUE);
		}
		else if (Reverse1)
		{
			DrawTurnGraph(static_cast<int>(x1) + drawOffsetX1,
				static_cast<int>(y1) + drawOffsetY1, graph1, TRUE);
		}
		else
		{
			DrawGraph(static_cast<int>(x1) + drawOffsetX1,
				static_cast<int>(y1) + drawOffsetY1, graph1, TRUE);
		}
	}
}

void Enemy::Draw2()
{
	//enemy2
	if (life2 > 0)
	{
		// �_���[�W���󂯂Ă���ꍇ�̓_���[�W���̃O���t�B�b�N��`�悷��
		if (damageFlag2 == true)
		{
			DrawGraph(static_cast<int>(x2) + drawOffsetX2,
				static_cast<int>(y2) + drawOffsetY2, damageGraph2, TRUE);
		}
		else if (Reverse2)
		{
			DrawTurnGraph(static_cast<int>(x2) + drawOffsetX2,
				static_cast<int>(y2) + drawOffsetY2, graph2, TRUE);
		}
		else
		{
			DrawGraph(static_cast<int>(x2) + drawOffsetX2,
				static_cast<int>(y2) + drawOffsetY2, graph2, TRUE);
		}
	}
}

void Enemy::Draw3()
{
	//enemy3
	if (life3 > 0)
	{
		// �_���[�W���󂯂Ă���ꍇ�̓_���[�W���̃O���t�B�b�N��`�悷��
		if (damageFlag3 == true)
		{
			DrawGraph(static_cast<int>(x3) + drawOffsetX3,
				static_cast<int>(y3) + drawOffsetY3, damageGraph3, TRUE);
		}
		else if (Reverse3)
		{
			DrawTurnGraph(static_cast<int>(x3) + drawOffsetX3,
				static_cast<int>(y3) + drawOffsetY3, graph3, TRUE);
		}
		else
		{
			DrawGraph(static_cast<int>(x3) + drawOffsetX3,
				static_cast<int>(y3) + drawOffsetY3, graph3, TRUE);
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
	// �G�l�~�[�Ƃ̓����蔻��
	if (((shotX > x1 && shotX < x1) ||
		(x1 > shotX && x1 < shotX + shotW)) &&
		((shotY > y1 && shotY < y1 + h1) ||
			(y1 > shotY && y1 < shotY + shotH)))
	{
		//�w�b�h�V���b�g����
		/*if (true )
		{
			life1 -= 10;
		}*/

		// �ڐG���Ă���ꍇ�͓��������e�̑��݂�����
		visibleFlag = false;

		// �G�l�~�[�̊��c�߂Ă��邩�ǂ�����ێ�����ϐ��Ɂw�c�߂Ă���x��\��TRUE����
		damageFlag1 = true;

		// �G�l�~�[�̊��c�߂Ă��鎞�Ԃ𑪂�J�E���^�ϐ��ɂO����
		damageCounter1 = 0;

		// ���C�t�������X�R�A���Z
		life1 -= 1;
	}
}

void Enemy::OnHitShot2(int shotX, int shotY, int shotW, int shotH, bool visibleFlag)
{
	// �G�l�~�[�Ƃ̓����蔻��
	if (((shotX > x2 && shotX < x2) ||
		(x2 > shotX && x2 < shotX + shotW)) &&
		((shotY > y2 && shotY < y2 + h2) ||
			(y2 > shotY && y2 < shotY + shotH)))
	{
		//�w�b�h�V���b�g����
		/*if (true )
		{
			life2 -= 10;
		}*/

		// �ڐG���Ă���ꍇ�͓��������e�̑��݂�����
		visibleFlag = false;

		// �G�l�~�[�̊��c�߂Ă��邩�ǂ�����ێ�����ϐ��Ɂw�c�߂Ă���x��\��TRUE����
		damageFlag2 = true;

		// �G�l�~�[�̊��c�߂Ă��鎞�Ԃ𑪂�J�E���^�ϐ��ɂO����
		damageCounter2 = 0;

		// ���C�t�������X�R�A���Z
		life2 -= 1;
	}
}

void Enemy::OnHitShot3(int shotX, int shotY, int shotW, int shotH, bool visibleFlag)
{
	// �G�l�~�[�Ƃ̓����蔻��
	if (((shotX > x3 && shotX < x3) ||
		(x3 > shotX && x3 < shotX + shotW)) &&
		((shotY > y3 && shotY < y3 + h3) ||
			(y3 > shotY && y3 < shotY + shotH)))
	{
		//�w�b�h�V���b�g����
		/*if (true )
		{
			life3 -= 10;
		}*/

		// �ڐG���Ă���ꍇ�͓��������e�̑��݂�����
		visibleFlag = false;

		// �G�l�~�[�̊��c�߂Ă��邩�ǂ�����ێ�����ϐ��Ɂw�c�߂Ă���x��\��TRUE����
		damageFlag3 = true;

		// �G�l�~�[�̊��c�߂Ă��鎞�Ԃ𑪂�J�E���^�ϐ��ɂO����
		damageCounter3 = 0;

		// ���C�t�������X�R�A���Z
		life3 -= 1;
	}
}

//void Enemy::setPosition(float x, float y, int num)
//{
//	PosX[num] = x;
//	PosY[num] = y;
//}

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


