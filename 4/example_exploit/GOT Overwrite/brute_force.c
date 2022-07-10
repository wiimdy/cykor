// gcc brute_force.c -o brute_force -fno-stack-protector -no-pie -z relro -m32
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char comment[0x50];

void init(){
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}

int main(){
    unsigned int *addr;
    unsigned int value;

    init();

    printf("addr : ");
    scanf("%u", &addr);
    printf("value : ");
    scanf("%u", &value);

    *addr = value;

    printf("Any comment? ");
    read(STDIN_FILENO, comment, sizeof(comment));

    printf("Your Comment : ");
    puts(comment);

    return 0;
}