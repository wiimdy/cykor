//gcc problem1.c -o problem1 -fno-stack-protector -no-pie
#include <stdio.h>
#include <stdlib.h>

int helper(){
    char *bash[] = {"/bin/sh", 0};
    execve(bash[0], &bash, 0);
}

int main(){
    int secret = 0xdeadbeef;
    char buf[128];

    setvbuf(stdin, 0, 2, 0);
    setvbuf(stdout, 0, 2, 0);

    scanf("%s", &buf);

    if (secret != 0xdeadbeef){
        printf("No hack.");
        exit(1);
    }

    return 0;
}