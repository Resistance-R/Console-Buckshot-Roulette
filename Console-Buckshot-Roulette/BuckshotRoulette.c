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
bool alreadyFire = false;

int blankShell;
int liveShell;

int usingItem;
int shootToWho;

bool isPlayerTurn = true;

int shotgun[8] = {};
char *totalItem[5] = {"담배", "톱", "캔 맥주", "돋보기", "수갑"};
char *playerItem[9] = {"샷건"};
char *dealerItem[9] = {"샷건"};

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
    printf("'s'를 입력해 시작하십시오.\n");
    scanf("%s", &start);

    while (start != 's')
    {
        printf("'s'를 입력해 시작하십시오.\n");
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

    printf("Dealer: 총알은 무작위로 장전되지.\n");
    sleep(1);

    Reload();

    while (playerHP > 0 || dealerHP > 0)
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

        alreadyFire = false;

        if (dealerHP > 0 && !isPlayerTurn)
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

    printf("Dealer: 더 재밌게 해 볼까.\n");
    sleep(1);
    printf("Dealer: 아이템은 최대 8개까지. 각자 장전 당 2개씩 받는다.\n");
    sleep(1);
    printf("Dealer: 마찬가지로 총알은 무작위로 장전되지.\n");
    sleep(2);

    Reload();

    alreadyDead = false;

    while (playerHP > 0 || dealerHP > 0)
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

        alreadyFire = false;

        if (dealerHP > 0 && !isPlayerTurn)
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

    printf("Dealer: 이제, 승부를 가릴 때로군.\n");
    sleep(1);
    printf("Dealer: 재세동기도, 수혈도. 그 어떤 도움도 없어.\n");
    sleep(1);
    printf("Dealer: 이제 너와 나. 모두 삶과 죽음의 작두 위에서 춤을 추게 되는거야.\n");
    sleep(2);
    printf("Dealer: 룰은 알고 있겠지.\n");
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

        alreadyFire = false;

        if (dealerHP > 0 && !isPlayerTurn)
        {
            DealerTurn();
        }
    }
}

void EnterPlayerName()
{
    printf("Dealer: 각서 먼저 쓰고 하지. \n\n");
    sleep(1);
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

    for (int i = 0; i < 8; i++)
    {
        shotgun[i] = 2;
    }

    printf("\n\n재장전!\n\n");

    srand(time(NULL));

    for (int i = 0; i < shells; i++)
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
}

void PlayerTurn()
{
    printf("당신의 차례!\n\n");

    ShowPlayerItem();

    printf("사용할 아이템(숫자로 입력)\n");
    scanf("%d", &usingItem);

    if(usingItem == 0)
    {
        ReadyToFire();
    }

    if(usingItem != 0)
    {
        if(roundNum <= 1)
        {
            printf("\n아이템이 없다.\n");
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

    printf("딜러의 차례!\n\n");

    ShowDealerItem();

    if(!alreadyFire && roundNum > 1)
    {
        DealerUseItem();
    }

    if(!alreadyFire && liveShell >= blankShell)
    {
        sleep(2);
        DealerFire(player);
    }

    else if(!alreadyFire && blankShell > liveShell)
    {
        sleep(2);
        DealerFire(dealer);
    }
}

bool IsPlayerFull()
{
    for (int i = 0; i < 10; i++)
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

    while (playerGetItem <= howManyItems && !IsPlayerFull())
    {
        int itemIndex = rand() % 5;

        if(IsPlayerFull())
        {
            printf("Dealer: 공간이 없군. 아이템을 줄 수 없어.\n");
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

    while (dealerGetItem <= howManyItems && !IsDealerFull())
    {
        int itemIndex = rand() % 5;

        if(IsDealerFull())
        {
            printf("Dealer: 공간이 없군.\n");
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
    for (int i = 1; i < 9; i++)
    {
        playerItem[i] = NULL;
        dealerItem[i] = NULL;
    }
}

void ShowPlayerItem()
{
    printf("당신의 아이템: \n");

    for (int i = 0; i < 9; i++)
    {
        if(playerItem[i] == NULL)
        {
            printf("\n%d: (없음)\n", i);
        }

        else if(playerItem[i] != NULL)
        {
            printf("\n%d: %s\n", i, playerItem[i]);
        }
    }
}

void ShowDealerItem()
{
    printf("딜러 아이템: \n");

    for (int i = 0; i < 9; i++)
    {
        if(dealerItem[i] == NULL)
        {
            printf("\n%d: (없음)\n", i);
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


    if(playerItem[usingItem] == NULL)
    {
        printf("\n아이템이 없다.\n");
        return;
    }

    if(strcmp(playerItem[usingItem], "돋보기") == 0)
    {
        if(shotgun[0] == 0)
        {
            printf("\n공탄이 장전되어 있다.\n");
        }

        if(shotgun[0] == 1)
        {
            printf("\n실탄이 장전되어 있다.\n");
        }
    }

    if(strcmp(playerItem[usingItem], "캔 맥주") == 0)
    {
        if(shotgun[0] == 0)
        {
            printf("\n공탄이 튀어나왔다.\n");
        }

        if(shotgun[0] == 1)
        {
            printf("\n실탄이 튀어나왔다.\n");
        }

        ShotgunPumping(shotgun, index);
    }

    if(strcmp(playerItem[usingItem], "톱") == 0)
    {
        printf("\n총열을 톱으로 잘랐다.\n");
        isCut = true;
    }

    if(strcmp(playerItem[usingItem], "담배") == 0)
    {
        printf("담배를 사용했다.\n");
        playerHP++;

        if(roundNum == 2 && playerHP > 4)
        {
            printf("하지만 이미 최대 체력이다.\n");
            playerHP--;
        }

        if(roundNum == 3)
        {
            if(playerHP > 6)
            {
                printf("하지만 이미 최대 체력이다.\n");
                playerHP--;
            }

            if(playerHP <= 2)
            {
                printf("Dealer: 잊었나? 더 이상의 수혈은 없다고.\n");
                playerHP--;
            }
        }

        printf("\nDealer's Life Points: %d | %s's Life Points: %d\n\n", dealerHP, playerName, playerHP);
    }

    if(strcmp(playerItem[usingItem], "수갑") == 0)
    {
        printf("\n수갑을 사용하였다.\n");
        isHandscuffsOfPlayer = true;
    }

    if(playerItem[usingItem] != NULL)
    {
        playerItem[usingItem] = NULL;
    }


    return;
}

void DealerUseItem()
{
    int player = 0;
    int dealer = 1;

    int index = 0;

    for (int i = 1; i < 9; i++)
    {
        bool dealerItemUsed = false;

        if(!alreadyFire)
        {

            if(dealerItem[i] == NULL)
            {
                continue;
            }

            if(!alreadyFire && strcmp(dealerItem[i], "돋보기") == 0)
            {
                printf("\n딜러는 돋보기를 사용했다.\n");
                printf("Dealer: 참 흥미롭군...\n");

                sleep(2);

                if(shotgun[0] == 0)
                {
                    DealerFire(dealer);
                }

                if(shotgun[0] == 1)
                {
                    DealerFire(player);
                }

                dealerItemUsed = true;
            }

            if(strcmp(dealerItem[i], "캔 맥주") == 0)
            {
                printf("\n딜러는 캔 맥주를 사용했다.\n");

                sleep(2);

                if(shotgun[0] == 0)
                {
                    printf("\n공탄이 튀어나왔다.\n");
                    blankShell--;
                }

                if(shotgun[0] == 1)
                {
                    printf("\n실탄이 튀어나왔다.\n");
                    liveShell--;
                }

                ShotgunPumping(shotgun, index);

                dealerItemUsed = true;
            }

            if(!isCut && liveShell >= blankShell && strcmp(dealerItem[i], "톱") == 0)
            {
                printf("\n딜러는 총열을 톱으로 잘랐다.\n");

                isCut = true;

                sleep(2);

                dealerItemUsed = true;
            }

            if(dealerHP <= 3 && strcmp(dealerItem[i], "담배") == 0)
            {
                printf("\n딜러는 담배를 사용했다.\n");

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

                dealerItemUsed = true;
            }

            if(!isHandscuffsOfDealer && strcmp(dealerItem[i], "수갑") == 0)
            {
                printf("\n딜러는 수갑을 사용하였다.\n");

                isHandscuffsOfDealer = true;

                sleep(2);

                dealerItemUsed = true;
            }

            if (dealerItemUsed && dealerItem[i] != NULL)
            {
                dealerItem[i] = NULL;
                dealerItemUsed = false;
            }
        }
    }
    
    return;
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
        printf("\n틱!\n(격발되지 않음)\n");
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
        printf("\n틱!\n(격발되지 않음)\n");
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
        printf("딜러는 나를 향해서 쐈다.\n");

        sleep(1);

        printf("\n틱!\n(격발되지 않음)\n");

        ShotgunPumping(shotgun, index);

        blankShell--;

        isPlayerTurn = true;
    }

    else if(shotgun[0] == 1 && dealerOrPlayer == player)
    {
        printf("딜러는 나를 향해서 쐈다.\n");

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
    }

    else if(shotgun[0] == 0 && dealerOrPlayer == dealer)
    {
        printf("딜러는 스스로를 향해서 쐈다.\n");

        sleep(1);

        printf("\n틱!\n(격발되지 않음)\n");

        ShotgunPumping(shotgun, index);

        blankShell--;

        isPlayerTurn = false;
    }

    else if(shotgun[0] == 1 && dealerOrPlayer == dealer)
    {
        printf("딜러는 스스로를 향해서 쐈다.\n");

        sleep(1);

        Bang();

        sleep(1);

        dealerHP -= shotgunDmg;

        printf("Dealer's Life Points: %d | %s's Life Points: %d\n\n", dealerHP, playerName, playerHP);

        ShotgunPumping(shotgun, index);

        liveShell--;

        isPlayerTurn = true;
    }

    alreadyFire = true;

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
        alreadyFire = false;
    }

    if(isPlayerTurn && isHandscuffsOfDealer)
    {
        isHandscuffsOfDealer = false;
        isPlayerTurn = false;
        alreadyFire = false;
    }
}

void RepairShotgun()
{
    isCut = false;

    if(isCut)
    {
        printf("\n샷건이 수리되었다.\n");
    }
}

void Dead()
{
    if(roundNum <= 2 && !alreadyDead)
    {
        sleep(3);

        printf("\n\n\n\n\n???: 제세동기가 충전되어서 다행이야, 하마터면 죽을 뻔 했어.\n");

        sleep(1);

        printf("???: 목숨 값은 외상으로 받아 두지. 아직 밤은 길어. 충분히 해낼 수 있을거야.\n\n");

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
    printf("Dealer: 축하하네. 네가 이겼어.\n");
    sleep(1);
    printf("Dealer: 보상을 받게.\n");
    sleep(2);

    printf("||====================================================================||\n");
    printf("||//$\\\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\//$\\\\||\n");
    printf("||(100)==================| FEDERAL RESERVE NOTE |================(100)||\n");
    printf("||\\\\$//        ~         '------==========------'                \\\\$//||\n");
    printf("||<</        /$\\               // ____ \\\\                          \\>>||\n");
    printf("||>>|  12   //L\\\\             // ///..) \\\\       L38036133B     12 |<<||\n");
    printf("||<<|       \\\\ //            || <||  >\\ ||                         |>>||\n");
    printf("||>>|        \\$/             ||  $$ --/ ||         One Hundred     |<<||\n");
    printf("||<<|      L38036133B        *\\\\  |\\_/  //* series                 |>>||\n");
    printf("||>>|  12                     *\\\\/___\\_//*   1989                  |<<||\n");
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
    for (int i = index; i < 8; i++)
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