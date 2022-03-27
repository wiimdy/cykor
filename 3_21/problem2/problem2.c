//gcc problem2.c -o problem2 -fno-stack-protector -no-pie -z execstack -mpreferred-stack-boundary=2 -m32
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char buf[256];

    memset(buf, 0, sizeof(buf));
    setvbuf(stdin, 0, 2, 0);
    setvbuf(stdout, 0, 2, 0);
    
    printf("buf = (%p)\n", buf);
    gets(buf);

    return 0;
} 
    