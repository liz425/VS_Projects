#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<pthread.h>

#define THREAD_NUM 50
#define SAMPLE_NUM 1

FILE *fp;
FILE *fp2;
char S[100001];
int P, Q, N;
int lengthP;
//__int64 f;  //%I64d
int loopend[100000] = { 0 };
int ans[100000] = { 0 };
int remainder[100000] = { 0 };
int out_loop = 0;
int up_bdy = 0;
int bottom_bdy;
clock_t start, stop;

void f_initial(int bottom, int up)
{
	int i, j;
	for (i = bottom; i <= up; i++)
	{
		long f = 0;
		int break_flag = 0;
		for (j = i; j < N; j++)
		{
			f = (f * 10 + (int)S[j] - 48) % P;
			if (f == 0)
			{
				loopend[i] = j;
				break_flag = 1;
				break;
			}
		}
		if (!break_flag)
		{
			loopend[i] = -(up);
			remainder[i] = f;
		}
	}
}

void* inquire(void *pArg)
{
	int b = *((int *)pArg);
	int e = *((int *)pArg + 1);
	int ans_index = *((int *)pArg + 2);
	int out = *((int *)pArg + 3);
	int i, j;
	int cnt_final = 0;
	long f;
	long loopfinal[100000] = { 0 };
	if (b < bottom_bdy)
	{
		f_initial(b, bottom_bdy - 1);
		bottom_bdy = b;
	}
	if (e > up_bdy)
	{
		f_initial(up_bdy + 1, e);
		up_bdy = e;
	}
	for (i = e - 1; i >= b - 1; i--)
	{
		if ((loopend[i] > 0) && (loopend[i] <= e - 1))
		{
			loopfinal[i] = loopfinal[loopend[i] + 1] + 1;
			cnt_final = loopfinal[i] + cnt_final;
			continue;
		}
		else if ((loopend[i] <= -(e - 1)) || (loopend[i] > e - 1))
		{
			continue;
		}
		else
		{
			f = remainder[i];
			//f = 0;
			for (j = 1 - loopend[i]; j <= e - 1; j++)
			//for (j = i; j <= e - 1; j++)
			{
				f = (f * 10 + (int)S[j] - 48) % P;
				if (f == 0)
				{
					loopend[i] = j;
					loopfinal[i] = loopfinal[j + 1] + 1;
					break;
				}
			}
			if (f != 0)
			{
				loopend[i] = -(e - 1);
				remainder[i] = f;
			}
			cnt_final = loopfinal[i] + cnt_final;
		}
	}
	ans[ans_index] = cnt_final;
	stop = clock();
	double duration = ((double)(stop - start)) / CLK_TCK;
	if (ans[ans_index] == out)
	{
		printf("testcase %d == True, Duration = %.4fs, outloop = %d\n", ans_index, duration, ++out_loop);
	}
	else
	{
		printf("testcase %d == False, Duration = %.4fs, outloop = %d\n", ans_index, duration, out_loop);
		printf("out = %d, cnt_final = %d\n", out, cnt_final);
		system("pause");
	}
	free(pArg);
}


int main(void)
{
	printf("THREAD_NUM = %d\n", THREAD_NUM);
	fp = fopen("input_#5.txt", "r");
	fp2 = fopen("output_#5.txt", "r");
	
	fscanf(fp, "%d%d", &P, &Q);
	fscanf(fp, "%s", S);
	N = strlen(S);
	bottom_bdy = N;
	start = clock();
	int i;
	/*stop = clock();
	double duration = ((double)(stop - start)) / CLK_TCK;
	printf("Initial finished: %.4fs\n", duration);*/
	printf("=====================================================\n");

	i=0;
	int temp = P;
	while (temp != 0)
	{
		temp = temp / 10;
		i++;
	}
	lengthP = i;
	pthread_t *tHandles = calloc(Q, sizeof(pthread_t));
	for (i = 0; i < Q; i++)
	{
		int *args = malloc(4 * sizeof(int));
	//	int j = 0;
	//	for (j = 0; j < SAMPLE_NUM;j++)
		fscanf(fp, "%d%d", args, args + 1);
		args[2] = i;
		fscanf(fp2, "%d", args + 3);
		//pthread_create(&tHandles[i], NULL, inquire, (void*)args);
		inquire(args);
	}
	/*for (i = 0; i < THREAD_NUM; i++){
		pthread_join(tHandles[i], NULL);
	}*/
	printf("=============================================================\n");
	printf("Result Analysis: %d out of %d are right.\n", out_loop, Q);
	fclose(fp);
	fclose(fp2);
	system("pause");
	return 0;
}