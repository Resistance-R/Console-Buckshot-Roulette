#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

bool gameIsStarted = false;
bool alreadyDead = false;
char playerName[6] = "";

int roundNum = 1;
int shells = 2;
int playerHP = 2;
int dealerHP = 2;
int howManyItems = 2;

int shotgunDmg = 1;
bool isCut = false;
bool isHandscuffsOfPlayer = false;
bool isHandscuffsOfDealer = false;

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
void BUCKSHOT_ROULETTE();
void EnterPlayerName();
void Reload();

void PlayerTurn();
void DealerTurn();
void DrawItem();
void ShowPlayerItem();
void ShowDealerItem();

void ResetItem();

void ReadyToFire();
void Fire(int dealerOrPlayer);
void DealerFire(int dealerOrPlayer);
void ShotgunPumping(int shotgun[], int index);
void Bang();

bool IsPlayerFull();
bool IsDealerFull();
void UseItem();
void DealerUseItem();
void CheckHandcuffs();
void RepairShotgun();

void RoundOne();
void RoundTwo();
void RoundThree();
void Dead();
void YouWin();

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

    }
        return 0;
}

void StartScene()
{
    char start;

    BUCKSHOT_ROULETTE();
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

void BUCKSHOT_ROULETTE()
{
    printf("'########::'##::::'##::'######::'##:::'##::'######::'##::::'##::'#######::'########:\n");
    printf(" ##.... ##: ##:::: ##:'##... ##: ##::'##::'##... ##: ##:::: ##:'##.... ##:... ##..::\n");
    printf(" ##:::: ##: ##:::: ##: ##:::..:: ##:'##::: ##:::..:: ##:::: ##: ##:::: ##:::: ##::::\n");
    printf(" ########:: ##:::: ##: ##::::::: #####::::. ######:: #########: ##:::: ##:::: ##::::\n");
    printf(" ##.... ##: ##:::: ##: ##::::::: ##. ##::::..... ##: ##.... ##: ##:::: ##:::: ##::::\n");
    printf(" ##:::: ##: ##:::: ##: ##::: ##: ##:. ##::'##::: ##: ##:::: ##: ##:::: ##:::: ##::::\n");
    printf(" ########::. #######::. ######:: ##::. ##:. ######:: ##:::: ##:. #######::::: ##::::\n");
    printf("........::::.......::::......:::..::::..:::......:::..:::::..:::.......::::::..:::::\n");
    printf("'########:::'#######::'##::::'##:'##:::::::'########:'########:'########:'########::\n");
    printf(" ##.... ##:'##.... ##: ##:::: ##: ##::::::: ##.....::... ##..::... ##..:: ##.....:::\n");
    printf(" ##:::: ##: ##:::: ##: ##:::: ##: ##::::::: ##:::::::::: ##::::::: ##:::: ##::::::::\n");
    printf(" ########:: ##:::: ##: ##:::: ##: ##::::::: ######:::::: ##::::::: ##:::: ######::::\n");
    printf(" ##.. ##::: ##:::: ##: ##:::: ##: ##::::::: ##...::::::: ##::::::: ##:::: ##...:::::\n");
    printf(" ##::. ##:: ##:::: ##: ##:::: ##: ##::::::: ##:::::::::: ##::::::: ##:::: ##::::::::\n");
    printf(" ##:::. ##:. #######::. #######:: ########: ########:::: ##::::::: ##:::: ########::\n");
    printf("..:::::..:::.......::::.......:::........::........:::::..::::::::..:::::........:::\n");
}

void RoundOne()
{
    EnterPlayerName();
    sleep(2);

    printf("\nRound 1.\n");
    sleep(2);

    printf("Dealer: �Ѿ��� �������� ��������.\n");
    sleep(1);

    Reload();

    while(playerHP > 0 || dealerHP > 0)
    {
        if(playerHP <= 0)
        {
            break;
        }

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
    printf("\nRound 2.\n");
    sleep(2);

    printf("Dealer: �� ��հ� �� ����.\n");
    sleep(1);
    printf("Dealer: �������� �ִ� 8������. ���� ���� �� 2���� �޴´�.\n");
    sleep(1);
    printf("Dealer: ���������� �Ѿ��� �������� ��������.\n");
    sleep(2);

    Reload();

    alreadyDead = false;

    while(playerHP > 0 || dealerHP > 0)
    {
        if(playerHP <= 0)
        {
            break;
        }

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
    howManyItems = 4;

    ResetItem();

    printf("\nFinal Round.\n");
    sleep(2);

    printf("Dealer: ����, �ºθ� ���� ���α�.\n");
    sleep(1);
    printf("Dealer: �缼���⵵, ������. �� � ���� ����.\n");
    sleep(1);
    printf("Dealer: ���� �ʿ� ��. ��� ��� ������ �۵� ������ ���� �߰� �Ǵ°ž�.\n");
    sleep(2);
    printf("Dealer: ���� �˰� �ְ���.\n");
    sleep(2);

    Reload();

    while (playerHP > 0 || dealerHP > 0)
    {
        if(playerHP <= 0)
        {
            break;
        }

        if(dealerHP <= 0)
        {
            YouWin();
            break;
        }

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
    }
}

void EnterPlayerName()
{
    printf("Dealer: ���� ���� ���� ����. \n\n");
    sleep(1);
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
}

void PlayerTurn()
{
    printf("����� ����!\n\n");

    ShowPlayerItem();

    printf("����� ������(���ڷ� �Է�)\n");
    scanf("%d", &usingItem);

    if(usingItem == 0)
    {
        ReadyToFire();
    }

    if(usingItem != 0)
    {
        if(roundNum <= 1)
        {
            printf("\n�������� ����.\n");
        }

        else
        {
            UseItem();
        }
    }
}

void DealerTurn()
{
    int player = 0;
    int dealer = 1;

    printf("������ ����!\n\n");

    ShowDealerItem();

    if(roundNum > 1)
    {
        DealerUseItem();
    }

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

bool IsPlayerFull()
{
    for(int i = 0; i < 10; i++)
    {
        if(playerItem[i] == NULL)
        {
            return false;
        }
    }

    return true;
}

bool IsDealerFull()
{
    for (int i = 0; i < 10; i++)
    {
        if(dealerItem[i] == NULL)
        {
            return false;
        }
    }

    return true;
}

void DrawItem()
{
    srand(time(NULL));

    int numOfMaxItem = 9;

    int playerGetItem = 1;
    int playerItemIndex = 1;

    int dealerGetItem = 1;
    int dealerItemIndex = 1;
    
    while(playerGetItem <= howManyItems && !IsPlayerFull())
    {
        int itemIndex = rand() % 5;

        if(IsPlayerFull())
        {
            printf("Dealer: ������ ����. �������� �� �� ����.\n");
            break;
        }

        if(playerGetItem > howManyItems)
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

    while(dealerGetItem <= howManyItems && !IsDealerFull())
    {
        int itemIndex = rand() % 5;

        if(IsDealerFull())
        {
            printf("Dealer: ������ ����.\n");
            break;
        }

        if(dealerGetItem > howManyItems)
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

void ResetItem()
{
    for(int i = 1; i < 10; i++)
    {
        playerItem[i] = NULL;
        dealerItem[i] = NULL;
    }
}

void ShowPlayerItem()
{
    printf("����� ������: \n");

    for(int i = 0; i < 9; i++)
    {
        if(playerItem[i] == NULL)
        {
            printf("\n%d: (����)\n", i);
        }

        else if(playerItem[i] != NULL)
        {
            printf("\n%d: %s\n", i, playerItem[i]);
        }
        
    }
}

void ShowDealerItem()
{
    printf("���� ������: \n");

    for(int i = 0; i < 9; i++)
    {
        if(dealerItem[i] == NULL)
        {
            printf("\n%d: (����)\n", i);
        }

        else if(dealerItem[i] != NULL)
        {
            printf("\n%d: %s\n", i, dealerItem[i]);
        }
    }
}

void UseItem()
{
    int index = 0;

    if(strcmp(playerItem[usingItem], "������") == 0)
    {
        if(shotgun[0] == 0)
        {
            printf("\n��ź�� �����Ǿ� �ִ�.\n");
        }

        if(shotgun[0] == 1)
        {
            printf("\n��ź�� �����Ǿ� �ִ�.\n");
        }
    }

    if(strcmp(playerItem[usingItem], "ĵ ����") == 0)
    {
        if(shotgun[0] == 0)
        {
            printf("\n��ź�� Ƣ��Դ�.\n");
        }

        if(shotgun[0] == 1)
        {
            printf("\n��ź�� Ƣ��Դ�.\n");
        }

        ShotgunPumping(shotgun, index);
    }

    if(strcmp(playerItem[usingItem], "��") == 0)
    {
        printf("\n�ѿ��� ������ �߶���.\n");
        isCut = true;
    }

    if(strcmp(playerItem[usingItem], "���") == 0)
    {
        printf("��踦 ����ߴ�.\n");
        playerHP++;

        if(roundNum == 2 && playerHP > 4)
        {
            printf("������ �̹� �ִ� ü���̴�.\n");
            playerHP--;
        }

        if(roundNum == 3)
        {
            if(playerHP > 6)
            {
                printf("������ �̹� �ִ� ü���̴�.\n");
                playerHP--;
            }

            if(playerHP <= 2)
            {
                printf("Dealer: �ؾ���? �� �̻��� ������ ���ٰ�.\n");
                playerHP--;
            }
        }

        printf("\nDealer's Life Points: %d | %s's Life Points: %d\n\n", dealerHP, playerName, playerHP);
    }

    if(strcmp(playerItem[usingItem], "����") == 0)
    {
        printf("\n������ ����Ͽ���.\n");
        isHandscuffsOfPlayer = true;
    }

    if(playerItem[usingItem] == NULL)
    {
        printf("\n�������� ����.\n");
    }

    playerItem[usingItem] = NULL;

    return;
}

void DealerUseItem()
{
    int player = 0;
    int dealer = 1;

    int index = 0;

    for(int i = 1; i < 9; i++)
    {
        if(dealerItem[i] == NULL)
        {
            continue;
        }

        if(strcmp(dealerItem[i], "������") == 0)
        {
            printf("\n������ �����⸦ ����ߴ�.\n");
            printf("Dealer: �� ��̷ӱ�...\n");

            sleep(2);

            if(shotgun[0] == 0)
            {
                DealerFire(dealer);
            }

            if(shotgun[0] == 1)
            {
                DealerFire(player);
            }
        }

        if(strcmp(dealerItem[i], "ĵ ����") == 0)
        {
            printf("\n������ ĵ ���ָ� ����ߴ�.\n");

            sleep(2);

            if(shotgun[0] == 0)
            {
                printf("\n��ź�� Ƣ��Դ�.\n");
                blankShell--;
            }

            if(shotgun[0] == 1)
            {
                printf("\n��ź�� Ƣ��Դ�.\n");
                liveShell--;
            }

            ShotgunPumping(shotgun, index);
        }

        if(!isCut && strcmp(dealerItem[i], "��") == 0)
        {
            printf("\n������ �ѿ��� ������ �߶���.\n");

            isCut = true;

            sleep(2);
        }

        if(dealerHP <= 3 && strcmp(dealerItem[i], "���") == 0)
        {
            printf("\n������ ��踦 ����ߴ�.\n");

            if(roundNum >= 3)
            {
                if(dealerHP > 6)
                {
                    dealerHP--;
                }

                if(dealerHP <= 2)
                {
                    dealerHP--;
                }
            }

            dealerHP++;

            if(roundNum == 2 && dealerHP > 4)
            {
                dealerHP--;
            }

            sleep(2);

            printf("\nDealer's Life Points: %d | %s's Life Points: %d\n\n", dealerHP, playerName, playerHP);
        }

        if (!isHandscuffsOfDealer && strcmp(dealerItem[i], "����") == 0)
        {
            printf("\n������ ������ ����Ͽ���.\n");

            isHandscuffsOfDealer = true;

            sleep(2);
        }

        dealerItem[i] = NULL;
    }

    return;
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

    if(isCut)
    {
        shotgunDmg = 2;
    }

    if(!isCut)
    {
        shotgunDmg = 1;
    }

    if(shotgun[0] == 0 && dealerOrPlayer == player)
    {
        printf("\nƽ!\n(�ݹߵ��� ����)\n");
        ShotgunPumping(shotgun, index);

        isPlayerTurn = true;
    }

    else if(shotgun[0] == 1 && dealerOrPlayer == player)
    {
        Bang();

        playerHP -= shotgunDmg;

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
        Bang();

        dealerHP -= shotgunDmg;

        printf("Dealer's Life Points: %d | %s's Life Points: %d\n\n", dealerHP, playerName, playerHP);

        ShotgunPumping(shotgun, index);

        isPlayerTurn = false;
    }

    RepairShotgun();
    CheckHandcuffs();
}

void DealerFire(int dealerOrPlayer)
{
    int player = 0;
    int dealer = 1;

    int index = 0;

    if(isCut)
    {
        shotgunDmg = 2;
    }

    if(!isCut)
    {
        shotgunDmg = 1;
    }

    if(shotgun[0] == 0 && dealerOrPlayer == player)
    {
        printf("������ ���� ���ؼ� ����.\n");

        sleep(1);

        printf("\nƽ!\n(�ݹߵ��� ����)\n");

        ShotgunPumping(shotgun, index);

        blankShell--;

        isPlayerTurn = true;
        isCut = false;
    }

    else if(shotgun[0] == 1 && dealerOrPlayer == player)
    {
        printf("������ ���� ���ؼ� ����.\n");

        sleep(1);

        Bang();

        sleep(1);

        playerHP -= shotgunDmg;

        liveShell--;

        printf("Dealer's Life Points: %d | %s's Life Points: %d\n\n", dealerHP, playerName, playerHP);

        ShotgunPumping(shotgun, index);

        if(playerHP <= 0)
        {
            Dead();
        }

        isPlayerTurn = true;
        isCut = false;
    }

    else if(shotgun[0] == 0 && dealerOrPlayer == dealer)
    {
        printf("������ �����θ� ���ؼ� ����.\n");

        sleep(1);

        printf("\nƽ!\n(�ݹߵ��� ����)\n");

        ShotgunPumping(shotgun, index);

        blankShell--;

        isPlayerTurn = false;
        isCut = false;
    }

    else if(shotgun[0] == 1 && dealerOrPlayer == dealer)
    {
        printf("������ �����θ� ���ؼ� ����.\n");

        sleep(1);

        Bang();

        sleep(1);

        dealerHP -= shotgunDmg;

        printf("Dealer's Life Points: %d | %s's Life Points: %d\n\n", dealerHP, playerName, playerHP);

        ShotgunPumping(shotgun, index);

        liveShell--;

        isPlayerTurn = true;
        isCut = false;
    }

    RepairShotgun();
    CheckHandcuffs();
}

void Bang()
{
  printf("88                                              \n");
  printf("88                                              \n");
  printf("88                                              \n");
  printf("88,dPPYba,  ,adPPYYba, 8b,dPPYba,   ,adPPYb,d8  \n");
  printf("88P'    `8a \"\"     `Y8 88P'   `\"8a a8\"    `Y88  \n");
  printf("88       d8 ,adPPPPP88 88       88 8b       88  \n");
  printf("88b,   ,a8\" 88,    ,88 88       88 \"8a,   ,d88  \n");
  printf("8Y\"Ybbd8\"'  `\"8bbdP\"Y8 88       88  `\"YbbdP\"Y8  \n");
  printf("                                    aa,    ,88  \n");
  printf("                                     \"Y8bbdP\"  \n");

  return;
}

void CheckHandcuffs()
{
    if(!isPlayerTurn && isHandscuffsOfPlayer)
    {
        isHandscuffsOfPlayer = false;
        isPlayerTurn = true;
    }

    if(isPlayerTurn && isHandscuffsOfPlayer)
    {
        isHandscuffsOfPlayer = true;
        isPlayerTurn = true;
    }

    if(!isPlayerTurn && isHandscuffsOfDealer)
    {
        isHandscuffsOfDealer = true;
        isPlayerTurn = false;
    }

    if(isPlayerTurn && isHandscuffsOfDealer)
    {
        isHandscuffsOfDealer = false;
        isPlayerTurn = false;
    }
}

void RepairShotgun()
{
    isCut = false;

    if(isCut)
    {
        printf("\n������ �����Ǿ���.\n");
    }
}

void Dead()
{
    if(roundNum <= 2 && !alreadyDead)
    {
        sleep(3);

        printf("\n\n\n\n\n???: �������Ⱑ �����Ǿ �����̾�, �ϸ��͸� ���� �� �߾�.\n");

        sleep(1);

        printf("???: ��� ���� �ܻ����� �޾� ����. ���� ���� ���. ����� �س� �� �����ž�.\n\n");

        sleep(2);

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

        alreadyDead = true;

        return;
    }

    if(alreadyDead || roundNum >= 3)
    {
        printf("                       ______\n");
        printf("                    .-\"      \"-.\n");
        printf("                   /            \\\n");
        printf("       _          |              |          _\n");
        printf("      ( \\         |,  .-.  .-.  ,|         / )\n");
        printf("       > \"=._     | )(__/  \\__)( |     _.=\" <\n");
        printf("      (_/\"=._\"=._ | /   /  \\   \\ | _.=\"_.=\"\\_)\n");
        printf("             \"=._ (_     ^^     _)\"_.=\"\n");
        printf("                 \"=\\__|IIIIII|__/=\"\n");
        printf("                _.=\"| \\IIIIII/ |\"=._\n");
        printf("      _     _.=\"_.=\"\\          /\"=._\"=._     _\n");
        printf("     ( \\_.=\"_.=\"     `--------`     \"=._\"=._/ )\n");
        printf("      > _.=\"                            \"=._ <\n");
        printf("      (_/                                   \\_)\n");
        printf("YOU ARE DEAD.\n");

        return;

        return;
    }
}

void YouWin()
{
    printf("Dealer: �����ϳ�. �װ� �̰��.\n");
    sleep(1);
    printf("Dealer: ������ �ް�.\n");
    sleep(2);

    printf("||====================================================================||\n");
    printf("||//$\\\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\//$\\\\||\n");
    printf("||(100)==================| FEDERAL RESERVE NOTE |================(100)||\n");
    printf("||\\\\$//        ~         '------========--------'                \\\\$//||\n");
    printf("||<< //        /$\\            // ____ \\\\                         \\\\ >>||\n");
    printf("||>>|  12    //L\\            // ///..) \\\\        L38036133B     12 |<<||\n");
    printf("||<<|        \\ //            || <||  >\\ ||                         |>>||\n");
    printf("||>>|         \\$/            ||  $$ --/ ||         One Hundred     |<<||\n");
    printf("||<<|      L38036133B        *\\  |\\_/  //* series                  |>>||\n");
    printf("||>>|  12                     *\\/___\\_//*   1989                   |<<||\n");
    printf("||<<\\      Treasurer     ______/Franklin\\________     Secretary 12 />>||\n");
    printf("||/$\\\\                 ~|UNITED STATES OF AMERICA|~               //$\\||\n");
    printf("||(100)===================  ONE HUNDRED DOLLARS =================(100)||\n");
    printf("||//$\\\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\//$\\\\||\n");
    printf("||====================================================================||\n\n");

    printf("YOU WIN.\n");

    return;
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