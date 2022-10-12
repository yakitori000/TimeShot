#pragma once

#include "DxLib.h"


class Player;
class Music;

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

	void Init(Music& music);

	void Updata(Player& player, Music &music);

	void Draw();

};