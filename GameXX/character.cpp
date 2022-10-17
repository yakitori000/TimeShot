
#include "character.h"
#include "Player.h"
#include "enemy.h"
#include "enemy2.h"
#include "Item.h"


void Character::Init()
{
    FontHandle2 = LoadFontDataToHandle("data/vermin vibes 1989�V�t�gJIS.dft",1);
}
void Character::Title()
{
    DrawStringToHandle(730, 800, "ENTER to START", GetColor(255, 255, 255), FontHandle2);
}

void Character::display(Player& player, Enemy& enemy,  Item& item)
{
    /*TimeCount = int(TimeCount - GetNowHiPerformanceCount());*/
    FontHandle = CreateFontToHandle(NULL, 40, 9);
    
    //�v���C���[���C�t�\��
    sprintf(buf, "HP�F%d", player.HitPoint);
    DrawString(80, 80, buf, GetColor(255, 255, 255));
    
    //�v���C���[�e���\��
    sprintf(buf, "Bullets�F%d", player.count);
    DrawString(180, 80, buf, GetColor(255, 255, 255), FontHandle);

    //�G�l�~�[���C�t1�\��
    sprintf(buf, "ENEMY LIFE�F%d", enemy.life1);
    DrawString(400, 20, buf, GetColor(255, 255, 255), FontHandle);

    //�G�l�~�[���C�t2�\��
    sprintf(buf, "ENEMY LIFE�F%d", enemy.life2);
    DrawString(400, 40, buf, GetColor(255, 255, 255), FontHandle);

    //�G�l�~�[���C�t3�\��
    sprintf(buf, "ENEMY LIFE�F%d", enemy.life3);
    DrawString(400, 60, buf, GetColor(255, 255, 255), FontHandle);

   /* sprintf(buf, "ENEMY LIFE�F%d", enemy.life);
    DrawString(enemy.GetPosX(), enemy.GetPosY(), buf, GetColor(255, 255, 255), FontHandle);*/

    ////�Q�[���X�R�A�\��
    //sprintf(buf, "SCORE�F%d", enemy.GetScore());
    //DrawString(420, 80, buf, GetColor(255, 255, 255), FontHandle);

   

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

void Character::GameTime(float deltaTime)
{
    //�������ԕ\��
    TimeDiff = int(TimeLimit - GetNowHiPerformanceCount());
    if (TimeDiff <= 30000000)
    {
        DrawFormatString(300, 80, GetColor(255, 0, 0), "TIME:%02d'%02d'%d%d", TimeDiff / 60000000, (TimeDiff % 60000000) / 1000000, ((TimeDiff % 60000000) % 1000000) / 100000, (((TimeDiff % 60000000) % 1000000) % 100000) / 10000);
    }
    else
    {
        DrawFormatString(300, 80, GetColor(255, 255, 255), "TIME:%02d'%02d'%d%d", TimeDiff / 60000000, (TimeDiff % 60000000) / 1000000, ((TimeDiff % 60000000) % 1000000) / 100000, (((TimeDiff % 60000000) % 1000000) % 100000) / 10000);
    }
}

void Character::GameCLEAR()
{
    DrawStringToHandle(725, 550, "ENTAR to TITLE\n          or\nESCKEY to END", GetColor(255, 255, 255), FontHandle2);
}

void Character::GameOVER()
{
    DrawStringToHandle(735, 550, "ENTAR to TITLE\n          or\nESCKEY to END", GetColor(255, 255, 255), FontHandle2);
}
