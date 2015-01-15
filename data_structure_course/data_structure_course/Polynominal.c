#include <stdio.h>
#include <time.h>
#include <math.h>

#define MAX_N 101
#define REPEAT 1e6

clock_t start, stop;
double ClockTicks;

double Fun1(int n, double a[], double x);
double Fun2(int n, double a[], double x);

int main()
{
	// Create the polynomial
	double a[MAX_N];
	int i;
	int	j;
	a[0] = 1;
	for (i = 1; i < MAX_N; i++)
		a[i] = 1 / i;

	//The slower way to calculate the value
	start = clock();
	for (j = 0; j < REPEAT; j++){
		Fun1(MAX_N, a, 1.1);
	}
	stop = clock();
	ClockTicks = (double)(stop - start);
	printf("ClockTicks 1 = %f\n", ClockTicks);
	printf("Time 1 = %6.2e\n", ClockTicks / CLOCKS_PER_SEC);

	//The better way to calculate the value
	start = clock();
	for (j = 0; j < REPEAT; j++){
		Fun2(MAX_N, a, 1.1);
	}
	stop = clock();
	ClockTicks = (double)(stop - start);
	printf("ClockTicks 1 = %f\n", ClockTicks);
	printf("Time 1 = %6.2e\n", ClockTicks / CLOCKS_PER_SEC);
	//system("pause");
}

double Fun1(int n, double a[], double x)
{
	double value = a[0];
	int i;
	for (i = 1; i < n; i++)
		value += a[i] * pow(x, i);
	return value;
}

double Fun2(int n, double a[], double x)
{
	double value = a[n - 1];
	int i;
	for (i = n - 1; i > 0; i--)
		value = a[i - 1] + value * x;
	return value;
}