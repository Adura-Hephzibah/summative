#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

/**
 * ls_directory - function to loop and list directory content
 * @path: argument pointer
 * Return: void
 */
void ls_directory(const char *path)
{
	struct dirent *entry;
	DIR *dir = opendir(path);

	if (dir == NULL)
	{
		return;
	}
	while ((entry = readdir(dir)) != NULL)
	{
		struct stat buffer;
		char *name = entry->d_name;

		/* Ignore . and .. and git directories */
		if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0 || strcmp(name, ".git") == 0)
			continue;

		stat(name, &buffer);

		/* Check if it's a directory or a file */
		if (S_ISDIR(buffer.st_mode))
		{
			printf("Directory: %s, Size: %ld\n", name, buffer.st_size);
		}
		else if (S_ISREG(buffer.st_mode))
		{
			printf("File: %s, Size: %ld\n", name, buffer.st_size);

			if (buffer.st_size == 0)
			{
				remove(name);
				printf("Deleted empty file: %s\n", entry->d_name);
			}
			if (strstr(entry->d_name, ".sh") != NULL)
			{
				remove(name);
				printf("Deleted .sh file: %s\n", entry->d_name);
			}
		}
	}
	closedir(dir);
}

/**
 * main - Entry Point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	ls_directory(".");
	return (0);
}
