
#include "Music.h"

void Music::Init()
{
	TitleMusic = LoadSoundMem("data/sound/GameMusic.mp3");
	GameMusic = LoadSoundMem("data/sound/GameMusic.WAV");
	ShotSound = LoadSoundMem("data/sound/shot.mp3");
	OutBulletSound = LoadSoundMem("data/sound/OutBullet.mp3");
	OpenSound = LoadSoundMem("data/sound/OpenBox.mp3");
}

void Music::playTitleSound()
{
	//PlaySoundMem(TitleMusic, DX_PLAYTYPE_BACK,FALSE);
}

void Music::playBGM()
{
	ChangeNextPlayVolumeSoundMem(90,GameMusic);
	PlaySoundMem(GameMusic, DX_PLAYTYPE_LOOP,FALSE);
}



void Music::playShot(int count)
{
	if (count > 0)	
	{
		ChangeNextPlayVolumeSoundMem(180, ShotSound);
		PlaySoundMem(ShotSound, DX_PLAYTYPE_BACK);
	}
	if (count <= 0)
	{
		ChangeNextPlayVolumeSoundMem(180, OutBulletSound);
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
