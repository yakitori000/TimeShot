#include "map.h"
#include "collision.h"
#include "ScreenImage.h"
#pragma warning (disable:4996)

//////////////////////////////////////////////
// �萔��`
//////////////////////////////////////////////

const int mapChipSize = 32;  // �}�b�v�`�b�v�P�̑傫��
const int mapImgXNum = 10;    // �}�b�v�`�b�v�摜�̉������`�b�v��
const int mapImgYNum = 2;    // �}�b�v�`�b�v�摜�̏c�����`�b�v��

sMapLayer layerHit;
sMapLayer layerNear;
sMapLayer layerBase;
sMapLayer layerBack;
sMapLayer map;
ScreenImage image;

int mapChipImg[20]; // �摜�n���h���z��

	/// <summary>
	/// �}�b�v�̃C���f�b�N�X�ʒu����u���b�N�ԍ���Ԃ�
	/// </summary>
	/// <param name ="ix">�}�b�v�̃C���f�b�N�X�ԍ�x</param>
	/// <param name ="iy">�}�b�v�̃C���f�b�N�X�ԍ�y</param>
	/// <returns>�}�b�v�̃u���b�N�ԍ���Ԃ�</returns>
unsigned char GetBlockType(int ix, int iy);

/// <summary>
/// �Ǐ��擾 ����u���b�N�̕ǂ̗L���𒲂� BlockInfo��Ԃ�
/// </summary>
/// <param name="x">�����������u���b�N�̉��C���f�b�N�X</param>
/// <param name="y">�����������u���b�N�̏c�C���f�b�N�X</param>
/// <returns>�ǂ̗L����� BLOCK_LEFT�` BLOCK_DOWN�܂ł̃r�b�g�l���d�˂��킳��ĕԋp�����</returns>
BlockInfo GetBlockInfo(int ix, int iy)

{
	BlockInfo ret = 0;

	// �u���b�N��1�����󔒂��H
	if (GetBlockType(ix - 1, iy) == 0)
	{
		ret |= BLOCK_LEFT;
	}
	// �u���b�N�̈�E���󔒂��H
	if (GetBlockType(ix + 1, iy) == 0)
	{
		ret |= BLOCK_RIGHT;
	}
	// �u���b�N�̈�オ�󔒂��H
	if (GetBlockType(ix, iy - 1) == 0)
	{
		ret |= BLOCK_UP;
	}
	//�u���b�N�̈�����󔒂��H
	if (GetBlockType(ix, iy + 1) == 0)
	{
		ret |= BLOCK_DOWN;
	}

	// ret�ɂ�4�����̕ǂ̗L���̃r�b�g���d�ˍ��킳��Ă���
	return ret;
}

void sMapLayer::Init()
{
	// �摜����  ������x�c����,��������,�c������,�`�b�v1���̉��T�C�Y, �`�b�v1���̏c�T�C�Y, �摜�z��擪�|�C���^ 
	LoadDivGraph("data/image/HeadBrid tile.png", mapImgXNum * mapImgYNum, mapImgXNum, mapImgYNum, mapChipSize, mapChipSize, mapChipImg);

	//�}�b�v�ǂݍ���
	LayerLoader(layerHit, "data/map/NewGamehit2.csv");
	//LayerLoader(layerBack, "dataisland_back.csv");
	LayerLoader(layerBase, "data/map/NewGame02.csv");
	//LayerLoader(layerNear, "data/island_near.csv");

	//�w�i�摜
	image.InitBack();	

}

void sMapLayer::Draw(int scrollOffsetX, int scrollOffsetY)
{
	image.DrawBack();
	//LayerDraw(layerBack, scrollOffsetX, scrollOffsetY);
	LayerDraw(layerBase, scrollOffsetX, scrollOffsetY);
	//LayerDraw(layerNear, scrollOffsetX, scrollOffsetY);
	
}

void sMapLayer::LayerDraw(sMapLayer& layer, int scrollOffsetX, int scrollOffsetY)
{
	for (int y = 0; y < layer.mapYNum; y++)
	{
		for (int x = 0; x < layer.mapXNum; x++)
		{
			int imgIndex = layer.mapData[y][x];              // map�z����u���b�N��ނ��擾

			//�`�悵�悤�Ƃ��Ă���id��-1�̎��͕`����X�L�b�v
			if (imgIndex == -1)
			{
				continue;
			}

			int imgHandle = mapChipImg[imgIndex];  // index�������ĉ摜�n���h���z�񂩂�摜�n���h�����擾

			// �}�b�v�`�b�v���Ńu���b�N�摜��~���l�߂ĕ`�悷��
			// x��0,1,2�E�E�E�ƕω�����B x * mapChipSize �̌v�Z�� 0,64,128,196, ... �ƃu���b�N�����Ƃɑ�����
			DrawGraph(x * mapChipSize - scrollOffsetX, y * mapChipSize - scrollOffsetY, imgHandle, TRUE);
		}
	}
}

void sMapLayer::Finalize()
{
	for (int i = 0; i < mapImgXNum * mapImgYNum; i++)
	{
		DeleteGraph(mapChipImg[i]);
	}

	Unloader(layerHit);
	Unloader(layerBack);
	Unloader(layerBase);
	Unloader(layerNear);
}

bool sMapLayer::HitCalc(sHitRect& checkRect)
{
	bool hitflg = false;
	sHitRect blockRect;

	blockRect.w = mapChipSize;
	blockRect.h = mapChipSize;

	// ���ׂẴ}�b�v�u���b�N vs �����u���b�N�̏Փ˂𒲂ׂ�
	for (int iy = 0; iy < layerHit.mapYNum; iy++)
	{
		//�}�b�v�u���b�N��Y���W
		blockRect.worldLY = static_cast<float>(iy * mapChipSize);
		blockRect.worldRY = static_cast<float>((iy + 1) * mapChipSize);

		for (int ix = 0; ix < layerHit.mapXNum; ix++)
		{
			// ������u���b�N�� 0���ʂ�� 0�ȊO���ʂ�Ȃ� 
			if (layerHit.mapData[iy][ix] != 0)
			{
				// �}�b�v�u���b�N��X���W
				blockRect.worldLX = static_cast<float>(ix * mapChipSize);
				blockRect.worldRX = (ix + 1) * static_cast<float>(mapChipSize);

				// �������Ă��邩�H
				if (isHitRect(checkRect, blockRect))
				{
					// ��x�ł��u���b�N�Ɠ���������hitflg��true��
					hitflg = true;

					// �u���b�N���i�㉺���E�ǂ̗L���𒲂ׂ�j
					BlockInfo bi = GetBlockInfo(ix, iy);

					// �{�b�N�X�̂߂荞�ݗʂ��v�Z����
					// checkRect�ɂ͂߂荞�ݖ߂��ʂ�����
					calcFixHitRectPosition(checkRect, blockRect, bi);

				}
			}
		}
	}

	return hitflg;
}

unsigned char GetBlockType(int ix, int iy)
{
	if (ix < 0 || iy < 0 || ix >= layerHit.mapXNum || iy >= layerHit.mapYNum)
	{
		return 0;
	}
	return layerHit.mapData[iy][ix];
}

unsigned char sMapLayer::GetBlockTypeXY(int x, int y)
{
	return GetBlockType(x / mapChipSize, y / mapChipSize);
}

bool sMapLayer::LayerLoader(sMapLayer& dst, const char* mapCSVFileName)
{
	// dst������
	dst.mapData = NULL;
	dst.mapXNum = 0;
	dst.mapYNum = 0;

	// �t�@�C�����J��
	FILE* fp;
	fp = fopen(mapCSVFileName, "rt");
	if (!fp)
	{
		printf("�t�@�C�����J���܂���");
		return 0;
	}

	// �t�@�C�����P�s����ǂ݂��A�P�s�̃f�[�^���𐔂���
	char c = 0;
	while (c != '\n')
	{
		// �ǂݎ�����������J���}�Ȃ�1�J�E���g���₷
		c = fgetc(fp);
		if (',' == c)
		{
			dst.mapXNum++;
		}
	}
	dst.mapXNum++;

	//�P�f�[�^ 16bit�ő�l "65535,"(6����)�Ƃ��ĕ���������Ă����Ƃ��̂P�s�T�C�Y
	int bufferLen = dst.mapXNum * 6 + 1;

	//�P�s���̃o�b�t�@�m��
	char* buf = new char[bufferLen];
	char* ptmp = buf;

	//�t�@�C���|�C���^��擪�ɖ߂��s����ǂ�
	fseek(fp, 0, SEEK_SET);
	bool firstRow = true;
	while (fgets(buf, bufferLen - 1, fp) != NULL)
	{
		dst.mapYNum++;
	}

	//2�����z��𓮓I�m�ۂ��� map[row][col] �Ƃ��ē��I�m�ۂ���
	dst.mapData = new int* [dst.mapYNum];

	int ix, iy;
	for (iy = 0; iy < dst.mapYNum; iy++)
	{
		dst.mapData[iy] = new int[dst.mapXNum];
	}

	//�t�@�C���|�C���^��擪�ɖ߂�
	fseek(fp, 0, SEEK_SET);
	// �t�@�C������f�[�^��z��Ɉڂ�
	char* readPoint;
	char* firstPoint;
	for (iy = 0; iy < dst.mapYNum; iy++)
	{
		// 1�s��荞��
		fgets(buf, bufferLen - 1, fp);
		readPoint = firstPoint = buf;

		for (ix = 0; ix < dst.mapXNum; ix++)
		{
			//�J���}�܂�readPoint�̈ʒu��i�߂�
			while (',' != *readPoint && '\n' != *readPoint)
			{
				readPoint++;
			}
			// �J���}��NULL�����ɒu������
			*readPoint = '\0';
			//���̎��_��firstPoint - readPoint�Ԃŕ����񂪊�������̂Ő��l�ɕϊ�
			dst.mapData[iy][ix] = atoi(firstPoint);

			//���̃f�[�^�ǂݎ��ʒu�܂Ői�߂�
			readPoint++;
			firstPoint = readPoint;
		}
	}

	// �t�@�C�������
	fclose(fp);

	// �o�b�t�@�J��
	delete[] buf;

	return true;
}

void sMapLayer::Unloader(sMapLayer& dst)
{
	// �f�[�^�̉��
	for (int iy = 0; iy < dst.mapYNum; iy++)
	{
		delete[] dst.mapData[iy];
	}
	delete[] dst.mapData;

	// dst������
	dst.mapData = NULL;
	dst.mapXNum = 0;
	dst.mapYNum = 0;
}

//
//#include "map.h"
//
//#pragma warning (disable:4996)
//
////////////////////////////////////////////////
//// �萔��`
////////////////////////////////////////////////
//sMapLayer layerHit;
//sMapLayer layerBase;
//sMapLayer map;
//
//int mapChipImg[20]; // �摜�n���h���z��
//
///// <summary>
///// �Ǐ��擾 ����u���b�N�̕ǂ̗L���𒲂� BlockInfo��Ԃ�
///// </summary>
///// <param name="x">�����������u���b�N�̉��C���f�b�N�X</param>
///// <param name="y">�����������u���b�N�̏c�C���f�b�N�X</param>
///// <returns>�ǂ̗L����� BLOCK_LEFT�` BLOCK_DOWN�܂ł̃r�b�g�l���d�˂��킳��ĕԋp�����</returns>
//BlockInfo mapGetBlockInfo(int ix, int iy)
//{
//	BlockInfo ret = 0;
//
//	// �u���b�N��1�����󔒂��H
//	if (map.GetBlockType(ix - 1, iy) == 0)
//	{
//		ret |= BLOCK_LEFT;
//	}
//	// �u���b�N�̈�E���󔒂��H
//	if (map.GetBlockType(ix + 1, iy) == 0)
//	{
//		ret |= BLOCK_RIGHT;
//	}
//	// �u���b�N�̈�オ�󔒂��H
//	if (map.GetBlockType(ix, iy - 1) == 0)
//	{
//		ret |= BLOCK_UP;
//	}
//	//�u���b�N�̈�����󔒂��H
//	if (map.GetBlockType(ix, iy + 1) == 0)
//	{
//		ret |= BLOCK_DOWN;
//	}
//
//	// ret�ɂ�4�����̕ǂ̗L���̃r�b�g���d�ˍ��킳��Ă���
//	return ret;
//}
//
//void sMapLayer::Init()
//{
//	// �摜����  ������x�c����,��������,�c������,�`�b�v1���̉��T�C�Y, �`�b�v1���̏c�T�C�Y, �摜�z��擪�|�C���^ 
//	LoadDivGraph("data/HeadBrid tile.png", mapImgXNum * mapImgYNum, mapImgXNum, mapImgYNum, mapChipSize, mapChipSize, mapChipImg);
//	//�}�b�v�ǂݍ��݁i���C���[���ƂɁj
//	map.LayerLoader(layerBase, "data/NewGame02.csv");
//	map.LayerLoader(layerHit, "data/NewGameHit2.csv");
//
//}
//
//void sMapLayer::Draw()
//{
//	map.LayerDraw(layerBase);
//}
//
//void sMapLayer::LayerDraw(sMapLayer& layer)
//{
//	for (int y = 0; y < layer.mapYNum; y++)
//	{
//		for (int x = 0; x < layer.mapXNum; x++)
//		{
//			int imgIndex = layer.mapData[y][x];              // map�z����u���b�N��ނ��擾
//
//			//�`�悵�悤�Ƃ��Ă���id��-1�̎��͕`����X�L�b�v
//			if (imgIndex == -1)
//			{
//				continue;
//			}
//
//			int imgHandle = mapChipImg[imgIndex];  // index�������ĉ摜�n���h���z�񂩂�摜�n���h�����擾
//
//			// �}�b�v�`�b�v���Ńu���b�N�摜��~���l�߂ĕ`�悷��
//			// x��0,1,2�E�E�E�ƕω�����B x * mapChipSize �̌v�Z�� 0,64,128,196, ... �ƃu���b�N�����Ƃɑ�����
//			DrawGraph(x * mapChipSize , y * mapChipSize, imgHandle, TRUE);
//		}
//	}
//}
//
//void sMapLayer::Finalize()
//{
//	for (int i = 0; i < mapImgXNum * mapImgYNum; i++)
//	{
//		DeleteGraph(mapChipImg[i]);
//	}
//
//	map.Unloader(layerBase);
//	
//}
//
//bool sMapLayer::HitCalc(sHitRect& checkRect)
//{
//	bool hitflg = false;
//	sHitRect blockRect;
//
//	blockRect.w = mapChipSize;
//	blockRect.h = mapChipSize;
//
//	// ���ׂẴ}�b�v�u���b�N vs �����u���b�N�̏Փ˂𒲂ׂ�
//	for (int iy = 0; iy < layerHit.mapYNum; iy++)
//	{
//		//�}�b�v�u���b�N��Y���W
//		blockRect.worldLY = static_cast<float>(iy * mapChipSize);
//		blockRect.worldRY = static_cast<float>((iy + 1) * mapChipSize);
//
//		for (int ix = 0; ix < layerHit.mapXNum; ix++)
//		{
//			// ������u���b�N�� 0���ʂ�� 0�ȊO���ʂ�Ȃ� 
//			if (layerHit.mapData[iy][ix] != 0)
//			{
//				// �}�b�v�u���b�N��X���W
//				blockRect.worldLX = static_cast<float>(ix * mapChipSize);
//				blockRect.worldRX = (ix + 1) * static_cast<float>(mapChipSize);
//
//				// �������Ă��邩�H
//				if (isHitRect(checkRect, blockRect))
//				{
//					// ��x�ł��u���b�N�Ɠ���������hitflg��true��
//					hitflg = true;
//
//					// �u���b�N���i�㉺���E�ǂ̗L���𒲂ׂ�j
//					BlockInfo bi = mapGetBlockInfo(ix, iy);
//
//					// �{�b�N�X�̂߂荞�ݗʂ��v�Z����
//					// checkRect�ɂ͂߂荞�ݖ߂��ʂ�����
//					calcFixHitRectPosition(checkRect, blockRect, bi);
//
//				}
//			}
//		}
//	}
//
//	return hitflg;
//}
//
//unsigned char sMapLayer::GetBlockType(int ix, int iy)
//{
//	if (ix < 0 || iy < 0 || ix >= layerHit.mapXNum || iy >= layerHit.mapYNum)
//	{
//		return 0;
//	}
//	return layerHit.mapData[iy][ix];
//}
//
//unsigned char sMapLayer::GetBlockTypeXY(int x, int y)
//{
//	return map.GetBlockType(x / mapChipSize, y / mapChipSize);
//}
//
//bool sMapLayer::LayerLoader(sMapLayer& dst, const char* mapCSVFileName)
//{
//	// dst������
//	dst.mapData = NULL;
//	dst.mapXNum = 0;
//	dst.mapYNum = 0;
//
//	// �t�@�C�����J��
//	FILE* fp;
//	fp = fopen(mapCSVFileName, "rt");
//	if (!fp)
//	{
//		printf("�t�@�C�����J���܂���");
//		return 0;
//	}
//
//	// �t�@�C�����P�s����ǂ݂��A�P�s�̃f�[�^���𐔂���
//	char c = 0;
//	while (c != '\n')
//	{
//		// �ǂݎ�����������J���}�Ȃ�1�J�E���g���₷
//		c = fgetc(fp);
//		if (',' == c)
//		{
//			dst.mapXNum++;
//		}
//	}
//	dst.mapXNum++;
//
//	//�P�f�[�^ 16bit�ő�l "65535,"(6����)�Ƃ��ĕ���������Ă����Ƃ��̂P�s�T�C�Y
//	int bufferLen = dst.mapXNum * 6 + 1;
//
//	//�P�s���̃o�b�t�@�m��
//	char* buf = new char[bufferLen];
//	char* ptmp = buf;
//
//	//�t�@�C���|�C���^��擪�ɖ߂��s����ǂ�
//	fseek(fp, 0, SEEK_SET);
//	bool firstRow = true;
//	while (fgets(buf, bufferLen - 1, fp) != NULL)
//	{
//		dst.mapYNum++;
//	}
//
//	//2�����z��𓮓I�m�ۂ��� map[row][col] �Ƃ��ē��I�m�ۂ���
//	dst.mapData = new int* [dst.mapYNum];
//
//	int ix, iy;
//	for (iy = 0; iy < dst.mapYNum; iy++)
//	{
//		dst.mapData[iy] = new int[dst.mapXNum];
//	}
//
//	//�t�@�C���|�C���^��擪�ɖ߂�
//	fseek(fp, 0, SEEK_SET);
//	// �t�@�C������f�[�^��z��Ɉڂ�
//	char* readPoint;
//	char* firstPoint;
//	for (iy = 0; iy < dst.mapYNum; iy++)
//	{
//		// 1�s��荞��
//		fgets(buf, bufferLen - 1, fp);
//		readPoint = firstPoint = buf;
//
//		for (ix = 0; ix < dst.mapXNum; ix++)
//		{
//			//�J���}�܂�readPoint�̈ʒu��i�߂�
//			while (',' != *readPoint && '\n' != *readPoint)
//			{
//				readPoint++;
//			}
//			// �J���}��NULL�����ɒu������
//			*readPoint = '\0';
//			//���̎��_��firstPoint - readPoint�Ԃŕ����񂪊�������̂Ő��l�ɕϊ�
//			dst.mapData[iy][ix] = atoi(firstPoint);
//
//			//���̃f�[�^�ǂݎ��ʒu�܂Ői�߂�
//			readPoint++;
//			firstPoint = readPoint;
//		}
//	}
//
//	// �t�@�C�������
//	fclose(fp);
//
//	// �o�b�t�@�J��
//	delete[] buf;
//
//	return true;
//}
//
//void sMapLayer::Unloader(sMapLayer& dst)
//{
//	// �f�[�^�̉��
//	for (int iy = 0; iy < dst.mapYNum; iy++)
//	{
//		delete[] dst.mapData[iy];
//	}
//	delete[] dst.mapData;
//
//	// dst������
//	dst.mapData = NULL;
//	dst.mapXNum = 0;
//	dst.mapYNum = 0;
//}