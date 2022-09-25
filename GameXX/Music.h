#pragma once

#include "DxLib.h"
#include "Player.h"

class player;

class Music
{
public:

	//ゲームミュージック
	int TitleMusic;			//タイトルサウンド
	int GameMusic;			//ゲームBGM
	int ClearMusic;			//ゲームクリアサウンド
	int OverMusic;			//ゲームオーバーサウンド

	//効果音
	int ShotSound;			//発射音
	int OutBulletSound;		//弾切れ音
	int ZonbiVoice;			//ゾンビ移動時
	int ScreamZonbiSound;	//ゾンビ死亡時

	void Init();						//サウンド初期化
	void ShotSoudInit();
	void playTitleSound();				//タイトルサウンド再生
	void playBGM();						//ゲームBGM再生
	void playShot();			//銃関連のサウンド再生


};