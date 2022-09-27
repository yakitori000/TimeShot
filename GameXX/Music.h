#pragma once

#include "DxLib.h"
#include "Player.h"
#include "Item.h"

class player;
class Item;

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
	int ZonbiScreamSound;	//ゾンビ死亡時
	int OpenSound;			//宝箱開けたときの音

	/// <summary>
	///サウンド初期化
	/// </summary>
	void Init();						
	
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
	void playEnemy(bool HitFlag);

	/// <summary>
	///銃関連のサウンド再生
	/// </summary>
	void playShot(int count);

	/// <summary>
	///宝箱関連のサウンド再生
	/// </summary>
	void playBox(bool OpenFlag);


};