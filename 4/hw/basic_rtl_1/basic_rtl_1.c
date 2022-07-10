// gcc basic_rtl_1.c -o basic_rtl_1 -fno-stack-protector -mpreferred-stack-boundary=2 -no-pie -z relro -m32
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void alarm_handler() {
    exit(-1);
}

void init(){
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
    signal(SIGALRM, alarm_handler);
    alarm(30);
}

enum {PING, IFCONFIG, DATE, ID, PS};
char name[0x40];
char* cmd[5] = {
        "ping 127.0.0.1 -c 3",
        "ifconfig",
        "date",
        "id",  
        "ps"
    };

void gift(int idx){
    system(cmd[idx]);
}

int main(int argc, char* argv[]) {
    char command[0x10];

    init();

    printf("what is your name? : ");
    scanf("%s", name);

    puts("what do you want?");
    puts("1. ping 127.0.0.1 -c 3");
    puts("2. ifconfig");
    puts("3. date");
    puts("4. id");
    puts("5. ps");
    printf("> ");
    scanf("%s", command);

    if (!strcmp("ping", command)){
        gift(PING);
    } 
    else if (!strcmp("ifconfig", command)){
        gift(IFCONFIG);
    }
    else if (!strcmp("date", command)){
        gift(DATE);
    }
    else if (!strcmp("id", command)){
        gift(ID);
    }
    else if (!strcmp("ps", command)){
        gift(PS);
    }
    else {
        puts("Invalid command :(");
    }

    return 0;
}