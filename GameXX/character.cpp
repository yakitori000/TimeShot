
#include "character.h"
void Character::Init()
{
    FontHandle2 = LoadFontDataToHandle("data/vermin vibes 1989�V�t�gJIS.dft",1);
}
void Character::Title()
{
    DrawStringToHandle(720, 800, "ENTER to START", GetColor(255, 255, 255), FontHandle2);
}

void Character::display(Player& player, Enemy& enemy, Item& item, float deltaTime)
{
    /*TimeCount = int(TimeCount - GetNowHiPerformanceCount());*/
    /*FontHandle = CreateFontToHandle(NULL, 40, 9);*/
    
    //�v���C���[���C�t�\��
    sprintf(buf, "HP�F%d", player.HitPoint);
    DrawString(80, 80, buf, GetColor(255, 255, 255));
    
    //�v���C���[�e���\��
    sprintf(buf, "Bullets�F%d", player.count);
    DrawString(180, 80, buf, GetColor(255, 255, 255), FontHandle);

    //�G�l�~�[���C�t�\��
   /* sprintf(buf, "ENEMY LIFE�F%d", enemy.GetLife());
    DrawString(300, 80, buf, GetColor(255, 255, 255), FontHandle);*/

    sprintf(buf, "ENEMY LIFE�F%d", enemy.life);
    DrawString(enemy.GetPosX(), enemy.GetPosY(), buf, GetColor(255, 255, 255), FontHandle);

    ////�Q�[���X�R�A�\��
    //sprintf(buf, "SCORE�F%d", enemy.GetScore());
    //DrawString(420, 80, buf, GetColor(255, 255, 255), FontHandle);

    //�������ԕ\��
    TimeDiff = int(TimeLimit - GetNowHiPerformanceCount());
    DrawFormatString(400, 80, GetColor(255, 255, 255), "TIME:%02d'%02d'%d%d", TimeDiff / 60000000, (TimeDiff % 60000000) / 1000000, ((TimeDiff % 60000000) % 1000000) / 100000, (((TimeDiff % 60000000) % 1000000) % 100000) / 10000);


    //�v���C���[���󔠂ɓ���������...
    if (item.HitFlag)
    {
        sprintf(buf, " �󔠂��J����\n(D�L�[������)");
        DrawString(885, 108, buf, GetColor(255, 255, 255), FontHandle);
    }
    //�v���C���[���l���o�����Ȃ�...
    else if (player.GetFlag )
    {
        sprintf(buf, " �e�e��20�A��ɓ��ꂽ�B");
        DrawString(835, 108, buf, GetColor(255, 255, 255), FontHandle);
    }
    
}

void Character::GameCLEAR()
{
    sprintf(buf, "ESCAPE�L�[�������Ă��������B");
    DrawString(970, 540, buf, GetColor(255, 255, 255));
}

void Character::GameOVER()
{
    sprintf(buf, "ESCAPE�L�[�������Ă��������B");
    DrawString(970, 540, buf, GetColor(255, 255, 255));
}
