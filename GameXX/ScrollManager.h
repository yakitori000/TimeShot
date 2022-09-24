#pragma once
#include "collision.h"


class Scroll
{
public:

    float scrollX;     // �X�N���[��X�����l
    float scrollY;     // �X�N���[��Y�����l

    float screenXMax;  // �X�N���[����̉E�X�N���[���J�n���E�l
    float screenYMin;  // �X�N���[����̏�X�N���[���J�n���E�l
    float screenYMax;  // �X�N���[����̉��X�N���[���J�n���E�l

    int screenWidth; // �X�N���[����
    int screenHeight;// �X�N���[������

    float scrollXMax;   // �X�e�[�W�S�̂�X�����ő�l
    float scrollYMin;   // �X�e�[�W�S�̂�Y�����ŏ��l
    float scrollYMax;   // �X�e�[�W�S�̂�Y�����ő�l

    float dx;
    float dy;

    const float scrollSpeed = 5.0f;

    /// <summary>
    /// �X�N���[���}�l�[�W��������
    /// </summary>
    /// <param name="windowWidth">�E�B���h�E�̕��h�b�g��</param>
    /// <param name="windowHeight">�E�B���h�E�̍����h�b�g��</param>
    /// <param name="worldRect">�X�e�[�W�S�̂̋�`</param>
    void Init(int screenWidth, int screenHeight, const sHitRect& worldRect);

    /// <summary>
    /// �X�N���[���̍X�V����
    /// </summary>
    /// <param name="playerRect">�X�N���[���̒��S�ƂȂ�L�����N�^�[��`</param>
    /// <param name="deltaTime">�E�B���h�E�X�V����</param>
    void Update(const sHitRect& playerRect, float deltaTime);

    /// <summary>
    /// �X�N���[���̕`��I�t�Z�b�gX���擾
    /// </summary>
    /// <returns>x�����I�t�Z�b�g</returns>
    int GetDrawOffsetX();

    /// <summary>
    /// �X�N���[���̕`��I�t�Z�b�gY���擾
    /// </summary>
    /// <returns>y�����I�t�Z�b�g</returns>
    int GetDrawOffsetY();

    /// <summary>
    /// �X�N���[���̃f�o�b�O���\��
    /// </summary>
    void DebugShow();
};

