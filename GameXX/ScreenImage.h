#pragma once

class ScreenImage
{
public:

	//�Q�[���^�C�g���摜
	int TITLEglaph;
	int TITLEimageX, TITLEimageY;

	//�Q�[���N���A�摜
	int CLEARglaph;
	int CLEARimageX, CLEARimageY;

	//�Q�[���I�[�o�[�摜
	int OVERglaph;
	int OVERimageX, OVERimageY;

	//�Q�[���^�C�g���摜�֘A
	void InitTitle();
	void DrawTitle();

	//�Q�[���N���A�摜�֘A
	void InitClear();
	void DrawClear();

	//�Q�[���I�[�o�[�摜�֘A
	void InitOver();
	void DrawOver();

};

