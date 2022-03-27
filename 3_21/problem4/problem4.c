//gcc problem4.c -o problem4 -fno-stack-protector -mpreferred-stack-boundary=2 -no-pie -m32
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void helper(){
    system("/bin/sh");
}

int main(){
    int fd;
    char name[64];
    char logo[512];
    int num;

    setvbuf(stdin, 0, 2, 0);
    setvbuf(stdout, 0, 2, 0);

    fd = open("logo.txt", 0);

    if(fd == -1){
        printf("File error.\n");
        exit(1);
    }

    while(1){
        printf("==================================================\n");
        printf("1. Input name\n");
        printf("2. Print logo\n");
        printf("3. Quit\n");
        printf("==================================================\n>>> ");
        scanf("%d", &num);

        switch(num){
            case 1:
                printf("Input name: ");
                scanf("%64s", &name);
                break;
            case 2:
                read(fd, logo, 0x400);
                printf("%s\n", logo);
                break;
            case 3:
                printf("Bye!\n");
                return 0;
                break;
            default:
                printf("No!\n");
                exit(1);
                break;
        }
    }
}
