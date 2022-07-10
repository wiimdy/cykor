// gcc shellcode.c -o shellcode_x86 -fno-stack-protector -no-pie -z execstack -mpreferred-stack-boundary=2 -m32
#include <stdio.h>
#include <unistd.h>

int main(){
    void (*shellcode)();
    char input[0x100];

    read(STDIN_FILENO, input, 0x100);
    shellcode = input;
    shellcode();

    return 0;
}