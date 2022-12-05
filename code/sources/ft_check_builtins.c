#include "../includes/minishell.h"

int    ft_pwd(void)
{
    char    cwd[PATH_LEN];

    if (getcwd(cwd, PATH_LEN))
    {
        ft_putendl_fd(cwd, 1);
        return (SUCCESS);
    }
    else
        return (ERROR);
}

void ft_check_builtins(t_data *minis)
{
    int i;

    i = 0;
    while(i < minis->nb_cmd)
    {
        if(ft_strncmp(minis->cmd[i].tab[0], "pwd", 3) == 0 && minis->cmd[i].nb_words == 2)//==2 ->aucune options 
            ft_pwd();
        i++;
    }
}