#pragma once

class ScreenImage
{
public:

	//ゲームタイトル画像
	int TITLEglaph;
	int TITLEimageX, TITLEimageY;

	//ゲームクリア画像
	int CLEARglaph;
	int CLEARimageX, CLEARimageY;

	//ゲームオーバー画像
	int OVERglaph;
	int OVERimageX, OVERimageY;

	//ゲームタイトル画像関連
	void InitTitle();
	void DrawTitle();

	//ゲームクリア画像関連
	void InitClear();
	void DrawClear();

	//ゲームオーバー画像関連
	void InitOver();
	void DrawOver();

};

