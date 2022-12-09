#include "../includes/minishell.h"
void    ft_delete_middle_node(t_var *env)
{
    t_var *tmp;
    
    tmp = env->next;
    env->next = tmp->next;
    free(tmp->name);
    free(tmp->value);
    tmp->next = NULL;
    free(tmp);
}

void    ft_delete_last_node(t_var *env)
{
    t_var *tmp;

    ft_printf("icii\n");
    tmp = env->next;
    free(tmp->name);
    free(tmp->value);
    tmp->next = NULL;
    free(tmp);
    env->next = NULL;
}

t_var    *ft_delete_first_node(t_var *env)
{
    t_var *tmp;

    tmp = env;
    env = env->next;
    free(tmp->name);
    free(tmp->value);
    //tmp->next = NULL;
    free(tmp);
    return(env);
}

t_var    *ft_delete_node(char *str, t_var *env)
{
    t_var *tmp;
    t_var *start;

    start = env;
    if(ft_strcmp(str, env->name) == 0)
    {
        env = ft_delete_first_node(env);
        return (env);
    }
    printf("->>>%s", env->name);
    tmp = env->next;
    while(tmp->next != NULL)
    {
        if(ft_strcmp(str, tmp->name) == 0)
        {
            ft_delete_middle_node(env);
            return(start);
        }   
        env = env->next;
        tmp = env->next;

    }
    if(ft_strcmp(str, tmp->name) == 0)
        ft_delete_last_node(env);
    return(start);

}

void    ft_unset(t_data *minis, t_board *cmd)
{
    int i;

    i = 1;
    while(i < cmd->nb_words - 1)
    {  
        minis->env = ft_delete_node(cmd->tab[i], minis->env);
        i++;
    }
}