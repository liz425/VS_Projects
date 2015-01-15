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
clock_t start, stop;


void* inquire(void *pArg)
{
	int b = *((int *)pArg);
	int e = *((int *)pArg + 1);
	int ans_index = *((int *)pArg + 2);
	int out = *((int *)pArg + 3);
	int i, j, loopstart;
	int cnt = 0;
	long f;
	for (i = b - 1; i <= e - 1; i++)
	//for (i = b - 1; i <= b + 50; i++)  //just for debuging
	{
		loopstart = i;
		f = 0;
		for (j = i; j <= e - 1; j++)
		{
			if (f == 0)
			{
				if ((loopend[j] > 0) && (loopend[j] <= e - 1))
				{
					cnt++;
					j = loopend[j];
					loopstart = j + 1;
					continue;
				}
				else if ((loopend[j] < 0) && (loopend[j] <= -(e - 1))) 
				{
					break;
				}
			}
			char c[] = { S[j] };
			f = (f * 10 + atoi(c)) % P;
			if (f == 0)
			{
				loopend[loopstart] = j;
				loopstart = j + 1;
				cnt++;
			}
		}
		if ((f != 0) && (loopend[loopstart] > -(e - 1)))
			loopend[loopstart] = -(e - 1);
	}
	ans[ans_index] = cnt;
	stop = clock();
	double duration = ((double)(stop - start)) / CLK_TCK;
	if (ans[ans_index] == out)
	{
		printf("testcase %d == True, Duration = %.4fs\n", ans_index, duration);
	}
	else
	{
		printf("testcase %d == False, Duration = %.4fs\n", ans_index, duration);
	}
	free(pArg);
}

int main(void)
{
	printf("THREAD_NUM = %d\n", THREAD_NUM);
	fp = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "r");

	fscanf(fp, "%d%d", &P, &Q);
	fscanf(fp, "%s", S);
	N = strlen(S);
	int i=0;
	int temp = P;
	while (temp != 0)
	{
		temp = temp / 10;
		i++;
	}
	lengthP = i;
	start = clock();
	pthread_t *tHandles = calloc(Q, sizeof(pthread_t));
	for (i = 0; i < THREAD_NUM; i++)
	{
		int *args = malloc(4 * sizeof(int));
	//	int j = 0;
	//	for (j = 0; j < SAMPLE_NUM;j++)
		fscanf(fp, "%d%d", args, args + 1);
		args[2] = i;
		fscanf(fp2, "%d", args + 3);
		pthread_create(&tHandles[i], NULL, inquire, (void*)args);
		//inquire(args);
	}
	for (i = 0; i < THREAD_NUM; i++){
		pthread_join(tHandles[i], NULL);
		
	}
	
	fclose(fp);
	fclose(fp2);
	system("pause");
	return 0;
}