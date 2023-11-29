#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 100
#define CANDIDATE_NAMES 1000

/**
 * compare_func - function to compare
 * @a: argument pointer
 * @b: argument pointer
 * Return: void
 */
/* Comparison function for qsort */
int compare_func(const void *a, const void *b)
{
	return (strcmp((char *)a, (char *)b));
}

/**
 * main - Entry Point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char candidates[CANDIDATE_NAMES][NAME_LEN];
	int count = 0;

	/* Read candidates from file */
	FILE *file = fopen("candidates", "r");

	while (fgets(candidates[count], NAME_LEN, file))
	{
		/* Remove newline character */
		candidates[count][strcspn(candidates[count], "\n")] = 0;
		count++;
	}
	fclose(file);

	/* Sort candidates */
	qsort(candidates, count, NAME_LEN, compare_func);

	/* Write unique candidates to file */
	file = fopen("unique_candidate.txt", "w");
	for (int i = 0; i < count; i++)
	{
		if (i == 0 || strcmp(candidates[i], candidates[i - 1]) != 0)
		{
			fprintf(file, "%s\n", candidates[i]);
		}
	}
	fclose(file);

	return (0);
}
