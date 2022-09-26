#include "DxLib.h"
#include "ScreenImage.h"


//ゲームタイトル画像処理
void ScreenImage::InitTitle()
{
	TITLEglaph = LoadGraph("data/image/title.png");
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
	
	CLEARglaph = LoadGraph("data/image/win.png");
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
	OVERglaph = LoadGraph("data/image/lose1.png");
	OVERimageX = 0;
	OVERimageY = 0;
}

void ScreenImage::DrawOver()
{
	DrawGraph(OVERimageX, OVERimageY, OVERglaph, TRUE);
}
