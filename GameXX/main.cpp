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

    // DxLib初期化
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

    // 初期化
    image.InitTitle();
    image.InitMenu();
    image.InitClear();
    image.InitOver();
    music.Init();
    player.Init();
    character.Init();
    for (int i = 0; i < ENEMY_NUM; i++)
    {
        enemy[i].Init();
    }
    map.Init();
    item.Init(music);
    for (int i = 0; i < SHOT; i++)
    {
        shot[i].Init();
    }

    GameSituation = TITLE;

    int nowCount, prevCount;
    nowCount = prevCount = GetNowCount();

    // ゲームループ
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

           // deltaTime計測
           float deltaTime;
           nowCount = GetNowCount();
           deltaTime = (nowCount - prevCount) / 1000.0f;
           
           music.playBGM();
            
           //更新処理 1201fps想定
           player.Update(shot, SHOT, item, music, 1.0f / 60.0f);
           for (int i = 0; i < ENEMY_NUM; i++)
           {
               
               enemy[i].Update(player, music, 1.0f / 60.0f);
           }
          
           item.Updata(player, music);
           for (int i = 0; i < SHOT; i++)
           {
              // music.playShot(player.count);
               for (int j = 0; j < ENEMY_NUM; j++)
               {
                   shot[i].Update(player, enemy[j]);
               }
           }

           // プレイヤーの当たり判定矩形
           sHitRect playerRect;
           playerRect = player.getHitRect();

           //エネミーの当たり判定短形
           sHitRect enemyRect;
           for (int i = 0; i < ENEMY_NUM; i++)
           {
               enemyRect = enemy[i].getHitRect();
           }

           // もしぶつかったなら当たり判定ボックスから位置を修正する
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

           // 足元チェック
           playerRect = player.GetGroundCollider();
           player.SetGroundFlag(map.HitCalc(playerRect));
           for (int i = 0; i < ENEMY_NUM; i++)
           {
               enemyRect = enemy[i].GetGroundCollider();
               enemy[i].SetGroundFlag(map.HitCalc(enemyRect));
           }

           // 頭上チェック
           playerRect = player.GetHeadCollider();
           player.SetHeadHitFlag(map.HitCalc(playerRect));
           for (int i = 0; i < ENEMY_NUM; i++)
           {
               enemyRect = enemy[i].GetHeadCollider();
               enemy[i].SetHeadHitFlag(map.HitCalc(enemyRect));
           }

           //スクロール更新処理
           scroll.Update(playerRect, deltaTime);

           // スクロール量取得
           int scrOffsX, scrOffsY;
           scrOffsX = scroll.GetDrawOffsetX();
           scrOffsY = scroll.GetDrawOffsetY();

           //画面更新処理
           ClearDrawScreen();

           // マップ描画
           map.Draw(scrOffsX, scrOffsY);

           //描画
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
           
           //文字、時間表示
           for (int i = 0; i < ENEMY_NUM; i++)
           {
               character.display(player, enemy[i], item, 1.0f / 60.0f); 
           }
           
           //ゲームクリア条件
            for (int i = 0; i < ENEMY_NUM; i++)
            {
                if (enemy[i].GetLife() <= 0)
                {
                    StopSoundMem(music.GameMusic);
                    GameSituation = CLEAR;
                }
            }
            //ゲームオーバー条件
            if (player.GetHitPoint() <= 0 || GetNowHiPerformanceCount() - character.IsTimeLimit() > GetNowHiPerformanceCount())
            {
                StopSoundMem(music.GameMusic);
                GameSituation = OVER;
            }
            
            break;

            //ゲームクリア処理
        case CLEAR:                 
            ClearDrawScreen();

            image.DrawClear();
            character.GameCLEAR();
            if (CheckHitKey(KEY_INPUT_ESCAPE))
            {
                DxLib_End();
            }
            ScreenFlip();
            break;

            //ゲームオーバー処理
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