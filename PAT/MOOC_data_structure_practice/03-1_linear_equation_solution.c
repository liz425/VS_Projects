#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double polynomial(double *a, double x);
int main(void)
{
	double coef[4];
	int i = 4;
	while (i--)
	{
		scanf("%lf", &coef[i]);
	}
	double a, b;
	scanf("%lf", &a);
	scanf("%lf", &b);
	while (fabs(polynomial(coef, a) - polynomial(coef, b)) > 0.001)
	{
		double mid = polynomial(coef, (a + b) / 2);
		if (mid == 0)
		{
			printf("%.2lf", (a + b)/2);
			return 0;
			break;
		}
		else if (polynomial(coef,a)*mid > 0)
		{
			a = (a + b) / 2;
		}
		else
		{
			b = (a + b) / 2;
		}
	}
	printf("%.2lf", (a + b) / 2);
	system("pause");
	return 0;
}

double polynomial(double *a, double x)
{
	return ((a[3]*x+a[2])*x+a[1])*x+a[0];
}
