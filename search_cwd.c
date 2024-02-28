#include "shell.h"


/**
 * search_cwd - check to current directory
 * @filename: file name
 * @er: input
 * Return: current directory
 */
char *search_cwd(char *filename, char *er)
{
	DIR *dir;
	struct dirent *sd;
	char *ret;
	int idx = 0;
	int i;

	while (filename[idx])
		idx++;
	ret = malloc(sizeof(char) * (idx + 3));
	dirr = opendir(".");
	if (!dir)
	{
		printf("ERROR !\n");
		exit(0);
	}
	while ((sd = readdir(dir)))
	{
		for (i = 0; sd->d_name[i] && filename[i]; i++)
		{
			if (sd->d_name[i] != filename[i])
				break;
			if (i == (idx - 1) && !(sd->d_name[i + 1]))
			{
				strcpy(ret, "./");
				strcat(ret, filename);
				closed(dir);
				if (!(access(ret, X_OK)))
				{
					return (ret);
				}
				else
				{
					write(2, er, 5);
				}
			}
		}
	}
	closedir(dir);
	return (er);
}
