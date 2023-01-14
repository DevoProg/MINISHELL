#include "../../includes/minishell.h"

/*
    Cas commande : PWD.
*/
void    ft_pwd(t_data *minis)
{
    char    cwd[PATH_LEN];

    if (getcwd(cwd, PATH_LEN))
    {
        ft_putendl_fd(cwd, 1);
        put_res_pipe(minis, 0);
        return ;
    }
    put_res_pipe(minis, 1);
}

/*
    Cas commande : ENV.
*/
void ft_envp(t_data *minis)
{
    print_list(minis->env, 0);
    put_res_pipe(minis, 0);

}

/*
    Cas commande : ECHO.
*/
void ft_echo(t_data *minis, t_board *cmd)
{
    int i;
    int option;

    if(cmd->nb_words == 2)//si il n'y a pas d'argument ni option
    {
        ft_putchar_fd('\n', 1);
        put_res_pipe(minis, 0);
        return ;
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
    put_res_pipe(minis, 0);

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
void builtins_with_fork(t_data *minis, t_board *cmd)
{    
    if(ft_strcmp(cmd->tab[0], "pwd") == 0)
        ft_pwd(minis);
    else if(ft_strcmp(cmd->tab[0], "env") == 0)
        ft_envp(minis);
    else if(ft_strcmp(cmd->tab[0], "echo") == 0)
        ft_echo(minis, cmd);
    else if(ft_strcmp(cmd->tab[0], "exit") == 0)
        ft_exit(minis);
    else if(ft_strcmp(cmd->tab[0], "cd") == 0)
        ft_cd(minis, cmd);
    else if(ft_strcmp(cmd->tab[0], "export") == 0)
        ft_export(minis, cmd);
    else if(ft_strcmp(cmd->tab[0], "unset") == 0)
        ft_unset(minis, cmd);
}

/*
    Fonction qui execute les buitlins si il y a pas besoin de fork
*/
void butiltins_without_fork(t_data *minis, t_board *cmd, int i)
{
    if(minis->cmd[i + 1].line_cmd)//si il y a une commande apres celle ci elle ne fait rien
        return;
    if(ft_strcmp(cmd->tab[0], "exit") == 0)
        ft_exit(minis);
    else if(ft_strcmp(cmd->tab[0], "cd") == 0)
        ft_cd(minis, cmd);
    else if(ft_strcmp(cmd->tab[0], "export") == 0 && cmd->nb_words > 2)
        ft_export(minis, cmd);
    else if(ft_strcmp(cmd->tab[0], "unset") == 0)
        ft_unset(minis, cmd);
}