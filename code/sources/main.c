#include "../includes/minishell.h"

void control_c()
{
	printf("tu as press control c");//il faudra kill les process en cours et free/close
	exit(1);
}

void minishell_loop(void)
{
	t_data minis;

	signal(SIGINT, &control_c);//si tu appuye sur control c ca quitte
	while(1)//looop qui lit avec un prompt
	{
		minis.line = readline(">$");
		if(minis.line)
		{
			line_to_cmd(&minis);//split les commandes
			init_struct(&minis);//init struct et put les commandes dans chaque struct
			//inserer les fonctions ici
			free_struct((&minis));//free la structure des commandes
			free(minis.line);//free uniquement si elle existe?
		}
	}
}

int    main(void)
{
	minishell_loop();
	return(1);
}
