#pragma once

#include "DxLib.h"


class player;
class Item;

class Music
{
public:

	//ゲームミュージック
	int TitleMusic;				//タイトルサウンド
	int GameMusic;				//ゲームBGM
	int GameImpatientMusic;		//焦らせるBGM
	int ClearMusic;				//ゲームクリアサウンド
	int OverMusic;				//ゲームオーバーサウンド

	//効果音
	int ShotSound;			//発射音
	int OutBulletSound;		//弾切れ音
	int ZonbiAtack;			//ゾンビ攻撃サウンド
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
	///ゲーム焦らせるBGM再生
	/// </summary>
	void playBGM2();
	
	/// <summary>
	///敵関連のサウンド再生
	/// </summary>
	void playEnemy(bool HitFlag);

	/// <summary>
	///敵攻撃関連のサウンド再生
	/// </summary>
	void playEnemyAtack(int count);


	/// <summary>
	///銃関連のサウンド再生
	/// </summary>
	void playShot(int count);

	/// <summary>
	///宝箱関連のサウンド再生
	/// </summary>
	void playBox(bool OpenFlag);


};