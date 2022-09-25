#pragma once
#include"DxLib.h"
#include "shot.h"
#include "Item.h"
#include "map.h"
#include "Music.h"
#include "collision.h"

class Shot;
class Item;
class Music;

//�v���C���[
class Player
{
public:

	const int animDown					= 0;		// ������
	const int animLeft					= 1;		// ������
	const int animRight					= 2;		// �E����
	const int animShotDown				= 3;		// �ˌ�������
	const int animShotLeft				= 4;		// �ˌ�������
	const int animShotRight				= 5;		// �ˌ��E����
	const int animStopShotLeft			= 6;		// ��~�ˌ�������
	const int animStopShotRight			= 7;		// ��~�ˌ��E����
	const int animGetDown				= 8;		// �l���|�[�Y

	const float animationFPS			= 6.0f;		// �b�� 6�R�}�̃A�j���[�V����
	const float moveSpeed				= 200.0f;	// �ړ����x (�����Ŏw�肵���l���̃s�N�Z��/�b�i��) 
	const float maxMoveSpeed			= 300.0f;	// �ő剡�ړ����x
	const float moveAccell				= 1.5f;		// �ړ������x
	const float frictionRatio			= 0.98f;	// ���C�W��
	const float brakeRatio				= 0.95f;	// �i�s�����ɑ΂��ē��͋t�����ɓ��ꂽ�Ƃ��̃u���[�L�W��
	const float inAirMoveAccelRatio		= 0.8f;		// �󒆉��ړ�������
	const float jumpInitalVelocity		= 5.5f;		// �W�����v�����x
	const float jumpUpSpeed				= 9.0f;		// �W�����v���������㏸���x
	const float hitHeadBrakeRatio		= -0.1f;	// ����Փˎ��̌�����

	const int   imageSizeX				= 64;		// �摜���T�C�Y
	const int   imageSizeY				= 96;		// �摜�c�T�C�Y
	const int   hitSizeX				= 40;		// �����蔻��T�C�Y��
	const int   hitSizeY				= 60;		// �����蔻��T�C�Y����

	const int   colliderOffset			= 10;		// �R���C�_�[���E���炵��
	const float gravity					= 15.0f;	// �d��
	const float maxFallSpeed			= 300.0f;	// �ő嗎�����x
	const float jumpButtonAcceptTime	= 0.95f;	// �W�����v��������t����

	int   HitPoint;									// �v���C���[�̗̑�
	float animTimer;								// �A�j���[�V�����^�C�}�[
	int   animNowType;								// ���݂̃A�j�����
	int   animNowPattern;							// ���݂̃A�j���p�^�[��
	int   animNowIndex;								// �A�j���[�V�����摜�z��̓Y���� 0�`11�܂ł̐��l
	int   drawOffsetX;								// �����蔻�肩��̉��������炵��
	int   drawOffsetY;								// �����蔻�肩��̏c�������炵��

	bool sideFlag;									// �E�����Ă��邩
	bool GetFlag;									// �A�C�e���l���ł��邩
	bool DamegeFlag;								// �_���[�W��H����Ă��邩
	int	 DamageCounter;								// �_���[�W��
	int	 DamageGraph;								// �_���[�W�摜

	bool  jumpFlag;									// �W�����v�t���O
	bool  onGround;									// �n�ʂɗ����Ă��邩
	bool  hitHead;									// �����Ԃ����Ă��邩
	float jumpTimer;								// �W�����v���������ԃ^�C�}�[

	float px, py;									// �v���C���[�̍��W
	float vx, vy;									// �v���C���[�̑��x
	int w;											// �摜�̕�
	int h;											// �摜�̍���
	int count;										// �e���J�E���g
	int ScoreCount;									// �Q�[���X�R�A
	int graph;										// �摜�T�C�Y
	int ShotIntervalCount;							// �O�t���[���ŃV���b�g����Ă�����

	//���ʉ�
	int ShotSound;			//���ˉ�
	int OutBulletSound;		//�e�؂ꉹ

	/// <summary>
	/// �v���C���[������
	/// </summary>
	void Init();

	/// <summary>
	/// �v���C���[�X�V
	/// </summary>
	/// <param name="deltaTime">1�t���[�����̏�������</param>
	void Update( Shot shot[], int shotnum, Item &item,Music &music, float deltaTime);

	/// <summary>
	/// �v���C���[�`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �v���C���[��n��
	/// </summary>
	void Finalize();

	void DrawShot(Shot shot);		//�e�֘A�̃T�E���h�Đ�

	/// <summary>
	/// �v���C���[�̓����蔻���`��Ԃ�
	/// </summary>
	/// <returns>�v���C���[�̓����蔻���`</returns>
	sHitRect getHitRect();

	/// <summary>
	/// �����蔻���`����v���C���[�ʒu���C������
	/// </summary>
	/// <param name="hitRect">�����蔻���`</param>
	void fixColPosition(sHitRect& hitRect);

	/// <summary>
	/// �G�l�~�[�ɓ������Ă��邩
	/// </summary>
	void OnHitEnemy(int enemyX, int enemyY, int enemyW, int enemyH);

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
	/// �v���C���[�̑����R���C�_�[�̃Q�b�g
	/// </summary>
	/// <returns>�����R���C�_�[�̋�`���</returns>
	sHitRect GetGroundCollider();

	/// <summary>
	/// �v���C���[�̓���R���C�_�[�̃Q�b�g
	/// </summary>
	/// <returns>����R���C�_�[�̋�`���</returns>
	sHitRect GetHeadCollider();

	bool GetHitPoint()const { return HitPoint; }
	bool inputMove(float deltaTime);
};



