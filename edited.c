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
} currentStatus = {5, 1,0};

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
    int data;
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
    char* animal[5];
    char* plant[5];
    char* diy[4];
    char* ingredient[7];
} storeStatus = {0};

struct i
{
    char* animal[5];
    char* animalNumber[5];
    char* plant[5];
    char* plantNumber[5];
    char* diy[4];
    char* diyNumber[4];
    char* ingredient[7];
    char* ingredientNumber[7];  
} inventoryStatus = {
    .animalNumber = {0,},
    .plantNumber = {0,},
    .diyNumber = {0,},
    .ingredientNumber = {0,},
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
void drawLine(int x1,int y1, int x2,int y2, const char *symbol);
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

char *character[4]={"\\(*_*)","(   (>","(   )","/   \\"};
char *characterClear[4]={"       ","       ","       ","       "};

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
    while (1){
        mainMenu();
        while (1){
            gotoxy(menuChoose, 22, "");
            if (_kbhit()){  
                choice = _getch();
                if (choice != LEFT && choice != RIGHT && choice != ENTER){
                    continue;
                }
                if (choice == LEFT){
                    if (menuChoose > 0){
                        menuChoose -= 7;
                        start--;
                    }
                }
                else if (choice == RIGHT){
                    if (menuChoose < 56){
                        menuChoose += 7;
                        start++;
                    }
                }
                else{
                    switch (menuChoose){
                    case 0:
                        if(checkStatus()){
                            animalGrowth();
                        }
                        break;

                    case 7:
                        if(checkStatus()){
                            plantGrowth();
                        }
                        break;

                    case 14:
                        if(checkStatus()){
                            making();    
                        }
                        break;

                    case 21:
                        if(checkStatus()){
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
    gotoxy(0,0,"");
    drawModule(2,14,character,4);
    drawLine(0,0,74,0,"■");
    drawLine(0,0,0,17,"■");
    drawLine(74,0,74,17,"■");
    drawLine(0,74,74,74,"■");
    
    gotoxy(0, 20, "오늘은 무엇을 할까?? (선택후 enter!) ");
        for (int i = 0; i < currentStatus.work; i++)
            printf("♥");
        for (int i = 0; i < 5 - currentStatus.work; i++)
            printf("♡");
        printf("  현재 잔액: %d",currentStatus.money);
        printf("  DAY %d", currentStatus.day);
        gotoxy(0, 22, "동물키우기");
        gotoxy(7, 22, "식물기르기");
        gotoxy(14, 22, "DIY");
        gotoxy(21, 22, "게임");
        gotoxy(28, 22, "잠자기");
        gotoxy(35, 22,"업적");
        gotoxy(42, 22, "상점");
        gotoxy(49, 22, "인벤토리");
        gotoxy(56,22, "저장 후 종료");
}
int checkStatus()
{
    if(currentStatus.work <= 0){
        gotoxy(0, 0, "더 이상 작업을 실행할 수 없습니다. 잠을 자야 일을 더 할 수 있을것 같네.");
        Sleep(1000);
        return 0;     
    } else {
        return 1;
    }
}
void loadData(){
    FILE *fp;
    fopen_s(&fp,FILENAME,"r");
    if(fp == NULL){
        fopen_s(&fp,FILENAME,"w");
        fwrite(&currentStatus,sizeof(struct cs),1,fp);
        fwrite(&animalStatus,sizeof(struct as),1,fp);
        fwrite(&plantStatus,sizeof(struct ps),1,fp);
        fwrite(&makingStatus,sizeof(struct m),1,fp);
        fwrite(&storeStatus,sizeof(struct s),1,fp);
        fwrite(&achievementStatus,sizeof(struct a),1,fp);
        fwrite(&gameStatus,sizeof(struct g),1,fp);
        fwrite(&inventoryStatus,sizeof(struct i),1,fp);
    } else {
        fread(&currentStatus,sizeof(struct cs),1,fp);
        fread(&animalStatus,sizeof(struct as),1,fp);
        fread(&plantStatus,sizeof(struct ps),1,fp);
        fread(&makingStatus,sizeof(struct m),1,fp);
        fread(&storeStatus,sizeof(struct s),1,fp);
        fread(&achievementStatus,sizeof(struct a),1,fp);
        fread(&gameStatus,sizeof(struct g),1,fp);
        fread(&inventoryStatus,sizeof(struct i),1,fp);
    }
    fclose(fp);
}
void saveData(){
    FILE *fp;
    fopen_s(&fp,FILENAME,"w");
    fwrite(&currentStatus,sizeof(struct cs),1,fp);
    fwrite(&animalStatus,sizeof(struct as),1,fp);
    fwrite(&plantStatus,sizeof(struct ps),1,fp);
    fwrite(&makingStatus,sizeof(struct m),1,fp);
    fwrite(&storeStatus,sizeof(struct s),1,fp);
    fwrite(&achievementStatus,sizeof(struct a),1,fp);
    fwrite(&gameStatus,sizeof(struct g),1,fp);
    fwrite(&inventoryStatus,sizeof(struct i),1,fp);
    fclose(fp);
}
void drawLine(int x1,int y1, int x2,int y2, const char *symbol){
    if(x1 == x2){
        for(int i = y1; i <= y2; i++){
            gotoxy(x1,i,symbol);
        }
    } else {
        for(int i = x1; i<=x2; i++){
            gotoxy(i,y1,symbol);
        }
    }
}
void drawModule(int x, int y, const char *symbol[], int size){
    for(int i = 0; i<size; i++){
        gotoxy(x,y+i,symbol[i]);
    }
}


void animalGrowth()
{
    system("cls");
    gotoxy(0, 0, "animalGrowth");
    currentStatus.work --;
    Sleep(1000);
    return;
}
void plantGrowth()
{
    system("cls");
    gotoxy(0, 0, "plantGrowth");
    currentStatus.work --;
    Sleep(1000);
    return;
}
void making()
{
    system("cls");
    gotoxy(0, 0, "making");
    currentStatus.work --;
    Sleep(1000);
    return;
}
void game(){
     system("cls");
    gotoxy(0, 0, "game");
    currentStatus.work --;
    currentStatus.money += 30000;
    Sleep(1000);
    return;
}
void sleep(){
    system("cls");
    gotoxy(0, 0, "sleep");
    currentStatus.day ++;
    currentStatus.work = 5;
    Sleep(1000);
    return;
} 
void achievement(){
    system("cls");
    gotoxy(0, 0, "achievement");
    Sleep(1000);
    return;
}
void store(){
    system("cls");
    gotoxy(0, 0, "store");
    currentStatus.work --;
    Sleep(1000);
    return;
}
void inventory(){
    system("cls");
    gotoxy(0,0,"");
    for(int i = 0; i<6; i++){
        printf("%d",inventoryStatus.animalNumber[i]);
    }
    Sleep(1000);
    return;
    
}
void saveAndExit(){
    system("cls");
    gotoxy(0, 0, "saveAndExit");
    saveData();
    Sleep(1000);
    exit(0);
    return;
}

void initialize(){
    storeStatus.animal[0] = "강아지";
    storeStatus.animal[1] = "고양이";
    storeStatus.animal[2] = "펭귄";
    storeStatus.animal[3] = "햄스터";
    storeStatus.animal[4] = "병아리";

    storeStatus.plant[0] = "방울토마토";
    storeStatus.plant[1] = "고추";
    storeStatus.plant[2] = "상추";
    storeStatus.plant[3] = "완두콩";
    storeStatus.plant[4] = "콩나물";

    storeStatus.ingredient[0] = "나무" ;
    storeStatus.ingredient[1] = "철" ;
    storeStatus.ingredient[2] = "못" ;
    storeStatus.ingredient[3] = "플라스틱" ;
    storeStatus.ingredient[4]= "드라이버" ;
    storeStatus.ingredient[5] = "나사" ;
    storeStatus.ingredient[6] = "얼음덩어리" ;


}

