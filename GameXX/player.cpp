
#include "player.h"
#include "shot.h"
#include "Item.h"
#include "Music.h"
#include "map.h"


const int animPatternNum         = 3;        // アニメーションのパターン数
const int animTypeNum            = 9;        // アニメーションの種類

int playerImg[animPatternNum * animTypeNum]; // プレイヤーの画像ハンドル

sHitRect playerHit;                          // プレイヤー当たり判定
sHitRect playerFootCollider;                 // 接地コライダー
sHitRect playerHeadCollider;                 // 頭上コライダー

bool prevJumpButton;
bool isJumpPush;

//bool inputMove(float deltaTime);

void Player::Init()
{
    px = 30.0f;
    py = 850.0f;
    vx = 0.0f;
    vy = 0.0f;
    HitPoint = 100;
    animTimer = 0.0f;
    jumpFlag = false;
    count = SHOT;

    animNowType = animRight;     // 右向きアニメーション種類
    animNowPattern = 0;         // 現在のアニメーションパターン

    animNowIndex = 0;

    // 当たり判定初期化
    initRect(playerHit, hitSizeX, hitSizeY);
    initRect(playerFootCollider, hitSizeX - colliderOffset, 1);
    initRect(playerHeadCollider, hitSizeX - colliderOffset, 1);

    // 横3 縦9 計27枚の画像ファイルの読み込み
    graph = LoadDivGraph("data/image/chara7.png", animPatternNum * animTypeNum, animPatternNum, animTypeNum, imageSizeX, imageSizeY, playerImg);

    GetGraphSize(graph, &w, &h);

    // 描画位置のオフセット値を計算
    // 左右から見てセンター、上下方向は底辺基準となるように計算
    drawOffsetX = (hitSizeX - imageSizeX) / 2;
    drawOffsetY = (hitSizeY - imageSizeY);

    onGround = false;
    hitHead = false;
    GetFlag = false;
    jumpTimer = jumpButtonAcceptTime;

    isJumpPush = false;
    prevJumpButton = false;

    ShotIntervalCount = 0;

}

void Player::Update(Shot shot[],int shotnum ,Item &item,Music &music, float deltaTime)
{
    bool isMove = inputMove(deltaTime);

    //接地してる？
    if (onGround)
    {
        jumpFlag = false;
        vy = 0.0f;
        jumpTimer = jumpButtonAcceptTime;
    }
    else
    {
        jumpFlag = true;
    }

    // 頭上に当たった？
    if (hitHead)
    {
        vy = hitHeadBrakeRatio * vy;
    }

    // プレイヤーが画面端からでそうになっていたら画面内の座標に戻す
    if (px > SCREEN_WMAX - w)
    {
        px = SCREEN_WMAX - w;
        
    }
    else if (px < SCREEN_WMIN)
    {
        px = SCREEN_WMIN;
        
    }

    // 弾の発射処理
    if (CheckHitKey(KEY_INPUT_S) == 1)
    {
        
        if (animNowType == animLeft && CheckHitKey(KEY_INPUT_LEFT) == false)
        {
            isMove = true;
            sideFlag = true;
            animNowType = animStopShotLeft;
        }
        if (animNowType == animRight && CheckHitKey(KEY_INPUT_RIGHT) == false)
        {
            isMove = true;
            sideFlag = false;
            animNowType = animStopShotRight;
        }
        // 前フレームでショットボタンを押したかが保存されている変数がfalseだったら弾を発射
        if (!ShotIntervalCount)
        {
            music.playShot(count);      //銃関連サウンド再生
            if (count > 0)
            {
                // 画面上にでていない弾があるか、弾の数だけ繰り返して調べる
                for (int i = 0; i < SHOT; i++)
                {
                    // 弾iが画面上にでていない場合はその弾を画面に出す
                    if (shot[i].IsVisibleFlag() == 0)
                    {
                       
                        shot[i].OnShot(px,py,w,h);
                        count -= 1;
                        // 一つ弾を出したので弾を出すループから抜けます
                        break;
                    }
                }
            }
        }

            // インターバル用のカウンターを設定.
            ShotIntervalCount = SHOT_INTERVAL;
    }
    else
    {
        ShotIntervalCount = 0;
    }

    if (ShotIntervalCount != 0)
    {
        --ShotIntervalCount;
    }

    if (CheckHitKey(KEY_INPUT_D))
    {
        if (GetFlag == true && item.OpenFlag == false)
        {
           count += 20;
           animNowType = animGetDown;
           item.OpenFlag = true;
           music.playBox(item.OpenFlag);
        }  
    }
    if(CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_RIGHT))
    {
        GetFlag = false;
    }

    // 当たり判定位置更新
    updateWorldRect(playerHit, px, py);
    updateWorldRect(playerFootCollider, px + colliderOffset / 2, py + playerHit.h);
    updateWorldRect(playerHeadCollider, px + colliderOffset / 2, py - playerHeadCollider.h);

    ////////////////////////////
    // アニメーション計算
    ////////////////////////////
    if (isMove)
    {
        // animTimer で時間経過を測り、 1.0 / animationFPS →次のアニメーションパターンに進んでよい秒数に
        // なったら次のコマに進める
        animTimer += deltaTime;
        if (animTimer > 1.0f / animationFPS)
        {
            // タイマーを0に 次のパターンに進めるが、animPetternNumを超えないようにループさせる
            animTimer = 0.0f;
            animNowPattern++;
            animNowPattern %= animPatternNum; // 余りなので 0,1,2のいずれかになる
        }
    }
    else
    {
        animNowPattern = 1; // 静止時は足をそろえたパターンに強制する
    }

    // 最終的な添え字を計算 
    // 添え字 = 一つのパターンのコマ数 + アニメーション種類 * １つのアニメーションのパターン枚数
    animNowIndex = animNowPattern + animNowType * animPatternNum;

}

void Player::Draw()
{
    // 描画位置は
    DrawGraph(static_cast<int>(px) + drawOffsetX, 
              static_cast<int>(py) + drawOffsetY, playerImg[animNowIndex], TRUE);
   /* drawRect(playerHit, scrollOffsetX, scrollOffsetY);*/
   /* drawRect(playerFootCollider, scrollOffsetX, scrollOffsetY);
    drawRect(playerHeadCollider, scrollOffsetX, scrollOffsetY);*/
}

void Player::OnHitShot(int shotX, int shotY, int shotW, int shotH, bool visibleFlag)
{
    // エネミーとの当たり判定
    if (((shotX > px && shotX < px) ||
        (px > shotX && px < shotX + shotW)) &&
        ((shotY > py && shotY < py + h) ||
            (py > shotY && py < shotY + shotH)))
    {

        // 接触している場合は当たった弾の存在を消す
        visibleFlag = false;

        // プレイヤーの顔を歪めているかどうかを保持する変数に『歪めている』を表すTRUEを代入
        DamageFlag = true;

        // プレイヤーの顔を歪めている時間を測るカウンタ変数に０を代入
        DamageCounter = 0;

        // ライフ減少
        HitPoint -= 1;
    }
}


void Player::Finalize()
{
    if (playerImg[0] != -1)
    {
        for (int i = 0; i < animPatternNum * animTypeNum; i++)
        {
            DeleteGraph(playerImg[i]);
        }
    }
}

sHitRect Player::getHitRect()
{
    return playerHit;
}

void Player::fixColPosition(sHitRect& hitRect)
{
    px = hitRect.worldLX;
    py = hitRect.worldLY;

    playerHit = hitRect;
}

void Player::OnHitEnemy(float enemyX, float enemyY, int enemyW, int enemyH)
{
    // エネミーとの当たり判定
    if (((px > enemyX && px < enemyX + enemyW) ||
        (enemyX > px && enemyX < px + w)) &&
        ((py > enemyY && py < enemyY + enemyH) ||
            (enemyY > py && enemyY < py + h)))
    {
        // ライフ減少
        HitPoint--;
    }
}

void Player::SetGroundFlag(bool groundFlag)
{
    onGround = groundFlag;
}

void Player::SetHeadHitFlag(bool headHitFlag)
{
    hitHead = headHitFlag;
}

sHitRect Player::GetGroundCollider()
{
    return playerFootCollider;
}

sHitRect Player::GetHeadCollider()
{
    return playerHeadCollider;
}

bool Player::inputMove(float deltaTime)
{
    ///////////////////////////////////////////
    // 入力処理
    ///////////////////////////////////////////

    // ジャンプボタン押した瞬間か？
    if (CheckHitKey(KEY_INPUT_SPACE))
    {
        if (!prevJumpButton)
        {
            isJumpPush = true;
        }
        else
        {
            isJumpPush = false;
        }
        prevJumpButton = true;
    }
    else
    {
        prevJumpButton = false;
    }

    bool isMove = false;
    if (CheckHitKey(KEY_INPUT_LEFT))
    {
        if (!jumpFlag)
        {
            // 方向転換
            if (vx > 0.0f)
            {
                vx *= brakeRatio;
            }
            // 地上加速度
            vx += -moveAccell * deltaTime;
        }
        else
        {
            //空中加速度
            vx += -moveAccell * inAirMoveAccelRatio * deltaTime;
        }

        //速度クリップ
        if (vx < -maxMoveSpeed)
        {
            vx = -maxMoveSpeed;
        }
        animNowType = animLeft;
        isMove = true;

        //プレイヤーが画面外に出そうなら
        if (px > SCREEN_WMAX - w)
        {
            px = SCREEN_WMAX - w;
        }
        else if (px < SCREEN_WMIN)
        {
            px = SCREEN_WMIN;
        }

        //射撃中
        if (CheckHitKey(KEY_INPUT_S))
        {
            animNowType = animShotLeft;
            sideFlag = true;
        }
        
    }
    if (CheckHitKey(KEY_INPUT_RIGHT))
    {
        if (!jumpFlag)
        {
            // 方向転換
            if (vx < 0.0f)
            {
                vx *= brakeRatio;
            }
            // 地上加速度
            vx += +moveAccell * deltaTime;
        }
        else
        {
            // 空中加速度
            vx += +moveAccell * inAirMoveAccelRatio * deltaTime;
        }

        // 速度クリップ
        if (vx > maxMoveSpeed)
        {
            vx = +maxMoveSpeed;
        }
        animNowType = animRight;       
        isMove = true;

        //射撃中
        if (CheckHitKey(KEY_INPUT_S))
        {
            animNowType = animShotRight;
            sideFlag = false;
        }
    }

    //ジャンプ可能でジャンプキーが押された
    if (isJumpPush && !jumpFlag && jumpTimer > 0.0f)
    {
        vy -= jumpInitalVelocity;
        jumpFlag = true;
        onGround = false;
    }

    // ジャンプ長押し中で上昇タイマー期間なら上昇
    if (prevJumpButton && jumpTimer > 0.0f)
    {
        vy -= jumpUpSpeed * deltaTime;
    }

    // ジャンプ中なら重力を発生
    if (jumpFlag)
    {
        jumpTimer -= deltaTime;
        vy += gravity * deltaTime;
    }

    // キー入力ないとき地上での減速
    if (!isMove && !jumpFlag)
    {
        vx *= frictionRatio;
    }
    // 落下速度抑制
    if (vy * deltaTime > maxFallSpeed)
    {
        vy = maxFallSpeed;
    }
    // 位置更新
    px += vx;
    py += vy;

    return isMove;
}