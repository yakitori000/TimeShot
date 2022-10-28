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
    // DxLib初期化
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

    // 初期化
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
           TimeDiff = int(TimeLimit - GetNowHiPerformanceCount());

           
           music.playBGM();

           if (TimeDiff <= 31000000)
           {
               StopSoundMem(music.GameMusic);
               music.playBGM2();
           }
            
           //更新処理 120fps想定
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

           // プレイヤーの当たり判定矩形
           sHitRect playerRect;
           playerRect = player.getHitRect();

           //エネミーの当たり判定短形
           sHitRect enemyRect1;
           sHitRect enemyRect2;
           sHitRect enemyRect3;

           enemyRect1 = enemy.getHitRect1();
           enemyRect2 = enemy.getHitRect2();
           enemyRect3 = enemy.getHitRect3();

           // もしぶつかったなら当たり判定ボックスから位置を修正する
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
          
           // 足元チェック
           playerRect = player.GetGroundCollider();
           player.SetGroundFlag(map.HitCalc(playerRect));
           
           enemyRect1 = enemy.GetGroundCollider1();
           enemy.SetGroundFlag1(map.HitCalc(enemyRect1));

           enemyRect2 = enemy.GetGroundCollider2();
           enemy.SetGroundFlag2(map.HitCalc(enemyRect2));

           enemyRect3 = enemy.GetGroundCollider3();
           enemy.SetGroundFlag3(map.HitCalc(enemyRect3));
           

           // 頭上チェック
           playerRect = player.GetHeadCollider();
           player.SetHeadHitFlag(map.HitCalc(playerRect));
           
           enemyRect1 = enemy.GetHeadCollider1();
           enemy.SetHeadHitFlag1(map.HitCalc(enemyRect1));

           enemyRect2 = enemy.GetHeadCollider2();
           enemy.SetHeadHitFlag2(map.HitCalc(enemyRect2));

           enemyRect3 = enemy.GetHeadCollider3();
           enemy.SetHeadHitFlag3(map.HitCalc(enemyRect3));

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

           for (int j = 0; j < ESHOT; j++)
           {
               Eshot[j].DrawShotEnemy(enemy);
           }
           item.Draw();
           player.Draw();
           enemy.Draw1();
           enemy.Draw2();
           enemy.Draw3();
           
           //文字、時間表示
           
               character.display(player, enemy, item); 
               character.GameTime(1.0f / 60.0f);
           
             //ゲームクリア条件
            if (enemy.life1 <= 0 && enemy.life2 <= 0 && enemy.life3 <= 0)
            {
                StopSoundMem(music.GameMusic);
                StopSoundMem(music.GameImpatientMusic);
                GameSituation = CLEAR;
            }
            
            //ゲームオーバー条件
            if (player.GetHitPoint() <= 0 || TimeDiff <= 02000000)
            {
                StopSoundMem(music.GameMusic);
                StopSoundMem(music.GameImpatientMusic);
                GameSituation = OVER;
            }
            
            break;

            //ゲームクリア処理
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