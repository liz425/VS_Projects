#include<stdio.h>
#include<stdlib.h>

//PAT Adcanced Level 1002: A + B For Polynominal
int read_poly(double in[])
{
	int i, N;
	int index = 0;
	scanf("%d", &N);
	for (i = 0; i < N; i++)
	{
		int expo;
		double coef;
		scanf("%d%lf", &expo, &coef);
		in[expo] = coef;
		if (i == 0)
			index = expo;
	}
	return index;
}

int main(void)
{
	double a[1001] = { 0 };
	double b[1001] = { 0 };
	int index_a = read_poly(a);
	int index_b = read_poly(b);
	int index_max = index_a > index_b ? index_a : index_b;
	int i, cnt = 0;
	for (i = index_max; i >=0; i--)
	{
		a[i] = a[i] + b[i];
		if (a[i] != 0)
			cnt++;
	}
	printf("%d", cnt);
	for (i = index_max; i >= 0; i--)
	{
		if (a[i] != 0)
			printf(" %d %.1lf", i, a[i]);
	}

	//system("pause");
	return 0;
}