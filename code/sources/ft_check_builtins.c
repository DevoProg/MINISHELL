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

void ft_envp(char **envp)
{
    int i;

    i = 0;
    while(envp[i])
    {
        ft_putendl_fd(envp[i], 1);
        i++;
    }
}

void ft_echo(t_board *cmd)
{
    int i;
    int option;

    if(ft_strncmp(cmd->tab[1], "-n", 2) == 0)
    {
        option = 1;
        i = 2;
    }
    else
    {
        option = 0;
        i = 1;
    }
    while(i < cmd->nb_words - 1)
    {
        ft_putendl_fd(cmd->tab[i], 1);
        i++;
    }
    if(option == 0)
        ft_putendl_fd("\n", 1);
}

void ft_check_builtins(t_data *minis, char **envp)
{
    int i;

    i = 0;
    while(i < minis->nb_cmd)
    {
        if(ft_strncmp(minis->cmd[i].tab[0], "pwd", 3) == 0 && minis->cmd[i].nb_words == 2)//==2 ->aucune options 
            ft_pwd();
        else if(ft_strncmp(minis->cmd[i].tab[0], "env", 3) == 0 && minis->cmd[i].nb_words == 2)//==2 ->aucune options
            ft_envp(envp);
        else if(ft_strncmp(minis->cmd[i].tab[0], "echo", 4) == 0)
            ft_echo(&minis->cmd[i]);
        i++;
    }
}