#pragma once

class ScreenImage
{
public:
	//�Q�[���N���A�摜
	int CLEARglaph;
	int CLEARimageX, CLEARimageY;

	//�Q�[���I�[�o�[�摜
	int OVERglaph;
	int OVERimageX, OVERimageY;

	//�Q�[���N���A�摜�֘A
	void LoadClear();
	void InitClear();
	void DrawClear();

	//�Q�[���I�[�o�[�摜�֘A
	void LoadOver();
	void InitOver();
	void DrawOver();

};

