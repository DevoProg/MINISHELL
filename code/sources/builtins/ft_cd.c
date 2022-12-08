#include "../includes/minishell.h"

int where_cut(char *str)
{
    int i;
    int res;

    i = 0;
    while(str[i])
    {
        if(str[i] == '/')
            res = i;
        i++;
    }
    return(res);
}

char *cut_pwd(char *str)
{
    char *new;
    int stop;
    int i;

    i = 0;
    stop = where_cut(str);
    new = malloc(sizeof(char) * (stop + 1));
    if(!new)
        exit(1);//il faudra exit proprement
    while(str[i] && i < stop)
    {
        new[i] = str[i];
        i++;
    }
    new[i] = '\0';
    //il faudra peut-etre free str
    return(new);
}

int access_check(char *path)
{
    DIR  *c;

    c = opendir(path);
    if(c == NULL)
        return(ERROR);
    return(SUCCESS);
}


void ft_cd(t_data *minis, t_board *cmd)
{
    if(access_check(cmd->tab[1]) == ERROR)
    {
        printf("%s\n", "wrong path or not authorized");
        return;
    }
    if(chdir(cmd->tab[1]) == -1)
    {
        printf("%s\n", "ERROR CHANGING DIR");
        return;
    }
    printf("NEW_PATH:");
    ft_pwd();
}