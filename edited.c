#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define FILENAME "data.dat"
#define LEFT 75
#define RIGHT 77
#define ENTER 13

struct cs
{
    int work;
    int day;
    int money;
} currentStatus = {5, 1, 0};

struct as
{
    int data;
} animalStatus = {0};

struct ps
{
    int data;
} plantStatus = {0};

struct m
{
    int diyNumber;
} makingStatus = {0};

struct g
{
    int data;
} gameStatus = {0};

struct a
{
    int data;
} achievementStatus = {0};

struct s
{
    int data;
} storeStatus = {0};

struct i
{
    char *animal[5];
    int animalNumber[5];
    char *plant[5];
    int plantNumber[5];
    char *diy[7];
    int diyNumber[7];
    char *ingredient[7];
    int ingredientNumber[7];
} inventoryStatus = {
    .animalNumber = {
        0,
    },
    .plantNumber = {
        0,
    },
    .diyNumber = {
        0,
    },
    .ingredientNumber = {
        0,
    },
};

void gotoxy(int x, int y, const char *s)
{
    COORD pos = {2 * x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    printf("%s", s);
}

void mainMenu();
int checkStatus();
void loadData();
void saveData();
void drawLine(int x1, int y1, int x2, int y2, const char *symbol);
void drawModule();
void initialize();

void animalGrowth();
void plantGrowth();
void making();
void game();
void sleep();
void achievement();
void store();
void inventory();
void saveAndExit();

char *character[4] = {"\\(*_*)", "(   (>", "(   )", "/   \\"};
char *characterClear[4] = {"       ", "       ", "       ", "       "};

int main()
{
    initialize();
    system("mode con cols=150 lines=40");
    loadData();

    int choice;
    int menuChoose = 0;
    int execute;
    int start = 3;
    int isX = 1;
    while (1)
    {
        mainMenu();
        while (1)
        {
            gotoxy(menuChoose, 22, "");
            if (_kbhit())
            {
                choice = _getch();
                if (choice != LEFT && choice != RIGHT && choice != ENTER)
                {
                    continue;
                }
                if (choice == LEFT)
                {
                    if (menuChoose > 0)
                    {
                        menuChoose -= 7;
                        start--;
                    }
                }
                else if (choice == RIGHT)
                {
                    if (menuChoose < 56)
                    {
                        menuChoose += 7;
                        start++;
                    }
                }
                else
                {
                    switch (menuChoose)
                    {
                    case 0:
                        if (checkStatus())
                        {
                            animalGrowth();
                        }
                        break;

                    case 7:
                        if (checkStatus())
                        {
                            plantGrowth();
                        }
                        break;

                    case 14:
                        if (checkStatus())
                        {
                            making();
                        }
                        break;

                    case 21:
                        if (checkStatus())
                        {
                            game();
                        }
                        break;

                    case 28:
                        sleep();
                        break;

                    case 35:
                        achievement();
                        break;

                    case 42:
                        store();
                        break;

                    case 49:
                        inventory();
                        break;

                    case 56:
                        saveAndExit();
                        break;
                    }
                    break;
                }
            }
        }
    }
}

void mainMenu()
{
    system("cls");
    gotoxy(0, 0, "");
    drawModule(2, 14, character, 4);
    drawLine(0, 0, 74, 0, "■");
    drawLine(0, 0, 0, 17, "■");
    drawLine(74, 0, 74, 17, "■");
    drawLine(0, 74, 74, 74, "■");

    gotoxy(0, 20, "오늘은 무엇을 할까?? (선택후 enter!) ");
    for (int i = 0; i < currentStatus.work; i++)
        printf("♥");
    for (int i = 0; i < 5 - currentStatus.work; i++)
        printf("♡");
    printf("  현재 잔액: %d", currentStatus.money);
    printf("  DAY %d", currentStatus.day);
    gotoxy(0, 22, "동물키우기");
    gotoxy(7, 22, "식물기르기");
    gotoxy(14, 22, "DIY");
    gotoxy(21, 22, "게임");
    gotoxy(28, 22, "잠자기");
    gotoxy(35, 22, "업적");
    gotoxy(42, 22, "상점");
    gotoxy(49, 22, "인벤토리");
    gotoxy(56, 22, "저장 후 종료");
}
int checkStatus()
{
    if (currentStatus.work <= 0)
    {
        gotoxy(4, 2, "더 이상 작업을 실행할 수 없습니다. 잠을 자야 일을 더 할 수 있을것 같네.");
        Sleep(1000);
        return 0;
    }
    else
    {
        return 1;
    }
}
void loadData()
{
    FILE *fp;
    fopen_s(&fp, FILENAME, "r");
    if (fp == NULL)
    {
        fopen_s(&fp, FILENAME, "w");
        fwrite(&currentStatus, sizeof(struct cs), 1, fp);
        fwrite(&animalStatus, sizeof(struct as), 1, fp);
        fwrite(&plantStatus, sizeof(struct ps), 1, fp);
        fwrite(&makingStatus, sizeof(struct m), 1, fp);
        fwrite(&storeStatus, sizeof(struct s), 1, fp);
        fwrite(&achievementStatus, sizeof(struct a), 1, fp);
        fwrite(&gameStatus, sizeof(struct g), 1, fp);
        fwrite(&inventoryStatus, sizeof(struct i), 1, fp);
    }
    else
    {
        fread(&currentStatus, sizeof(struct cs), 1, fp);
        fread(&animalStatus, sizeof(struct as), 1, fp);
        fread(&plantStatus, sizeof(struct ps), 1, fp);
        fread(&makingStatus, sizeof(struct m), 1, fp);
        fread(&storeStatus, sizeof(struct s), 1, fp);
        fread(&achievementStatus, sizeof(struct a), 1, fp);
        fread(&gameStatus, sizeof(struct g), 1, fp);
        fread(&inventoryStatus, sizeof(struct i), 1, fp);
    }
    fclose(fp);
}
void saveData()
{
    FILE *fp;
    fopen_s(&fp, FILENAME, "w");
    fwrite(&currentStatus, sizeof(struct cs), 1, fp);
    fwrite(&animalStatus, sizeof(struct as), 1, fp);
    fwrite(&plantStatus, sizeof(struct ps), 1, fp);
    fwrite(&makingStatus, sizeof(struct m), 1, fp);
    fwrite(&storeStatus, sizeof(struct s), 1, fp);
    fwrite(&achievementStatus, sizeof(struct a), 1, fp);
    fwrite(&gameStatus, sizeof(struct g), 1, fp);
    fwrite(&inventoryStatus, sizeof(struct i), 1, fp);
    fclose(fp);
}
void drawLine(int x1, int y1, int x2, int y2, const char *symbol)
{
    if (x1 == x2)
    {
        for (int i = y1; i <= y2; i++)
        {
            gotoxy(x1, i, symbol);
        }
    }
    else
    {
        for (int i = x1; i <= x2; i++)
        {
            gotoxy(i, y1, symbol);
        }
    }
}
void drawModule(int x, int y, const char *symbol[], int size)
{
    for (int i = 0; i < size; i++)
    {
        gotoxy(x, y + i, symbol[i]);
    }
}

void animalGrowth()
{
    system("cls");
    gotoxy(0, 0, "animalGrowth");
    currentStatus.work--;
    Sleep(1000);
    return;
}
void plantGrowth()
{
    system("cls");
    gotoxy(0, 0, "plantGrowth");
    currentStatus.work--;
    Sleep(1000);
    return;
}

//////////////////////making start
void making(void)
{
    system("cls");
    int i, k;
    while (currentStatus.work)
    {

        system("cls");
        drawLine(0, 0, 74, 0, "■");
        drawLine(0, 0, 0, 17, "■");
        drawLine(74, 0, 74, 17, "■");
        drawLine(0, 74, 74, 74, "■");
        gotoxy(4, 2, "어서오세요 FORIF공방입니다!");
        gotoxy(4, 4, "1.공구,작업도구");
        gotoxy(4, 6, "2.동물용품(집,장난감)");
        gotoxy(4, 8, "3.공방 나가기");
        gotoxy(4, 10, "무엇을 만드실 건가요?:");
        scanf("%d", &i);
        if (i == 1)
        {
            system("cls");
            drawLine(0, 0, 74, 0, "■");
            drawLine(0, 0, 0, 17, "■");
            drawLine(74, 0, 74, 17, "■");
            drawLine(0, 74, 74, 74, "■");
            gotoxy(4, 4, "1.망치");
            gotoxy(4, 6, "2.삽");
            gotoxy(4, 8, "3.호미");
            gotoxy(4, 10, "무엇을 만드실 건가요?:");
            scanf("%d", &k);

            system("cls");
            drawLine(0, 0, 74, 0, "■");
            drawLine(0, 0, 0, 17, "■");
            drawLine(74, 0, 74, 17, "■");
            drawLine(0, 74, 74, 74, "■");
            gotoxy(4, 4, "재료는 철과 나무 각각 하나씩입니다.");
            gotoxy(4, 6, "재료는 인벤토리에서 차감됩니다.");
            if (inventoryStatus.ingredientNumber[0] >= 1 && inventoryStatus.ingredientNumber[1] >= 1)
            {
                inventoryStatus.ingredientNumber[0]--;
                inventoryStatus.ingredientNumber[1]--;
                system("cls");
                drawLine(0, 0, 74, 0, "■");
                drawLine(0, 0, 0, 17, "■");
                drawLine(74, 0, 74, 17, "■");
                drawLine(0, 74, 74, 74, "■");
                if (k == 1)
                {
                    gotoxy(4, 4, "망치를 만들었습니다!");
                    inventoryStatus.diyNumber[0]++;
                    currentStatus.work--;
                }
                if (k == 2)
                {
                    gotoxy(4, 4, "삽을 만들었습니다!");
                    inventoryStatus.diyNumber[1]++;
                    currentStatus.work--;
                }
                if (k == 3)
                {
                    gotoxy(4, 4, "호미를 만들었습니다!");
                    inventoryStatus.diyNumber[2]++;
                    currentStatus.work--;
                }
                makingStatus.diyNumber++;
            }
            else gotoxy(4,4,"재료가 부족하여 만들지 못합니다.");

        }
        else if (i == 2)
        {
            system("cls");
            drawLine(0, 0, 74, 0, "■");
            drawLine(0, 0, 0, 17, "■");
            drawLine(74, 0, 74, 17, "■");
            drawLine(0, 74, 74, 74, "■");
            gotoxy(4, 4, "1.강아지집");
            gotoxy(4, 6, "2.캣타워");
            gotoxy(4, 8, "3.이글루");
            gotoxy(4, 10, "4.햄스터 쳇바퀴");
            gotoxy(4, 12, "무엇을 만드실 건가요?:");
            scanf("%d", &k);
            system("cls");
            drawLine(0, 0, 74, 0, "■");
            drawLine(0, 0, 0, 17, "■");
            drawLine(74, 0, 74, 17, "■");
            drawLine(0, 74, 74, 74, "■");
            if (k == 1 || k == 2)
            {
                gotoxy(4, 4, "재료는 못과 드라이버,그리고 나무 각각 하나씩입니다.");
                gotoxy(4, 6, "재료는 인벤토리에서 차감됩니다.");
                if (inventoryStatus.ingredientNumber[0] >= 1 && inventoryStatus.ingredientNumber[4] >= 1 && inventoryStatus.ingredientNumber[5] >= 1)
                {
                    inventoryStatus.ingredientNumber[0]--;
                    inventoryStatus.ingredientNumber[4]--;
                    inventoryStatus.ingredientNumber[5]--;
                    system("cls");
                    drawLine(0, 0, 74, 0, "■");
            drawLine(0, 0, 0, 17, "■");
            drawLine(74, 0, 74, 17, "■");
            drawLine(0, 74, 74, 74, "■");
                    if (k == 1)
                    {
                        gotoxy(4, 4, "강아지집을 만들었습니다!");
                        inventoryStatus.diyNumber[3]++;
                        currentStatus.work--;
                    }
                    if (k == 2)
                    {
                        gotoxy(4, 4, "캣타워를 만들었습니다!");
                        inventoryStatus.diyNumber[4]++;
                        currentStatus.work--;
                    }
                    makingStatus.diyNumber++;
                }
                else
                    gotoxy(4, 4, "재료가 부족하여 만들지 못합니다.");
            }
            else if (k == 3)
            {
                gotoxy(4, 4, "재료는 얼음덩어리 세개입니다.");
                gotoxy(4, 6, "재료는 인벤토리에서 차감됩니다.");
                if (inventoryStatus.ingredientNumber[6] >= 3)
                {
                    inventoryStatus.ingredientNumber[6] -= 3;
                    system("cls");
                    drawLine(0, 0, 74, 0, "■");
                    drawLine(0, 0, 0, 17, "■");
                    drawLine(74, 0, 74, 17, "■");
                    drawLine(0, 74, 74, 74, "■");
                    gotoxy(4, 4, "이글루를 만들었습니다!");
                    inventoryStatus.diyNumber[5]++;
                    currentStatus.work--;
                    makingStatus.diyNumber++;
                }
                else
                    gotoxy(4, 4, "재료가 부족하여 만들지 못합니다.");
            }
            else if (k == 4)
            {
                gotoxy(4, 4, "재료는 플라스틱, 나사, 드라이버 각각 하나씩입니다.");
                gotoxy(4, 6, "재료는 인벤토리에서 차감됩니다.");
                if (inventoryStatus.ingredientNumber[3] >= 1 && inventoryStatus.ingredientNumber[4] >= 1 && inventoryStatus.ingredientNumber[5] >= 1)
                {
                    inventoryStatus.ingredientNumber[3]--;
                    inventoryStatus.ingredientNumber[4]--;
                    inventoryStatus.ingredientNumber[5]--;
                    system("cls");
                    drawLine(0, 0, 74, 0, "■");
                    drawLine(0, 0, 0, 17, "■");
                    drawLine(74, 0, 74, 17, "■");
                    drawLine(0, 74, 74, 74, "■");
                    gotoxy(4, 4, "햄스터 쳇바퀴를 만들었습니다!");
                    inventoryStatus.diyNumber[6]++;
                    currentStatus.work--;
                    makingStatus.diyNumber++;
                }
                else
                    gotoxy(4, 4, "재료가 부족하여 만들지 못합니다.");
            }
        }
        else if (i == 3)
            break;
        Sleep(1000);
    }
    if(currentStatus.work <=0){
        system("cls");
    drawLine(0, 0, 74, 0, "■");
    drawLine(0, 0, 0, 17, "■");
    drawLine(74, 0, 74, 17, "■");
    drawLine(0, 74, 74, 74, "■");
    gotoxy(4,2,"더 이상 작업을 실행할 수 없습니다. 잠을 자야 일을 더 할 수 있을것 같네.");
    Sleep(1000);
    }
    return;
}
///////////////////////making end

////////////////////////////////////game start
int Numrandom(void)
{
    srand(time(NULL));
    int num1, num2, num3, num4, temp;
    num1 = rand() % 900 + 100;
    num2 = num1 / 100;
    num3 = (num1 - num2 * 100) / 10;
    num4 = num1 % 10;
    while (num2 == num3 || num2 == num4 || num3 == num4)
    {
        num1 = rand() % 900 + 100;
        num2 = num1 / 100;
        num3 = (num1 - num2 * 100) / 10;
        num4 = num1 % 10;
    }
    return num1;
}
int game1()
{
    system("cls");
    int i;
    srand(time(NULL));
    i = rand() % 3 + 1;
    if (i == 1)
    {
        int ans, realnum, num2, num3, num4, num5, num6, num7, temp, cnt = 0;
        int out, ball = 0;
        int strike = 0;
        realnum = Numrandom();
        num2 = realnum / 100;
        temp = realnum % 100;
        num3 = temp / 10;
        num4 = temp % 10;
        printf("안녕 나는 야구선수 한양이야! 내 특기는 숫자 야구! 혹시 숫자 야구 알아?\n\n");
        printf("혹시 모르는 애들이 있을 수 있으니까 룰을 간단하게 알려줄게!\n\n");
        printf("===============================RULE=================================\n");
        printf("1.정답은 세자리 숫자야! 100~999안에 숫자중 하나이고 너는 그 숫자를 맞추면 되는거야!\n");
        printf("2.너가 숫자를 말하면 백의 자리 숫자와 십의 자리 숫자, 일의 자리 숫자 각각을 비교해\n");
        printf("자리와 숫자가 같으면 스트라이크! 숫자는 포함되는데 자리가 다르면 볼! 숫자가 포함안되면 아웃!\n");
        printf("3.예를 들어 정답이 123이고 너가 말한 숫자가 524라면 1스트라이크 2아웃이 되는거야!\n");
        printf("만약 317을 말한다면 2볼 1아웃이 되겠지??\n");
        printf("\n7번안에 맞춘다면 보상이 주어질거야! 적으면서 하는 것을 추천할게!, 이제 시작하자!!\n\n");
        printf("정답은 무엇일까?:");
        scanf("%d", &ans);
        while (cnt < 7)
        {
            if (ans == realnum && cnt < 7)
            {
                printf("정답이야! %d번만에 맞추다니 대단한걸? 보상을 받아가!", cnt + 1);
                return 1;
            }
            else
            {
                num5 = ans / 100;
                temp = ans % 100;
                num6 = temp / 10;
                num7 = temp % 10;
                if (num2 == num5)
                    strike++;
                if (num2 == num6 || num2 == num7)
                    ball++;
                if (num3 == num5 || num3 == num7)
                    ball++;
                if (num3 == num6)
                    strike++;
                if (num4 == num7)
                    strike++;
                if (num4 == num5 || num4 == num6)
                    ball++;
                out = 3 - (strike + ball);
                printf("%d스트라이크 %d볼 %d아웃!\n\n", strike, ball, out);
                strike = 0;
                ball = 0;
                out = 0;
                cnt++;
                if (cnt >= 7)
                    break;
                printf("정답은 무엇일까?:");
                scanf("%d", &ans);
            }
        }
        printf("정답은 %d 이거로 실패야ㅠㅠㅠ\n", realnum);
        printf("7번이 넘었는걸? 안타깝지만 실패야ㅠㅠㅠㅠ 다음을 바라도록!");
        return 0;
    }
    else if (i == 2)
    {
        int num1, num2, ans;
        printf("다음화면에 나올 클로버의 개수는 홀수일까요? 아니면 짝수일까요??\n\n");
        printf("당신의 운에 맡기세요!!!\n\n");
        printf("당신의 대답은?(홀수면 1, 짝수면 2) : ");
        scanf("%d", &num1);
        printf("\n======================================\n");
        ans = rand() % 2 + 1;
        if (num1 == ans && num1 == 1)
        {
            printf("♣ ♣ ♣ ♣ ♣\n");
            printf("\n=====================================\n");
            printf("5개네요! 정답입니다!!\n\n");
            printf("보상이 있겠습니다.");
            return 1;
        }
        else if (num1 == ans && num1 == 2)
        {
            printf("♣ ♣ ♣ ♣ ♣ ♣\n");
            printf("\n=====================================\n");
            printf("6개네요! 정답입니다!!\n\n");
            printf("보상이 있겠습니다.");
            return 1;
        }
        else if (num1 != ans && num1 == 1)
        {
            printf("♣ ♣ ♣ ♣\n");
            printf("\n=====================================\n");
            printf("4개로 짝수네요ㅠㅠ 다음에 도전하세요!");
            return 0;
        }
        else
        {
            printf("♣ ♣ ♣ \n");
            printf("\n=====================================\n");
            printf("3개로 홀수네요ㅠㅠ 다음에 도전하세요!");
            return 0;
        }
    }
    else
    {
        int ans, realday, num1, cnt = 0;
        realday = rand() % 31 + 1;
        printf("안녕 내 이름은 포리프야! 7월에 해커톤 한다고 수고가 많아\n\n");
        printf("마침 내 생일도 7월인데 내 생일을 맞추어 볼래? 기회는 4번이야!\n\n");
        printf("내 생일은 언제 일까?(1~31):");
        scanf("%d", &ans);
        while (cnt < 3)
        {
            if (ans == realday)
            {
                printf("\n맞아 그 날이 내 생일이야!\n\n");
                printf("보상을 받아가도록해!");
                return 1;
            }
            else if (ans > realday)
            {
                printf("\n내 생일치고는 좀 늦은 감이 있네..\n\n");
                printf("다시 맞춰봐!\n\n");
                printf("내 생일은 언제 일까?(1~31):");
                scanf("%d", &ans);
                cnt++;
            }
            else
            {
                printf("\n내 생일치고는 좀 이른 감이 있네..\n\n");
                printf("다시 맞춰봐!\n\n");
                printf("내 생일은 언제 일까?(1~31):");
                scanf("%d", &ans);
                cnt++;
            }
        }
        if (ans != realday)
        {
            printf("\n4번 다 틀렸네 정답은 %d일이야!\n\n", realday);
            printf("틀렸으니까 보상은 없어!");
            return 0;
        }
        else
        {
            printf("\n마지막 기회에 맞추다니!! 아쉽다.. 축하해!\n\n");
            printf("보상을 받아가도록 해!");
            return 1;
        }
    }
}

void game()
{
    int num;
    num = game1();
    currentStatus.work--;
    if (num == 1)
        currentStatus.money += 30000;
    Sleep(2000);
    return;
}
/////////////////////////////////game end

void sleep()
{
    system("cls");
    gotoxy(0, 0, "sleep");
    currentStatus.day++;
    currentStatus.work = 5;
    Sleep(1000);
    return;
}
void achievement()
{
    system("cls");
    gotoxy(0, 0, "achievement");
    Sleep(1000);
    return;
}
void store()
{
    system("cls");
    gotoxy(0, 0, "store");
    currentStatus.work--;
    Sleep(1000);
    return;
}
void inventory()
{
    system("cls");
    gotoxy(0, 0, "");
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", inventoryStatus.animalNumber[i]);
    }
    printf("\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", inventoryStatus.plantNumber[i]);
    }
    printf("\n");
    for (int i = 0; i < 7; i++)
    {
        printf("%d ", inventoryStatus.diyNumber[i]);
    }
    printf("\n");
    for (int i = 0; i < 7; i++)
    {
        printf("%d ", inventoryStatus.ingredientNumber[i]);
    }
    printf("\n");

    Sleep(1000);
    return;
}
void saveAndExit()
{
    system("cls");
    gotoxy(0, 0, "saveAndExit");
    saveData();
    Sleep(1000);
    exit(0);
    return;
}

void initialize()
{
    inventoryStatus.animal[0] = "강아지";
    inventoryStatus.animal[1] = "고양이";
    inventoryStatus.animal[2] = "펭귄";
    inventoryStatus.animal[3] = "햄스터";
    inventoryStatus.animal[4] = "병아리";
    inventoryStatus.plant[0] = "방울토마토";
    inventoryStatus.plant[1] = "고추";
    inventoryStatus.plant[2] = "상추";
    inventoryStatus.plant[3] = "완두콩";
    inventoryStatus.plant[4] = "콩나물";
    inventoryStatus.diy[0] = "망치";
    inventoryStatus.diy[1] = "삽";
    inventoryStatus.diy[2] = "호미";
    inventoryStatus.diy[3] = "개집";
    inventoryStatus.diy[4] = "캣타워";
    inventoryStatus.diy[5] = "이글루";
    inventoryStatus.diy[6] = "쳇바퀴";
    inventoryStatus.ingredient[0] = "나무" ;
    inventoryStatus.ingredient[1] = "철" ;
    inventoryStatus.ingredient[2] = "못" ;
    inventoryStatus.ingredient[3] = "플라스틱" ;
    inventoryStatus.ingredient[4]= "드라이버" ;
    inventoryStatus.ingredient[5] = "나사" ;
    inventoryStatus.ingredient[6] = "얼음덩어리" ;



    inventoryStatus.animalNumber[0] = 12;
    inventoryStatus.animalNumber[1] = 23;
    inventoryStatus.animalNumber[2] = 45;
    inventoryStatus.animalNumber[3] = 56;
    inventoryStatus.animalNumber[4] = 56;
    inventoryStatus.plantNumber[0] = 64;
    inventoryStatus.plantNumber[1] = 34;
    inventoryStatus.plantNumber[2] = 34;
    inventoryStatus.plantNumber[3] = 45;
    inventoryStatus.plantNumber[4] = 655;
    inventoryStatus.diyNumber[0] = 34;
    inventoryStatus.diyNumber[1] = 56;
    inventoryStatus.diyNumber[2] = 676;
    inventoryStatus.diyNumber[3] = 56;
    inventoryStatus.diyNumber[4] = 45;
    inventoryStatus.diyNumber[5] = 67;
    inventoryStatus.diyNumber[6] = 23;
    inventoryStatus.ingredientNumber[0] = 45;
    inventoryStatus.ingredientNumber[1] = 67;
    inventoryStatus.ingredientNumber[2] = 578;
    inventoryStatus.ingredientNumber[3] = 564;
    inventoryStatus.ingredientNumber[4] = 34;
    inventoryStatus.ingredientNumber[5] = 65;
    inventoryStatus.ingredientNumber[6] = 34;
}
