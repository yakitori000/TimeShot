#include "DxLib.h"
#include "ScreenImage.h"

void ScreenImage::LoadClear()
{
	
}

void ScreenImage::InitClear()
{
	CLEARglaph = LoadGraph("data/win.png");
	CLEARimageX = 0;
	CLEARimageY = 0;
}

void ScreenImage::DrawClear()
{
	DrawGraph(CLEARimageX, CLEARimageY, CLEARglaph, TRUE);
}

void ScreenImage::LoadOver()
{
	DrawGraph(OVERimageX, OVERimageY, OVERglaph, TRUE);
}

void ScreenImage::InitOver()
{
	OVERglaph = LoadGraph("data/lose.png");
	OVERimageX = 0;
	OVERimageY = 0;
}

void ScreenImage::DrawOver()
{
	DrawGraph(OVERimageX, OVERimageY, OVERglaph, TRUE);
}
