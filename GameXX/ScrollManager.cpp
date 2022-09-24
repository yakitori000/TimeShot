#include "scrollManager.h"
#pragma warning (disable:4996)

Scroll scroll;

void Scroll::Init(int screenwidth, int screenheight, const sHitRect& worldRect)
{
	screenWidth = screenwidth;
	screenHeight = screenheight;

	screenXMax = screenWidth / 12.0f * 7.0f;  // �X�N���[�� 5/8 �̈ʒu���X�N���[���J�n�n�_ 
	screenYMin = screenHeight / 12.0f * 3.0f; // �X�N���[�� 3/8 �̈ʒu����X�N���[���J�n�n�_
	screenYMax = screenHeight / 12.0f * 7.0f; // �X�N���[�� 5/8 �̈ʒu�����X�N���[���J�n�n�_

	scrollXMax = worldRect.worldRX - screenWidth;
	scrollYMin = worldRect.worldLY;
	scrollYMax = worldRect.worldRY - screenHeight;



}

void Scroll::Update(const sHitRect& playerRect, float deltaTime)
{
	dx = dy = 0.0f;
	// �v���C���[���X�N���[�����E�𒴂��Ă�����߂��ʂ��v�Z����
	if (playerRect.worldRX > scrollX + screenXMax)
	{
		dx = playerRect.worldRX - (scrollX + screenXMax);
	}

	// ��X�N���[��
	if (playerRect.worldLY < scrollY + screenYMin)
	{
		dy = playerRect.worldLY - (scrollY + screenYMin);
	}

	//�@���X�N���[��
	if (playerRect.worldRY > scrollY + screenYMax)
	{
		dy = playerRect.worldRY - (scrollY + screenYMax);
	}

	// ���݂̋�`�ʒu��ύX����
	scrollX += dx;
	scrollY += dy;

	if (scrollX > scrollXMax)
	{
		scrollX = scrollXMax;
	}

	if (scrollY > scrollYMax)
	{
		scrollY = scrollYMax;
	}

	if (scrollY < scrollYMin)
	{
		scrollY = scrollYMin;
	}

}



int Scroll::GetDrawOffsetX()
{
	return static_cast<int>(scroll. scrollX);
}

int Scroll::GetDrawOffsetY()
{
	return static_cast<int>(scroll.scrollY);
}

void Scroll::DebugShow()
{
	char buf[256];
	sprintf(buf, "xOffset %f, yOffset %f\ndx : %f dy : %f", scroll.scrollX, scroll.scrollY, scroll.dx, scroll.dy);

	DrawString(0, 30, buf, GetColor(0, 255, 0));

	DrawLine(scroll.screenXMax, 0, scroll.screenXMax, 1280, GetColor(255, 255, 0));
	DrawLine(0, scroll.screenYMin, 1980, scroll.screenYMin, GetColor(255, 255, 0));
	DrawLine(0, scroll.screenYMax, 1980, scroll.screenYMax, GetColor(255, 255, 0));

}

