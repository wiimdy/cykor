//gcc -o rop_master rop_master.c -fno-stack-protector -Wl,-z,relro,-z,now -no-pie
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char name[0x1000] = {0,};

int main(){
    char buf[0x100];

    write(1, "Your name : ", 12);
    read(0, &name, 0x1000);

    write(1, "Can you rop it?\n", 16);
    read(0, &buf, 0x110);
    return 0;
}