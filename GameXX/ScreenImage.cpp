#include "DxLib.h"
#include "ScreenImage.h"


//ゲームタイトル画像処理
void ScreenImage::InitTitle()
{
	TITLEgraph = LoadGraph("data/image/title2.png");
	TITLEimageX = 0;
	TITLEimageY = 0;
}

void ScreenImage::DrawTitle()
{
	DrawGraph(TITLEimageX, TITLEimageY, TITLEgraph, TRUE);
}

void ScreenImage::InitMenu()
{
	MENUgraph = LoadGraph("data/image/KeyMenu1.png");
	MENUimageX = 0;
	MENUimageY = 0;
}

void ScreenImage::DrawMenu()
{
	DrawGraph(MENUimageX, MENUimageY, MENUgraph,TRUE);
}

void ScreenImage::InitBack()
{
	BACKgraph = LoadGraph("data/image/back.png");
	BACKimageX = 0;
	BACKimageY = 0;
}

void ScreenImage::DrawBack()
{
	DrawGraph(BACKimageX, BACKimageY, BACKgraph, TRUE);
}

//ゲームクリア画像処理
void ScreenImage::InitClear()
{
	
	CLEARgraph = LoadGraph("data/image/win.png");
	CLEARimageX = 0;
	CLEARimageY = 0;
}

void ScreenImage::DrawClear()
{
	DrawGraph(CLEARimageX, CLEARimageY, CLEARgraph, TRUE);
}


//ゲームオーバー画像処理
void ScreenImage::InitOver()
{
	OVERgraph = LoadGraph("data/image/lose.png");
	OVERimageX = 0;
	OVERimageY = 0;
}

void ScreenImage::DrawOver()
{
	DrawGraph(OVERimageX, OVERimageY, OVERgraph, TRUE);
}
