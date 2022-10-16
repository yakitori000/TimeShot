
#include "player.h"
#include "shot.h"
#include "Item.h"
#include "Music.h"
#include "map.h"


const int animPatternNum         = 3;        // �A�j���[�V�����̃p�^�[����
const int animTypeNum            = 9;        // �A�j���[�V�����̎��

int playerImg[animPatternNum * animTypeNum]; // �v���C���[�̉摜�n���h��

sHitRect playerHit;                          // �v���C���[�����蔻��
sHitRect playerFootCollider;                 // �ڒn�R���C�_�[
sHitRect playerHeadCollider;                 // ����R���C�_�[

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

    animNowType = animRight;     // �E�����A�j���[�V�������
    animNowPattern = 0;         // ���݂̃A�j���[�V�����p�^�[��

    animNowIndex = 0;

    // �����蔻�菉����
    initRect(playerHit, hitSizeX, hitSizeY);
    initRect(playerFootCollider, hitSizeX - colliderOffset, 1);
    initRect(playerHeadCollider, hitSizeX - colliderOffset, 1);

    // ��3 �c9 �v27���̉摜�t�@�C���̓ǂݍ���
    graph = LoadDivGraph("data/image/chara7.png", animPatternNum * animTypeNum, animPatternNum, animTypeNum, imageSizeX, imageSizeY, playerImg);

    GetGraphSize(graph, &w, &h);

    // �`��ʒu�̃I�t�Z�b�g�l���v�Z
    // ���E���猩�ăZ���^�[�A�㉺�����͒�ӊ�ƂȂ�悤�Ɍv�Z
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

    //�ڒn���Ă�H
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

    // ����ɓ��������H
    if (hitHead)
    {
        vy = hitHeadBrakeRatio * vy;
    }

    // �v���C���[����ʒ[����ł����ɂȂ��Ă������ʓ��̍��W�ɖ߂�
    if (px > SCREEN_WMAX - w)
    {
        px = SCREEN_WMAX - w;
        
    }
    else if (px < SCREEN_WMIN)
    {
        px = SCREEN_WMIN;
        
    }

    // �e�̔��ˏ���
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
        // �O�t���[���ŃV���b�g�{�^���������������ۑ�����Ă���ϐ���false��������e�𔭎�
        if (!ShotIntervalCount)
        {
            music.playShot(count);      //�e�֘A�T�E���h�Đ�
            if (count > 0)
            {
                // ��ʏ�ɂłĂ��Ȃ��e�����邩�A�e�̐������J��Ԃ��Ē��ׂ�
                for (int i = 0; i < SHOT; i++)
                {
                    // �ei����ʏ�ɂłĂ��Ȃ��ꍇ�͂��̒e����ʂɏo��
                    if (shot[i].IsVisibleFlag() == 0)
                    {
                       
                        shot[i].OnShot(px,py,w,h);
                        count -= 1;
                        // ��e���o�����̂Œe���o�����[�v���甲���܂�
                        break;
                    }
                }
            }
        }

            // �C���^�[�o���p�̃J�E���^�[��ݒ�.
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

    // �����蔻��ʒu�X�V
    updateWorldRect(playerHit, px, py);
    updateWorldRect(playerFootCollider, px + colliderOffset / 2, py + playerHit.h);
    updateWorldRect(playerHeadCollider, px + colliderOffset / 2, py - playerHeadCollider.h);

    ////////////////////////////
    // �A�j���[�V�����v�Z
    ////////////////////////////
    if (isMove)
    {
        // animTimer �Ŏ��Ԍo�߂𑪂�A 1.0 / animationFPS �����̃A�j���[�V�����p�^�[���ɐi��ł悢�b����
        // �Ȃ����玟�̃R�}�ɐi�߂�
        animTimer += deltaTime;
        if (animTimer > 1.0f / animationFPS)
        {
            // �^�C�}�[��0�� ���̃p�^�[���ɐi�߂邪�AanimPetternNum�𒴂��Ȃ��悤�Ƀ��[�v������
            animTimer = 0.0f;
            animNowPattern++;
            animNowPattern %= animPatternNum; // �]��Ȃ̂� 0,1,2�̂����ꂩ�ɂȂ�
        }
    }
    else
    {
        animNowPattern = 1; // �Î~���͑������낦���p�^�[���ɋ�������
    }

    // �ŏI�I�ȓY�������v�Z 
    // �Y���� = ��̃p�^�[���̃R�}�� + �A�j���[�V������� * �P�̃A�j���[�V�����̃p�^�[������
    animNowIndex = animNowPattern + animNowType * animPatternNum;

}

void Player::Draw()
{
    // �`��ʒu��
    DrawGraph(static_cast<int>(px) + drawOffsetX, 
              static_cast<int>(py) + drawOffsetY, playerImg[animNowIndex], TRUE);
   /* drawRect(playerHit, scrollOffsetX, scrollOffsetY);*/
   /* drawRect(playerFootCollider, scrollOffsetX, scrollOffsetY);
    drawRect(playerHeadCollider, scrollOffsetX, scrollOffsetY);*/
}

void Player::OnHitShot(int shotX, int shotY, int shotW, int shotH, bool visibleFlag)
{
    // �G�l�~�[�Ƃ̓����蔻��
    if (((shotX > px && shotX < px) ||
        (px > shotX && px < shotX + shotW)) &&
        ((shotY > py && shotY < py + h) ||
            (py > shotY && py < shotY + shotH)))
    {

        // �ڐG���Ă���ꍇ�͓��������e�̑��݂�����
        visibleFlag = false;

        // �v���C���[�̊��c�߂Ă��邩�ǂ�����ێ�����ϐ��Ɂw�c�߂Ă���x��\��TRUE����
        DamageFlag = true;

        // �v���C���[�̊��c�߂Ă��鎞�Ԃ𑪂�J�E���^�ϐ��ɂO����
        DamageCounter = 0;

        // ���C�t����
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
    // �G�l�~�[�Ƃ̓����蔻��
    if (((px > enemyX && px < enemyX + enemyW) ||
        (enemyX > px && enemyX < px + w)) &&
        ((py > enemyY && py < enemyY + enemyH) ||
            (enemyY > py && enemyY < py + h)))
    {
        // ���C�t����
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
    // ���͏���
    ///////////////////////////////////////////

    // �W�����v�{�^���������u�Ԃ��H
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
            // �����]��
            if (vx > 0.0f)
            {
                vx *= brakeRatio;
            }
            // �n������x
            vx += -moveAccell * deltaTime;
        }
        else
        {
            //�󒆉����x
            vx += -moveAccell * inAirMoveAccelRatio * deltaTime;
        }

        //���x�N���b�v
        if (vx < -maxMoveSpeed)
        {
            vx = -maxMoveSpeed;
        }
        animNowType = animLeft;
        isMove = true;

        //�v���C���[����ʊO�ɏo�����Ȃ�
        if (px > SCREEN_WMAX - w)
        {
            px = SCREEN_WMAX - w;
        }
        else if (px < SCREEN_WMIN)
        {
            px = SCREEN_WMIN;
        }

        //�ˌ���
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
            // �����]��
            if (vx < 0.0f)
            {
                vx *= brakeRatio;
            }
            // �n������x
            vx += +moveAccell * deltaTime;
        }
        else
        {
            // �󒆉����x
            vx += +moveAccell * inAirMoveAccelRatio * deltaTime;
        }

        // ���x�N���b�v
        if (vx > maxMoveSpeed)
        {
            vx = +maxMoveSpeed;
        }
        animNowType = animRight;       
        isMove = true;

        //�ˌ���
        if (CheckHitKey(KEY_INPUT_S))
        {
            animNowType = animShotRight;
            sideFlag = false;
        }
    }

    //�W�����v�\�ŃW�����v�L�[�������ꂽ
    if (isJumpPush && !jumpFlag && jumpTimer > 0.0f)
    {
        vy -= jumpInitalVelocity;
        jumpFlag = true;
        onGround = false;
    }

    // �W�����v���������ŏ㏸�^�C�}�[���ԂȂ�㏸
    if (prevJumpButton && jumpTimer > 0.0f)
    {
        vy -= jumpUpSpeed * deltaTime;
    }

    // �W�����v���Ȃ�d�͂𔭐�
    if (jumpFlag)
    {
        jumpTimer -= deltaTime;
        vy += gravity * deltaTime;
    }

    // �L�[���͂Ȃ��Ƃ��n��ł̌���
    if (!isMove && !jumpFlag)
    {
        vx *= frictionRatio;
    }
    // �������x�}��
    if (vy * deltaTime > maxFallSpeed)
    {
        vy = maxFallSpeed;
    }
    // �ʒu�X�V
    px += vx;
    py += vy;

    return isMove;
}