// gcc simple_pie_32.c -o simple_pie_32 -fno-stack-protector -z noexecstack -m32
#include <stdio.h>
#include <stdlib.h>

int main() {
    vuln();
    return 0;
}

void vuln() {
    char buffer[20];

    printf("Main Function is at: %#lx\n", main);

    gets(buffer);
}

void win() {
    puts("PIE bypassed! Great job :D");
    system("/bin/sh");
}
