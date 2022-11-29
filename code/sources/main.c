#include "../includes/minishell.h"

void control_c()
{
	printf("tu as press control c");//il faudra kill les process en cours et free/close
	exit(1);
}

void minishell_loop(void)
{
	t_data minis;

	signal(SIGINT, &control_c);
	while(1)
	{
		minis.line = readline(">$");
		if(minis.line)
		{
			line_to_cmd(&minis);
			init_struct(&minis);
		}
		free(minis.line);
	}
}

int    main(void)
{
	minishell_loop();
	return(1);
}
