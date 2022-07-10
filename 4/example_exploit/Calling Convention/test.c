// gcc test.c -o test -fno-stack-protector -mpreferred-stack-boundary=2 -no-pie -m32
#include <stdio.h>

int sum(int x, int y){
    return x + y;
}

int main(){
    int a = sum(3, 5);
    printf("%d", a);
    return 0;
}