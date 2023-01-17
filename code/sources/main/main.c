#include "../../includes/minishell.h"

void each_things_to_do(t_data *minis, char **envp)
{
	int res;

	add_history(minis->line);	
	line_to_cmd(minis);						//split les commandes
	init_struct(minis);						//init struct et put les commandes dans chaque struct
	redirection(minis); 						//stock chaque redirection dans la structure de sa commande et retire la redirection de la ligne de la commande
	put_env_var(minis);						//si on la déplace atttention au free	//fonction qui substitue la variable env en son contenu dans la ligne de commande
	ft_split_cmd(minis);						//fonction qui split la commande des espaces et prendre en compte les quotes
	delete_quote(minis);						//retire les quotes "inutiles"
	res = ft_pipe(minis, envp);				//fonction qui execute les commandes une par une et retourne la valeure du pipe
	if(!ft_is_not_fork(&minis->cmd[minis->nb_cmd - 1]))//si il y a fork sur la derniere commande on stock la variable
		put_res_pipe(minis, res);					//resultat de l'execution dans la variable '?'
	free_struct((minis));						//free
}


/*
	Fonction de la loop principale du shell.
	Gere les lignes recues et effectue tout type d'actions.
*/
void minishell_loop(char **envp)
{
	t_data minis;
	int res;

	init_signals();									// Analyse les siganux recus
	
	ft_create_env(&minis, envp);					//ne pas oublier de free avec les exit	//creation d'une liste chainée avec les variable d'env
	while(1)										//looop qui lit avec un prompt
	{
		minis.line = readline(">$");
		if(!minis.line)								// pour le control D
		{
			line_empty(&minis);						// Free minis si signal ctrl+d, puis exit
			exit(1);
		}
		else if(minis.line && *minis.line)
			each_things_to_do(&minis, envp);
	}
	free_list(minis.env);
	//rl_clear_history(); il faut le garder juste que sur mon pc il est pas trouvé dans la lib
}

int    main(int argc, char **argv, char **envp)
{
	int i;

	if(argc == 1)
	{
		minishell_loop(envp);
		(void)argv;
		(void)argc;
		return(1);
	}
}
