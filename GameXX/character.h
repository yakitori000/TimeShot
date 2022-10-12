#pragma once
#include <windows.h>
#include "DxLib.h"
#include <time.h>

#pragma warning(disable:4996)

class Player;
class Enemy;
class Item;

class Character
{
private:
  
    char buf[64];
    char shot[255];
    int NowCount;
    int FontHandle;
    int FontHandle2;
    
    int nowCount = GetNowCount();
    int TimeCount = nowCount;

    int TimeDiff;
    LONGLONG TimeLimit = GetNowHiPerformanceCount() + 120000000.0f;

    double start, end;
    double total = 0.0f, set = 0.0f;

public:

    /// <summary>
    ///フォント初期化
    /// </summary>
    void Init();

    /// <summary>
    ///タイトル時表示
    /// </summary>
    void Title();
    
    /// <summary>
    ///ゲーム内文字
    /// </summary>
    void display(Player& player, Enemy& enemy, Item& item);
    
    /// <summary>
    ///時間表示
    /// </summary>
    void GameTime(float deltaTime);


    /// <summary>
    ///ゲームクリア時表示
    /// </summary>
    void GameCLEAR();
    
    /// <summary>
    ///ゲームオーバー時表示
    /// </summary>
    void GameOVER();

    bool IsTimeLimit() { return TimeLimit; }
    
};