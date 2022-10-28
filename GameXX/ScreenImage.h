#pragma once

class ScreenImage
{
public:

	//</sumary>
	//ゲームタイトル画像
	int TITLEgraph;
	int TITLEimageX, TITLEimageY;

	//操作方法画像
	int MENUgraph;
	int MENUimageX, MENUimageY;

	//ゲーム背景
	int BACKgraph;
	int BACKimageX, BACKimageY;

	//ゲームクリア画像
	int CLEARgraph;
	int CLEARimageX, CLEARimageY;

	//ゲームオーバー画像
	int OVERgraph;
	int OVERimageX, OVERimageY;

	//初期化
	void Init();

	//ゲームタイトル画像関連
	//void InitTitle();
	void DrawTitle();

	//操作方法画像関連
	//void InitMenu();
	void DrawMenu();

	//ゲーム背景画像関連
	void InitBack();
	void DrawBack();

	//ゲームクリア画像関連
	//void InitClear();
	void DrawClear();

	//ゲームオーバー画像関連
	//void InitOver();
	void DrawOver();

};

