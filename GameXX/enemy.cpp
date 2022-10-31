
#include "Enemy.h"
#include "Player.h"
#include "ShotEnemy.h"
#include "Music.h"
#include "map.h"
#include "function.h"
#include "collision.h"

//�G�P
sHitRect hitrect[ENEMY_NUM];
sHitRect enemyHit[ENEMY_NUM];                          // �G�����蔻��
sHitRect enemyFootCollider[ENEMY_NUM];                 // �ڒn�R���C�_�[
sHitRect enemyHeadCollider[ENEMY_NUM];                 // ����R���C�_�[

////�G�P
//sHitRect hitrect1;
//sHitRect enemyHit1;                          // �G�P�����蔻��
//sHitRect enemyFootCollider1;                 // �ڒn�R���C�_�[
//sHitRect enemyHeadCollider1;                 // ����R���C�_�[
//
////�G�Q
//sHitRect hitrect2;
//sHitRect enemyHit2;                          // �G�Q�����蔻��
//sHitRect enemyFootCollider2;                 // �ڒn�R���C�_�[
//sHitRect enemyHeadCollider2;                 // ����R���C�_�[
//
////�G�R
//sHitRect hitrect3;
//sHitRect enemyHit3;                          // �G�R�����蔻��
//sHitRect enemyFootCollider3;                 // �ڒn�R���C�_�[
//sHitRect enemyHeadCollider3;                 // ����R���C�_�[

void Enemy::Init()
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		// �G�l�~�[�̃O���t�B�b�N���������Ƀ��[�h���\�����W��������
		Graph[i] = LoadGraph("data/image/Zonbi1.png");
		DamageGraph[i] = LoadGraph("data/image/Zonbi.png");
		GraphFilter(DamageGraph[i], DX_GRAPH_FILTER_HSB, 120, 120, 120, 256);

		life[i] = ENEMY_LIFE;			//�G�̗̑�

		x[i] = GetRand(ENEMY_MAXX);		//�G��X���W
		y[i] = GetRand(ENEMY_MAXY);		//�G��Y���W

		if (x[i] >= ENEMY_MAXX)
		{
			x[i] == ENEMY_MAXX;
		}
		if (y[i] >= ENEMY_MAXY)
		{
			y[i] == ENEMY_MAXY;
		}

		for (int i = 0; i < ENEMY_NUM; i++)
		{
			// �����蔻�菉�����@�G
			initRect(enemyHit[i], hitSizeX, hitSizeY);
			initRect(enemyFootCollider[i], hitSizeX - colliderOffset, 1);
			initRect(enemyHeadCollider[i], hitSizeX - colliderOffset, 1);
		}

		// �G�l�~�[�̃O���t�B�b�N�̃T�C�Y���擾
		GetGraphSize(Graph[i], &w[i], &h[i]);

		// �`��ʒu�̃I�t�Z�b�g�l���v�Z
	   // ���E���猩�ăZ���^�[�A�㉺�����͒�ӊ�ƂȂ�悤�Ɍv�Z
		DrawOffsetX[i] = (hitSizeX - imageSizeX) / 2;
		DrawOffsetY[i] = (hitSizeY - imageSizeY);

		jumpFlag = false;
		onGround = false;
		hitHead	 = false;
		Reverse	 = false;

		hitPlayerFlag = false;
		DamageFlag[i] = false;
		ShotFlag	 = false;

		LivCounter[i] = 0;
		ShotTimeCount[i] = 0;
		count[i] = ESHOT;
	}
	
}

// ������
//void Enemy::Init1()
//{
//	// �G�l�~�[�̃O���t�B�b�N���������Ƀ��[�h���\�����W��������
//	
//	Graph1 = LoadGraph("data/image/Zonbi1.png");
//	DamageGraph1 = LoadGraph("data/image/Zonbi.png");
//	GraphFilter(DamageGraph1, DX_GRAPH_FILTER_HSB, 120, 120, 120, 256);
//	
//	life1 = ENEMY_LIFE;				//�G1�̗̑�
//
//
//
//	x1 = GetRand(ENEMY_MAXX);		//�G1��X���W
//	y1 = GetRand(ENEMY_MAXY);		//�G1��Y���W
//	
//	if (x1 >= ENEMY_MAXX)
//	{
//		x1 == ENEMY_MAXX;
//	}
//	if (y1 >= ENEMY_MAXY)
//	{
//		y1 == ENEMY_MAXY;
//	}
//
//	// �����蔻�菉�����@�G�P
//	initRect(enemyHit1, hitSizeX, hitSizeY);
//	initRect(enemyFootCollider1, hitSizeX - colliderOffset, 1);
//	initRect(enemyHeadCollider1, hitSizeX - colliderOffset, 1);
//	
//	// �G�l�~�[�̃O���t�B�b�N�̃T�C�Y���擾
//	GetGraphSize(Graph1, &w1, &h1);
//
//	// �`��ʒu�̃I�t�Z�b�g�l���v�Z
//   // ���E���猩�ăZ���^�[�A�㉺�����͒�ӊ�ƂȂ�悤�Ɍv�Z
//	DrawOffsetX1 = (hitSizeX - imageSizeX) / 2;
//	DrawOffsetY1 = (hitSizeY - imageSizeY);
//
//	jumpFlag1		= false;
//	onGround1		= false;
//	hitHead1		= false;
//	Reverse1		= false;
//	hitPlayerFlag1  = false;
//	DamageFlag1		= false;
//	ShotFlag1		= false;
//	
//	LivCounter1 = 0;
//	ShotTimeCount1 = 0;
//	count1 = ESHOT;
//}
//
//void Enemy::Init2()
//{
//	Graph2 = LoadGraph("data/image/Zonbi2.png");
//	DamageGraph2 = LoadGraph("data/image/Zonbi.png");
//	GraphFilter(DamageGraph2, DX_GRAPH_FILTER_HSB, 120, 120, 120, 256);
//
//	life2 = ENEMY_LIFE;				//�G2�̗̑�
//
//	x2 = GetRand(ENEMY_MAXX);		//�G2��X���W
//	y2 = GetRand(ENEMY_MAXY);		//�G2��Y���W
//
//	if (x2 >= ENEMY_MAXX)
//	{
//		x2 == ENEMY_MAXX;
//	}
//	if (y2 >= ENEMY_MAXY)
//	{
//		y2 == ENEMY_MAXY;
//	}
//
//	// �����蔻�菉�����@�G�Q
//	initRect(enemyHit2, hitSizeX, hitSizeY);
//	initRect(enemyFootCollider2, hitSizeX - colliderOffset, 1);
//	initRect(enemyHeadCollider2, hitSizeX - colliderOffset, 1);
//
//	// �G�l�~�[�̃O���t�B�b�N�̃T�C�Y���擾
//	GetGraphSize(Graph2, &w2, &h2);
//
//	// �`��ʒu�̃I�t�Z�b�g�l���v�Z
//   // ���E���猩�ăZ���^�[�A�㉺�����͒�ӊ�ƂȂ�悤�Ɍv�Z
//	DrawOffsetX2 = (hitSizeX - imageSizeX) / 2;
//	DrawOffsetY2 = (hitSizeY - imageSizeY);
//
//	jumpFlag2		= false;
//	onGround2		= false;
//	hitHead2		= false;
//	Reverse2		= false;
//	hitPlayerFlag2  = false;
//	DamageFlag2		= false;
//	
//	LivCounter2 = 0;
//}
//
//void Enemy::Init3()
//{
//	Graph3 = LoadGraph("data/image/Zonbi3.png");
//	DamageGraph3 = LoadGraph("data/image/Zonbi.png");
//	GraphFilter(DamageGraph3, DX_GRAPH_FILTER_HSB, 120, 120, 120, 256);
//
//	life3 = ENEMY_LIFE;				//�G3�̗̑�
//
//	x3 = GetRand(ENEMY_MAXX);		//�G3��X���W
//	y3 = GetRand(ENEMY_MAXY);		//�G3��Y���W
//
//	if (x3 >= ENEMY_MAXX)
//	{
//		x3 == ENEMY_MAXX;
//	}
//	if (y3 >= ENEMY_MAXY)
//	{
//		y3 == ENEMY_MAXY;
//	}
//
//	// �����蔻�菉�����@�G�R
//	initRect(enemyHit3, hitSizeX, hitSizeY);
//	initRect(enemyFootCollider3, hitSizeX - colliderOffset, 1);
//	initRect(enemyHeadCollider3, hitSizeX - colliderOffset, 1);
//
//	// �G�l�~�[�̃O���t�B�b�N�̃T�C�Y���擾
//	GetGraphSize(Graph3, &w3, &h3);
//
//	// �`��ʒu�̃I�t�Z�b�g�l���v�Z
//   // ���E���猩�ăZ���^�[�A�㉺�����͒�ӊ�ƂȂ�悤�Ɍv�Z
//	DrawOffsetX3 = (hitSizeX - imageSizeX) / 2;
//	DrawOffsetY3 = (hitSizeY - imageSizeY);
//
//	jumpFlag3		 = false;
//	onGround3		 = false;
//	hitHead3		 = false;
//	Reverse3		 = false;
//	hitPlayerFlag3   = false;
//	DamageFlag3		 = false;
//	
//	LivCounter3 = 0;
//}

// �G�A�b�v�f�[�g
void Enemy::Update(Player player, Music music, ShotEnemy shot[], int shotnum, float deltaTime)
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		//�ڒn���Ă�H
		if (onGround)
		{
			jumpFlag = false;
			vy[i] = 0.0f;
		}
		else
		{
			jumpFlag = true;
		}

		//����ɓ��������H
		if (hitHead)
		{
			vy[i] = hitHeadBrakeRatio * vy[i];
		}

		// �G�l�~�[�̍��W���ړ����Ă�������Ɉړ�����

		if (IsRightMove[i] == true)
		{
			x[i] += ENEMY_SPEED;
			Reverse = true;
		}
		else
		{
			x[i] -= ENEMY_SPEED;
			Reverse = false;
		}

		if (!jumpFlag)
		{
			vy[i] -= jumpInitalVelocity;
			jumpFlag = true;
			onGround = false;
		}

		// �W�����v���Ȃ�d�͂𔭐�
		if (jumpFlag)
		{
			vy[i] += gravity * deltaTime;
		}

		// �ʒu�X�V

		x[i] += vx[i];
		y[i] += vy[i];


		// �G�l�~�[����ʊO�ɂł����Ȃ牟���߂��B�i�ړ�������������]����j
		if (x[i] > SCREEN_WMAX - w[i])
		{
			x[i] = SCREEN_WMAX - w[i];
			IsRightMove[i] = false;
		}
		else if (x[i] < SCREEN_WMIN)
		{
			x[i] = SCREEN_WMIN;

			IsRightMove[i] = true;
		}

		if (life[i] > 0)
		{
			//�e������Ȃ�
			if (count[i] > 0)
			{
				ShotTimeCount[i]++;
				music.playEnemyAtack(count[i]);
				if (ShotTimeCount[i] >= ENEMY_SHOTTIME)
				{
					// ��ʏ�ɂłĂ��Ȃ��e�����邩�A�e�̐������J��Ԃ���
					for (int j = 0; j < ESHOT; j++)
					{
						// �ei����ʏ�ɂłĂ��Ȃ��ꍇ�͂��̒e����ʂɏo��
						if (shot[j].IsEVisibleFlag() == 0)
						{
							shot[j].OnShotEnemy(x[i], (y[i] + 50), w[i], h[i]);
							count[i]--;
							ShotFlag = false;
							ShotTimeCount[i] = 0;
							break;
						}
					}
				}
			}
		}

		// �G�l�~�[��`��
		// �_���[�W���󂯂Ă��邩�ǂ����ŏ����𕪊�
		if (DamageFlag[i] == true)
		{
			DamageCounter[i]++;
			life[i]--;

			if (DamageCounter[i] == 5)
			{
				//�w�_���[�W�������Ă��Ȃ��x��\��FALSE����
				DamageFlag[i] = false;
			}
			if (life[i] <= 0)
			{
				LivCounter[i]--;
			}
		}

		//�v���C���[�ɓ������Ă��邩
		if (player.GetHitPoint() >= 0)
		{
			player.OnHitEnemy(x[i], y[i], w[i], h[i]);

			hitPlayerFlag = true;
			//music.playEnemy(hitPlayerFlag);
		}


		for (int i = 0; i < ENEMY_NUM; i++)
		{
			// �����蔻��ʒu�X�V
			updateWorldRect(enemyHit[i], x[i], y[i]);
			updateWorldRect(enemyFootCollider[i], x[i] + colliderOffset / 2, y[i] + enemyHit[i].h);
			updateWorldRect(enemyHeadCollider[i], x[i] + colliderOffset / 2, y[i] + enemyHeadCollider[i].h);
		}

	}
	
}

void Enemy::Draw()
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		//enemy
		if (life[i] > 0)
		{
			// �_���[�W���󂯂Ă���ꍇ�̓_���[�W���̃O���t�B�b�N��`�悷��
			if (DamageFlag[i] == true)
			{
				DrawGraph(static_cast<int>(x[i]) + DrawOffsetX[i],
					static_cast<int>(y[i]) + DrawOffsetY[i], Graph[i], TRUE);
			}
			else if (Reverse)
			{
				DrawTurnGraph(static_cast<int>(x[i]) + DrawOffsetX[i],
					static_cast<int>(y[i]) + DrawOffsetY[i], Graph[i], TRUE);
			}
			else
			{
				DrawGraph(static_cast<int>(x[i]) + DrawOffsetX[i],
					static_cast<int>(y[i]) + DrawOffsetY[i], Graph[i], TRUE);
			}
		}
	}
	
}



// �G�P�A�b�v�f�[�g
//void Enemy::Update1(Player player, Music music, ShotEnemy shot[], int shotnum, float deltaTime)
//{
//	//�ڒn���Ă�H
//	if (onGround1)
//	{
//		jumpFlag1 = false;
//		vy1 = 0.0f;	
//	}
//	else
//	{
//		jumpFlag1 = true;
//	}
//
//	//����ɓ��������H
//	if (hitHead1)
//	{
//		vy1 = hitHeadBrakeRatio * vy1;
//	}
//
//	// �G�l�~�[�̍��W���ړ����Ă�������Ɉړ�����
//	
//	if (IsRightMove1 == true)
//	{
//		x1 += ENEMY_SPEED;
//		Reverse1 = true;
//	}
//	else
//	{
//		x1 -= ENEMY_SPEED;
//		Reverse1 = false;
//	}
//	
//	if (!jumpFlag1)
//	{
//		vy1 -= jumpInitalVelocity	;
//		jumpFlag1 = true;
//		onGround1 = false;
//	}
//
//	// �W�����v���Ȃ�d�͂𔭐�
//	if (jumpFlag1)
//	{
//		vy1 += gravity * deltaTime;
//	}
//
//	// �ʒu�X�V
//	
//	x1 += vx1;
//	y1 += vy1;
//	
//
//	// �G�l�~�[����ʊO�ɂł����Ȃ牟���߂��B�i�ړ�������������]����j
//	if (x1 > SCREEN_WMAX - w1)
//	{
//		x1 = SCREEN_WMAX - w1;
//		IsRightMove1 = false;
//	}
//	else if (x1 < SCREEN_WMIN)
//	{
//		x1 = SCREEN_WMIN;
//	
//		IsRightMove1 = true;
//	}
//
//	if (life1 > 0)
//	{
//		//�e������Ȃ�
//		if (count1 > 0)
//		{
//			ShotTimeCount1++;
//			music.playEnemyAtack(count1);
//			if (ShotTimeCount1 >= ENEMY_SHOTTIME)
//			{
//				// ��ʏ�ɂłĂ��Ȃ��e�����邩�A�e�̐������J��Ԃ���
//				for (int i = 0; i < ESHOT; i++)
//				{
//					// �ei����ʏ�ɂłĂ��Ȃ��ꍇ�͂��̒e����ʂɏo��
//					if (shot[i].IsEVisibleFlag() == 0)
//					{
//						shot[i].OnShotEnemy(x1, (y1 + 50), w1, h1);
//						count1 --;
//						ShotFlag1 = false;
//						ShotTimeCount1 = 0;
//						break;
//					}
//				}
//			}
//		}
//	}
//
//	// �G�l�~�[��`��
//	// �_���[�W���󂯂Ă��邩�ǂ����ŏ����𕪊�
//	if (DamageFlag1 == true)
//	{
//		DamageCounter1++;
//		life1 --;
//
//		if (DamageCounter1 == 5)
//		{
//			//�w�_���[�W�������Ă��Ȃ��x��\��FALSE����
//			DamageFlag1 = false;
//		}
//		if (life1 <= 0)
//		{
//			LivCounter1 --;
//		}
//	}
//
//	//�v���C���[�ɓ������Ă��邩
//	if (player.GetHitPoint() >= 0)
//	{
//		player.OnHitEnemy(x1, y1, w1, h1);
//
//		hitPlayerFlag1 = true;
//		//music.playEnemy(hitPlayerFlag);
//	}
//	
//	// �����蔻��ʒu�X�V
//	updateWorldRect(enemyHit1, x1, y1);
//	updateWorldRect(enemyFootCollider1, x1 + colliderOffset / 2, y1 + enemyHit1.h);
//	updateWorldRect(enemyHeadCollider1, x1 + colliderOffset / 2, y1 + enemyHeadCollider1.h);
//	
//}
//
//// �G�Q�A�b�v�f�[�g
//void Enemy::Update2(Player player, Music music, float deltaTime)
//{
//	//�ڒn���Ă�H
//	if (onGround2)
//	{
//		jumpFlag2 = false;
//		vy2 = 0.0f;
//	}
//	else
//	{
//		jumpFlag2 = true;
//	}
//
//	//����ɓ��������H
//	if (hitHead2)
//	{
//		vy2 = hitHeadBrakeRatio * vy2;
//	}
//
//	// �G�l�~�[�̍��W���ړ����Ă�������Ɉړ�����
//	if (IsRightMove2 == true)
//	{
//		x2 += ENEMY_SPEED;
//		Reverse2 = true;
//	}
//	else
//	{
//		x2 -= ENEMY_SPEED;
//		Reverse2 = false;
//	}
//
//
//	if (!jumpFlag2)
//	{
//		vy2 -= jumpInitalVelocity	;
//		jumpFlag2 = true;
//		onGround2 = false;
//	}
//
//	// �W�����v���Ȃ�d�͂𔭐�
//	if (jumpFlag2)
//	{
//		vy2 += gravity * deltaTime;
//	}
//
//	// �ʒu�X�V
//	x2 += vx2;
//	y2 += vy2;
//
//
//	// �G�l�~�[����ʒ[����ł����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă����A�ړ�������������]����
//	if (x2 > SCREEN_WMAX - w2)
//	{
//		x2 = SCREEN_WMAX - w2;
//		IsRightMove2 = false;
//	}
//	else if (x2 < SCREEN_WMIN)
//	{
//		x2 = SCREEN_WMIN;
//
//		IsRightMove2 = true;
//	}
//
//	// �G�l�~�[��`��
//	// �_���[�W���󂯂Ă��邩�ǂ����ŏ����𕪊�
//	if (DamageFlag2 == true)
//	{
//		DamageCounter2++;
//		life2--;
//
//		if (DamageCounter2 == 5)
//		{
//			//�w�_���[�W�������Ă��Ȃ��x��\��FALSE����
//			DamageFlag2 = false;
//		}
//		if (life2 <= 0)
//		{
//			LivCounter2--;
//		}
//	}
//
//	//�v���C���[�ɓ������Ă��邩
//	if (player.GetHitPoint() >= 0)
//	{
//		player.OnHitEnemy(x2, y2, w2, h2);
//
//		hitPlayerFlag2 = true;
//		//music.playEnemy(hitPlayerFlag);
//	}
//
//	// �����蔻��ʒu�X�V
//	updateWorldRect(enemyHit2, x2, y2);
//	updateWorldRect(enemyFootCollider2, x2 + colliderOffset / 2, y2 + enemyHit2.h);
//	updateWorldRect(enemyHeadCollider2, x2 + colliderOffset / 2, y2 + enemyHeadCollider2.h);
//
//}
//
//// �G�R�A�b�v�f�[�g
//void Enemy::Update3(Player player, Music music, float deltaTime)
//{
//	//�ڒn���Ă�H
//	if (onGround3)
//	{
//		jumpFlag3 = false;
//		vy3 = 0.0f;
//	}
//	else
//	{
//		jumpFlag3 = true;
//	}
//
//	//����ɓ��������H
//	if (hitHead3)
//	{
//		vy3 = hitHeadBrakeRatio * vy3;
//	}
//
//	// �G�l�~�[�̍��W���ړ����Ă�������Ɉړ�����
//	if (IsRightMove3 == true)
//	{
//		x3 += ENEMY_SPEED;
//		Reverse3 = true;
//	}
//	else
//	{
//		x3 -= ENEMY_SPEED;
//		Reverse3 = false;
//	}
//
//	if (!jumpFlag3)
//	{
//		vy3 -= jumpInitalVelocity	;
//		jumpFlag3 = true;
//		onGround3 = false;
//	}
//
//	// �W�����v���Ȃ�d�͂𔭐�
//	if (jumpFlag3)
//	{
//		vy3 += gravity * deltaTime;
//	}
//
//	// �ʒu�X�V
//	x3 += vx3;
//	y3 += vy3;
//
//	// �G�l�~�[����ʒ[����ł����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă����A�ړ�������������]����
//	if (x3 > SCREEN_WMAX - w3)
//	{
//		x3 = SCREEN_WMAX - w3;
//		IsRightMove3 = false;
//	}
//	else if (x3 < SCREEN_WMIN)
//	{
//		x3 = SCREEN_WMIN;
//
//		IsRightMove3 = true;
//	}
//
//	// �G�l�~�[��`��
//	// �_���[�W���󂯂Ă��邩�ǂ����ŏ����𕪊�
//	if (DamageFlag3 == true)
//	{
//		DamageCounter3++;
//		life3--;
//
//		if (DamageCounter3 == 5)
//		{
//			//�w�_���[�W�������Ă��Ȃ��x��\��FALSE����
//			DamageFlag3 = false;
//		}
//		if (life3 <= 0)
//		{
//			LivCounter3--;
//		}
//	}
//
//	//�v���C���[�ɓ������Ă��邩
//	if (player.GetHitPoint() >= 0)
//	{
//		player.OnHitEnemy(x3, y3, w3, h3);
//
//		hitPlayerFlag3 = true;
//		//music.playEnemy(hitPlayerFlag);
//	}
//
//	// �����蔻��ʒu�X�V
//	updateWorldRect(enemyHit3, x3, y3);
//	updateWorldRect(enemyFootCollider3, x3 + colliderOffset / 2, y3 + enemyHit3.h);
//	updateWorldRect(enemyHeadCollider3, x3 + colliderOffset / 2, y3 + enemyHeadCollider3.h);
//
//}
//
//// �`��
//void Enemy::Draw1()
//{
//	//enemy1
//	if (life1 > 0)
//	{
//		// �_���[�W���󂯂Ă���ꍇ�̓_���[�W���̃O���t�B�b�N��`�悷��
//		if (DamageFlag1 == true)
//		{
//			DrawGraph(static_cast<int>(x1) + DrawOffsetX1,
//				static_cast<int>(y1) + DrawOffsetY1, Graph1, TRUE);
//		}
//		else if (Reverse1)
//		{
//			DrawTurnGraph(static_cast<int>(x1) + DrawOffsetX1,
//				static_cast<int>(y1) + DrawOffsetY1, Graph1, TRUE);
//		}
//		else
//		{
//			DrawGraph(static_cast<int>(x1) + DrawOffsetX1,
//				static_cast<int>(y1) + DrawOffsetY1, Graph1, TRUE);
//		}
//	}
//}
//
//void Enemy::Draw2()
//{
//	//enemy2
//	if (life2 > 0)
//	{
//		// �_���[�W���󂯂Ă���ꍇ�̓_���[�W���̃O���t�B�b�N��`�悷��
//		if (DamageFlag2 == true)
//		{
//			DrawGraph(static_cast<int>(x2) + DrawOffsetX2,
//				static_cast<int>(y2) + DrawOffsetY2, DamageGraph2, TRUE);
//		}
//		else if (Reverse2)
//		{
//			DrawTurnGraph(static_cast<int>(x2) + DrawOffsetX2,
//				static_cast<int>(y2) + DrawOffsetY2, Graph2, TRUE);
//		}
//		else
//		{
//			DrawGraph(static_cast<int>(x2) + DrawOffsetX2,
//				static_cast<int>(y2) + DrawOffsetY2, Graph2, TRUE);
//		}
//	}
//}
//
//
//void Enemy::Draw3()
//{
//	//enemy3
//	if (life3 > 0)
//	{
//		// �_���[�W���󂯂Ă���ꍇ�̓_���[�W���̃O���t�B�b�N��`�悷��
//		if (DamageFlag3 == true)
//		{
//			DrawGraph(x3 + DrawOffsetX3,
//				y3 + DrawOffsetY3, DamageGraph3, TRUE);
//		}
//		else if (Reverse3)
//		{
//			DrawTurnGraph(static_cast<int>(x3) + DrawOffsetX3,
//				static_cast<int>(y3) + DrawOffsetY3, Graph3, TRUE);
//		}
//		else
//		{
//			DrawGraph(static_cast<int>(x3) + DrawOffsetX3,
//				static_cast<int>(y3) + DrawOffsetY3, Graph3, TRUE);
//		}
//	}
//}

void Enemy::DrawHP(int life, int MAXlife)
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (GetLife() > 0)
		{
			const int FlameColor = GetColor(255, 100, 100);
			const int Color = GetColor(220, 220, 220);
			DrawBox(x[i] + 0, y[i] - 45, x[i] + 99, y[i] - 30, FlameColor, FALSE);
			DrawBox(x[i] + 0, y[i] - 44, x[i] + 98 * life / MAXlife, y[i] - 29, Color, TRUE);
		}
	}
	
}




sHitRect Enemy::getHitRect()
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		return enemyHit[i];
	}

}

//sHitRect Enemy::getHitRect1()
//{
//	return enemyHit1;
//}
//
//sHitRect Enemy::getHitRect2()
//{
//	return enemyHit2;
//}
//
//sHitRect Enemy::getHitRect3()
//{
//	return enemyHit3;
//}

void Enemy::fixColPosition(sHitRect& hitRect)
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		x[i] = hitRect.worldLX;
		y[i] = hitRect.worldLY;

		enemyHit[i] = hitRect;
	}
}

void Enemy::OnHitShot(int shotX, int shotY, int shotW, int shotH, bool visibleFlag)
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		// �G�l�~�[�Ƃ̓����蔻��
		if (((shotX > x[i] && shotX < x[i]) ||
			(x[i] > shotX && x[i] < shotX + shotW)) &&
			((shotY > y[i] && shotY < y[i] + h[i]) ||
				(y[i] > shotY && y[i] < shotY + shotH)))
		{
			//�w�b�h�V���b�g����
			/*if (true )
			{
				life1 -= 10;
			}*/

			// �ڐG���Ă���ꍇ�͓��������e�̑��݂�����
			visibleFlag = false;

			// �G�l�~�[�̊��c�߂Ă��邩�ǂ�����ێ�����ϐ��Ɂw�c�߂Ă���x��\��TRUE����
			DamageFlag[i] = true;

			// �G�l�~�[�̊��c�߂Ă��鎞�Ԃ𑪂�J�E���^�ϐ��ɂO����
			DamageCounter[i] = 0;

			// ���C�t�������X�R�A���Z
			life[i] -= 1;
		}
	}
	
}

//void Enemy::OnHitShot1(int shotX, int shotY, int shotW, int shotH, bool visibleFlag)
//{
//	// �G�l�~�[�Ƃ̓����蔻��
//	if (((shotX > x1 && shotX < x1) ||
//		(x1 > shotX && x1 < shotX + shotW)) &&
//		((shotY > y1 && shotY < y1 + h1) ||
//			(y1 > shotY && y1 < shotY + shotH)))
//	{
//		//�w�b�h�V���b�g����
//		/*if (true )
//		{
//			life1 -= 10;
//		}*/
//
//		// �ڐG���Ă���ꍇ�͓��������e�̑��݂�����
//		visibleFlag = false;
//
//		// �G�l�~�[�̊��c�߂Ă��邩�ǂ�����ێ�����ϐ��Ɂw�c�߂Ă���x��\��TRUE����
//		DamageFlag1 = true;
//
//		// �G�l�~�[�̊��c�߂Ă��鎞�Ԃ𑪂�J�E���^�ϐ��ɂO����
//		DamageCounter1 = 0;
//
//		// ���C�t�������X�R�A���Z
//		life1 -= 1;
//	}
//}
//
//void Enemy::OnHitShot2(int shotX, int shotY, int shotW, int shotH, bool visibleFlag)
//{
//	// �G�l�~�[�Ƃ̓����蔻��
//	if (((shotX > x2 && shotX < x2) ||
//		(x2 > shotX && x2 < shotX + shotW)) &&
//		((shotY > y2 && shotY < y2 + h2) ||
//			(y2 > shotY && y2 < shotY + shotH)))
//	{
//		//�w�b�h�V���b�g����
//		/*if (true )
//		{
//			life2 -= 10;
//		}*/
//
//		// �ڐG���Ă���ꍇ�͓��������e�̑��݂�����
//		visibleFlag = false;
//
//		// �G�l�~�[�̊��c�߂Ă��邩�ǂ�����ێ�����ϐ��Ɂw�c�߂Ă���x��\��TRUE����
//		DamageFlag2 = true;
//
//		// �G�l�~�[�̊��c�߂Ă��鎞�Ԃ𑪂�J�E���^�ϐ��ɂO����
//		DamageCounter2 = 0;
//
//		// ���C�t�������X�R�A���Z
//		life2 -= 1;
//	}
//}
//
//void Enemy::OnHitShot3(int shotX, int shotY, int shotW, int shotH, bool visibleFlag)
//{
//	// �G�l�~�[�Ƃ̓����蔻��
//	if (((shotX > x3 && shotX < x3) ||
//		(x3 > shotX && x3 < shotX + shotW)) &&
//		((shotY > y3 && shotY < y3 + h3) ||
//			(y3 > shotY && y3 < shotY + shotH)))
//	{
//		//�w�b�h�V���b�g����
//		/*if (true )
//		{
//			life3 -= 10;
//		}*/
//
//		// �ڐG���Ă���ꍇ�͓��������e�̑��݂�����
//		visibleFlag = false;
//
//		// �G�l�~�[�̊��c�߂Ă��邩�ǂ�����ێ�����ϐ��Ɂw�c�߂Ă���x��\��TRUE����
//		DamageFlag3 = true;
//
//		// �G�l�~�[�̊��c�߂Ă��鎞�Ԃ𑪂�J�E���^�ϐ��ɂO����
//		DamageCounter3 = 0;
//
//		// ���C�t�������X�R�A���Z
//		life3 -= 1;
//	}
//}
//
//void Enemy::fixColPosition1(sHitRect& hitRect)
//{
//	x1 = hitRect.worldLX;
//	y1 = hitRect.worldLY;
//
//	enemyHit1 = hitRect;
//}
//
//void Enemy::fixColPosition2(sHitRect& hitRect)
//{
//	x2 = hitRect.worldLX;
//	y2 = hitRect.worldLY;
//
//	enemyHit2 = hitRect;
//}
//
//void Enemy::fixColPosition3(sHitRect& hitRect)
//{
//	x3 = hitRect.worldLX;
//	y3 = hitRect.worldLY;
//
//	enemyHit3 = hitRect;
//}

void Enemy::SetGroundFlag(bool groundFlag)
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		onGround = groundFlag;
	}
	
}

//void Enemy::SetGroundFlag1(bool groundFlag)
//{
//	onGround1 = groundFlag;
//}
//
//void Enemy::SetGroundFlag2(bool groundFlag)
//{
//	onGround2 = groundFlag;
//}
//
//void Enemy::SetGroundFlag3(bool groundFlag)
//{
//	onGround3 = groundFlag;
//}

void Enemy::SetHeadHitFlag(bool headHitFlag)
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		hitHead = headHitFlag;
	}
	
}

//void Enemy::SetHeadHitFlag1(bool headHitFlag)
//{
//	hitHead1 = headHitFlag;
//}
//
//void Enemy::SetHeadHitFlag2(bool headHitFlag)
//{
//	hitHead2 = headHitFlag;
//}
//
//void Enemy::SetHeadHitFlag3(bool headHitFlag)
//{
//	hitHead3 = headHitFlag;
//}

sHitRect Enemy::GetGroundCollider()
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		return enemyFootCollider[i];
	}
}

//sHitRect Enemy::GetGroundCollider1()
//{
//	return enemyFootCollider1;
//}
//
//sHitRect Enemy::GetGroundCollider2()
//{
//	return enemyFootCollider2;
//}
//
//sHitRect Enemy::GetGroundCollider3()
//{
//	return enemyFootCollider3;
//}

sHitRect Enemy::GetHeadCollider()
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		return enemyHeadCollider[i];
	}
	
}

//sHitRect Enemy::GetHeadCollider1()
//{
//	return enemyHeadCollider1;
//}
//
//sHitRect Enemy::GetHeadCollider2()
//{
//	return enemyHeadCollider2;
//}
//
//sHitRect Enemy::GetHeadCollider3()
//{
//	return enemyHeadCollider3;
//}



