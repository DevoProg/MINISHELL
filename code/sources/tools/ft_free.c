#include "../../includes/minishell.h"

void	free_redi(t_data *minis)
{
	int		i;
	t_redi *current;
    t_redi *next;

	i = 0;
    while (i < minis->nb_cmd) {
        current = minis->cmd[i].redi;
        while (current) {
            next = current->next;
            free(current->file);
            close(current->file_fd);   // A close? ou deja fait?
            free(current);
            current = next;
        }
        minis->cmd[i].redi = NULL;
        i++;
    }
}

/*
	Fonction servant a free minis->tab_cmd.
	Free chaque element minis->tab_cmd[i] puis l'element minis->tab a la fin.
	Peut servir a free une table en général.
*/
void free_tab_cmd(t_data *minis)
{
    int j;

    j = 0;
    while(j < minis->nb_cmd)
    {
        free(minis->tab_cmd[j]);
        j++;
    }
    free(minis->tab_cmd);
}

/*
	Fonction servant a free la memoire allouée a la liste chainée des variables d'environnements.
	Free env->name et env->value puis free la t_var qui contenait les elements avant de passer a la suivante.
*/
void	put_env_var_cleanup(t_data *minis) 
{
    t_var	*current;
	t_var	*next;

	current = minis->env;
    while (current) {
		next = current->next;
        free(current->name);
        free(current->value);
		free(current);
        current = next;
    }
	minis->env = NULL;
}

void	free_all(t_data *minis)
{

	free_tab_cmd(minis);
	free_redi(minis);
	put_env_var_cleanup(minis);
}