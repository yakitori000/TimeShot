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
    ///�t�H���g������
    /// </summary>
    void Init();

    /// <summary>
    ///�^�C�g�����\��
    /// </summary>
    void Title();
    
    /// <summary>
    ///�Q�[���������E���ԕ\��
    /// </summary>
    void display(Player& player, Enemy& enemy, Item& item, float deltaTime);
    
    /// <summary>
    ///�Q�[���N���A���\��
    /// </summary>
    void GameCLEAR();
    
    /// <summary>
    ///�Q�[���I�[�o�[���\��
    /// </summary>
    void GameOVER();

    bool IsTimeLimit() { return TimeDiff; }
    
};