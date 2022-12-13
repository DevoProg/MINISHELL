#include "../../includes/minishell.h"

/*
    Cas commande : PWD.
*/
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

/*
    Cas commande : ENV.
*/
void ft_envp(t_data *minis)
{
    print_list(minis->env, 0);
}

/*
    Cas commande : ECHO.
*/
void ft_echo(t_board *cmd)
{
    int i;
    int option;

    if(cmd->nb_words == 2)//si il n'y a pas d'argument ni option
    {
        ft_putchar_fd('\n', 1);
        return;
    }
    if (ft_strcmp(cmd->tab[1], "-n") == 0)//option détécté est on passe a l'argument d'apres
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
        if ((i > 1 && option == 0) || (i > 2 && option == 1))//afficher un espace entre chaque argument
            ft_putchar_fd(' ', 1);
        ft_putstr_fd(cmd->tab[i], 1);
        i++;
    }
    if(option == 0)
        ft_putchar_fd('\n', 1);
}

/*
    Cas commande : EXIT
    Fonction servant a exit. 
    Free tout les elements en mémoire.
*/
void ft_exit(t_data *minis)
{
    free_struct(minis);
    free_list(minis->env);
    exit(1);
}

/*
    Fonction servant a check si une commande contient les différentes fct bash.
*/
void ft_check_builtins(t_data *minis)
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