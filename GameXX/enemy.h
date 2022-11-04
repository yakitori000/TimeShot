#pragma once

#include "DxLib.h"

#define ENEMY_LIFE		80
#define ENEMY_NUM		5
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
	//float	x1;
	//float	y1;
	//int		w1;
	//int		h1;
	//float	vx1, vy1;
	//int		count1;						//�c��e���J�E���g
	//int		ShotTimeCount1;				//���ˎ��ԃJ�E���g

	//float	x2;
	//float	y2;
	//int		w2;
	//int		h2;
	//float	vx2, vy2;

	//float	x3;
	//float	y3;
	//int		w3;
	//int		h3;
	//float	vx3, vy3;

	float	x[ENEMY_NUM];
	float	y[ENEMY_NUM];
	int 	w[ENEMY_NUM];
	int 	h[ENEMY_NUM];
	float	vx[ENEMY_NUM], vy[ENEMY_NUM];
	int		count[ENEMY_NUM];							//�c��e���J�E���g
	int		ShotTimeCount[ENEMY_NUM];					//���ˎ��ԃJ�E���g

	int		Graph[ENEMY_NUM];							// �ʏ�摜
	int		DamageGraph[ENEMY_NUM];						// �_���[�W�摜
	bool	DamageFlag[ENEMY_NUM];						// �_���[�W�󂯂���
	int		DamageCounter[ENEMY_NUM];					// �_���[�W��

	bool	LivFlag[ENEMY_NUM];							// �����Ă��邩
	int		LivCounter[ENEMY_NUM];						// �����Ґ�
	int		LivGraph[ENEMY_NUM];						// 
	
	bool	IsRightMove[ENEMY_NUM];						// ��ʊO�ɂ����Ȃ�
	int		DrawOffsetX[ENEMY_NUM];						// �����蔻�肩��̉��������炵��
	int		DrawOffsetY[ENEMY_NUM];						// �����蔻�肩��̏c�������炵��

	//int num[ENEMY_NUM];
	//float x[ENEMY_NUM];
	//float y[ENEMY_NUM];
	//float PosX[ENEMY_NUM] = {};
	//float PosY[ENEMY_NUM] = {};

	//int		Graph1;										// �ʏ�摜
	//int		DamageGraph1;								// �_���[�W�摜
	//bool	DamageFlag1;								// �_���[�W�󂯂���
	//int		DamageCounter1;								// �_���[�W��

	//int		Graph2;										// �ʏ�摜
	//int		DamageGraph2;								// �_���[�W�摜
	//bool	DamageFlag2;								// �_���[�W�󂯂���
	//int		DamageCounter2;								// �_���[�W��

	//int		Graph3;										// �ʏ�摜
	//int		DamageGraph3;								// �_���[�W�摜
	//bool	DamageFlag3;								// �_���[�W�󂯂���
	//int		DamageCounter3;								// �_���[�W��

	//bool	LivFlag1;									// �����Ă��邩
	//int		LivCounter1;								// �����Ґ�
	//int		LivGraph1;									// 

	//bool	LivFlag2;									// �����Ă��邩
	//int		LivCounter2;								// �����Ґ�
	//int		LivGraph2;									// 

	//bool	LivFlag3;									// �����Ă��邩
	//int		LivCounter3;								// �����Ґ�
	//int		LivGraph3;									// 
	//
	//bool	IsRightMove1;								// ��ʊO�ɂ����Ȃ�
	//int		DrawOffsetX1;								// �����蔻�肩��̉��������炵��
	//int		DrawOffsetY1;								// �����蔻�肩��̏c�������炵��

	//bool	IsRightMove2;								// ��ʊO�ɂ����Ȃ�
	//int		DrawOffsetX2;								// �����蔻�肩��̉��������炵��
	//int		DrawOffsetY2;								// �����蔻�肩��̏c�������炵��

	//bool	IsRightMove3;								// ��ʊO�ɂ����Ȃ�
	//int		DrawOffsetX3;								// �����蔻�肩��̉��������炵��
	//int		DrawOffsetY3;								// �����蔻�肩��̏c�������炵��
	
	const int		imageSizeX	= 64;					// �摜���T�C�Y
	const int		imageSizeY	= 128;					// �摜�c�T�C�Y
	const int		hitSizeX	= 50;					// �����蔻��T�C�Y��
	const int		hitSizeY	= 100;					// �����蔻��T�C�Y����

	const float		jumpInitalVelocity	= 10.5f;		// �W�����v�����x
	const int		colliderOffset		= 10;			// �R���C�_�[���E���炵��
	const float		gravity				= 15.0f;		// �d��
	const float		maxFallSpeed		= 300.0f;		// �ő嗎�����x
	const float		hitHeadBrakeRatio	= -0.1f;		// ����Փˎ��̌�����

	bool  jumpFlag;							// �W�����v�t���O
	bool  onGround;							// �n�ʂɗ����Ă��邩
	bool  hitHead;							// ��������������
	bool  hitPlayerFlag;						// �v���C���[�ɓ���������
	bool  ShotFlag;							// ���˂��Ă��邩
	bool  Reverse;							//���]	

	//bool  jumpFlag1;									// �W�����v�t���O
	//bool  onGround1;									// �n�ʂɗ����Ă��邩
	//bool  hitHead1;										// ��������������
	//bool  hitPlayerFlag1;								// �v���C���[�ɓ���������
	//bool  ShotFlag1;									// ���˂��Ă��邩
	//bool  Reverse1;										//���]	
	//
	//bool  jumpFlag2;									// �W�����v�t���O
	//bool  onGround2;									// �n�ʂɗ����Ă��邩
	//bool  hitHead2;										// ��������������
	//bool  hitPlayerFlag2;								// �v���C���[�ɓ���������
	//bool  Reverse2;										//���]

	//bool  jumpFlag3;									// �W�����v�t���O
	//bool  onGround3;									// �n�ʂɗ����Ă��邩
	//bool  hitHead3;										// ��������������	
	//bool  hitPlayerFlag3;								// �v���C���[�ɓ���������
	//bool  Reverse3;										//���]

public:

	int		life;
	int		life1;										// �G�P�̗̑�
	int		life2;										// �G�Q�̗̑�
	int		life3;										// �G�R�̗̑�

	// ������
	void Init();
	/*void Init1();
	void Init2();
	void Init3();*/
	
	// �A�b�v�f�[�g
	void Update(Player player, Music music, ShotEnemy shot[], int shotnum, float deltaTime);
	/*void Update1(Player player, Music music, ShotEnemy shot[], int shotnum, float deltaTime);
	void Update2(Player player, Music music, float deltaTime);
	void Update3(Player player, Music music, float deltaTime);*/

	// �`��
	void Draw();
	/*void Draw1();
	void Draw2();
	void Draw3();
	*/
	void DrawHP(int life1, int MAXlife);

	void OnHitShot(int shotX, int shotY, int shotW, int shotH, bool visibleFlag);
	/*void OnHitShot1(int shotX, int shotY, int shotW, int shotH, bool visibleFlag);
	void OnHitShot2(int shotX, int shotY, int shotW, int shotH, bool visibleFlag);
	void OnHitShot3(int shotX, int shotY, int shotW, int shotH, bool visibleFlag);*/

	//bool GetPosX()const { return PosX; }
	//bool GetPosY()const { return PosY; }
	//bool GetScore()const { return Score; }


	bool GetLife()const { return life; }
	
	bool GetX() const { return x; }
	bool GetY() const { return y; }
	bool GetW() const { return w; }
	bool GetH() const { return h; }

	bool GetReverse() const { return Reverse; }

	/*bool GetLife1()const { return life1; }
	bool GetLife2()const { return life2; }
	bool GetLife3()const { return life3; }

	bool GetX1() const { return x1; }
	bool GetY1() const { return y1; }
	bool GetW1() const { return w1; }
	bool GetH1() const { return h1; }

	bool GetReverse1() const { return Reverse1; }*/


	//<summary>
	//�G�l�~�[�̓����蔻���`��Ԃ�
	//</summary>
	//<returns>�����蔻���`</returns>
	sHitRect getHitRect();

	//<summary>
	//�G�l�~�[�̓����蔻���`��Ԃ�
	//</summary>
	//<returns>�����蔻���`</returns>
	//sHitRect getHitRect1();

	//<summary>
	//�G�l�~�[�̓����蔻���`��Ԃ�
	//</summary>
	//<returns>�����蔻���`</returns>
	//sHitRect getHitRect2();

	//<summary>
	//�G�l�~�[�̓����蔻���`��Ԃ�
	//</summary>
	//<returns>�����蔻���`</returns>
	//sHitRect getHitRect3();

	//<summary>
//�����蔻��̈ʒu�C��
//</summary>
//<param name="hitRect">�����蔻���`</param>
	void fixColPosition(sHitRect& hitRect);

	//<summary>
	//�����蔻��̈ʒu�C��
	//</summary>
	//<param name="hitRect">�����蔻���`</param>
	//void fixColPosition1(sHitRect& hitRect);

	//<summary>
	//�����蔻��̈ʒu�C��
	//</summary>
	//<param name="hitRect">�����蔻���`</param>
	//void fixColPosition2(sHitRect& hitRect);

	//<summary>
	//�����蔻��̈ʒu�C��
	//</summary>
	//<param name="hitRect">�����蔻���`</param>
	//void fixColPosition3(sHitRect& hitRect);

	//<summary>
	//���������蔻��
	//</summary>
	//<param name="groundFlg">�����̓����蔻�茋��</param>
	void SetGroundFlag(bool groundFlag);

	//<summary>
	//���������蔻��
	//</summary>
	//<param name="groundFlg">�����̓����蔻�茋��</param>
	//void SetGroundFlag1(bool groundFlag);

	//<summary>
	//���������蔻��
	//</summary>
	//<param name="groundFlg">�����̓����蔻�茋��</param>
	//void SetGroundFlag2(bool groundFlag);

	//<summary>
	//���������蔻��
	//</summary>
	//<param name="groundFlg">�����̓����蔻�茋��</param>
	//void SetGroundFlag3(bool groundFlag);
	
	//<summary>
	//���̓����蔻��
	//</summary>
	//<param name="headHitFlg">���̓����蔻�茋��</param>
	void SetHeadHitFlag(bool headHitFlag);

	//<summary>
	//���̓����蔻��
	//</summary>
	//<param name="headHitFlg">���̓����蔻�茋��</param>
	//void SetHeadHitFlag1(bool headHitFlag);

	//<summary>
	//���̓����蔻��
	//</summary>
	//<param name="headHitFlg">���̓����蔻�茋��</param>
	//void SetHeadHitFlag2(bool headHitFlag);

	// <summary>
	// ���̓����蔻��
	// </summary>
	// <param name="headHitFlg">���̓����蔻�茋��</param>
	//void SetHeadHitFlag3(bool headHitFlag);


	//<summary>
	//�����R���C�_�[�擾
	//</summary>
	//<returns>�����R���C�_�[�̋�`���</returns>
	sHitRect GetGroundCollider();

	//<summary>
	//�����R���C�_�[�擾
	//</summary>
	//<returns>�����R���C�_�[�̋�`���</returns>
	//sHitRect GetGroundCollider1();

	//<summary>
	//�����R���C�_�[�擾
	//</summary>
	//<returns>�����R���C�_�[�̋�`���</returns>
	//sHitRect GetGroundCollider2();

	//<summary>
	//�����R���C�_�[�擾
	//</summary>
	//<returns>�����R���C�_�[�̋�`���</returns>
	//sHitRect GetGroundCollider3();

	//<summary>
	//����R���C�_�[�擾
	//</summary>
	//<returns>����R���C�_�[�̋�`���</returns>
	sHitRect GetHeadCollider();

	//<summary>
	//����R���C�_�[�擾
	//</summary>
	//<returns>����R���C�_�[�̋�`���</returns>
	//sHitRect GetHeadCollider1();

	//<summary>
	//����R���C�_�[�擾
	//</summary>
	//<returns>����R���C�_�[�̋�`���</returns>
	//sHitRect GetHeadCollider2();

	//<summary>
	//����R���C�_�[�擾
	//</summary>
	//<returns>����R���C�_�[�̋�`���</returns>
	//sHitRect GetHeadCollider3();
	
};