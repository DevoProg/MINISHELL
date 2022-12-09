#include "../../includes/minishell.h"

/*
  Fonction servant a récupérer la taille de la lignes.
   
*/
int ft_len_words(char *line)
{
    int i;

    if(!line)
		return(0);
	i = 0;
	while(line[i])
	{
		if(is_no_open_quote(line, i) && line[i] == ' ')
			return(i);
		i++;
	}
	return (i);
}

/*
  Fonction servant a compter le nombre de commandes dans une ligne par rapport au ' '.
  Chaque element entre ' ' est compatbilisé.  
*/
int ft_count_split(char *line)  //fonction qui compte le nombre de commande
{
	int i;
	int count;

	if(!line)
		return(0);
	i = 0;
	count = 0;
  while(line[i] && line[i] == ' ')
    i++;
	while(line[i])
	{
		if(is_no_open_quote(line, i) && line[i] != ' ')
        {
			count++;
            while(line[i] && line[i] != ' ')
                i++;
            continue;
        }
		i++;
	}
	return(count);
}

/*
  Fonction servant a allouer la string et a remplir le tableau.
*/
char *str_cpy_words(char *line, int *i)
{
    char *new;
    int j;
    int k;

    j = ft_len_words(line);
    new = malloc(sizeof(char) * (j + 1));
    if(!new)
        exit(1);   //il faudra exit proprement
    j = 0;
    k = 0;
    while(line[j] == ' ')
        j++;
    while(line[j])
	{
		if(is_no_open_quote(line, j) && line[j] == ' ')
      break;
    new[k] = line[j];
    k++;
    j++;
	}
    new[k] = '\0';
    while(line[j] == ' ')
        j++;
    *i += j;
    return(new);
}

/*
  Fonction servant a créer un tableau avec les commandes.
  Renvoie le tableau rempli.
*/
char **ft_split_each_cmd(char *str, t_board *cmd)
{
    int i;
    int j;
    char **tab;

    cmd->nb_words = ft_count_split(str) + 1;          //+1 pour alloc de la denriere ligne pour null??
    tab = malloc(sizeof(char *) * (cmd->nb_words));
    if(!tab)
        exit(1);      //il faudra exit proprement
    j = 0;
    i = 0;
    while(str[i])
    {
        tab[j] = str_cpy_words(str + i, &i);
        j++;
    }
    tab[j] = NULL;
    return(tab);
}

/*
  Fonction servant a spit les commande stockée dans "minis->cmd[n]->line_cmd".
  Les commandes obtenues sont placées dans "minis->cmd[n]->tab".
*/
void    ft_split_cmd(t_data *minis)
{
    int i;

    i = 0;
    while(i < minis->nb_cmd)
    {
        minis->cmd[i].tab = ft_split_each_cmd(minis->cmd[i].line_cmd, &minis->cmd[i]);
        i++;
    }
}