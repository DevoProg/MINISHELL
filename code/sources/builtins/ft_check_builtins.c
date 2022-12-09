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

void ft_envp(t_data *minis)
{
    print_list(minis->env, 0);
}

void ft_echo(t_board *cmd)
{
    int i;
    int option;

    if (ft_strncmp(cmd->tab[1], "-n", 2) == 0)
    {
        option = 1;
        i = 2;
    }
    else
    {
        option = 0;
        i = 1;
    }
    while (i < cmd->nb_words - 1)
    {
        if ((i > 1 && option == 0) || (i > 2 && option == 1))
            ft_putchar_fd(' ', 1);
        ft_putstr_fd(cmd->tab[i], 1);
        i++;
    }
    if(option == 0)
        ft_putchar_fd('\n', 1);
}

void ft_exit(t_data *minis)
{
    free_struct(minis);
    free(minis->line);
    exit(1);
}

void ft_check_builtins(t_data *minis, char **envp)
{
    int i;
    int len;

    i = 0;
    while(i < minis->nb_cmd)
    {
        len = ft_strlen(minis->cmd[i].tab[0]);
        if(ft_strcmp(minis->cmd[i].tab[0], "pwd") == 0 && minis->cmd[i].nb_words == 2)//==2 ->aucune options ni arg
            ft_pwd();
        else if(ft_strcmp(minis->cmd[i].tab[0], "env") == 0 && minis->cmd[i].nb_words == 2)//==2 ->aucune options ni arg
            ft_envp(minis);
        else if(ft_strcmp(minis->cmd[i].tab[0], "echo") == 0)
            ft_echo(&minis->cmd[i]);
        else if(ft_strcmp(minis->cmd[i].tab[0], "exit") == 0 && minis->cmd[i].nb_words == 2)//==2 ->aucune options ni arg
            ft_exit(minis);
        else if(ft_strcmp(minis->cmd[i].tab[0], "cd") == 0)
            ft_cd(minis, &minis->cmd[i]);
        else if(ft_strcmp(minis->cmd[i].tab[0], "export") == 0)
            ft_export(minis, &minis->cmd[i]);
        else if(ft_strcmp(minis->cmd[i].tab[0], "unset") == 0)
            ft_unset(minis, &minis->cmd[i]);
        i++;
    }
}