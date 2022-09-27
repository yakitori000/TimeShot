
#include "Enemy.h"

sHitRect hitrect;
sHitRect enemyHit;                          // �v���C���[�����蔻��
sHitRect enemyFootCollider;                 // �ڒn�R���C�_�[
sHitRect enemyHeadCollider;                 // ����R���C�_�[

// ������
void Enemy::Init()
{
	// �G�l�~�[�̃O���t�B�b�N���������Ƀ��[�h���\�����W��������
	
	graph = LoadGraph("data/image/Zonbi3.png");
	damageGraph = LoadGraph("data/image/Zonbi.png");
	GraphFilter(damageGraph, DX_GRAPH_FILTER_HSB, 120, 120, 120, 256);
	
	life = ENEMY_LIFE;				//�G�̗̑�

	x = GetRand(ENEMY_MAXX);		//�G��X���W
	y = GetRand(ENEMY_MAXY);		//�G��Y���W
	
	// �����蔻�菉����
	initRect(enemyHit, hitSizeX, hitSizeY);
	initRect(enemyFootCollider, hitSizeX - colliderOffset, 1);
	initRect(enemyHeadCollider, hitSizeX - colliderOffset, 1);

	// �G�l�~�[�̃O���t�B�b�N�̃T�C�Y�𓾂�
	GetGraphSize(graph, &w, &h);

	// �`��ʒu�̃I�t�Z�b�g�l���v�Z
   // ���E���猩�ăZ���^�[�A�㉺�����͒�ӊ�ƂȂ�悤�Ɍv�Z
	drawOffsetX = (hitSizeX - imageSizeX) / 2;
	drawOffsetY = (hitSizeY - imageSizeY);

	jumpFlag = false;
	onGround = false;
	hitHead = false;
	Reverse = false;
	hitPlayerFlag = false;
	LivCounter = 0;

	// �G�l�~�[�����c�߂Ă��邩�ǂ����̕ϐ��Ɂw�c�߂Ă��Ȃ��x��\��FALSE����
	damageFlag = false;	
}


// �A�b�v�f�[�g.
void Enemy::Update(Player player, Music music, float deltaTime)
{
	//�ڒn���Ă�H
	if (onGround)
	{
		jumpFlag = false;
		vy = 0.0f;	
	}
	else
	{
		jumpFlag = true;
	}

	//����ɓ��������H
	if (hitHead)
	{
		vy = hitHeadBrakeRatio * vy;
	}

	// �G�l�~�[�̍��W���ړ����Ă�������Ɉړ�����
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

	//�ǂɓ���������W�����v����
	if (x == hitrect.worldLX)
	{
		// �����]��
		if (vx > 0.0f)
		{
			vx *= brakeRatio;
		}
		// �n������x
		vx += -moveAccell * deltaTime;
	}
	else
	{
		//�󒆉����x
		vy += -moveAccell * inAirMoveAccelRatio * deltaTime;
	}
	
	if (!jumpFlag)
	{
		vy -= jumpInitalVelocity;
		jumpFlag = true;
		onGround = false;
	}

	// �W�����v���Ȃ�d�͂𔭐�
	if (jumpFlag)
	{
		vy += gravity * deltaTime;
	}

	// �ʒu�X�V
	x += vx;
	y += vy;

	// �G�l�~�[����ʒ[����ł����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă����A�ړ�������������]����
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

	// �G�l�~�[��`��
	// �_���[�W���󂯂Ă��邩�ǂ����ŏ����𕪊�
	if (damageFlag == true)
	{
		damageCounter++;
		life--;

		if (damageCounter == 5)
		{
			//�w�_���[�W�������Ă��Ȃ��x��\��FALSE����
			damageFlag = false;
		}
		if (life <= 0)
		{
			LivCounter--;
		}
	}

	//�v���C���[�ɓ������Ă��邩
	if (player.GetHitPoint() > 0)
	{
		player.OnHitEnemy(x, y, w, h);
		hitPlayerFlag = true;
		//music.playEnemy(hitPlayerFlag);
	}

	// �����蔻��ʒu�X�V
	updateWorldRect(enemyHit, x, y);
	updateWorldRect(enemyFootCollider, x + colliderOffset / 2, y + enemyHit.h);
	updateWorldRect(enemyHeadCollider, x + colliderOffset / 2, y + enemyHeadCollider.h);
}

// �`��.
void Enemy::Draw()
{

	if (life > 0)
	{
		// �_���[�W���󂯂Ă���ꍇ�̓_���[�W���̃O���t�B�b�N��`�悷��
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
	// �G�l�~�[�Ƃ̓����蔻��
	if (((shotX > x && shotX < x) ||
		(x > shotX && x < shotX + shotW)) &&
		((shotY > y && shotY < y + h) ||
			(y > shotY && y < shotY + shotH)))
	{
		//�w�b�h�V���b�g����
		/*if (true )
		{
			life -= 10;
		}*/
		
		// �ڐG���Ă���ꍇ�͓��������e�̑��݂�����
		visibleFlag = false;

		// �G�l�~�[�̊��c�߂Ă��邩�ǂ�����ێ�����ϐ��Ɂw�c�߂Ă���x��\��TRUE����
		damageFlag = true;

		// �G�l�~�[�̊��c�߂Ă��鎞�Ԃ𑪂�J�E���^�ϐ��ɂO����
		damageCounter = 0;

		// ���C�t�������X�R�A���Z
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

