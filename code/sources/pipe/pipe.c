#include "../../includes/minishell.h"

/*
    fonction qui ferme tous les pipes
*/
void close_all_pipes(t_data *minis)
{
    int i;

    i = 0;
    while(i < minis->nb_cmd - 1)
    {
        close(minis->cmd[i].pipe_fd[0]);
        close(minis->cmd[i].pipe_fd[1]);
        i++;
    }
}

/*
    fonction qui recherche le chemin d'acces de la commande pour execve
*/
void find_path_struct(t_data *minis)
{
    char *path;
    int i;

    i = 0;
    path = list_chr(minis->env, "PATH");
    while(i < minis->nb_cmd)
    {
        if(!ft_is_builtins(&minis->cmd[i]))
        {
            minis->cmd[i].cmd_path = ft_try_path(minis, path, &minis->cmd[i]);
            if(!minis->cmd[i].cmd_path)
                printf("command not found: %s\n", minis->cmd[i].tab[0]);
        }
        i++;
    }
    return ;
}

/*
    fonction qui crée le nombre de pipe nécessaire
*/
void create_pipe(t_data *minis)
{
    int i;

    i = 0;
    while(i < minis->nb_cmd - 1)
    {
        if (pipe(minis->cmd[i].pipe_fd) == -1)
            exit(1);//il faudra quitter prorpement
        i++;
    }
}

/*
    fonction principale du pipe
*/
int ft_pipe(t_data *minis, char **envp)
{   
    int **fd;
    int res;

    find_path_struct(minis);
    if(minis->nb_cmd == 1)//si il n'y a qu'un seule commande
    {
        if(!minis->cmd[0].cmd_path && !ft_is_builtins(&minis->cmd[0]))
            return(127);
        res = just_one_cmd(minis, &minis->cmd[0], envp);
        if(!ft_is_not_fork(&minis->cmd[minis->nb_cmd - 1]) && ft_is_builtins(&minis->cmd[minis->nb_cmd - 1]))
            res = 0;
        return (res);
    }
    create_pipe(minis);
    res = ft_execute(minis, envp);
    if(!ft_is_not_fork(&minis->cmd[minis->nb_cmd - 1]) && ft_is_builtins(&minis->cmd[minis->nb_cmd - 1]))
            res = 0;
    return(res);//il faudra chopper la variable
}