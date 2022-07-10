// gcc rop.c -o rop -fno-stack-protector -z noexecstack
#include <stdio.h>
#include <stdlib.h>

char * bin = "/bin/sh\x00";

void tool(){

    __asm__("pop %rdx;"
            "ret;");
    __asm__("pop %rcx;"
            "ret;");
    __asm__("pop %r8;"
            "ret;");

    return;
}

int main() {
    char buffer[20];

    printf("printf Function is at: %p\n", printf);

    gets(buffer);
    return 0;
}
