//gcc -no-pie -fno-stack-protector -z relro -z now -o pivot2 pivot2.c
#include <stdio.h>
#include <unistd.h>

void	vulnerable(void)
{
	char	buf[0x100];
	
	printf("%p\n", buf);
	read(0, buf, 0x100 + 2);
}

int	main(void)
{
	int	i;

    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
	i = 314;
	vulnerable();
}