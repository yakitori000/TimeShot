#pragma once

class ScreenImage
{
public:

	//�Q�[���^�C�g���摜
	int TITLEgraph;
	int TITLEimageX, TITLEimageY;

	//������@�摜
	int MENUgraph;
	int MENUimageX, MENUimageY;

	//�Q�[���N���A�摜
	int CLEARgraph;
	int CLEARimageX, CLEARimageY;

	//�Q�[���I�[�o�[�摜
	int OVERgraph;
	int OVERimageX, OVERimageY;

	//�Q�[���^�C�g���摜�֘A
	void InitTitle();
	void DrawTitle();

	//������@�摜�֘A
	void InitMenu();
	void DrawMenu();

	//�Q�[���N���A�摜�֘A
	void InitClear();
	void DrawClear();

	//�Q�[���I�[�o�[�摜�֘A
	void InitOver();
	void DrawOver();

};

