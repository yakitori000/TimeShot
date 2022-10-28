#include <windows.h>
#include "DxLib.h"
#include "player.h"
#include "enemy.h"
#include "shot.h"
#include "ShotEnemy.h"
#include "Item.h"
#include "map.h"
#include "character.h"
#include "collision.h"
#include "function.h"
#include "GameSituation.h"
#include "ScreenImage.h"
#include "Music.h"
#include "ScrollManager.h"
#pragma warning(disable:4996)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    // DxLib������
    SetGraphMode(SCREEN_WMAX, SCREEN_H, 16);
    ChangeWindowMode(TRUE);

    if (DxLib_Init() == -1)
    {
        return -1;
    }

    Player player{ };
    Enemy enemy{ };
    Shot shot[SHOT]{ };
    ShotEnemy Eshot[ESHOT]{ };
    sMapLayer map;
    Item item;
    Character character;
    ScreenImage image;
    Scroll scroll;
    Music music;

    // ������
    image.Init();
    music.Init();
    player.Init();
    character.Init();
    
    enemy.Init1();
    enemy.Init2();
    enemy.Init3();
    
    map.Init();
    item.Init(music);
    for (int i = 0; i < SHOT; i++)
    {
        shot[i].Init();
    }
    for (int j = 0; j < ESHOT; j++)
    {
        Eshot[j].InitShotEnemy();
    }

    int TimeDiff = 0;
    LONGLONG TimeLimit = GetNowHiPerformanceCount() + 120000000.0f;

    GameSituation = TITLE;

    int nowCount, prevCount;
    nowCount = prevCount = GetNowCount();

    // �Q�[�����[�v
    while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
    {
        switch (GameSituation)
        {
        case TITLE:
            ClearDrawScreen();

            music.playTitleSound();
            image.DrawTitle();
            character.Title();

            if (CheckHitKey(KEY_INPUT_Q))
            {
                GameSituation = MENU;
            }

            if (CheckHitKey(KEY_INPUT_RETURN))
            {
                StopSoundMem(music.TitleMusic);
                GameSituation = PLAY;
            }
            ScreenFlip();
            break;

        case MENU:
            ClearDrawScreen();
            
            image.DrawMenu();
            if (CheckHitKey(KEY_INPUT_RETURN))
            {
                WaitTimer(1000);
                GameSituation = TITLE;
            }
            break;

        case PLAY:
           ClearDrawScreen();

           // deltaTime�v��
           float deltaTime;
           nowCount = GetNowCount();
           deltaTime = (nowCount - prevCount) / 1000.0f;
           TimeDiff = int(TimeLimit - GetNowHiPerformanceCount());

           
           music.playBGM();

           if (TimeDiff <= 31000000)
           {
               StopSoundMem(music.GameMusic);
               music.playBGM2();
           }
            
           //�X�V���� 120fps�z��
           player.Update(shot, SHOT, item, music, 1.0f / 60.0f);
               
               enemy.Update1(player, music, Eshot, ESHOT, 1.0f / 60.0f);
               enemy.Update2(player, music, 1.0f / 60.0f);
               enemy.Update3(player, music, 1.0f / 60.0f);
          
           item.Updata(player, music);
           for (int i = 0; i < SHOT; i++)
           {
              // music.playShot(player.count);
               
                   shot[i].Update(player, enemy);
               
           }
           for (int j = 0; j < ESHOT; j++)
           {
               Eshot[j].UpdateShotEnemy(player, enemy);
           }

           // �v���C���[�̓����蔻���`
           sHitRect playerRect;
           playerRect = player.getHitRect();

           //�G�l�~�[�̓����蔻��Z�`
           sHitRect enemyRect1;
           sHitRect enemyRect2;
           sHitRect enemyRect3;

           enemyRect1 = enemy.getHitRect1();
           enemyRect2 = enemy.getHitRect2();
           enemyRect3 = enemy.getHitRect3();

           // �����Ԃ������Ȃ瓖���蔻��{�b�N�X����ʒu���C������
           if (map.HitCalc(playerRect))
           {
               player.fixColPosition(playerRect);
           }

           if (map.HitCalc(enemyRect1))
           {
              enemy.fixColPosition1(enemyRect1);
           }
           if (map.HitCalc(enemyRect2))
           {
               enemy.fixColPosition2(enemyRect2);
           }
           if (map.HitCalc(enemyRect3))
           {
               enemy.fixColPosition3(enemyRect3);
           }
          
           // �����`�F�b�N
           playerRect = player.GetGroundCollider();
           player.SetGroundFlag(map.HitCalc(playerRect));
           
           enemyRect1 = enemy.GetGroundCollider1();
           enemy.SetGroundFlag1(map.HitCalc(enemyRect1));

           enemyRect2 = enemy.GetGroundCollider2();
           enemy.SetGroundFlag2(map.HitCalc(enemyRect2));

           enemyRect3 = enemy.GetGroundCollider3();
           enemy.SetGroundFlag3(map.HitCalc(enemyRect3));
           

           // ����`�F�b�N
           playerRect = player.GetHeadCollider();
           player.SetHeadHitFlag(map.HitCalc(playerRect));
           
           enemyRect1 = enemy.GetHeadCollider1();
           enemy.SetHeadHitFlag1(map.HitCalc(enemyRect1));

           enemyRect2 = enemy.GetHeadCollider2();
           enemy.SetHeadHitFlag2(map.HitCalc(enemyRect2));

           enemyRect3 = enemy.GetHeadCollider3();
           enemy.SetHeadHitFlag3(map.HitCalc(enemyRect3));

           //�X�N���[���X�V����
           scroll.Update(playerRect, deltaTime);

           // �X�N���[���ʎ擾
           int scrOffsX, scrOffsY;
           scrOffsX = scroll.GetDrawOffsetX();
           scrOffsY = scroll.GetDrawOffsetY();

           //��ʍX�V����
           ClearDrawScreen();

           // �}�b�v�`��
           map.Draw(scrOffsX, scrOffsY);

           //�`��
           for (int i = 0; i < SHOT; i++)
           {
               shot[i].Draw(player);
           }

           for (int j = 0; j < ESHOT; j++)
           {
               Eshot[j].DrawShotEnemy(enemy);
           }
           item.Draw();
           player.Draw();
           enemy.Draw1();
           enemy.Draw2();
           enemy.Draw3();
           
           //�����A���ԕ\��
           
               character.display(player, enemy, item); 
               character.GameTime(1.0f / 60.0f);
           
             //�Q�[���N���A����
            if (enemy.life1 <= 0 && enemy.life2 <= 0 && enemy.life3 <= 0)
            {
                StopSoundMem(music.GameMusic);
                StopSoundMem(music.GameImpatientMusic);
                GameSituation = CLEAR;
            }
            
            //�Q�[���I�[�o�[����
            if (player.GetHitPoint() <= 0 || TimeDiff <= 02000000)
            {
                StopSoundMem(music.GameMusic);
                StopSoundMem(music.GameImpatientMusic);
                GameSituation = OVER;
            }
            
            break;

            //�Q�[���N���A����
        case CLEAR:                 
            ClearDrawScreen();

            image.DrawClear();
            character.GameCLEAR();
            ScreenFlip();
            if (CheckHitKey(KEY_INPUT_ESCAPE))
            {
                DxLib_End();
            }
            ScreenFlip();
            break;

            //�Q�[���I�[�o�[����
        case OVER:                  
            ClearDrawScreen();

            image.DrawOver();
            character.GameOVER();
            if (CheckHitKey(KEY_INPUT_ESCAPE))
            {
                DxLib_End();
            }
            ScreenFlip();
            break;

        default:
            break;
        }

        ScreenFlip();

    }

    player.Finalize();
    map.Finalize();

    DxLib_End();
    return 0;
}