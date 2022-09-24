#pragma once
#include "DxLib.h"
#include <math.h>

/// <summary>
/// �����蔻��Z�`
/// </summary>
struct sHitRect
{
	float w;			//������Z�`���s�N�Z����
	float h;			//������Z�`�����s�N�Z����
	float worldLX;		//����w���W
	float worldLY;		//����x���W
	float worldRX;		//�E��w���W
	float worldRY;		//�E��x���W

};

//�u���b�N�Ǐ��
#define BLOCK_LEFT	0x01	// 0001
#define BLOCK_RIGHT	0x02	// 0010
#define BLOCK_UP	0x04	// 0100
#define BLOCK_DOWN	0x08	// 1000

/// <summary>
/// �u���b�N�Ǐ��^
/// </summary>
typedef unsigned char BlockInfo;

/// <summary>
/// �����蔻�菉����
/// </summary>
/// <param name="dstRect">�����������������蔻��ϐ�</param>
/// <param name="W">�����蔻��̕�</param>
/// <param name="W">�����蔻��̍���</param>
void initRect(sHitRect& dstRect, float w, float h);

/// <summary>
/// �����蔻��̈ړ��X�V����
/// </summary>
/// <param name="dstRect">�X�V�����������蔻��ϐ�</param>
/// <param name="X">�����蔻�荶��x���W</parma>
/// <param name="Y">�����蔻�荶��y���W</parma>
void updateWorldRect(sHitRect& dstRect, float x, float y);

/// <summary>
/// �����蔻��̒Z�`�̕`��
/// </summary>
/// <param name="rect">�`�悵���������蔻��Z�`</param>
//void drawRect(const sHitRect& rect);

/// <summary>
/// ��̋�`���Փ˂�������Ԃ�
/// </summary>
/// <param name="rect1">��`1</param>
/// <param name="rect2">��`2</param>
/// <returns>��`�̓���Փ˂�������true/false�ŕԂ�</returns>
bool isHitRect(const sHitRect& rect1, const sHitRect& rect2);

///// <summary>
/// 2�̋�`�̏Փ˂߂荞�ݗʂ��v�Z���AmobableRect�ʒu��ύX����
/// </summary>
/// <param name="movableRect">�ړ��\��`</param>
/// <param name="staticRect">�Î~��`(�����Ȃ��u���b�N�Ȃ�)</param>
void calcFixHitRectPosition(sHitRect& movableRect, const sHitRect& staticRect);

/// <summary>
/// 2�̋�`�̏Փ˂߂荞�ݗʂ��v�Z���AmobableRect�ʒu��ύX����
/// </summary>
/// <param name="movableRect">�ړ��\��`</param>
/// <param name="staticRect">�Î~��`(�����Ȃ��u���b�N�Ȃ�)</param>
/// <param name="blockInfo">�u���b�N���</param>
void calcFixHitRectPosition(sHitRect& movableRect, const sHitRect& staticRect, BlockInfo blockinfo);