#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

bool gameIsStarted = false;
char playerName[6] = "";

int roundNum = 1;
int shells = 2;
int shellSize;
int playerHP = 2;
int dealerHP = 2;

int usingItem;
int shootToWho;

bool isPlayerTurn = true;

int shotgun[] = {};
char* playerItem[9] = {"샷건"};
char* dealerItem[8] = {};

void StartScene();
void EnterPlayerName();
void Reload();

void PlayerTurn();
void DealerTurn();
void DrawPlayerItem();
void DrawDealerItem();
void ShowPlayerItem();
void ShowDealerItem();

void ReadyToFire();
void Fire();
void ShotgunPumping(int shotgun[], int size, int index);

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

        else if(roundNum == 2)
        {
            RoundTwo();
        }

        else if(roundNum == 3)
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
    Reload();

    while(playerHP > 0 || dealerHP > 0)
    {
        if(playerHP > 0 && isPlayerTurn)
        {
            PlayerTurn();
            Fire();
        }

        else if(dealerHP > 0 && !isPlayerTurn)
        {
            DealerTurn();
        }

        if(shotgun[0] == NULL)
        {
            Reload();
        }
    }
}

void RoundTwo()
{

}

void RoundThree()
{

}

void EnterPlayerName()
{
    printf("Dealer: 각서 먼저 쓰고 합시다. \n\n");
    printf("... 계약에 따라 '을'의 모든 신체에 대한 권리를 담보물로서\n 사업자 '갑'에게 양도했음을 확인하고, 분란의 여지를 없애고자\n 이 각서를 작성함.\n");
    printf("갑: Dealer, 을: ");
    scanf("%s", playerName);
    printf("\n\n");
}

void Reload()
{
    int live = 0;
    int blank = 0;

    printf("\n\n재장전!\n\n");

    for(int i = 0; i < shells; i++)
    {
        srand(time(NULL));

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

    printf("공탄: %d발, 실탄: %d발.\n", blank, live);


    //디버그
    DebugFunc();
}

void PlayerTurn()
{
    if(roundNum > 1)
    {
        DrawPlayerItem();
    }

    ShowPlayerItem();

    if(usingItem == 0)
    {
        ReadyToFire();
    }
}

void DealerTurn()
{

}

void DrawPlayerItem()
{

}

void DrawDealerItem()
{

}

void ShowPlayerItem()
{
    for(int i = 0; i < 10; i++)
    {
        if(playerItem[i] == NULL)
        {
            printf("이하 아이템 없음.\n");
            break;
        }

        printf("\n%d: %s\n", i, playerItem[i]);
    }

    printf("사용할 아이템(숫자로 입력)\n");
    scanf("%d", &usingItem);
}

void ShowDealerItem()
{
    for(int i = 0; i < 9; i++)
    {
        if(dealerItem[i] == NULL)
        {
            printf("이하 아이템 없음.\n");
            break;
        }

        printf("%d: %s", i, dealerItem[i]);
    }
}

void ReadyToFire()
{
    printf("스스로에게 쏘려면 0을, 딜러에게 쏘려면 1을 누르시오.\n");
    scanf("%d", &shootToWho);
}

void Fire()
{
    int index = 0;

    shellSize = shells;

    if(shotgun[0] == 0 && shootToWho == 0)
    {
        printf("틱!\n(격발되지 않음)\n");
        ShotgunPumping(shotgun, shellSize, index);
        shellSize--;
    }

    else if(shotgun[0] == 1 && shootToWho == 0)
    {
        printf("탕!\n(격발됨!)\n");

        playerHP--;

        printf("Dealer's Life Points: %d | %s's Life Points: %d\n", dealerHP, playerName, playerHP);

        if(playerHP <= 0)
        {
            Dead();
        }

        isPlayerTurn = false;
    }

    else if(shotgun[0] == 0 && shootToWho == 1)
    {
        printf("틱!\n(격발되지 않음)\n");
        ShotgunPumping(shotgun, shellSize, index);
        shellSize--;
        isPlayerTurn = false;
    }

    else if(shotgun[0] == 1 && shootToWho == 1)
    {
        printf("탕!\n(격발됨!)\n");

        dealerHP--;

        printf("Dealer's Life Points: %d | %s's Life Points: %d\n", dealerHP, playerName, playerHP);

        if (dealerHP <= 0)
        {
            roundNum++;
        }

        isPlayerTurn = false;
    }


    //디버그
    DebugFunc();
}

void Dead()
{

}

void ShotgunPumping(int shotgun[], int size, int index)
{
    for(int i = index; i < size - 1; ++i)
    {
        shotgun[i] = shotgun[i + 1];
        shotgun[i + 1] = NULL;
    }
}

void DebugFunc()
{
    printf("shotgun array: ");
    
    for (int i = 0; i < shells; i++)
    {
        printf("%d ", shotgun[i]);
    }
}