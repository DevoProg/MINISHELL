#include "../../includes/minishell.h"

void 	control_c()
{
	printf("tu as press control c");//il faudra kill les process en cours et free/close
	exit(1);
}

void minishell_loop(void)
{
	char	buffer[RDLINE_BUF_SIZE];
	char	*line_read;
	
	signal(SIGINT, &control_c);
	while(1)
	{
		line_read = readline("> ");
		if(ft_strlen(line_read) == 0)
			ft_strlcpy(buffer, "\n", RDLINE_BUF_SIZE - 1);
		else
			ft_strlcpy(buffer, line_read, RDLINE_BUF_SIZE - 1);
		if(ft_strncmp(line_read, "exit", 5) == 0)
		{	
			exit(0);
		}
		printf("Ligne recue : %s\n", line_read);
		printf("Valeur buffer : %s\n", buffer);
		free(line_read);
	}
}

void	main_loop(void)
{
	char	*readed_line;
	char	**args_lst;
	int		status;
	
	while(status)
	{
		readed_line = readline("> ");
		if(!readed_line)
			exit(EXIT_FAILURE); 				//A VERIFIER SI COND ET EXIT UTILE ICI
		args_lst = split_line(readed_line);
		status = shell_exec(args_lst);
		free(readed_line);
		free(args_lst);
	}
	
}

int    main(void)
{
	minishell_loop();
	return(EXIT_SUCCESS);
	
}
