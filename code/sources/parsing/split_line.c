#include "../../includes/minishell.h"

/*
  Fonction servant a compter le nombre de commandes présent dans la ligne recue.
  Retourne le (total commandes + 1).
*/
int ft_count_command(char *line)
{
	int i;
	int count;

	if(!line)
		return(0);
	i = 0;
	count = 0;
	while(line[i])
	{
		if(is_no_open_quote(line, i) && line[i] == '|')
			count++;
		i++;
	}
	return(count + 1);
}

/*
  Fonction servant a copier une commande.
  Renvoie un char * avec l'elem situé entre des '|' + quotes vérifiés.
  Le résultat sera placé par la suite dans le tableau.
*/
char *str_cpy_cmd(char *line, int *i, t_data *minis)
{
    char *new;
    int j;
    int k;

    j = ft_len_cmd(line);
    new = malloc(sizeof(char) * (j + 1));
    if(!new)
        ft_error("Malloc", minis, 1, 1);
    j = 0;
    k = 0;
    if(line[j] == '|')               // Techniquement pas besoin car checking dans "line_to_cmd" + error
        j++;
    while(line[j])
	{
		if(is_no_open_quote(line, j) && line[j] == '|')
            break;
        new[k] = line[j];
        k++;
        j++;
	}
    new[k] = '\0';
    *i += j;
    return(new);
}

/*
  Fonction servant a transformer la ligne lue en commandes.
  Les commandes sont placés dans "minis->tab_cmd".
*/
void line_to_cmd(t_data *minis)
{
    int i;
    int nb_cmd;

    if(minis->line && *minis->line == '|')                      //si la ligne lue commence par un pipe->error
        ft_error("Parsing error", minis, 0, 0);                 //message erreur?
    nb_cmd = ft_count_command(minis->line);                     //retourne le nombre de commande dans la ligne
    minis->tab_cmd = malloc(sizeof(char *) * (nb_cmd + 1));     //allocation d'un tableau pour les commmandes
    if(!minis->tab_cmd)
        ft_error("Malloc", minis, 0, 1);
    i = 0;
    minis->nb_cmd = 0;
    while(minis->nb_cmd < nb_cmd)                                               //boucle qui met chaque commande dans une case du tableau
    {
        minis->tab_cmd[minis->nb_cmd] = str_cpy_cmd(minis->line + i, &i, minis);// avance l'index en fct du nbr de char recupérés.
        minis->nb_cmd++;
    }
    minis->tab_cmd[minis->nb_cmd] = malloc(sizeof(char) * 2);//dernier element du tableau = '\0'
    if(!minis->tab_cmd[minis->nb_cmd])
        ft_error("Malloc", minis, 1, 1);
    minis->tab_cmd[minis->nb_cmd][0] = '\0';         // Plutot mettre NULL ??
}

void ft_write(char *new, char *str, int *i, int *j)
{
    new[*j] = str[*i];
    *i += 1;
    *j += 1;
}