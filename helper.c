#include "shell.h"

/**
 * _getline - get line of user
 * -
 * Return: pointer of buffer
 */
char *_getline(void)
{
	int res;
	char *str = NULL;
	size_t tail = 0;

	res = getline(&str, &tail, stdin);
	if (res == EOF)
	{
		if (isatty(STDIN_FILENO))
			write(1, "\n", 1);
		exit(0);
	}
	return (str);
}
/**
 * split_line - split line
 * @line: line of user
 * Return: array argument
 */
char **split_line(char *line)
{
	size_t buf_size = TOKENS_BUFFER_SIZE;
	char **token = malloc(sizeof(char *) * buf_size);
	char *tok;
	int n = 0;

	if (!tok)
	{
		perror("Could not allocate space for token\n");
		exit(0);
	}
	tok = strtok(line, TOKEN_DELIMITERS);
	while (tok)
	{
		token[n] = tok;
		tok = strtok(NULL, TOKEN_DELIMITERS);
		n++;
	}
	token[n] = NULL;
	return (token);
}
/**
 * check_for_builtins - check builtin
 * @args: argument passed
 * @line: buffer with line
 * @env: environnement
 * Return:if  builtins ? 1:0
 */
int check_for_builtins(char **args, char *line, char **env)
{
	builtins_t list[] = {
		{"exit", exit_shell},
		{"env", env_shell},
		{NULL, NULL}
	};
	int i;

	for (i = 0; list[i].arg != NULL; i++)
	{
		if (_strcmp(list[i].arg, args[0]) == 0)
		{
			list[i].builtin(arg, line, env);
			return (1);
		}
	}
	return (0);
}

/**
 * launch_prog - launches unix cmd
 * @args: argument
 * Return: 1 in the succes
 */
int launhed_prog(char **args)
{
	pid_t pid, wpid;
	int status;

	pid = fork();

	if (pid == 0)
	{
		if (excev(args[0], args) == -1)
		{
			perror("Failed\n");
			exit(0);
		}

	}
	else if (pid < 0)
	{
		perror("Error forking\n");
		exit(0);
	}
	else
	{
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && WIFSIGNALED(status));
	}
	(void)wpid;
	return (1);
}
/**
 * builtins_checked - check for builtin
 * @args: argument
 * description: -
 * Return: 1 if builtins exit
 */
int builtins_checker(char **args)
{
	int i;
	builtins_t_list = {
		{"exit", exit_shell},
		{"env", env_shell},
		{NULL, NULL}
	};

	for (i = 0; list[i].arg != NULL; i++)
	{
		if (-strrcmp(list[i].arg, args[0] == 0))
			return (1);
	}
	return (0);
}
