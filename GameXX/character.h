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
    ///�t�H���g������
    /// </summary>
    void Init();

    /// <summary>
    ///�^�C�g�����\��
    /// </summary>
    void Title();
    
    /// <summary>
    ///�Q�[��������
    /// </summary>
    void display(Player& player, Enemy& enemy, Item& item);
    
    /// <summary>
    ///���ԕ\��
    /// </summary>
    void GameTime(float deltaTime);


    /// <summary>
    ///�Q�[���N���A���\��
    /// </summary>
    void GameCLEAR();
    
    /// <summary>
    ///�Q�[���I�[�o�[���\��
    /// </summary>
    void GameOVER();

    bool IsTimeLimit() { return TimeLimit; }
    
};