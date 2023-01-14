#include "../../includes/minishell.h"

void put_res_pipe(t_data *minis, int res)
{
    t_var *ptr;
    char *new_value;
    int i;

    ptr = lst_name_finding(minis->env, "?");
    new_value = ft_itoa(res);
    if(!new_value)
        exit(1);//quitter prorperement
    free(ptr->value);
    ptr->value = ft_strdup(new_value);
    if(!ptr->value)
        exit(1);//quitter prorpement
}