//gcc problem3.c -o problem3 -no-pie
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <time.h>

int money = 100;

void init(){
    srand(time(NULL));
    setvbuf(stdin, 0, 2, 0);
    setvbuf(stdout, 0, 2, 0);
}

void start_game(){
    int betting_money;
    int select;

    int random = rand();

    printf("Betting money: ");
    scanf("%d", &betting_money);

    if (betting_money > money){
        printf("Not enough money...\n");
        return 0;
    }

    printf("(1)Holl, (2)JJAK: ");
    scanf("%d", &select);

    if (select == 1){
        if (random % 2 == 1){
            money += betting_money * 2;
            printf("WIN!!\n");
        }
        else{
            money -= betting_money;
            printf("LOSE!!\n");
        }
    }
    else if (select == 2){
        if (random % 2 == 0){
            money += betting_money * 2;
            printf("WIN!!\n");
        }
        else{
            money -= betting_money;
            printf("LOSE!!\n");
        }
    }
    else {
        printf("Input Wrong...\n");
        return 0;
    }

}

void view_money(){
    printf("Your current money is %d\n", money);
}

void buy_shell(){
    if (money >= 10000000){
        printf("Great!!\n");
        system("/bin/sh");
    }
    else{
        printf("Not enough money...\n");
    }
}

int main(int argc, char *argv[]) {
    int num;

    while(1){
        printf("==============\n");
        printf("Holl-JJAK Game\n");
        printf("==============\n");
        printf("1. Start game\n");
        printf("2. View money\n");
        printf("3. Buy shell\n");
        printf("4. exit\n");
        printf("==============\n>>>");

        scanf("%d", &num);

        switch(num){
            case 1: start_game(); break;
            case 2: view_money(); break;
            case 3: buy_shell(); break;
            case 4: return 0;
            default: break;
        }
    }
    

}
    