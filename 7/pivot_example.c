//gcc -z execstack -fno-stack-protector -no-pie -o pivot_example pivot_example.c
#include <unistd.h>
#include <stdio.h>

void	vulnerable(void)
{
	char	buf[0x100];

	printf("%p\n", buf);
	read(0, buf, 0x100 + 8); 
}

int main(void)
{
	int	i;

	i = 0;
	vulnerable();
}