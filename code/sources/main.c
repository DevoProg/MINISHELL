#include "../includes/minishell.h"

void control_c()
{
	printf("tu as press control c");//il faudra kill les process en cours et free/close
	exit(1);
}

void minishell_loop(void)
{
	char *line_read;

	signal(SIGINT, &control_c);
	while(1)
	{
		line_read = readline(">$");
		ft_strlen(line_read);
		free(line_read);
	}
}

int    main(void)
{
	minishell_loop();
	return(1);
	
}
