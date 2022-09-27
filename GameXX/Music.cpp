
#include "Music.h"

void Music::Init()
{
	TitleMusic		 = LoadSoundMem("data/sound/GameMusic.mp3");
	GameMusic		 = LoadSoundMem("data/sound/GameMusic.WAV");
	ShotSound		 = LoadSoundMem("data/sound/shot.mp3");
	OutBulletSound	 = LoadSoundMem("data/sound/OutBullet.mp3");
	OpenSound		 = LoadSoundMem("data/sound/OpenBox.mp3");
	ZonbiVoice		 = LoadSoundMem("data/sound/ZonbiVoice2.mp3");
	ZonbiScreamSound = LoadSoundMem("data/sound/ZonbiScream.mp3");
}

void Music::playTitleSound()
{
	//PlaySoundMem(TitleMusic, DX_PLAYTYPE_BACK,FALSE);
}

void Music::playBGM()
{
	//Й╣Ч╩Т▓Ро
	ChangeNextPlayVolumeSoundMem(90,GameMusic);
	//Н─Р╢
	PlaySoundMem(GameMusic, DX_PLAYTYPE_LOOP,FALSE);
}

void Music::playEnemy(bool HitFlag)
{
	
	if (HitFlag)
	{
		//Й╣Ч╩Т▓Ро
		ChangeNextPlayVolumeSoundMem(90, ZonbiVoice);
		//Н─Р╢
		PlaySoundMem(ZonbiVoice, DX_PLAYTYPE_BACK, FALSE);
	}


	//Й╣Ч╩Т▓Ро
	ChangeNextPlayVolumeSoundMem(90, ZonbiScreamSound);
	//Н─Р╢
	//PlaySoundMem(ZonbiScreamSound, DX_PLAYTYPE_LOOP, FALSE);
}

void Music::playShot(int count)
{
	if (count > 0)	
	{
		//Й╣Ч╩Т▓Ро
		ChangeNextPlayVolumeSoundMem(180, ShotSound);
		//Н─Р╢
		PlaySoundMem(ShotSound, DX_PLAYTYPE_BACK);
	}
	if (count <= 0)
	{
		//Й╣Ч╩Т▓Ро
		ChangeNextPlayVolumeSoundMem(180, OutBulletSound);
		//Н─Р╢
		PlaySoundMem(OutBulletSound, DX_PLAYTYPE_BACK,TRUE);
	}

	
}

void Music::playBox(bool OpenFlag)
{
	if (OpenFlag)
	{
		ChangeNextPlayVolumeSoundMem(180, OpenSound);
		PlaySoundMem(OpenSound, DX_PLAYTYPE_BACK, TRUE);
	}
	
	
}
