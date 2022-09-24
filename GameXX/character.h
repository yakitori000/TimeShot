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
    
    int nowCount = GetNowCount();
    int TimeCount = nowCount;

    int TimeDiff;
    LONGLONG TimeLimit = GetNowHiPerformanceCount() + 120000000;

    double start, end;
    double total = 0.0f, set = 0.0f;

public:


    void display(Player& player, Enemy& enemy, Item& item, float deltaTime);
    void GameCLEAR();
    void GameOVER();

    bool IsTimeLimitFlag() { return TimeDiff; }
    
};