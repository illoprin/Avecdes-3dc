#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

const unsigned ARR_SIZE = 16;
const unsigned ARR_VALUE_SCATTER = 37;
int main(void)
{
	/* Set random seed */
	srand(time(NULL));

	/* Allocate memory for 4byte array */
	int* arr = (int*)malloc((size_t)ARR_SIZE * sizeof(int));
	/* Add values to array (int array - step is 4 bytes) */
	for (unsigned i = ARR_SIZE - 1; i > 0; i--)
	{
		*(arr + (ARR_SIZE - i)) = pow(2, i) + rand() % ARR_VALUE_SCATTER;
	}

	/* Print values on screen */
	printf("Values of arr in 4 byte step: ");
	for (unsigned i = 0; i < ARR_SIZE; i++)
	{
		printf("%d ", *(arr + i));
	}
	printf("\n\n");


	char* arr_byte_ptr = (char*)arr;
	/* Get each byte in int 4 byte array memory range */
	printf("Values of arr in 1 byte step (print each byte of each 4byte int):\n");
	for (unsigned i = 0; i < ARR_SIZE * sizeof(int); i++)
	{
		if (i % 4 == 0) printf("\n\t");
		printf("%d ", *(arr_byte_ptr + i));
	}
	
	printf("\n");
	/* Clear allocated memory */
	free(arr);
	
	return 0;
}