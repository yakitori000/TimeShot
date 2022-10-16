#pragma once

#include "DxLib.h"


class player;
class Item;

class Music
{
public:

	//�Q�[���~���[�W�b�N
	int TitleMusic;				//�^�C�g���T�E���h
	int GameMusic;				//�Q�[��BGM
	int GameImpatientMusic;		//�ł点��BGM
	int ClearMusic;				//�Q�[���N���A�T�E���h
	int OverMusic;				//�Q�[���I�[�o�[�T�E���h

	//���ʉ�
	int ShotSound;			//���ˉ�
	int OutBulletSound;		//�e�؂ꉹ
	int ZonbiAtack;			//�]���r�U���T�E���h
	int ZonbiVoice;			//�]���r�ړ���
	int ZonbiScreamSound;	//�]���r���S��
	int OpenSound;			//�󔠊J�����Ƃ��̉�

	/// <summary>
	///�T�E���h������
	/// </summary>
	void Init();						
	
	/// <summary>
	///�^�C�g���T�E���h�Đ�
	/// </summary>
	void playTitleSound();				
	
	/// <summary>
	///�Q�[��BGM�Đ�
	/// </summary>
	void playBGM();						

	/// <summary>
	///�Q�[���ł点��BGM�Đ�
	/// </summary>
	void playBGM2();
	
	/// <summary>
	///�G�֘A�̃T�E���h�Đ�
	/// </summary>
	void playEnemy(bool HitFlag);

	/// <summary>
	///�G�U���֘A�̃T�E���h�Đ�
	/// </summary>
	void playEnemyAtack(int count);


	/// <summary>
	///�e�֘A�̃T�E���h�Đ�
	/// </summary>
	void playShot(int count);

	/// <summary>
	///�󔠊֘A�̃T�E���h�Đ�
	/// </summary>
	void playBox(bool OpenFlag);


};