#pragma once


#include "DxLib.h"
#include "Player.h"
#include "collision.h"
#include "function.h"

class Player;

class Item
{
public:

	
	int BoxGraph;			//” 
	int OpenBoxGraph;		//‹ó‚«” 
	int Graph		= 0;	//‹ó‰æ‘œ
	int DropGraph	= 1;	//’e
	int ItemNowType = 2;
	int x;
	int y;
	int w;
	int h;
	int dropX, dropY;
	int Score;

	bool OpenFlag;
	bool HitFlag;

	void Init();

	void Updata(Player& player);

	void Draw();

};