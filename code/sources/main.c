#include "../includes/minishell.h"

void control_c()
{
	printf("tu as press control c");//il faudra kill les process en cours et free/close
	exit(1);
}

void minishell_loop(void)
{
	t_data minis;
	int i;

	signal(SIGINT, &control_c);
	while(1)
	{
		minis.line = readline(">$");
		if(minis.line)
		{
			line_to_cmd(&minis);
			i = 0;
			while(minis.tab_cmd[i][0] != '\0')//pour voir les commmandes dans le tableau mais il faudra supprimer la boucle
			{
				printf("cmd[%d] = %s\n", i, minis.tab_cmd[i]);
				i++;
			}
		}
		free(minis.line);
	}
}

int    main(void)
{
	minishell_loop();
	return(1);
}
