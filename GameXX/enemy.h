#pragma once

#include "DxLib.h"
#include "Player.h"
#include "Music.h"
#include "map.h"
#include "function.h"
#include "collision.h"

#define ENEMY_LIFE		10
#define ENEMY_NUM		5
#define ENEMY_MAXX		1900
#define ENEMY_MAXY		600


class Player;
class Music;
struct sHitRect;



// �G�l�~�[.
class Enemy
{
private:
	/*float x[ENEMY_NUM];
	float y[ENEMY_NUM];*/
	float	x;
	float	y;
	int		w;
	int		h;
	float	vx, vy;
	int		graph;

	int num[ENEMY_NUM];


	float PosX[ENEMY_NUM] = {};
	float PosY[ENEMY_NUM] = {};

	bool	damageFlag;									// �_���[�W�H����Ă邩
	int		damageCounter;								// �_���[�W��
	int		damageGraph;								// �_���[�W�摜

	bool	LivFlag;									// �����Ă��邩
	int		LivCounter;									// �����Ґ�
	int		LivGraph;									// 
	
	int		Score;

	bool	isRightMove;								// ��ʊO�ɂ����Ȃ�
	int		drawOffsetX;								// �����蔻�肩��̉��������炵��
	int		drawOffsetY;								// �����蔻�肩��̏c�������炵��

	const int		imageSizeX				= 64;       // �摜���T�C�Y
	const int		imageSizeY				= 128;      // �摜�c�T�C�Y
	const int		hitSizeX				= 50;       // �����蔻��T�C�Y��
	const int		hitSizeY				= 100;       // �����蔻��T�C�Y����

	const float		moveSpeed				= 200.0f;   // �ړ����x (�����Ŏw�肵���l���̃s�N�Z��/�b�i��) 
	const float		maxMoveSpeed			= 300.0f;   // �ő剡�ړ����x
	const float		moveAccell				= 1.5f;     // �ړ������x
	const float		frictionRatio			= 0.98f;    // ���C�W��
	const float		brakeRatio				= 0.95f;    // �i�s�����ɑ΂��ē��͋t�����ɓ��ꂽ�Ƃ��̃u���[�L�W��
	const float		inAirMoveAccelRatio		= 0.8f;     // �󒆉��ړ�������
	const float		jumpInitalVelocity		= 10.5f;     // �W�����v�����x
	const float		jumpUpSpeed				= 9.0f;     // �W�����v���������㏸���x

	const int		colliderOffset			= 10;		// �R���C�_�[���E���炵��
	const float		gravity					= 15.0f;	// �d��
	const float		maxFallSpeed			= 300.0f;	// �ő嗎�����x
	const float		hitHeadBrakeRatio		= -0.1f;    // ����Փˎ��̌�����

	bool  jumpFlag;										// �W�����v�t���O
	bool  onGround;										// �n�ʂɗ����Ă��邩
	bool  hitHead;										// ��������������	
	bool  hitWool;										// �ǂɓ���������
	bool  hitPlayerFlag;								// �v���C���[�ɓ���������
	bool  Reverse;										//���]

public:

	int		life;										// �̗�

	// ������.
	void Init();

	// �A�b�v�f�[�g.
	void Update(Player player, Music music, float deltaTime);

	// �`��.
	void Draw();
	void OnHitShot(int shotX, int shotY, int shotW, int shotH, bool visibleFlag);
	void setPosition(float x, float y, int num);

	bool GetPosX()const { return PosX; }
	bool GetPosY()const { return PosY; }
	bool GetScore()const { return Score; }
	bool GetLife()const { return life; }

	/// <summary>
	/// �G�l�~�[�̓����蔻���`��Ԃ�
	/// </summary>
	/// <returns>�����蔻���`</returns>
	sHitRect getHitRect();

	/// <summary>
	/// �����蔻���`����ʒu���C������
	/// </summary>
	/// <param name="hitRect">�����蔻���`</param>
	void fixColPosition(sHitRect& hitRect);

	/// <summary>
	/// �n�ʂɗ����Ă��邩�H
	/// </summary>
	/// <param name="groundFlg">�����̓����蔻�茋��</param>
	void SetGroundFlag(bool groundFlag);

	/// <summary>
	/// ����ǂɂԂ�����
	/// </summary>
	/// <param name="headHitFlg">���̓����蔻�茋��</param>
	void SetHeadHitFlag(bool headHitFlag);

	/// <summary>
	/// �����R���C�_�[�̃Q�b�g
	/// </summary>
	/// <returns>�����R���C�_�[�̋�`���</returns>
	sHitRect GetGroundCollider();

	/// <summary>
	/// ����R���C�_�[�̃Q�b�g
	/// </summary>
	/// <returns>����R���C�_�[�̋�`���</returns>
	sHitRect GetHeadCollider();

};


