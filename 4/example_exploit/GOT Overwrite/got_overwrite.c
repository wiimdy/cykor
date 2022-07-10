// gcc got_overwrite.c -o got_overwrite -fno-stack-protector -no-pie -z relro
#include <stdio.h>
#include <stdlib.h>

void init(){
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}

void getshell(){
    system("/bin/sh");
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

    puts("bye!");

    return 0;
}
