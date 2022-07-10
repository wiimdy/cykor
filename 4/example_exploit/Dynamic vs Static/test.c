// gcc test.c -o dynamic -fno-stack-protector -no-pie -mpreferred-stack-boundary=2 -m32
// gcc test.c -o static -fno-stack-protector -no-pie -mpreferred-stack-boundary=2 -m32 -static
#include <stdio.h>

int sum(int x, int y){
    return x + y;
}

int main(){
    int a = sum(3, 5);
    printf("%d", a);
    return 0;
}