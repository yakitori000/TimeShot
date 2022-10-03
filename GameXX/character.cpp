
#include "character.h"
void Character::Init()
{
    FontHandle2 = LoadFontDataToHandle("data/vermin vibes 1989シフトJIS.dft",1);
}
void Character::Title()
{
    DrawStringToHandle(730, 800, "ENTER to START", GetColor(255, 255, 255), FontHandle2);
}

void Character::display(Player& player, Enemy& enemy, Item& item, float deltaTime)
{
    /*TimeCount = int(TimeCount - GetNowHiPerformanceCount());*/
    FontHandle = CreateFontToHandle(NULL, 40, 9);
    
    //プレイヤーライフ表示
    sprintf(buf, "HP：%d", player.HitPoint);
    DrawString(80, 80, buf, GetColor(255, 255, 255));
    
    //プレイヤー弾数表示
    sprintf(buf, "Bullets：%d", player.count);
    DrawString(180, 80, buf, GetColor(255, 255, 255), FontHandle);

    //エネミーライフ表示
    sprintf(buf, "ENEMY LIFE：%d", enemy.life);
    DrawString(300, 40, buf, GetColor(255, 255, 255), FontHandle);

   /* sprintf(buf, "ENEMY LIFE：%d", enemy.life);
    DrawString(enemy.GetPosX(), enemy.GetPosY(), buf, GetColor(255, 255, 255), FontHandle);*/

    ////ゲームスコア表示
    //sprintf(buf, "SCORE：%d", enemy.GetScore());
    //DrawString(420, 80, buf, GetColor(255, 255, 255), FontHandle);

    //制限時間表示
    TimeDiff = int(TimeLimit - GetNowHiPerformanceCount());
    if (TimeDiff <= 30000000)
    {
        DrawFormatString(400, 80, GetColor(255, 0, 0), "TIME:%02d'%02d'%d%d", TimeDiff / 60000000, (TimeDiff % 60000000) / 1000000, ((TimeDiff % 60000000) % 1000000) / 100000, (((TimeDiff % 60000000) % 1000000) % 100000) / 10000);
    }
    else
    {
        DrawFormatString(400, 80, GetColor(255, 255, 255), "TIME:%02d'%02d'%d%d", TimeDiff / 60000000, (TimeDiff % 60000000) / 1000000, ((TimeDiff % 60000000) % 1000000) / 100000, (((TimeDiff % 60000000) % 1000000) % 100000) / 10000);
    }

    //プレイヤーが宝箱に当たったら...
    if (item.HitFlag)
    {
        sprintf(buf, " 宝箱を開ける\n(Dキーを押す)");
        DrawString(885, 108, buf, GetColor(255, 255, 255), FontHandle);
    }
    //プレイヤーが獲得出来たなら...
    else if (player.GetFlag )
    {
        sprintf(buf, " 銃弾を20個、手に入れた。");
        DrawString(835, 108, buf, GetColor(255, 255, 255), FontHandle);
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
