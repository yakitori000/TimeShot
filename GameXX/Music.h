#pragma once

#include "DxLib.h"
#include "Player.h"

class player;

class Music
{
public:

	//�Q�[���~���[�W�b�N
	int TitleMusic;			//�^�C�g���T�E���h
	int GameMusic;			//�Q�[��BGM
	int ClearMusic;			//�Q�[���N���A�T�E���h
	int OverMusic;			//�Q�[���I�[�o�[�T�E���h

	//���ʉ�
	int ShotSound;			//���ˉ�
	int OutBulletSound;		//�e�؂ꉹ
	int ZonbiVoice;			//�]���r�ړ���
	int ScreamZonbiSound;	//�]���r���S��

	/// <summary>
	///�T�E���h������
	/// </summary>
	void Init();						
	
	/// <summary>
	///�e�֘A�T�E���h������
	/// </summary>
	void ShotSoudInit();
	
	/// <summary>
	///�^�C�g���T�E���h�Đ�
	/// </summary>
	void playTitleSound();				
	
	/// <summary>
	///�Q�[��BGM�Đ�
	/// </summary>
	void playBGM();						
	
	/// <summary>
	///�e�֘A�̃T�E���h�Đ�
	/// </summary>
	void playShot();


};