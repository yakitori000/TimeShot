#pragma once

class ScreenImage
{
public:
	//ゲームクリア画像
	int CLEARglaph;
	int CLEARimageX, CLEARimageY;

	//ゲームオーバー画像
	int OVERglaph;
	int OVERimageX, OVERimageY;

	//ゲームクリア画像関連
	void LoadClear();
	void InitClear();
	void DrawClear();

	//ゲームオーバー画像関連
	void LoadOver();
	void InitOver();
	void DrawOver();

};

