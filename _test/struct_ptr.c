#include <stdio.h>
#include <stdlib.h>

typedef struct data {
	float a;
} data;

int main()
{
	data* dt = (data*)malloc(sizeof(data) * 5);
	printf("DT: %ld\n", sizeof(dt));
	printf("float: %ld\n", sizeof(float));
	getchar();
	free(dt);
	return 0;
}