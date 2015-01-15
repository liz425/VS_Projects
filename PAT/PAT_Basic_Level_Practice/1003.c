#include<stdio.h>
#include<stdlib.h>

int PAT_test(void);

int main(void)
{
	int i, n;
	int ans_buf[10];
	scanf("%d",&n);
	getchar();    //remove '\n' after n
	for (i = 0; i < n; i++)
	{
		ans_buf[i] = PAT_test();
	}
	for (i = 0; i < n; i++)
	{
		if (ans_buf[i])
			printf("%s\n", "YES");
		else
			printf("%s\n", "NO");
	}
}

int PAT_test(void)
{
	char chr;
	int a=0, b=0, c=0; //number of 'A' in :aPbTc
	int p=0, t=0;    //
	int flag = 1;  //flag==1, YES  flag==0,NO
	chr = 'A';
	while ((chr!='\n')&&(chr!=' '))
	{
		chr = getchar();
		if ((chr == '\n') || (chr == ' '))
			continue;
		else if (flag == 0)
			continue;
		else if (chr == 'P')
		{
			if (t == 0)
				p += 1;
			else
			{
				flag = 0;
				continue;
			}
		}
		else if (chr == 'T')
		{
			if (p == 1)
				t += 1;
			else
			{
				flag = 0;
				continue;
			}
		}
		else if (chr == 'A')
		{
			if (p == 0 && t == 0)
				a += 1;
			else if (p == 1&& t == 0)
				b += 1;
			else
				c += 1;
		}
		else
			flag = 0;
	}
	if (p == 1 && t == 1)
	{
		if (b == 0)
			flag = 0;
		else if (c != a*b)
			flag = 0;
	}
	else
		flag = 0;
	return flag;
}