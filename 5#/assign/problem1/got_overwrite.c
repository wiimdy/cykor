// gcc got_overwrite.c -o got_overwrite -no-pie -fno-PIE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int gift(){
    char *bash[] = {"/bin/sh", 0};
    execve(bash[0], &bash, 0);
}

void init(){
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
}

int main(){
    unsigned long long *addr;
    unsigned long long value;

    init();

    puts("Arbitary-Address-Write");
    printf("addr: ");
    scanf("%llu", &addr);
    printf("value: ");
    scanf("%llu", &value);
    printf("[%p] = %llu\n", addr, value);
    *addr = value;

    puts("bye");
    return 0;
}