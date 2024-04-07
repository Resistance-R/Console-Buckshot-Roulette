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

int blankShell;
int liveShell;

int usingItem;
int shootToWho;

bool isPlayerTurn = true;

int shotgun[8] = {};
char* totalItem[5] = {"���", "��", "ĵ ����", "������", "����"};
char* playerItem[9] = {"����"};
char* dealerItem[9] = {"����"};

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
    printf("'s'�� �Է��� �����Ͻʽÿ�.\n");
    scanf("%s", &start);

    while(start != 's')
    {
        printf("'s'�� �Է��� �����Ͻʽÿ�.\n");
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

    printf("Dealer: �Ѿ��� �������� �����ȴٳ�.\n");

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
            printf("\n%d ", roundNum);
            playerHP = 4;
            dealerHP = 4;
            break;
        }
    }

    return;
}

void RoundTwo()
{
    printf("Dealer: �� ��հ� �� ����.\n");
    printf("Dealer: �������� �ִ� 8������. ���� ���� �� 2���� �޴´�.\n");
    printf("Dealer: ���������� �Ѿ��� �������� ��������.\n");

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
            printf("\n%d ", roundNum);
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
    printf("Dealer: ���� ���� ���� ����. \n\n");
    printf("... ��࿡ ���� '��'�� ��� ��ü�� ���� �Ǹ��� �㺸���μ�\n ����� '��'���� �絵������ Ȯ���ϰ�, �ж��� ������ ���ְ���\n �� ������ �ۼ���.\n");
    printf("��: Dealer, ��: ");
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

    printf("\n\n������!\n\n");

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

    printf("��ź: %d��, ��ź: %d��.\n", blank, live);


    //�����
    DebugFunc();
}

void PlayerTurn()
{
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

}

void ShowPlayerItem()
{
    printf("����� ������: \n");

    for(int i = 0; i < 10; i++)
    {
        if(playerItem[i] == NULL)
        {
            printf("���� ������ ����.\n");
            break;
        }

        printf("\n%d: %s\n", i, playerItem[i]);
    }

    printf("����� ������(���ڷ� �Է�)\n");
    scanf("%d", &usingItem);
}

void ShowDealerItem()
{
    printf("���� ������: \n");

    for(int i = 0; i < 9; i++)
    {
        if(dealerItem[i] == NULL)
        {
            printf("\n���� ������ ����.\n");
            break;
        }

        printf("%d: %s", i, dealerItem[i]);
    }
}

void ReadyToFire()
{
    printf("�����ο��� ����� 0��, �������� ����� 1�� �����ÿ�.\n");
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
        printf("\nƽ!\n(�ݹߵ��� ����)\n");
        ShotgunPumping(shotgun, index);

        isPlayerTurn = true;
    }

    else if(shotgun[0] == 1 && dealerOrPlayer == player)
    {
        printf("\n��!\n(�ݹߵ�!)\n");

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
        printf("\nƽ!\n(�ݹߵ��� ����)\n");
        ShotgunPumping(shotgun, index);
        isPlayerTurn = false;
    }

    else if(shotgun[0] == 1 && dealerOrPlayer == dealer)
    {
        printf("\n��!\n(�ݹߵ�!)\n");

        dealerHP--;

        printf("Dealer's Life Points: %d | %s's Life Points: %d\n\n", dealerHP, playerName, playerHP);

        ShotgunPumping(shotgun, index);

        isPlayerTurn = false;
    }


    //�����
    DebugFunc();
}

void DealerFire(int dealerOrPlayer)
{
    int player = 0;
    int dealer = 1;

    int index = 0;

    if(shotgun[0] == 0 && dealerOrPlayer == player)
    {
        printf("\nƽ!\n(�ݹߵ��� ����)\n");

        ShotgunPumping(shotgun, index);

        blankShell--;

        isPlayerTurn = true;
    }

    else if(shotgun[0] == 1 && dealerOrPlayer == player)
    {
        printf("\n��!\n(�ݹߵ�!)\n");

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
        printf("\nƽ!\n(�ݹߵ��� ����)\n");

        ShotgunPumping(shotgun, index);

        blankShell--;

        isPlayerTurn = false;
    }

    else if(shotgun[0] == 1 && dealerOrPlayer == dealer)
    {
        printf("\n��!\n(�ݹߵ�!)\n");

        dealerHP--;

        printf("Dealer's Life Points: %d | %s's Life Points: %d\n\n", dealerHP, playerName, playerHP);

        ShotgunPumping(shotgun, index);

        liveShell--;

        isPlayerTurn = true;
    }


    //�����
    DebugFunc();
}

void Dead()
{
    if(roundNum <= 2)
    {
        sleep(3);

        printf("\n\n\n\n\n???: �������Ⱑ �����Ǿ �����̾�, �ϸ��͸� ���� �� �߾�.\n");

        sleep(1);

        printf("???: ��� ���� �ܻ����� �޾� ����. ���� ���� ���. ����� �س� �� �����ž�.\n\n");

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
            shotgun[i] == 2;
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