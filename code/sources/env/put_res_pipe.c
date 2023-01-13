#include "../../includes/minishell.h"


//si pas fork le valeur pourra etre 1 si cd fail
void builtin_res_pipe(t_data *minis)
{
    t_var *ptr;
    char *new_value;

    ptr = lst_name_finding(minis->env, "?");
    new_value = ft_itoa(0);
    if(!new_value)
        exit(1);//quitter prorperement
    free(ptr->value);
    ptr->value = ft_strdup(new_value);
    if(!ptr->value)
        exit(1);//quitter prorpement
}

void put_res_pipe(t_data *minis, int res)
{
    t_var *ptr;
    char *new_value;
    int i;

    i = minis->nb_cmd - 1;
    if(ft_is_builtins(&minis->cmd[i]))
    {
        builtin_res_pipe(minis);
        return ;
    }
    ptr = lst_name_finding(minis->env, "?");
    new_value = ft_itoa(res);
    if(!new_value)
        exit(1);//quitter prorperement
    free(ptr->value);
    ptr->value = ft_strdup(new_value);
    if(!ptr->value)
        exit(1);//quitter prorpement
}