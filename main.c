#include "minishell.h"
int main(int argc, char **argv, char **envp)
{
	char *line;
	// char **args;
	// int status;
	(void)argc;
	(void)argv;
	while (1)
	{
		printf(RED"minishell> ");
		line = readline();
		// args = split_line(line);
		// status = execute(args);
		free(line);
		// free(args);
	}
}
