// gcc plt_got.c -o plt_got -fno-stack-protector -no-pie -z relro -fcf-protection=none
#include <stdio.h>

int main(){
    puts("call _dl_runtime_resolve");
    puts("call real printf");

    return 0;
}