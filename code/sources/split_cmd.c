#include "../includes/minishell.h"

int ft_count_command(char *line)//fonction qui compte le nombre de commande
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

char *str_cpy_cmd(char *line, int *i, t_data *minis)//fonction qui alloue une string avec la commande et la retourne pour la mettre dans le tableau
{
    char *new;
    int j;
    int k;

    j = ft_len_cmd(line);
    new = malloc(sizeof(char) * (j + 1));
    if(!new)
        ft_error("malloc doesn't work", minis, 2);
    j = 0;
    k = 0;
    if(line[j] == '|')
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

void line_to_cmd(t_data *minis)
{
    int i;
    int nb_cmd;

    if(minis->line && *minis->line == '|')//si la ligne lue commence par un pipe->error
        ft_error("Parsing error", minis, 1);//ne devrait pas perror(!!!a changer!!!!)
    nb_cmd = ft_count_command(minis->line);//retourne le nombre de commande dans la ligne
    minis->tab_cmd = malloc(sizeof(char *) * (nb_cmd + 1));//allocation d'un tableau pour les commmandes
    if(!minis->tab_cmd)
        ft_error("Malloc", minis, 1);
    i = 0;
    minis->nb_cmd = 0;
    while(minis->nb_cmd < nb_cmd)//boucle qui met chaque commande dans une case du tableau
    {
        minis->tab_cmd[minis->nb_cmd] = str_cpy_cmd(minis->line + i, &i, minis);
        minis->nb_cmd++;
    }
    minis->tab_cmd[minis->nb_cmd] = malloc(sizeof(char) * 2);//dernier element du tableau = '\0'
    if(!minis->tab_cmd[minis->nb_cmd])
        ft_error("Malloc", minis, 2);
    minis->tab_cmd[minis->nb_cmd][0] = '\0';
}