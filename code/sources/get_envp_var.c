#include "../includes/minishell.h"

int is_no_open_single_quote(char *line, int i)//verifier qu'il n'y ait pas de signle quote ouvert
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
        return(0);
    return(1);
}


int repalce_env_var(char *str)
{
    int i;
    int j;
    char *variable;

    i = 0;
    while(str[i])
    {
        j = 0;
        if(str[i] == '$' && is_no_open_single_quote(str, i))
        {
            
        }
    }
    return(0);
}

char *get_envp_var(t_data *minis)
{
    int i;

    i = 0;
    while(i < minis->nb_cmd)
    {
        replace_env_var(minis->cmd[i].line_cmd);
        i++;
    }
    return(NULL);
}