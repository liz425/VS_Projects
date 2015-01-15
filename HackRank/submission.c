#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<pthread.h>



char S[100001];
int P, Q, N;
int lengthP;
//__int64 f;  //%I64d
int loopend[100000] = { 0 };
int ans[100000] = { 0 };



void* inquire(void *pArg)
{
	int b = *((int *)pArg);
	int e = *((int *)pArg + 1);
	int ans_index = *((int *)pArg + 2);
	int for_break;		//used for set breakpoint
	if (ans_index == 3)
		for_break = 1;
	int i, j, loopstart;
	int cnt = 0;
	long f;
	for (i = b - 1; i <= e - 1; i++)
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
			f = f * 10 + atoi(c);
			f = f % P;
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
	free(pArg);
	return 0;
}

int main(void)
{
	scanf("%d%d", &P, &Q);
	scanf("%s", S);

	N = strlen(S);
	int i=0;
	int temp = P;
	while (temp != 0)
	{
		temp = temp / 10;
		i++;
	}
	lengthP = i;
	//pthread_t *tHandles = calloc(Q, sizeof(pthread_t));
	for (i = 0; i < Q; i++)
	{
		int *args = malloc(3 * sizeof(int));
		scanf("%d%d", args, args + 1);
		args[2] = i;
		//pthread_create(&tHandles[i], NULL, inquire, (void*)args);
		inquire(args);
		printf("%d\n", ans[i]);
	}
	/*for (i = 0; i < Q; i++){
		pthread_join(tHandles[i], NULL);
	}*/
	/*for (i = 0; i < Q; i++){
		printf("%d\n", ans[i]);
	}*/
	
	//system("pause");
	return 0;
}