#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

bool gameIsStarted = false;
char playerName[6] = "";

int roundNum = 1;
int shells = 2;
int playerHP = 2;
int dealerHP = 2;
int howMamyItems = 3;

int blankShell;
int liveShell;

int usingItem;
int shootToWho;

bool isPlayerTurn = true;

int shotgun[8] = {};
char* totalItem[5] = {"담배", "톱", "캔 맥주", "돋보기", "수갑"};
char* playerItem[9] = {"샷건"};
char* dealerItem[9] = {"샷건"};

void StartScene();
void EnterPlayerName();
void Reload();

void PlayerTurn();
void DealerTurn();
void DrawItem();
void ShowPlayerItem();
void ShowDealerItem();

void ReadyToFire();
void Fire(int dealerOrPlayer);
void DealerFire(int dealerOrPlayer);
void ShotgunPumping(int shotgun[], int index);

void RoundOne();
void RoundTwo();
void RoundThree();
void Dead();

void DebugFunc();

int main(void)
{
    if(!gameIsStarted)
    {
        StartScene();
    }

    if(gameIsStarted)
    {
        if(roundNum == 1)
        {
            RoundOne();
        }

        if(roundNum == 2)
        {
            RoundTwo();
        }

        if(roundNum == 3)
        {
            RoundThree();
        }

        printf("Debug Log");
    }
}

void StartScene()
{
    char start;

    printf("BUCKSHOT ROULETTE\n");
    printf("'s'를 입력해 시작하십시오.\n");
    scanf("%s", &start);

    while(start != 's')
    {
        printf("'s'를 입력해 시작하십시오.\n");
        scanf("%s", &start);
    }

    if(start == 's')
    {
        gameIsStarted = true;
    }
}

void RoundOne()
{
    EnterPlayerName();

    printf("Dealer: 총알은 무작위로 장전된다네.\n");

    Reload();

    while(playerHP > 0 || dealerHP > 0)
    {
        if((playerHP > 0 || dealerHP > 0) && shotgun[0] >= 2)
        {
            Reload();
        }

        if(playerHP > 0 && isPlayerTurn)
        {
            PlayerTurn();
        }

        else if(dealerHP > 0 && !isPlayerTurn)
        {
            DealerTurn();
        }

        if(dealerHP <= 0)
        {
            roundNum++;
            playerHP = 4;
            dealerHP = 4;
            break;
        }
    }

    return;
}

void RoundTwo()
{
    printf("Dealer: 더 재밌게 해 볼까.\n");
    printf("Dealer: 아이템은 최대 8개까지. 각자 장전 당 2개씩 받는다.\n");
    printf("Dealer: 마찬가지로 총알은 무작위로 장전되지.\n");

    Reload();

    while(playerHP > 0 || dealerHP > 0)
    {
        if((playerHP > 0 || dealerHP > 0) && shotgun[0] >= 2)
        {
            Reload();
        }

        if(playerHP > 0 && isPlayerTurn)
        {
            PlayerTurn();
        }

        else if(dealerHP > 0 && !isPlayerTurn)
        {
            DealerTurn();
        }

        if(dealerHP <= 0)
        {
            roundNum++;
            playerHP = 6;
            dealerHP = 6;
            break;
        }
    }

    return;
}

void RoundThree()
{

}

void EnterPlayerName()
{
    printf("Dealer: 각서 먼저 쓰고 하지. \n\n");
    printf("... 계약에 따라 '을'의 모든 신체에 대한 권리를 담보물로서\n 사업자 '갑'에게 양도했음을 확인하고, 분란의 여지를 없애고자\n 이 각서를 작성함.\n");
    printf("갑: Dealer, 을: ");
    scanf("%s", playerName);
    printf("\n\n");
}

void Reload()
{
    int live = 0;
    int blank = 0;

    shells++;

    if(roundNum > 1)
    {
        DrawItem();
    }

    if(shells >= 8)
    {
        shells = 8;
    }

    for(int i = 0; i < 8; i++)
    {
        shotgun[i] = 2;
    }

    printf("\n\n재장전!\n\n");

    srand(time(NULL));

    for(int i = 0; i < shells; i++)
    {

        int BlankOrLive = rand() % 2;

        shotgun[i] = BlankOrLive;

        if(shotgun[i] == 0)
        {
            blank++;
        }

        else if(shotgun[i] == 1)
        {
            live++;
        }
    }

    blankShell = blank;
    liveShell = live;

    printf("공탄: %d발, 실탄: %d발.\n", blank, live);


    //디버그
    DebugFunc();
}

void PlayerTurn()
{
    printf("당신의 차례!\n\n");

    ShowPlayerItem();

    if(usingItem == 0)
    {
        ReadyToFire();
    }
}

void DealerTurn()
{
    int player = 0;
    int dealer = 1;

    ShowDealerItem();

    if(liveShell >= blankShell)
    {
        sleep(2);
        DealerFire(player);
    }

    else if(blankShell > liveShell)
    {
        sleep(2);
        DealerFire(dealer);
    }
}

void DrawItem()
{
    srand(time(NULL));

    int playerGetItem = 1;
    int playerItemIndex = 1;

    int dealerGetItem = 1;
    int dealerItemIndex = 1;
    
    while(playerGetItem < howMamyItems)
    {
        int itemIndex = rand() % 6;

        if (playerGetItem >= howMamyItems)
        {
            playerGetItem = 1;
            break;
        }

        if(playerItem[playerItemIndex] == NULL)
        {
            playerItem[playerItemIndex] = totalItem[itemIndex];
            playerGetItem++;
        }

        playerItemIndex++;

        if(playerItemIndex > 8)
        {
            playerItemIndex = 1;
        }
    }

    while(dealerGetItem < howMamyItems)
    {
        int itemIndex = rand() % 6;

        if (dealerGetItem >= howMamyItems)
        {
            dealerGetItem = 1;
            break;
        }

        if(dealerItem[dealerItemIndex] == NULL)
        {
            dealerItem[dealerItemIndex] = totalItem[itemIndex];
            dealerGetItem++;
        }

        dealerItemIndex++;

        if(dealerItemIndex > 8)
        {
            dealerItemIndex = 1;
        }
    }
}

void ShowPlayerItem()
{
    printf("당신의 아이템: \n");

    for(int i = 0; i < 10; i++)
    {
        if(playerItem[i] == NULL)
        {
            printf("\n이하 아이템 없음.\n");
            break;
        }

        printf("\n%d: %s\n", i, playerItem[i]);
    }

    printf("사용할 아이템(숫자로 입력)\n");
    scanf("%d", &usingItem);
}

void ShowDealerItem()
{
    printf("딜러 아이템: \n");

    for(int i = 0; i < 9; i++)
    {
        if(dealerItem[i] == NULL)
        {
            printf("\n이하 아이템 없음.\n");
            break;
        }

        printf("\n%d: %s\n", i, dealerItem[i]);
    }
}

void ReadyToFire()
{
    printf("스스로에게 쏘려면 0을, 딜러에게 쏘려면 1을 누르시오.\n");
    scanf("%d", &shootToWho);

    Fire(shootToWho);
}

void Fire(int dealerOrPlayer)
{
    int player = 0;
    int dealer = 1;

    int index = 0;

    if(shotgun[0] == 0 && dealerOrPlayer == player)
    {
        printf("\n틱!\n(격발되지 않음)\n");
        ShotgunPumping(shotgun, index);

        isPlayerTurn = true;
    }

    else if(shotgun[0] == 1 && dealerOrPlayer == player)
    {
        printf("\n탕!\n(격발됨!)\n");

        playerHP--;

        printf("Dealer's Life Points: %d | %s's Life Points: %d\n\n", dealerHP, playerName, playerHP);

        ShotgunPumping(shotgun, index);

        if(playerHP <= 0)
        {
            Dead();
        }

        isPlayerTurn = false;
    }

    else if(shotgun[0] == 0 && dealerOrPlayer == dealer)
    {
        printf("\n틱!\n(격발되지 않음)\n");
        ShotgunPumping(shotgun, index);
        isPlayerTurn = false;
    }

    else if(shotgun[0] == 1 && dealerOrPlayer == dealer)
    {
        printf("\n탕!\n(격발됨!)\n");

        dealerHP--;

        printf("Dealer's Life Points: %d | %s's Life Points: %d\n\n", dealerHP, playerName, playerHP);

        ShotgunPumping(shotgun, index);

        isPlayerTurn = false;
    }


    //디버그
    DebugFunc();
}

void DealerFire(int dealerOrPlayer)
{
    int player = 0;
    int dealer = 1;

    int index = 0;

    if(shotgun[0] == 0 && dealerOrPlayer == player)
    {
        printf("\n틱!\n(격발되지 않음)\n");

        ShotgunPumping(shotgun, index);

        blankShell--;

        isPlayerTurn = true;
    }

    else if(shotgun[0] == 1 && dealerOrPlayer == player)
    {
        printf("\n탕!\n(격발됨!)\n");

        playerHP--;

        liveShell--;

        printf("Dealer's Life Points: %d | %s's Life Points: %d\n\n", dealerHP, playerName, playerHP);

        ShotgunPumping(shotgun, index);

        if(playerHP <= 0)
        {
            Dead();
        }

        isPlayerTurn = true;
    }

    else if(shotgun[0] == 0 && dealerOrPlayer == dealer)
    {
        printf("\n틱!\n(격발되지 않음)\n");

        ShotgunPumping(shotgun, index);

        blankShell--;

        isPlayerTurn = false;
    }

    else if(shotgun[0] == 1 && dealerOrPlayer == dealer)
    {
        printf("\n탕!\n(격발됨!)\n");

        dealerHP--;

        printf("Dealer's Life Points: %d | %s's Life Points: %d\n\n", dealerHP, playerName, playerHP);

        ShotgunPumping(shotgun, index);

        liveShell--;

        isPlayerTurn = true;
    }


    //디버그
    DebugFunc();
}

void Dead()
{
    if(roundNum <= 2)
    {
        sleep(3);

        printf("\n\n\n\n\n???: 제세동기가 충전되어서 다행이야, 하마터면 죽을 뻔 했어.\n");

        sleep(1);

        printf("???: 목숨 값은 외상으로 받아 두지. 아직 밤은 길어. 충분히 해낼 수 있을거야.\n\n");

        if(roundNum == 1)
        {
            playerHP = 2;
            dealerHP = 2;
        }

        else if(roundNum == 2)
        {
            playerHP = 4;
            dealerHP = 4;
        }

        Reload();

        return;
    }
}

void ShotgunPumping(int shotgun[], int index)
{
    for(int i = index; i < 8; i++)
    {
        if(i == 7)
        {
            shotgun[i] = 2;
        }

        if(i < 7)
        {
            shotgun[i] = shotgun[i + 1];
        }
    }
}

void DebugFunc()
{
    printf("shotgun array: ");
    
    for (int i = 0; i < 8; i++)
    {
        printf("%d ", shotgun[i]);
    }
}