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

	/// <summary>
	///サウンド初期化
	/// </summary>
	void Init();						
	
	/// <summary>
	///銃関連サウンド初期化
	/// </summary>
	void ShotSoudInit();
	
	/// <summary>
	///タイトルサウンド再生
	/// </summary>
	void playTitleSound();				
	
	/// <summary>
	///ゲームBGM再生
	/// </summary>
	void playBGM();						
	
	/// <summary>
	///銃関連のサウンド再生
	/// </summary>
	void playShot();


};