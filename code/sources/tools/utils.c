#include "../../includes/minishell.h"

/*
    Fonction servant a print la list des noms et des valeurs des variables d environnement. 
*/
void print_list(t_var *exp)
{
    if(!exp)
        return ;
    while(exp->next != NULL)
    {
        ft_putstr_fd(exp->name, 1);
        ft_putchar_fd('=', 1);
        ft_putstr_fd(exp->value, 1);
        ft_putchar_fd('\n', 1);
        exp = exp->next;
    }
    ft_putstr_fd(exp->name, 1);
    ft_putchar_fd('=', 1);
    ft_putstr_fd(exp->value, 1);
    ft_putchar_fd('\n', 1);

}

/*
    Fonction servant a rechercher une variable dans la liste via son "name".
*/
char *list_chr(t_var *exp, char *str_name)
{
    while(exp->next != NULL)
    {
        if(ft_strcmp(exp->name, str_name) == 0)
            return(exp->value);
        exp = exp->next;
    }
    if(ft_strcmp(exp->name, str_name) == 0)
        return(exp->value);
    ft_printf("test");
    return(NULL);
}

/*
    Fonction servant a comparer deux strings.
*/
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

/*
    Fonction servant a vérifier qu'il n y ait pas de single quotes.
    A VERIFIER SI OK A FAIRE COMME CA.    
*/
int is_no_open_single_quote(char *line, int i)
{
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
        return(0);                //si ouverte return 0
    return(1);                     //si fermée ou pas de quote return 1
}                    //la fonction pour simple et double qote existe dans le fichier split_cmd.c

/*
    Fonction servant a calculer la taille de la prochaine commande.
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
    Fonction vérifiant si un quote qui s'ouvre est bien fermé derriere le pipe. 
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
        if(line[j] == 39)        // 39 == '
            single_quote++;
        if(line[j] == 34)         //34 == "
            double_quote++;
        j++;
    }
    if(single_quote % 2 != 0)
        return(0);
    if(double_quote % 2 != 0)
        return(0);
    return(1);
}

/*
    Fcontion servant a copier le resultat et la fin de la commande.
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
    //free(var_env);
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