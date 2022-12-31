#include "../../includes/minishell.h"

/*
    fonction qui regarde si il n'y a pas de open single quote sur la string a l'index i
*/
int is_no_open_single_quote(char *line, int i)//verifier qu'il n'y ait pas de single quote ouvert 
{
    //il faudra quand meme verifier cette maniere de faire  /!\'
    int single_quote;
    int j;

    j = 0;
    single_quote = 0;
    while(j < i)
    {
        if(line[j] == 39)// 39 == '
            single_quote++;
        j++;
    }
    if(single_quote % 2 != 0)
        return(0);//si ouverte return 0
    return(1);//si fermée ou pas de quote return 1
}

/*
    fonction qui calcule la longueur de la prochaine commande
*/
int ft_len_cmd(char *line)
{
    int i;

    if(!line)
		return(0);
    i = 0;
	while(line[i])
	{
		if(is_no_open_quote(line, i) && line[i] == '|')
			return(i);
		i++;
	}
	return (i);
}

/*
    fonction qui y ait pas de single ou double pipe ouvert a l'index i
*/
int is_no_open_quote(char *line, int i)
{
    int single_quote;
    int double_quote;
    int j;

    j = 0;
    single_quote = 0;
    double_quote = 0;
    while(j < i)
    {
        if(line[j] == 39)// 39 == '
            single_quote++;
        if(line[j] == 34)//34 == "
            double_quote++;
        j++;
    }
    if(single_quote % 2 != 0)
        return(0);
    if(double_quote % 2 != 0)
        return(0);
    return(1); //si y'a de quote ouverte
}

/*
    fonction qui copie le resultat et la fin de la commande
*/
char *ft_cpy_new_line_bis(char *cmd, char *var_env, char *new, int i)
{
    int k;
    int j;

    k = 0;
    j = 0;
    while(new[j])
        j++;
    while(var_env && var_env[k])
    {
        new[j] = var_env[k];
        j++;
        k++;
    }
    //free(var_env);//ne pas free sinon crash
    k = i + ft_strlen_var(cmd, i);
    while(cmd[k] && cmd)
    {
        new[j] = cmd[k];
        j++;
        k++;
    }
    new[j] = '\0';
    free(cmd);
    return(new);
}