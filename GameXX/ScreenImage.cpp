#include "DxLib.h"
#include "ScreenImage.h"


//ゲームタイトル画像処理
void ScreenImage::InitTitle()
{
	TITLEglaph = LoadGraph("data/title.png");
	TITLEimageX = 0;
	TITLEimageY = 0;
}

void ScreenImage::DrawTitle()
{
	DrawGraph(TITLEimageX, TITLEimageY, TITLEglaph, TRUE);
}

//ゲームクリア画像処理
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


//ゲームオーバー画像処理
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
