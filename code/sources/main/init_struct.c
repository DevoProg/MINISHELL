#include "../includes/minishell.h"

void free_struct(t_data *minis)//free le tableau de structure
{
    int i;

    i = 0;
    while(i < minis->nb_cmd)
    {
        free(minis->cmd[i].line_cmd);
        free_tab(minis->cmd[i].tab, minis->cmd[i].nb_words);
        //free(&minis->cmd[i]);
        i++;
    }
    free(minis->cmd);
}

t_var	*lst_last(t_var *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void lst_add(t_var **lst, t_var *new)
{
	t_var   *aux_lst;

	if (new)
	{
		if (!*lst)
		{
			*lst = new;
			return ;
		}
		aux_lst = lst_last(*lst);
		aux_lst->next = new;
	}
}

char *list_chr(t_var *exp, char *str_name)//chercher une var dans la liste
{
    while(exp->next != NULL)
    {
        if(exp->name == str_name)
            return(exp->value);
        exp = exp->next;
    }
    if(exp->name == str_name)
        return(exp->value);
    return(NULL);
}

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
        printf("%d\n", exp->is_export);
        exp = exp->next;
    }
    ft_putstr_fd(exp->name, 1);
    ft_putchar_fd('=', 1);
    ft_putstr_fd(exp->value, 1);
    ft_putchar_fd('\n', 1);
    printf("%d\n", exp->is_export);

}

void ft_get_name(char *str, t_var *ptr)
{
    int i;

    i = 0;
    while(str[i] != '=')
        i++;
    ptr->name = malloc(sizeof(char) * (i + 1));
    if(!ptr->name)
        exit(1);//il faudra quitter proprement
    i = 0;
    while(str[i] != '=')
    {
        ptr->name[i] = str[i];
        i++;
    }
    ptr->name[i] = '\0';
}

void ft_get_value(char *str, t_var *ptr)
{
    int i;
    int j;
    int len;

    i = 0;
    while(str[i] && str[i] != '=')
        i++;
    i++;
    len = ft_strlen(str + i);
    ptr->value = malloc(sizeof(char) * (len + 1));
    if(!ptr->value)
        exit(1);//quitter proprement
    j = 0;
    while(str[i])
    {
        ptr->value[j] = str[i];
        j++;
        i++;
    }
    ptr->value[j] = '\0';
}

void ft_create_env(t_data *minis, char **envp)
{
    t_var *ptr;
    int i;

    i = 0;
    while(envp[i])
    {
        ptr = malloc(sizeof(t_var));
        if(!ptr)
            exit(1);//il faudra exit proprement
        ft_get_name(envp[i], ptr);
        ft_get_value(envp[i], ptr);
        if(ptr->name && ptr->name[0] == '_' && ptr->name[1] == '\0')
            ptr->is_export = 0;
        else
            ptr->is_export = 1;
        i++;
        lst_add(&minis->env, ptr);
        ptr = NULL;
    }
}

void init_struct(t_data *minis, char **envp)//allocation d'un tableau de strcuture et copier le tableau dans chaque structure
{
    int i;

    //ft_create_env(minis, envp);
    print_list(minis->env);
    minis->cmd = malloc(sizeof(t_board) * minis->nb_cmd);//allocation d'un tableau de structure
    if(!minis->cmd)
        ft_error("Malloc", minis, 2);
    i = 0;
    while(i < minis->nb_cmd)//boucle qui met les commandes dans le tableau de structure
    {
        minis->cmd[i].line_cmd = ft_strdup(minis->tab_cmd[i]);
        if(!minis->cmd[i].line_cmd)
            ft_error("Malloc", minis, 3);
        i++;
    }
    free_tab(minis->tab_cmd, minis->nb_cmd + 1);//free le tableau du split_cmd car les lignes ont ete copiee dans cmd[i]->cmd_line
}