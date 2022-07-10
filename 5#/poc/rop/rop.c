// Compile: gcc -o rop rop.c -fno-PIE -no-pie -fno-stack-protector
#include <stdio.h>
#include <unistd.h>
int main() {
  char buf[0x10];
  
  puts("hello");
  gets(buf);

  puts(buf);
  return 0;
}