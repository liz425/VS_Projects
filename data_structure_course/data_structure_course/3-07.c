#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double prefixEvalue(void);
int main(void)
{
	double ans;
	ans = prefixEvalue();
	printf("%.1lf\n", ans);
	//system("pause");
}

double prefixEvalue(void)
{
	double a, b;
	char *opt = malloc(30);
	scanf("%s", opt);
	if (strlen(opt) == 1){
		switch (*opt)
		{
		case '+':return prefixEvalue() + prefixEvalue();
		case '-':return prefixEvalue() - prefixEvalue();
		case '*':return prefixEvalue() * prefixEvalue();
		case '/':
				{
					a = prefixEvalue();
					b = prefixEvalue();
					if (b)
						return a / b;
					else
					{
						printf("ERROR\n");
						//system("pause");
						exit(0);
					}
				}
		default: return	atof(opt);
		}
	}
	else
	{
		return atof(opt);
	}
}