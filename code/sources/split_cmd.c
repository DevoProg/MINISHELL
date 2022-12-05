#include "../includes/minishell.h"

int ft_len_words(char *line, int i)//calcule la de la prochaine commande
{
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

int ft_count_split(char *line)//fonction qui compte le nombre de commande
{
	int i;
	int count;

	if(!line)
		return(0);
	i = 0;
	count = 0;
	while(line[i])
	{
		if(is_no_open_quote(line, i) && line[i] == ' ')
        {
			count++;
            while(line[i] == ' ')
                i++;
            continue;
        }
		i++;
	}
	return(count + 1);
}

char *str_cpy_words(char *line, int *i)//fonction qui alloue une string et la retourne pour la mettre dans le tableau
{
    char *new;
    int j;
    int k;

    j = ft_len_words(line, *i);
    new = malloc(sizeof(char) * (j + 1));
    if(!new)
        exit(1);//il faudra exit proprement
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
    *i += j;
    return(new);
}


char **ft_split_each_cmd(char *str, t_data *minis)
{
    int nb_split;
    int i;
    char **tab;

    nb_split = ft_count_split(str);
    tab = malloc(sizeof(char *) * (nb_split + 1));
    if(!tab)
        exit(1);//il faudra exit proprement
    i = 0;
    while(i < nb_split)
    {
        tab[i] = str_cpy_words(str, &i, minis);
        i++;
    }
    tab[i] = NULL;
}

void    ft_split_cmd(t_data *minis)
{
    int i;

    i = 0;
    while(i < minis->nb_cmd)
    {
        minis->cmd[i].tab = ft_split_each_cmd(minis->cmd[i].line_cmd);
        i++;
    }
}