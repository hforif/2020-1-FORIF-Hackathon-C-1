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
