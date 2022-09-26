
#include "Music.h"

void Music::Init()
{
	TitleMusic = LoadSoundMem("data/sound/GameMusic.mp3");
	GameMusic = LoadSoundMem("data/sound/GameMusic.mp3");
	
}

void Music::ShotSoudInit()
{
	ShotSound = LoadSoundMem("data/sound/shot.mp3");
	OutBulletSound = LoadSoundMem("data/sound/OutBullet.mp3");
}


void Music::playTitleSound()
{
	//PlaySoundMem(TitleMusic, DX_PLAYTYPE_BACK,FALSE);
}

void Music::playBGM()
{
	ChangeNextPlayVolumeSoundMem(90,GameMusic);
	PlaySoundMem(GameMusic, DX_PLAYTYPE_BACK,FALSE);
}



void Music::playShot()
{
	/*if (count > 0)*/
	//{
	//	PlaySoundMem(ShotSound, DX_PLAYTYPE_NORMAL);
	//}
	//else
	//{
		//PlaySoundMem(OutBulletSound, DX_PLAYTYPE_NORMAL,TRUE);
	//}

	
}
