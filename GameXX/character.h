#pragma once
#include <windows.h>
#include "DxLib.h"
#include "Player.h"
#include <time.h>
#include "Item.h"
#pragma warning(disable:4996)

class Character
{
private:
  
    char buf[64];
    int NowCount;
    int FontHandle;
    int FontHandle2;
    
    int nowCount = GetNowCount();
    int TimeCount = nowCount;

    int TimeDiff;
    LONGLONG TimeLimit = GetNowHiPerformanceCount() + 120000000;

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
    ///ゲーム内文字・時間表示
    /// </summary>
    void display(Player& player, Enemy& enemy, Item& item, float deltaTime);
    
    /// <summary>
    ///ゲームクリア時表示
    /// </summary>
    void GameCLEAR();
    
    /// <summary>
    ///ゲームオーバー時表示
    /// </summary>
    void GameOVER();

    bool IsTimeLimit() { return TimeDiff; }
    
};