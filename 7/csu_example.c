//gcc -no-pie -fno-stack-protector -z relro -z now -o csu_example csu_example.c
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	char	buf[0x100];

	setvbuf(stdin, 0, 2, 0);
	setvbuf(stdout, 0, 2, 0);
	write(1, "hello\n", 6);
	read(0, buf, 0x200);
	return (0);
}