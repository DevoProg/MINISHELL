#include "../../includes/minishell.h"
/*
	Fonction s'appliquant a la reception du signal ctrl-c.
*/
void control_c()
{
	exit(1);
}

void control_backslash()
{
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
	signal(SIGQUIT, &control_backslash);
	ft_create_env(&minis, envp);//ne pas oublier de free avec les exit	//creation d'une liste chainée avec les variable d'env
	while(1)											//looop qui lit avec un prompt
	{
		minis.line = readline(">$");
		if(!minis.line)// pour le control D
		{
			free_list(minis.env);
			exit(1);
		}
		else if(minis.line && *minis.line)
		{
			add_history(minis.line);
			line_to_cmd(&minis);						//split les commandes
			init_struct(&minis);						//init struct et put les commandes dans chaque struct
			
			//inserer les fonctions ici

			put_env_var(&minis);						//si on la déplace atttention au free	//fonction qui substitue la variable env en son contenu dans la ligne de commande
			ft_split_cmd(&minis);						//fonction qui split la commande des espaces et prendre en compte les quotes
			delete_quote(&minis);
			ft_pipe(&minis, envp);						//fonction qui execute les commandes une par une
			free_struct((&minis));						//free la structure des commandes
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
