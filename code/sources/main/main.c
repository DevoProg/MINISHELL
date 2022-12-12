#include "../../includes/minishell.h"

/*
	Fonction s'appliquant a la reception du signal ctrl-c.
*/
void control_c()
{
	printf("tu as press control c");//il faudra kill les process en cours et free/close
	exit(1);
}

/*
	Fonction de la loop principale du shell.
	Gere les lignes recues et effectue tout type d'actions.
*/
void minishell_loop(char **envp)
{
	t_data minis;

	signal(SIGINT, &control_c);
	ft_create_env(&minis, envp);						//creation d'une liste chainée avec les variable d'env
	while(1)											//looop qui lit avec un prompt
	{
		minis.line = readline(">$");
		if(*minis.line)
		{
			add_history(minis.line);
			line_to_cmd(&minis);						//split les commandes
			init_struct(&minis);						//init struct et put les commandes dans chaque struct
			
			//inserer les fonctions ici
			

			put_env_var(&minis);						//fonction qui substitue la variable env en son contenu dans la ligne de commande
			ft_split_cmd(&minis);						//fonction qui split la commande ' ' et prendre en compte les quotes
			ft_check_builtins(&minis);					//fonction qui regarde si la fonction comprend des echo pwd ect
			free_struct((&minis));						//free la structure des commandes
			free(minis.line);							//free ligne lue
		}
	}
}

int    main(int argc, char **argv, char **envp)
{
	minishell_loop(envp);
	(void)argv;
	(void)argc;
	return(1);
}
