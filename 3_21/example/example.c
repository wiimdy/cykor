//gcc test.c -o test -fno-stack-protector -no-pie -mpreferred-stack-boundary=2 -m32 
#include <stdio.h>

int helper(){
    char *bash[] = {"/bin/sh", 0};
    execve(bash[0], &bash, 0);
}

int main(){
    char buf[64];

    scanf("%s", &buf);

    return 0;
}