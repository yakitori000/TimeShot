#pragma once

class ScreenImage
{
public:

	//</sumary>
	//�Q�[���^�C�g���摜
	int TITLEgraph;
	int TITLEimageX, TITLEimageY;

	//������@�摜
	int MENUgraph;
	int MENUimageX, MENUimageY;

	//�Q�[���w�i
	int BACKgraph;
	int BACKimageX, BACKimageY;

	//�Q�[���N���A�摜
	int CLEARgraph;
	int CLEARimageX, CLEARimageY;

	//�Q�[���I�[�o�[�摜
	int OVERgraph;
	int OVERimageX, OVERimageY;

	//������
	void Init();

	//�Q�[���^�C�g���摜�֘A
	//void InitTitle();
	void DrawTitle();

	//������@�摜�֘A
	//void InitMenu();
	void DrawMenu();

	//�Q�[���w�i�摜�֘A
	void InitBack();
	void DrawBack();

	//�Q�[���N���A�摜�֘A
	//void InitClear();
	void DrawClear();

	//�Q�[���I�[�o�[�摜�֘A
	//void InitOver();
	void DrawOver();

};

