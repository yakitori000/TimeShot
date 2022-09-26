#include <windows.h>
#include "DxLib.h"
#include "player.h"
#include "enemy.h"
#include "shot.h"
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
    SetGraphMode(SCREEN_W, SCREEN_H, 16);
    ChangeWindowMode(TRUE);

    if (DxLib_Init() == -1)
    {
        return -1;
    }

    Player player{ };
    Enemy enemy[ENEMY_NUM]{ };
    Shot shot[SHOT]{ };
    sMapLayer map;
    Item item;
    Character character;
    ScreenImage image;
    Scroll scroll;
    Music music;

    LPCSTR font_path = "vermin_vibes.ttf"; // �ǂݍ��ރt�H���g�t�@�C���̃p�X

    // ������
    image.InitTitle();
    image.InitClear();
    image.InitOver();
    music.Init();
    music.ShotSoudInit();
    player.Init();
    character.Init();
    for (int i = 0; i < ENEMY_NUM; i++)
    {
        enemy[i].Init();
    }
    map.Init();
    item.Init();
    for (int i = 0; i < SHOT; i++)
    {
        shot[i].Init();
    }

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

            if (CheckHitKey(KEY_INPUT_RETURN))
            {
                GameSituation = PLAY;
            }
            ScreenFlip();
            break;

        case PLAY:
           ClearDrawScreen();

           // deltaTime�v��
           float deltaTime;
           nowCount = GetNowCount();
           deltaTime = (nowCount - prevCount) / 1000.0f;
           
           music.playBGM();
            
           //�X�V���� 1201fps�z��
           player.Update(shot, SHOT, item, music, 1.0f / 60.0f);
           for (int i = 0; i < ENEMY_NUM; i++)
           {
               
               enemy[i].Update(player, 1.0f / 60.0f);
           }
          
           item.Updata(player);
           for (int i = 0; i < SHOT; i++)
           {
              // music.playShot(player.count);
               for (int j = 0; j < ENEMY_NUM; j++)
               {
                   shot[i].Update(player, enemy[j]);
               }
           }

           // �v���C���[�̓����蔻���`
           sHitRect playerRect;
           playerRect = player.getHitRect();

           //�G�l�~�[�̓����蔻��Z�`
           sHitRect enemyRect;
           for (int i = 0; i < ENEMY_NUM; i++)
           {
               enemyRect = enemy[i].getHitRect();
           }

           // �����Ԃ������Ȃ瓖���蔻��{�b�N�X����ʒu���C������
           if (map.HitCalc(playerRect))
           {
               player.fixColPosition(playerRect);
           }

           if (map.HitCalc(enemyRect))
           {
               for (int i = 0; i < ENEMY_NUM; i++)
               {
                   enemy[i].fixColPosition(enemyRect);
               }           
           }

           // �����`�F�b�N
           playerRect = player.GetGroundCollider();
           player.SetGroundFlag(map.HitCalc(playerRect));
           for (int i = 0; i < ENEMY_NUM; i++)
           {
               enemyRect = enemy[i].GetGroundCollider();
               enemy[i].SetGroundFlag(map.HitCalc(enemyRect));
           }

           // ����`�F�b�N
           playerRect = player.GetHeadCollider();
           player.SetHeadHitFlag(map.HitCalc(playerRect));
           for (int i = 0; i < ENEMY_NUM; i++)
           {
               enemyRect = enemy[i].GetHeadCollider();
               enemy[i].SetHeadHitFlag(map.HitCalc(enemyRect));
           }

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
           item.Draw();
           player.Draw();
           for (int i = 0; i < ENEMY_NUM; i++)
           {
               enemy[i].Draw();
           }
           
           for (int i = 0; i < ENEMY_NUM; i++)
           {
               character.display(player, enemy[i], item, 1.0f / 60.0f); //�����A���ԕ\��
           }

         
           
           
           //�Q�[���N���A����
            for (int i = 0; i < ENEMY_NUM; i++)
            {
                if (enemy[i].GetLife() <= 0)
                {
                    GameSituation = CLEAR;
                }
            }
            //�Q�[���I�[�o�[����
            if (player.GetHitPoint() <= 0 || GetNowHiPerformanceCount() - character.IsTimeLimit() > GetNowHiPerformanceCount())
            {
                GameSituation = OVER;
            }
            
            break;

        case CLEAR:                 //�Q�[���N���A����
            ClearDrawScreen();

            image.DrawClear();
            if (CheckHitKey(KEY_INPUT_ESCAPE))
            {
                DxLib_End();
            }
            ScreenFlip();
            break;


        case OVER:                  //�Q�[���I�[�o�[����
            ClearDrawScreen();

            image.DrawOver();
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