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
			put_env_var(&minis);//fonction qui substitue la variable env en son contenu dans la ligne de commande
			ft_split_cmd(&minis);//fonction qui split la commande ' ' et prendre en compte les quotes


			int i = 0;
    		while(i < minis.nb_cmd)//boucle pour imprimer les commandes de la struct on peut la supprimer elle est juste utile pur visualiser les structure en fin de programmme
    		{
				int j = 0;
				while(j < minis.cmd[i].nb_words - 1)
				{
					printf("->%s\n", minis.cmd[i].tab[j]);
					j++;
				}
        		i++;
    		}

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
