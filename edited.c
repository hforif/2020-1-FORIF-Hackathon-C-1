#define _CRT_SECURE_NO_WARNINGS
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
    int day;
    int isPlanted;
} plantStatus = {
    .day = 0,
};

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
void title();

void animalGrowth();
void plantGrowth();
void making();
void game();
void sleep();
void achievement();
void store();
void inventory();
void saveAndExit();

const char *character[4] = {"\\(*_*)", "(   (>", "(   )", "/   \\"};
const char *character2[4] = {"( ^��^)\n", "( /   )/\n", " )    )\n", "/     \\"};

const char *wakedup[5]={"     ��_��","���� ('��')","�� ��|������(�ߣ�_","������-(�ߣߣ�_��","��������������"};
const char *wakedupClear[5]={"                                 ","                                 ","                                 ","                                 ","                                 "};
const char *sleeping[3]={"�����ң�`-._��_","����_/�ߣߣߣߣ�","��������������"};

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
    int cnt1, cnt2, cnt4;
    title();
    while (!_kbhit())
        ;

    getchar();

    system("cls");

    story();

    while (!_kbhit())
        ;

    getchar();

    system("cls");

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
                        saveData();
                        break;

                    case 7:
                        if (checkStatus())
                        {
                            plantGrowth();
                        }
                        saveData();
                        break;

                    case 14:
                        if (checkStatus())
                        {
                            making();
                        }
                        saveData();
                        break;

                    case 21:
                        if (checkStatus())
                        {
                            game();
                        }
                        saveData();
                        break;

                    case 28:
                        sleep();
                        saveData();
                        break;

                    case 35:
                        achievement();
                        saveData();
                        break;

                    case 42:
                        if(checkStatus()){
                            store();    
                        }
                        saveData();
                        break;

                    case 49:
                        inventory();
                        saveData();
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
    drawLine(0, 0, 74, 0, "��");
    drawLine(0, 0, 0, 17, "��");
    drawLine(74, 0, 74, 17, "��");
    drawLine(0, 74, 74, 74, "��");

    gotoxy(0, 20, "������ ������ �ұ�?? (������ enter!) ");
    for (int i = 0; i < currentStatus.work; i++)
        printf("��");
    for (int i = 0; i < 5 - currentStatus.work; i++)
        printf("��");
    printf("  ���� �ܾ�: %d", currentStatus.money);
    printf("  DAY %d", currentStatus.day);
    gotoxy(0, 22, "����Ű���");
    gotoxy(7, 22, "�Ĺ��⸣��");
    gotoxy(14, 22, "DIY");
    gotoxy(21, 22, "����");
    gotoxy(28, 22, "���ڱ�");
    gotoxy(35, 22, "����");
    gotoxy(42, 22, "����");
    gotoxy(49, 22, "�κ��丮");
    gotoxy(56, 22, "���� �� ����");
}
int checkStatus()
{
    if (currentStatus.work <= 0)
    {
        gotoxy(4, 2, "�� �̻� �۾��� ������ �� �����ϴ�. ���� �ھ� ���� �� �� �� ������ ����.");
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
    int i, j;
    int thanksgivingday[5] = {3, 2, 200, 4, 1};
    int price[5] = {60000, 40000,  100000000, 90000, 35000};
    if (plantStatus.day == 0) {
        drawLine(0, 0, 74, 0, "��");
        drawLine(0, 0, 0, 17, "��");
        drawLine(74, 0, 74, 17, "��");
        drawLine(0, 74, 74, 74, "��");
        gotoxy(4, 4, "1. ����丶��");
        gotoxy(4, 6, "2. ����");
        gotoxy(4, 8, "3. ����");
        gotoxy(4, 10, "4. �ϵ���");
        gotoxy(4, 12, "5. �ᳪ��");
        gotoxy(4, 15, "� �۹��� Ű��ðڽ��ϱ�? ");
        
        scanf("%d(1~5)", &j);
        if(inventoryStatus.plantNumber[j-1] <= 0){
            system("cls");
             drawLine(0, 0, 74, 0, "��");
        drawLine(0, 0, 0, 17, "��");
        drawLine(74, 0, 74, 17, "��");
        drawLine(0, 74, 74, 74, "��");
            gotoxy(4,4,"");
            printf("%s ������ �����ϴ�.",inventoryStatus.plant[j-1]);
            Sleep(1000);
            return;
        }
        
        
        if (j == 1) {
            system("cls");
            drawLine(0, 0, 74, 0, "��");
        drawLine(0, 0, 0, 17, "��");
        drawLine(74, 0, 74, 17, "��");
        drawLine(0, 74, 74, 74, "��");
            gotoxy(4, 4, "����丶�並 �ɾ����ϴ�!");
            gotoxy(4, 6, "�۹��� 3�� �ڿ� �ڶ��ϴ�.");
            plantStatus.isPlanted = j-1;
            inventoryStatus.plantNumber[0]--;
            plantStatus.day = currentStatus.day;
            currentStatus.work--;
        }
        else if (j == 2) {
            system("cls");
            drawLine(0, 0, 74, 0, "��");
        drawLine(0, 0, 0, 17, "��");
        drawLine(74, 0, 74, 17, "��");
        drawLine(0, 74, 74, 74, "��");
            gotoxy(4, 4, "���߸� �ɾ����ϴ�!");
            gotoxy(4, 6, "�۹��� 2�� �ڿ� �ڶ��ϴ�.");
            plantStatus.isPlanted = j-1;
            inventoryStatus.plantNumber[1]--;
            plantStatus.day = currentStatus.day;
            currentStatus.work--;
        }
        if (j == 3) {
            system("cls");
            drawLine(0, 0, 74, 0, "��");
        drawLine(0, 0, 0, 17, "��");
        drawLine(74, 0, 74, 17, "��");
        drawLine(0, 74, 74, 74, "��");
            gotoxy(4, 4, "���߸� �ɾ����ϴ�!");
            gotoxy(4, 6, "�۹��� 200�� �ڿ� �ڶ��ϴ�.");
            plantStatus.isPlanted = j-1;
            inventoryStatus.plantNumber[2]--;
            plantStatus.day = currentStatus.day;
            currentStatus.work--;
        }
        if (j == 4) {
            system("cls");
            drawLine(0, 0, 74, 0, "��");
        drawLine(0, 0, 0, 17, "��");
        drawLine(74, 0, 74, 17, "��");
        drawLine(0, 74, 74, 74, "��");
            gotoxy(4, 4, "�ϵ����� �ɾ����ϴ�!");
            gotoxy(4, 6, "�۹��� 4�� �ڿ� �ڶ��ϴ�.");
            plantStatus.isPlanted = j-1;
            inventoryStatus.plantNumber[3]--;
            plantStatus.day = currentStatus.day;
            currentStatus.work--;
        }
        if (j == 5) {
            system("cls");
            drawLine(0, 0, 74, 0, "��");
        drawLine(0, 0, 0, 17, "��");
        drawLine(74, 0, 74, 17, "��");
        drawLine(0, 74, 74, 74, "��");
            gotoxy(4, 4, "�ᳪ���� �ɾ����ϴ�!");
            gotoxy(4, 6, "�۹��� 1�� �ڿ� �ڶ��ϴ�.");
            plantStatus.isPlanted = j-1;
            inventoryStatus.plantNumber[4]--;
            plantStatus.day = currentStatus.day;
            currentStatus.work--;
        }
    }
    else if (currentStatus.day - plantStatus.day >= thanksgivingday[plantStatus.isPlanted] ) {
        system("cls");
            drawLine(0, 0, 74, 0, "��");
        drawLine(0, 0, 0, 17, "��");
        drawLine(74, 0, 74, 17, "��");
        drawLine(0, 74, 74, 74, "��");
        gotoxy(4, 4, "");
        printf("������ �۹��� �� �ڶ� ��Ȯ�� �Ͽ� %d���� ȹ���Ͽ����ϴ�.",price[plantStatus.isPlanted]);
        currentStatus.money += price[plantStatus.isPlanted];
        plantStatus.day = 0;
    }
    else {
        system("cls");
        gotoxy(4, 4, "�۹��� ���� �� �ڶ��� �ʾҽ��ϴ�.");
        
    }
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
        drawLine(0, 0, 74, 0, "��");
        drawLine(0, 0, 0, 17, "��");
        drawLine(74, 0, 74, 17, "��");
        drawLine(0, 74, 74, 74, "��");
        gotoxy(4, 2, "������� FORIF�����Դϴ�!");
        gotoxy(4, 4, "1.����,�۾�����");
        gotoxy(4, 6, "2.������ǰ(��,�峭��)");
        gotoxy(4, 8, "3.���� ������");
        gotoxy(4, 10, "������ ����� �ǰ���?:");
        scanf("%d", &i);
        if (i == 1)
        {
            system("cls");
            drawLine(0, 0, 74, 0, "��");
            drawLine(0, 0, 0, 17, "��");
            drawLine(74, 0, 74, 17, "��");
            drawLine(0, 74, 74, 74, "��");
            gotoxy(4, 4, "1.��ġ");
            gotoxy(4, 6, "2.��");
            gotoxy(4, 8, "3.ȣ��");
            gotoxy(4, 10, "������ ����� �ǰ���?:");
            scanf("%d", &k);

            system("cls");
            drawLine(0, 0, 74, 0, "��");
            drawLine(0, 0, 0, 17, "��");
            drawLine(74, 0, 74, 17, "��");
            drawLine(0, 74, 74, 74, "��");
            gotoxy(4, 4, "���� ö�� ���� ���� �ϳ����Դϴ�.");
            gotoxy(4, 6, "���� �κ��丮���� �����˴ϴ�.");
            if (inventoryStatus.ingredientNumber[0] >= 1 && inventoryStatus.ingredientNumber[1] >= 1)
            {
                inventoryStatus.ingredientNumber[0]--;
                inventoryStatus.ingredientNumber[1]--;
                system("cls");
                drawLine(0, 0, 74, 0, "��");
                drawLine(0, 0, 0, 17, "��");
                drawLine(74, 0, 74, 17, "��");
                drawLine(0, 74, 74, 74, "��");
                if (k == 1)
                {
                    gotoxy(4, 4, "��ġ�� ��������ϴ�!");
                    inventoryStatus.diyNumber[0]++;
                    currentStatus.work--;
                }
                if (k == 2)
                {
                    gotoxy(4, 4, "���� ��������ϴ�!");
                    inventoryStatus.diyNumber[1]++;
                    currentStatus.work--;
                }
                if (k == 3)
                {
                    gotoxy(4, 4, "ȣ�̸� ��������ϴ�!");
                    inventoryStatus.diyNumber[2]++;
                    currentStatus.work--;
                }
                makingStatus.diyNumber++;
            }
            else gotoxy(4,4,"��ᰡ �����Ͽ� ������ ���մϴ�.");

        }
        else if (i == 2)
        {
            system("cls");
            drawLine(0, 0, 74, 0, "��");
            drawLine(0, 0, 0, 17, "��");
            drawLine(74, 0, 74, 17, "��");
            drawLine(0, 74, 74, 74, "��");
            gotoxy(4, 4, "1.��������");
            gotoxy(4, 6, "2.ĹŸ��");
            gotoxy(4, 8, "3.�̱۷�");
            gotoxy(4, 10, "4.�ܽ��� �¹���");
            gotoxy(4, 12, "������ ����� �ǰ���?:");
            scanf("%d", &k);
            system("cls");
            drawLine(0, 0, 74, 0, "��");
            drawLine(0, 0, 0, 17, "��");
            drawLine(74, 0, 74, 17, "��");
            drawLine(0, 74, 74, 74, "��");
            if (k == 1 || k == 2)
            {
                gotoxy(4, 4, "���� ���� ����̹�,�׸��� ���� ���� �ϳ����Դϴ�.");
                gotoxy(4, 6, "���� �κ��丮���� �����˴ϴ�.");
                if (inventoryStatus.ingredientNumber[0] >= 1 && inventoryStatus.ingredientNumber[4] >= 1 && inventoryStatus.ingredientNumber[5] >= 1)
                {
                    inventoryStatus.ingredientNumber[0]--;
                    inventoryStatus.ingredientNumber[4]--;
                    inventoryStatus.ingredientNumber[5]--;
                    system("cls");
                    drawLine(0, 0, 74, 0, "��");
            drawLine(0, 0, 0, 17, "��");
            drawLine(74, 0, 74, 17, "��");
            drawLine(0, 74, 74, 74, "��");
                    if (k == 1)
                    {
                        gotoxy(4, 4, "���������� ��������ϴ�!");
                        inventoryStatus.diyNumber[3]++;
                        currentStatus.work--;
                    }
                    if (k == 2)
                    {
                        gotoxy(4, 4, "ĹŸ���� ��������ϴ�!");
                        inventoryStatus.diyNumber[4]++;
                        currentStatus.work--;
                    }
                    makingStatus.diyNumber++;
                }
                else
                    gotoxy(4, 4, "��ᰡ �����Ͽ� ������ ���մϴ�.");
            }
            else if (k == 3)
            {
                gotoxy(4, 4, "���� ������� �����Դϴ�.");
                gotoxy(4, 6, "���� �κ��丮���� �����˴ϴ�.");
                if (inventoryStatus.ingredientNumber[6] >= 3)
                {
                    inventoryStatus.ingredientNumber[6] -= 3;
                    system("cls");
                    drawLine(0, 0, 74, 0, "��");
                    drawLine(0, 0, 0, 17, "��");
                    drawLine(74, 0, 74, 17, "��");
                    drawLine(0, 74, 74, 74, "��");
                    gotoxy(4, 4, "�̱۷縦 ��������ϴ�!");
                    inventoryStatus.diyNumber[5]++;
                    currentStatus.work--;
                    makingStatus.diyNumber++;
                }
                else
                    gotoxy(4, 4, "��ᰡ �����Ͽ� ������ ���մϴ�.");
            }
            else if (k == 4)
            {
                gotoxy(4, 4, "���� �ö�ƽ, ����, ����̹� ���� �ϳ����Դϴ�.");
                gotoxy(4, 6, "���� �κ��丮���� �����˴ϴ�.");
                if (inventoryStatus.ingredientNumber[3] >= 1 && inventoryStatus.ingredientNumber[4] >= 1 && inventoryStatus.ingredientNumber[5] >= 1)
                {
                    inventoryStatus.ingredientNumber[3]--;
                    inventoryStatus.ingredientNumber[4]--;
                    inventoryStatus.ingredientNumber[5]--;
                    system("cls");
                    drawLine(0, 0, 74, 0, "��");
                    drawLine(0, 0, 0, 17, "��");
                    drawLine(74, 0, 74, 17, "��");
                    drawLine(0, 74, 74, 74, "��");
                    gotoxy(4, 4, "�ܽ��� �¹����� ��������ϴ�!");
                    inventoryStatus.diyNumber[6]++;
                    currentStatus.work--;
                    makingStatus.diyNumber++;
                }
                else
                    gotoxy(4, 4, "��ᰡ �����Ͽ� ������ ���մϴ�.");
            }
        }
        else if (i == 3)
            break;
        Sleep(1000);
    }
    if(currentStatus.work <=0){
        system("cls");
    drawLine(0, 0, 74, 0, "��");
    drawLine(0, 0, 0, 17, "��");
    drawLine(74, 0, 74, 17, "��");
    drawLine(0, 74, 74, 74, "��");
    gotoxy(4,2,"�� �̻� �۾��� ������ �� �����ϴ�. ���� �ھ� ���� �� �� �� ������ ����.");
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
        printf("�ȳ� ���� �߱����� �Ѿ��̾�! �� Ư��� ���� �߱�! Ȥ�� ���� �߱� �˾�?\n\n");
        printf("Ȥ�� �𸣴� �ֵ��� ���� �� �����ϱ� ���� �����ϰ� �˷��ٰ�!\n\n");
        printf("===============================RULE=================================\n");
        printf("1.������ ���ڸ� ���ھ�! 100~999�ȿ� ������ �ϳ��̰� �ʴ� �� ���ڸ� ���߸� �Ǵ°ž�!\n");
        printf("2.�ʰ� ���ڸ� ���ϸ� ���� �ڸ� ���ڿ� ���� �ڸ� ����, ���� �ڸ� ���� ������ ����\n");
        printf("�ڸ��� ���ڰ� ������ ��Ʈ����ũ! ���ڴ� ���ԵǴµ� �ڸ��� �ٸ��� ��! ���ڰ� ���ԾȵǸ� �ƿ�!\n");
        printf("3.���� ��� ������ 123�̰� �ʰ� ���� ���ڰ� 524��� 1��Ʈ����ũ 2�ƿ��� �Ǵ°ž�!\n");
        printf("���� 317�� ���Ѵٸ� 2�� 1�ƿ��� �ǰ���??\n");
        printf("\n7���ȿ� ����ٸ� ������ �־����ž�! �����鼭 �ϴ� ���� ��õ�Ұ�!, ���� ��������!!\n\n");
        printf("������ �����ϱ�?:");
        scanf("%d", &ans);
        while (cnt < 7)
        {
            if (ans == realnum && cnt < 7)
            {
                printf("�����̾�! %d������ ���ߴٴ� ����Ѱ�? ������ �޾ư�!", cnt + 1);
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
                printf("%d��Ʈ����ũ %d�� %d�ƿ�!\n\n", strike, ball, out);
                strike = 0;
                ball = 0;
                out = 0;
                cnt++;
                if (cnt >= 7)
                    break;
                printf("������ �����ϱ�?:");
                scanf("%d", &ans);
            }
        }
        printf("������ %d �̰ŷ� ���оߤФФ�\n", realnum);
        printf("7���� �Ѿ��°�? ��Ÿ������ ���оߤФФФ� ������ �ٶ󵵷�!");
        return 0;
    }
    else if (i == 2)
    {
        int num1, num2, ans;
        printf("����ȭ�鿡 ���� Ŭ�ι��� ������ Ȧ���ϱ��? �ƴϸ� ¦���ϱ��??\n\n");
        printf("����� � �ñ⼼��!!!\n\n");
        printf("����� �����?(Ȧ���� 1, ¦���� 2) : ");
        scanf("%d", &num1);
        printf("\n======================================\n");
        ans = rand() % 2 + 1;
        if (num1 == ans && num1 == 1)
        {
            printf("�� �� �� �� ��\n");
            printf("\n=====================================\n");
            printf("5���׿�! �����Դϴ�!!\n\n");
            printf("������ �ְڽ��ϴ�.");
            return 1;
        }
        else if (num1 == ans && num1 == 2)
        {
            printf("�� �� �� �� �� ��\n");
            printf("\n=====================================\n");
            printf("6���׿�! �����Դϴ�!!\n\n");
            printf("������ �ְڽ��ϴ�.");
            return 1;
        }
        else if (num1 != ans && num1 == 1)
        {
            printf("�� �� �� ��\n");
            printf("\n=====================================\n");
            printf("4���� ¦���׿�Ф� ������ �����ϼ���!");
            return 0;
        }
        else
        {
            printf("�� �� �� \n");
            printf("\n=====================================\n");
            printf("3���� Ȧ���׿�Ф� ������ �����ϼ���!");
            return 0;
        }
    }
    else
    {
        int ans, realday, num1, cnt = 0;
        realday = rand() % 31 + 1;
        printf("�ȳ� �� �̸��� ��������! 7���� ��Ŀ�� �Ѵٰ� ���� ����\n\n");
        printf("��ħ �� ���ϵ� 7���ε� �� ������ ���߾� ����? ��ȸ�� 4���̾�!\n\n");
        printf("�� ������ ���� �ϱ�?(1~31):");
        scanf("%d", &ans);
        while (cnt < 3)
        {
            if (ans == realday)
            {
                printf("\n�¾� �� ���� �� �����̾�!\n\n");
                printf("������ �޾ư�������!");
                return 1;
            }
            else if (ans > realday)
            {
                printf("\n�� ����ġ��� �� ���� ���� �ֳ�..\n\n");
                printf("�ٽ� �����!\n\n");
                printf("�� ������ ���� �ϱ�?(1~31):");
                scanf("%d", &ans);
                cnt++;
            }
            else
            {
                printf("\n�� ����ġ��� �� �̸� ���� �ֳ�..\n\n");
                printf("�ٽ� �����!\n\n");
                printf("�� ������ ���� �ϱ�?(1~31):");
                scanf("%d", &ans);
                cnt++;
            }
        }
        if (ans != realday)
        {
            printf("\n4�� �� Ʋ�ȳ� ������ %d���̾�!\n\n", realday);
            printf("Ʋ�����ϱ� ������ ����!");
            return 0;
        }
        else
        {
            printf("\n������ ��ȸ�� ���ߴٴ�!! �ƽ���.. ������!\n\n");
            printf("������ �޾ư����� ��!");
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
    drawLine(0, 0, 74, 0, "��");
    drawLine(0, 0, 0, 17, "��");
    drawLine(74, 0, 74, 17, "��");
    drawLine(0, 74, 74, 74, "��");
    drawModule(30,10,sleeping,3);
    currentStatus.day++;
    currentStatus.work = 5;
    Sleep(800);
    drawModule(30,10,wakedupClear,5);
    drawModule(30,8,wakedup,5);
    Sleep(500);
    return;
}
void achievement()
{
    system("cls");
    gotoxy(0, 0, "achievement");
    Sleep(1000);
    return;
}
void store() {
    if(!checkStatus()){
        return;
    }
    int menuChoose =28;
    int choice;
    int execute;
    system("cls");
    gotoxy(0, 0, "");
    drawModule(2, 14, character, 4);
    drawLine(0, 0, 74, 0, "��");
    drawLine(0, 0, 0, 17, "��");
    drawLine(74, 0, 74, 17, "��");
    drawLine(0, 74, 74, 74, "��");
    gotoxy(28, 22, "����");
    gotoxy(35, 22, "�۹�");
    gotoxy(42, 22, "DIY���");
    gotoxy(49, 22, "������");
    gotoxy(49, 25, "");
        printf("���� ��: %d", currentStatus.money);
    while (1) {
        gotoxy(menuChoose, 22, "");
        if (_kbhit()) {
            choice = _getch();
            if (choice != LEFT && choice != RIGHT && choice != ENTER) {
                continue;
            }
            if (choice == LEFT) {
                if (menuChoose > 28) {
                    menuChoose -= 7;
                }
            }
            else if (choice == RIGHT) {
                if (menuChoose < 49) {
                    menuChoose += 7;
                }
            }
            else {
                break;
            }
        }
    }
    switch (menuChoose) {
    case 28:
        system("cls");
        gotoxy(0, 0, "");
        drawModule(2, 14, character, 4);
        drawLine(0, 0, 74, 0, "��");
        drawLine(0, 0, 0, 17, "��");
        drawLine(74, 0, 74, 17, "��");
        drawLine(0, 74, 74, 74, "��");
        gotoxy(21, 22, "������");
        gotoxy(28, 22, "�����");
        gotoxy(35, 22, "���");
        gotoxy(42, 22, "�ܽ���");
        gotoxy(49, 22, "���Ƹ�");
        gotoxy(21, 23, "$100000");
        gotoxy(28, 23, "$100000");
        gotoxy(35, 23, "$100000");
        gotoxy(42, 23, "$100000");
        gotoxy(49, 23, "$100000");

        gotoxy(49, 25, "");
        printf("���� ��: %d", currentStatus.money);
        while (1) {
            gotoxy(menuChoose, 22, "");
            if (_kbhit()) {
                choice = _getch();
                if (choice != LEFT && choice != RIGHT && choice != ENTER) {
                    continue;
                }
                if (choice == LEFT) {
                    if (menuChoose > 21) {
                        menuChoose -= 7;
                    }
                }
                else if (choice == RIGHT) {
                    if (menuChoose < 49) {
                        menuChoose += 7;
                    }
                }
                else {
                    switch (menuChoose) {
                    case 21:
                        if (checkStatus()) {
                            if (currentStatus.money >= 100000) {
                                currentStatus.money -= 100000;
                                system("cls");
                                gotoxy(35, 25, "���ſϷ�");
                                inventoryStatus.animalNumber[0]++;
                            }
                            else {
                                printf("���� �����մϴ�.");
                            }
                            currentStatus.work--;
                            Sleep(1000);
                        }
                        break;

                    case 28:
                        if (checkStatus()) {
                            if (currentStatus.money >= 100000) {
                                currentStatus.money -= 100000;
                                system("cls");
                                gotoxy(35, 25, "���ſϷ�");
                                inventoryStatus.animalNumber[1]++;
                            }
                            else {
                                printf("���� �����մϴ�.");
                            }
                            currentStatus.work--;
                            Sleep(1000);
                        }
                        break;

                    case 35:
                        if (checkStatus()) {
                            if (currentStatus.money >= 100000) {
                                currentStatus.money -= 100000;
                                system("cls");
                                gotoxy(35, 25, "���ſϷ�");
                                inventoryStatus.animalNumber[2]++;
                            }
                            else {
                                printf("���� �����մϴ�.");
                            }
                            currentStatus.work--;
                            Sleep(1000);
                        }
                        break;

                    case 42:
                        if (checkStatus()) {
                            if (currentStatus.money >= 100000) {
                                currentStatus.money -= 100000;
                                system("cls");
                                gotoxy(35, 25, "���ſϷ�");
                                inventoryStatus.animalNumber[3]++;
                            }
                            else {
                                printf("���� �����մϴ�.");
                            }
                            currentStatus.work--;
                            Sleep(1000);
                        }
                        break;

                    case 49:
                        if (checkStatus()) {
                            if (currentStatus.money >= 100000) {
                                currentStatus.money -= 100000;
                                system("cls");
                                gotoxy(35, 25, "���ſϷ�");
                                inventoryStatus.animalNumber[4]++;
                            }
                            else {
                                printf("���� �����մϴ�.");
                            }
                            currentStatus.work--;
                            Sleep(1000);
                        }
                        break;

                    }
                    break;
                }

            }
        }
        break;
    case 35:
        system("cls");
        gotoxy(0, 0, "");
        drawModule(2, 14, character, 4);
        drawLine(0, 0, 74, 0, "��");
        drawLine(0, 0, 0, 17, "��");
        drawLine(74, 0, 74, 17, "��");
        drawLine(0, 74, 74, 74, "��");
        gotoxy(21, 22, "����丶��");
        gotoxy(28, 22, "����");
        gotoxy(35, 22, "����");
        gotoxy(42, 22, "����");
        gotoxy(49, 22, "�ϵ���");
        gotoxy(56, 22, "�ᳪ��");
        gotoxy(21, 23, "$30000");
        gotoxy(28, 23, "$30000");
        gotoxy(35, 23, "$30000");
        gotoxy(42, 23, "$30000");
        gotoxy(49, 23, "$30000");
        gotoxy(56, 23, "$30000");
        gotoxy(49, 25, "");
        printf("���� ��: %d", currentStatus.money);
        while (1) {
            gotoxy(menuChoose, 22, "");
            if (_kbhit()) {
                choice = _getch();
                if (choice != LEFT && choice != RIGHT && choice != ENTER) {
                    continue;
                }
                if (choice == LEFT) {
                    if (menuChoose > 21) {
                        menuChoose -= 7;
                    }
                }
                else if (choice == RIGHT) {
                    if (menuChoose < 56) {
                        menuChoose += 7;
                    }
                }
                else {
                    break;
                }
            }
        }
        switch (menuChoose) {
        case 21:
            if (checkStatus()) {
                if (currentStatus.money >= 30000) {
                    currentStatus.money -= 30000;
                    system("cls");
                    gotoxy(35, 25, "���ſϷ�");
                    inventoryStatus.plantNumber[0]++;
                }
                else {
                    printf("���� �����մϴ�.");
                }
                currentStatus.work--;
                Sleep(1000);
            }
            break;

        case 28:
            if (checkStatus()) {
                if (currentStatus.money >= 30000) {
                    currentStatus.money -= 30000;
                    system("cls");
                    gotoxy(35, 25, "���ſϷ�");
                    inventoryStatus.plantNumber[1]++;
                }
                else {
                    printf("���� �����մϴ�.");
                }
                currentStatus.work--;
                Sleep(1000);
            }
            break;

        case 35:
            if (checkStatus()) {
                if (currentStatus.money >= 30000) {
                    system("cls");
                    gotoxy(35, 25, "���ſϷ�");
                    inventoryStatus.plantNumber[2]++;
                    currentStatus.money -= 30000;
                }
                else {
                    printf("���� �����մϴ�.");
                }
                currentStatus.work--;
                Sleep(1000);
            }
            break;

        case 42:
            if (checkStatus()) {
                if (currentStatus.money >= 30000) {
                    currentStatus.money -= 30000;
                    system("cls");
                    gotoxy(35, 25, "���ſϷ�");
                    inventoryStatus.plantNumber[3]++;
                }
                else {
                    printf("���� �����մϴ�.");
                }
                currentStatus.work--;
                Sleep(1000);
            }
            break;

        case 49:
            if (checkStatus()) {
                if (currentStatus.money >= 30000) {
                    currentStatus.money -= 30000;
                    system("cls");
                    gotoxy(35, 25, "���ſϷ�");
                    inventoryStatus.plantNumber[4]++;
                }
                else {
                    printf("���� �����մϴ�.");
                }
                currentStatus.work--;
                Sleep(1000);
            }
            break;

        case 56:
            if (checkStatus()) {
                if (currentStatus.money >= 30000) {
                    currentStatus.money -= 30000;
                    system("cls");
                    gotoxy(35, 25, "���ſϷ�");
                    inventoryStatus.plantNumber[5]++;
                }
                else {
                    printf("���� �����մϴ�.");
                }
                currentStatus.work--;
                Sleep(1000);
            }
            break;

        }
        break;
    case 42:
        system("cls");
        gotoxy(0, 0, "");
        drawModule(2, 14, character, 4);
        drawLine(0, 0, 74, 0, "��");
        drawLine(0, 0, 0, 17, "��");
        drawLine(74, 0, 74, 17, "��");
        drawLine(0, 74, 74, 74, "��");
        gotoxy(14, 22, "����");
        gotoxy(21, 22, "ö");
        gotoxy(28, 22, "��");
        gotoxy(35, 22, "�ö�ƽ");
        gotoxy(42, 22, "����̹�");
        gotoxy(49, 22, "����");
        gotoxy(56, 22, "�������");
        gotoxy(49, 25, "");
        gotoxy(14, 23, "$20000");
        gotoxy(21, 23, "$20000");
        gotoxy(28, 23, "$10000");
        gotoxy(35, 23, "$20000");
        gotoxy(42, 23, "$30000");
        gotoxy(49, 23, "$10000");
        gotoxy(56, 23, "$10000");
        gotoxy(49, 25, "");
        printf("���� ��: %d", currentStatus.money);
        while (1) {
            gotoxy(menuChoose, 22, "");
            if (_kbhit()) {
                choice = _getch();
                if (choice != LEFT && choice != RIGHT && choice != ENTER) {
                    continue;
                }
                if (choice == LEFT) {
                    if (menuChoose > 14) {
                        menuChoose -= 7;
                    }
                }
                else if (choice == RIGHT) {
                    if (menuChoose < 56) {
                        menuChoose += 7;
                    }
                }
                else {
                    break;
                }
            }
        }
        switch (menuChoose) {
        case 14:
            if (checkStatus()) {
                if (currentStatus.money >= 20000) {
                    currentStatus.money -= 20000;
                    system("cls");
                    gotoxy(35, 25, "���ſϷ�");
                    inventoryStatus.ingredientNumber[0]++;
                }
                else {
                    printf("���� �����մϴ�.");
                }
                currentStatus.work--;
                Sleep(1000);
            }
            break;

        case 21:
            if (checkStatus()) {
                if (currentStatus.money >= 20000) {
                    currentStatus.money -= 20000;
                    system("cls");
                    gotoxy(35, 25, "���ſϷ�");
                    inventoryStatus.ingredientNumber[1]++;
                }
                else {
                    printf("���� �����մϴ�.");
                }
                currentStatus.work--;
                Sleep(1000);
            }
            break;

        case 28:
            if (checkStatus()) {
                if (currentStatus.money >= 10000) {
                    currentStatus.money -= 10000;
                    system("cls");
                    gotoxy(35, 25, "���ſϷ�");
                    inventoryStatus.ingredientNumber[2]++;
                }
                else {
                    printf("���� �����մϴ�.");
                }
                currentStatus.work--;
                Sleep(1000);
            }
            break;

        case 35:
            if (checkStatus()) {
                if (currentStatus.money >= 20000) {
                    currentStatus.money -= 20000;
                    system("cls");
                    gotoxy(35, 25, "���ſϷ�");
                    inventoryStatus.ingredientNumber[3]++;
                }
                else {
                    printf("���� �����մϴ�.");
                }
                currentStatus.work--;
                Sleep(1000);
            }
            break;

        case 42:
            if (checkStatus()) {
                if (currentStatus.money >= 30000) {
                    currentStatus.money -= 30000;
                    system("cls");
                    gotoxy(35, 25, "���ſϷ�");
                    inventoryStatus.ingredientNumber[4]++;
                }
                else {
                    printf("���� �����մϴ�.");
                }
                currentStatus.work--;
                Sleep(1000);
            }
            break;

        case 49:
            if (checkStatus()) {
                if (currentStatus.money >= 10000) {
                    currentStatus.money -= 10000;
                    system("cls");
                    gotoxy(35, 25, "���ſϷ�");
                    inventoryStatus.ingredientNumber[5]++;
                }
                else {
                    printf("���� �����մϴ�.");
                }
                currentStatus.work--;
                Sleep(1000);
            }
            break;

        case 56:
            if (checkStatus()) {
                if (currentStatus.money >= 10000) {
                    currentStatus.money -= 10000;
                    system("cls");
                    gotoxy(35, 25, "���ſϷ�");
                    inventoryStatus.ingredientNumber[6]++;
                }
                else {
                    printf("���� �����մϴ�.");
                }
                currentStatus.work--;
                Sleep(1000);
            }   
            break;
        }
    case 49: break;
        
    }
    return;
}
void inventory()
{
    system("cls");
    drawLine(0, 0, 74, 0, "��");
    drawLine(0, 0, 0, 17, "��");
    drawLine(74, 0, 74, 17, "��");
    drawLine(0, 74, 74, 74, "��");
    gotoxy(1,2,"<����>");
    for (int i = 0; i < 5; i++)
    {
        gotoxy(1+i*5,3, inventoryStatus.animal[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        gotoxy(1+i*5,4, "");
        printf("%d",inventoryStatus.animalNumber[i]);
    }

    gotoxy(1,6,"<�Ĺ�>");
    for (int i = 0; i < 5; i++)
    {
        gotoxy(1+i*5,7, inventoryStatus.plant[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        gotoxy(1+i*5,8, "");
        printf("%d",inventoryStatus.plantNumber[i]);
    }

    gotoxy(1,10,"<����ǰ>");
    for (int i = 0; i < 7; i++)
    {
        gotoxy(1+i*5,11, inventoryStatus.diy[i]);
    }
    for (int i = 0; i < 7; i++)
    {
        gotoxy(1+i*5,12, "");
        printf("%d",inventoryStatus.diyNumber[i]);
    }

    gotoxy(1,14,"<���>");
    for (int i = 0; i < 7; i++)
    {
        gotoxy(1+i*5,15, inventoryStatus.ingredient[i]);
    }
    for (int i = 0; i < 7; i++)
    {
        gotoxy(1+i*5,16, "");
        printf("%d",inventoryStatus.ingredientNumber[i]);
    }
    
    gotoxy(0,20,"�ƹ�Ű�� �����ʽÿ�...");
    
    while(!_kbhit());
    getchar();
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
    currentStatus.money = 100000;

    inventoryStatus.animal[0] = "������";
    inventoryStatus.animal[1] = "�����";
    inventoryStatus.animal[2] = "���";
    inventoryStatus.animal[3] = "�ܽ���";
    inventoryStatus.animal[4] = "���Ƹ�";
    inventoryStatus.plant[0] = "����丶��";
    inventoryStatus.plant[1] = "����";
    inventoryStatus.plant[2] = "����";
    inventoryStatus.plant[3] = "�ϵ���";
    inventoryStatus.plant[4] = "�ᳪ��";
    inventoryStatus.diy[0] = "��ġ";
    inventoryStatus.diy[1] = "��";
    inventoryStatus.diy[2] = "ȣ��";
    inventoryStatus.diy[3] = "����";
    inventoryStatus.diy[4] = "ĹŸ��";
    inventoryStatus.diy[5] = "�̱۷�";
    inventoryStatus.diy[6] = "�¹���";
    inventoryStatus.ingredient[0] = "����" ;
    inventoryStatus.ingredient[1] = "ö" ;
    inventoryStatus.ingredient[2] = "��" ;
    inventoryStatus.ingredient[3] = "�ö�ƽ" ;
    inventoryStatus.ingredient[4]= "����̹�" ;
    inventoryStatus.ingredient[5] = "����" ;
    inventoryStatus.ingredient[6] = "�������" ;



    inventoryStatus.animalNumber[0] = 0;
    inventoryStatus.animalNumber[1] = 0;
    inventoryStatus.animalNumber[2] = 0;
    inventoryStatus.animalNumber[3] = 0;
    inventoryStatus.animalNumber[4] = 0;
    inventoryStatus.plantNumber[0] = 0;
    inventoryStatus.plantNumber[1] = 0;
    inventoryStatus.plantNumber[2] = 0;
    inventoryStatus.plantNumber[3] = 0;
    inventoryStatus.plantNumber[4] = 0;
    inventoryStatus.diyNumber[0] = 0;
    inventoryStatus.diyNumber[1] = 0;
    inventoryStatus.diyNumber[2] = 0;
    inventoryStatus.diyNumber[3] = 0;
    inventoryStatus.diyNumber[4] = 0;
    inventoryStatus.diyNumber[5] = 0;
    inventoryStatus.diyNumber[6] = 0;
    inventoryStatus.ingredientNumber[0] = 0;
    inventoryStatus.ingredientNumber[1] = 0;
    inventoryStatus.ingredientNumber[2] = 0;
    inventoryStatus.ingredientNumber[3] = 0;
    inventoryStatus.ingredientNumber[4] = 0;
    inventoryStatus.ingredientNumber[5] = 0;
    inventoryStatus.ingredientNumber[6] = 0;
}

void title() 
{
    gotoxy(0, 0, "");
    drawLine(0, 0, 74, 0, "��");
    drawLine(0, 0, 0, 17, "��");
    drawLine(74, 0, 74, 17, "��");
    drawLine(0, 74, 74, 74, "��");

    gotoxy(10, 5, "                  ###      ##     #######   ##        #####      ##      #####    ##       ");
    gotoxy(10, 6, "                #######    ##           #   ##     ###     ###   ##        ###    ##       ");
    gotoxy(10, 7, "                 ###       ##     #######   ##     ###     ###   ##      ##  ##   ##       ");
    gotoxy(10, 8, "                ##  ##     ##     #         ##     ###     ###   ##     ##    ##  ##       ");
    gotoxy(10, 9, "                 ###       ##     #######   ##        #####      ##                        ");
    gotoxy(10, 10, "                   ########                                      ##       ###   ###        ");
    gotoxy(10, 11, "                          #          ######       ##################      ###   ###        ");
    gotoxy(10, 12, "                   ########         ##    ##                     ##       #########        ");
    gotoxy(10, 13, "                   #                ##    ##                     ##       ###   ###        ");
    gotoxy(10, 14, "                   ########          ######                      ##       #########        ");

    while (!_kbhit())
    {
        gotoxy(7, 16, "                             <      PRESS      ENTER      KEY      TO      START      >    ");
        Sleep(400);
        gotoxy(7, 16, "                                                                                         ");
        Sleep(400);
    }
}

void story()
{

    gotoxy(4, 1, "INTRO...");
        Sleep(100);
        gotoxy(4, 3, "�ȳ��ϼ���! ������ ���� ���� ���� ȯ���մϴ�!");
        Sleep(300);
        gotoxy(4, 5, "������ ������ ������, ������ �������� ���� �������� Ȱ���� �غ�Ǿ� �ֽ��ϴ�.");
        Sleep(300);
        gotoxy(4, 7, "�پ��� ���� Ű���, �۹� Ű������ diy, ���ӱ���!!!");
        Sleep(300);
        gotoxy(4, 9, "�� �� Ȱ���� �� ������ ü�� 1�� �����ǰ�, ��� ü���� �����Ǹ� ���� ��ϴ�! ");
        Sleep(300);
        gotoxy(4, 11, "�������� �Ǹ� �ٽ� ü���� �����Ǿ� �ٽ� Ȱ���� �� �� �ֽ��ϴ�.");
        Sleep(300);
        gotoxy(4, 13, "���� ȣ���� max�� �Ǹ� �پ��� event�� �غ�Ǿ� ������ ���ϸ��� ������ �� �����ּ���!");
        Sleep(300);
        gotoxy(4, 15, "�����̳� �۹� Ű��⸦ ���� ���� ������ ������ ���� diy�� ���� �� �ֽ��ϴ�!");
        Sleep(200);
        gotoxy(4, 17, "���� �� ��� ������ �޼��ϸ� ������ �Ϸ�˴ϴ�!");
        Sleep(200);
        gotoxy(4, 19, "�׷� ���� ������ �����մϴ�!");
        Sleep(100);
        gotoxy(4, 21, "�ƹ�Ű�� �����ʽÿ�...");
}