#pragma once

#include "DxLib.h"

#define ENEMY_LIFE		80
#define ENEMY_NUM		2
#define ENEMY_MAXX		1900
#define ENEMY_MAXY		600
#define ENEMY_SPEED		3
#define ENEMY_SHOTTIME  60

class Player;
class Music;
class ShotEnemy;
struct sHitRect;

// �G�l�~�[.
class Enemy
{
private:
	float	x1;
	float	y1;
	int		w1;
	int		h1;
	float	vx1, vy1;
	int		count1;						//�c��e���J�E���g
	int		ShotTimeCount1;				//���ˎ��ԃJ�E���g

	float	x2;
	float	y2;
	int		w2;
	int		h2;
	float	vx2, vy2;

	float	x3;
	float	y3;
	int		w3;
	int		h3;
	float	vx3, vy3;
	
	//int num[ENEMY_NUM];
	//float x[ENEMY_NUM];
	//float y[ENEMY_NUM];
	//float PosX[ENEMY_NUM] = {};
	//float PosY[ENEMY_NUM] = {};

	int		Graph1;										// �ʏ�摜
	int		DamageGraph1;								// �_���[�W�摜
	bool	DamageFlag1;								// �_���[�W�󂯂���
	int		DamageCounter1;								// �_���[�W��

	int		Graph2;										// �ʏ�摜
	int		DamageGraph2;								// �_���[�W�摜
	bool	DamageFlag2;								// �_���[�W�󂯂���
	int		DamageCounter2;								// �_���[�W��

	int		Graph3;										// �ʏ�摜
	int		DamageGraph3;								// �_���[�W�摜
	bool	DamageFlag3;								// �_���[�W�󂯂���
	int		DamageCounter3;								// �_���[�W��

	bool	LivFlag1;									// �����Ă��邩
	int		LivCounter1;								// �����Ґ�
	int		LivGraph1;									// 

	bool	LivFlag2;									// �����Ă��邩
	int		LivCounter2;								// �����Ґ�
	int		LivGraph2;									// 

	bool	LivFlag3;									// �����Ă��邩
	int		LivCounter3;								// �����Ґ�
	int		LivGraph3;									// 
	
	bool	IsRightMove1;								// ��ʊO�ɂ����Ȃ�
	int		DrawOffsetX1;								// �����蔻�肩��̉��������炵��
	int		DrawOffsetY1;								// �����蔻�肩��̏c�������炵��

	bool	IsRightMove2;								// ��ʊO�ɂ����Ȃ�
	int		DrawOffsetX2;								// �����蔻�肩��̉��������炵��
	int		DrawOffsetY2;								// �����蔻�肩��̏c�������炵��

	bool	IsRightMove3;								// ��ʊO�ɂ����Ȃ�
	int		DrawOffsetX3;								// �����蔻�肩��̉��������炵��
	int		DrawOffsetY3;								// �����蔻�肩��̏c�������炵��

	const int		imageSizeX1				= 64;		// �摜���T�C�Y
	const int		imageSizeY1				= 128;		// �摜�c�T�C�Y
	const int		hitSizeX1				= 50;		// �����蔻��T�C�Y��
	const int		hitSizeY1				= 100;		// �����蔻��T�C�Y����

	const int		imageSizeX2				= 64;		// �摜���T�C�Y
	const int		imageSizeY2				= 128;		// �摜�c�T�C�Y
	const int		hitSizeX2				= 50;		// �����蔻��T�C�Y��
	const int		hitSizeY2				= 100;		// �����蔻��T�C�Y����

	const int		imageSizeX3				= 64;		// �摜���T�C�Y
	const int		imageSizeY3				= 128;		// �摜�c�T�C�Y
	const int		hitSizeX3				= 50;		// �����蔻��T�C�Y��
	const int		hitSizeY3				= 100;		// �����蔻��T�C�Y����

	const float		jumpInitalVelocity1		= 10.5f;	// �W�����v�����x
	const int		colliderOffset1			= 10;		// �R���C�_�[���E���炵��
	const float		gravity1				= 15.0f;	// �d��
	const float		maxFallSpeed1			= 300.0f;	// �ő嗎�����x
	const float		hitHeadBrakeRatio1		= -0.1f;	// ����Փˎ��̌�����
	
	const float		jumpInitalVelocity2		= 11.0f;	// �W�����v�����x
	const int		colliderOffset2			= 10;		// �R���C�_�[���E���炵��
	const float		gravity2				= 15.0f;	// �d��
	const float		maxFallSpeed2			= 300.0f;	// �ő嗎�����x
	const float		hitHeadBrakeRatio2		= -0.1f;	// ����Փˎ��̌�����

	const float		jumpInitalVelocity3		= 11.5f;	// �W�����v�����x
	const int		colliderOffset3			= 10;		// �R���C�_�[���E���炵��
	const float		gravity3				= 15.0f;	// �d��
	const float		maxFallSpeed3			= 300.0f;	// �ő嗎�����x
	const float		hitHeadBrakeRatio3		= -0.1f;    // ����Փˎ��̌�����


	bool  jumpFlag1;									// �W�����v�t���O
	bool  onGround1;									// �n�ʂɗ����Ă��邩
	bool  hitHead1;										// ��������������
	bool  hitPlayerFlag1;								// �v���C���[�ɓ���������
	bool  ShotFlag1;									// ���˂��Ă��邩
	bool  Reverse1;										//���]	
	
	bool  jumpFlag2;									// �W�����v�t���O
	bool  onGround2;									// �n�ʂɗ����Ă��邩
	bool  hitHead2;										// ��������������
	bool  hitPlayerFlag2;								// �v���C���[�ɓ���������
	bool  Reverse2;										//���]

	bool  jumpFlag3;									// �W�����v�t���O
	bool  onGround3;									// �n�ʂɗ����Ă��邩
	bool  hitHead3;										// ��������������	
	bool  hitPlayerFlag3;								// �v���C���[�ɓ���������
	bool  Reverse3;										//���]

public:

	int		life1;										// �G�P�̗̑�
	int		life2;										// �G�Q�̗̑�
	int		life3;										// �G�R�̗̑�

	// ������
	void Init1();
	void Init2();
	void Init3();

	// �A�b�v�f�[�g
	void Update1(Player player, Music music, ShotEnemy shot[], int shotnum, float deltaTime);
	void Update2(Player player, Music music, float deltaTime);
	void Update3(Player player, Music music, float deltaTime);

	// �`��
	void Draw1();
	void Draw2();
	void Draw3();
	
	void OnHitShot1(int shotX, int shotY, int shotW, int shotH, bool visibleFlag);
	void OnHitShot2(int shotX, int shotY, int shotW, int shotH, bool visibleFlag);
	void OnHitShot3(int shotX, int shotY, int shotW, int shotH, bool visibleFlag);

	//bool GetPosX()const { return PosX; }
	//bool GetPosY()const { return PosY; }
	//bool GetScore()const { return Score; }
	
	bool GetLife1()const { return life1; }
	bool GetLife2()const { return life2; }
	bool GetLife3()const { return life3; }

	bool GetX1() const { return x1; }
	bool GetY1() const { return y1; }
	bool GetW1() const { return w1; }
	bool GetH1() const { return h1; }

	bool GetReverse1() const { return Reverse1; }

	//<summary>
	//�G�l�~�[�̓����蔻���`��Ԃ�
	//</summary>
	//<returns>�����蔻���`</returns>
	sHitRect getHitRect1();

	//<summary>
	//�G�l�~�[�̓����蔻���`��Ԃ�
	//</summary>
	//<returns>�����蔻���`</returns>
	sHitRect getHitRect2();

	//<summary>
	//�G�l�~�[�̓����蔻���`��Ԃ�
	//</summary>
	//<returns>�����蔻���`</returns>
	sHitRect getHitRect3();

	//<summary>
	//�����蔻��̈ʒu�C��
	//</summary>
	//<param name="hitRect">�����蔻���`</param>
	void fixColPosition1(sHitRect& hitRect);

	//<summary>
	//�����蔻��̈ʒu�C��
	//</summary>
	//<param name="hitRect">�����蔻���`</param>
	void fixColPosition2(sHitRect& hitRect);

	//<summary>
	//�����蔻��̈ʒu�C��
	//</summary>
	//<param name="hitRect">�����蔻���`</param>
	void fixColPosition3(sHitRect& hitRect);

	//<summary>
	//���������蔻��
	//</summary>
	//<param name="groundFlg">�����̓����蔻�茋��</param>
	void SetGroundFlag1(bool groundFlag);

	//<summary>
	//���������蔻��
	//</summary>
	//<param name="groundFlg">�����̓����蔻�茋��</param>
	void SetGroundFlag2(bool groundFlag);

	//<summary>
	//���������蔻��
	//</summary>
	//<param name="groundFlg">�����̓����蔻�茋��</param>
	void SetGroundFlag3(bool groundFlag);

	//<summary>
	//���̓����蔻��
	//</summary>
	//<param name="headHitFlg">���̓����蔻�茋��</param>
	void SetHeadHitFlag1(bool headHitFlag);

	//<summary>
	//���̓����蔻��
	//</summary>
	//<param name="headHitFlg">���̓����蔻�茋��</param>
	void SetHeadHitFlag2(bool headHitFlag);

	// <summary>
	// ���̓����蔻��
	// </summary>
	// <param name="headHitFlg">���̓����蔻�茋��</param>
	void SetHeadHitFlag3(bool headHitFlag);

	//<summary>
	//�����R���C�_�[�擾
	//</summary>
	//<returns>�����R���C�_�[�̋�`���</returns>
	sHitRect GetGroundCollider1();

	//<summary>
	//�����R���C�_�[�擾
	//</summary>
	//<returns>�����R���C�_�[�̋�`���</returns>
	sHitRect GetGroundCollider2();

	//<summary>
	//�����R���C�_�[�擾
	//</summary>
	//<returns>�����R���C�_�[�̋�`���</returns>
	sHitRect GetGroundCollider3();

	//<summary>
	//����R���C�_�[�擾
	//</summary>
	//<returns>����R���C�_�[�̋�`���</returns>
	sHitRect GetHeadCollider1();

	//<summary>
	//����R���C�_�[�擾
	//</summary>
	//<returns>����R���C�_�[�̋�`���</returns>
	sHitRect GetHeadCollider2();

	//<summary>
	//����R���C�_�[�擾
	//</summary>
	//<returns>����R���C�_�[�̋�`���</returns>
	sHitRect GetHeadCollider3();
	
};