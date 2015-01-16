#include <stdio.h>
#include <stdlib.h>

int	checkEndian();

int main(void)
{
	int i;
	i = checkEndian();
	if (i)
		printf("Little_endian\n");
	else
		printf("Big_endian\n");
}

int checkEndian()
{
	union check
	{
		int i;
		char ch;
	}c;
	c.i = 1;
	return(c.ch==1);
}