//#pragma once
//#include <DxLib.h>
//#include "collision.h"
//
///// <summary>
///// �}�b�v�f�[�^�\����
///// </summary>
//class sMapLayer
//{
//public:
//	int** mapData;	//�}�b�v�`�b�v�̓񎟌��z��
//	int   mapXNum;	//�}�b�v�`�b�v���������ɕ���ł��鐔
//	int   mapYNum;	//�}�b�v�`�b�v���c�����ɕ���ł��鐔
//
//	
//
//	/// <summary>
///// �}�b�v������
///// </summary>
//	void Init();
//
//	/// <summary>
//	/// �}�b�v�`��
//	/// </summary>
//	void Draw();
//
//	/// <summary>
//	/// �}�b�v��n��
//	/// </summary>
//	void Finalize();
//
//	/// <summary>
//	/// �}�b�v��n��
//	/// </summary>
//	/// <param name ="checkRect">�}�b�v�Ɠ������Ă��邩������������`</param>
//	/// <returns>�}�b�v�ƏՓ˂�������true/false�ŕԂ�</returns>
//	bool HitCalc(sHitRect& checkRect);
//
//	/// <summary>
//	/// �}�b�v�̃C���f�b�N�X�ʒu����u���b�N�ԍ���Ԃ�
//	/// </summary>
//	/// <param name ="ix">�}�b�v�̃C���f�b�N�X�ԍ�x</param>
//	/// <param name ="iy">�}�b�v�̃C���f�b�N�X�ԍ�y</param>
//	/// <returns>�}�b�v�̃u���b�N�ԍ���Ԃ�</returns>
//	unsigned char GetBlockType(int ix, int iy);
//
//	/// <summary>
//	/// ���W�ʒu����u���b�N�ԍ���Ԃ�
//	/// </summary>
//	/// <param name ="ix">x���W</pram>
//	/// <param name ="iy".y���W</pram>
//	/// <returns>�}�b�v�̃u���b�N�ԍ���Ԃ�</returns>
//	unsigned char GetBlockTypeXY(int x, int y);
//
//	/// <summary>
///// �}�b�v���[�_�[
///// </summary>
///// <param name="dst">�������������}�b�v�f�[�^</param>
///// <param name="mapCSVFileName">�}�b�v�t�@�C����</param>
///// <returns>�ǂݍ��݂ɐ�����������true false�ŕԋp</returns>
//	bool LayerLoader(sMapLayer& dst, const char* mapCSVFileName);
//
//	/// <summary>
//	/// �}�b�v�̔j��
//	/// </summary>
//	/// <param name="dst">�������J���������}�b�v�f�[�^</param>
//	void Unloader(sMapLayer& dst);
//
//	/// <summary>
//	/// �}�b�v�̃��C���[��`��
//	/// </summary>
//	/// <param name="layer">�`�悵�������C���[</param>
//	void LayerDraw(sMapLayer& layer);
//};

#pragma once
#include <DxLib.h>
#include "collision.h"

/// <summary>
/// �}�b�v�f�[�^�\����
/// </summary>
class sMapLayer
{
public:
	int** mapData; // �}�b�v�`�b�v��2�����z��
	int   mapXNum; // �}�b�v�`�b�v���������ɕ���ł��鐔
	int   mapYNum; // �}�b�v�`�b�v���c�����ɕ���ł��鐔

	/// <summary>
/// �}�b�v������
/// </summary>
	void Init();

	/// <summary>
	/// �}�b�v�`��
	/// </summary>
	void Draw(int scrollOffsetX, int scrollOffsetY);

	/// <summary>
	/// �}�b�v��n��
	/// </summary>
	void Finalize();

	/// <summary>
	/// �}�b�v��n��
	/// </summary>
	/// <param name ="checkRect">�}�b�v�Ɠ������Ă��邩������������`</param>
	/// <returns>�}�b�v�ƏՓ˂�������true/false�ŕԂ�</returns>
	bool HitCalc(sHitRect& checkRect);

	/// <summary>
	/// ���W�ʒu����u���b�N�ԍ���Ԃ�
	/// </summary>
	/// <param name ="ix">x���W</param>
	/// <param name ="iy">y���W</param>
	/// <returns>�}�b�v�̃u���b�N�ԍ���Ԃ�</returns>
	unsigned char GetBlockTypeXY(int x, int y);

	/// <summary>
	/// �}�b�v���[�_�[
	/// </summary>
	/// <param name="dst">�������������}�b�v�f�[�^</param>
	/// <param name="mapCSVFileName">�}�b�v�t�@�C����</param>
	/// <returns>�ǂݍ��݂ɐ�����������true false�ŕԋp</returns>
	bool LayerLoader(sMapLayer& dst, const char* mapCSVFileName);

	/// <summary>
	/// �}�b�v�̔j��
	/// </summary>
	/// <param name="dst">�������J���������}�b�v�f�[�^</param>
	void Unloader(sMapLayer& dst);

	/// <summary>
	/// �}�b�v�̃��C���[��`��
	/// </summary>
	/// <param name="layer">�`�悵�������C���[</param>
	void LayerDraw(sMapLayer& layer, int scrollOffsetX, int scrollOffsetY);
};

