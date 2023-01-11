#include "../../includes/minishell.h"

/*
    fonction qui attend l'execution de tous les forks
*/
int wait_all_pids(t_data *minis)
{
    int i;
    int res;

    i = 0;
    while(i < minis->nb_cmd)
    {
        if(!ft_is_not_fork(&minis->cmd[i]))//si il faut fork alors on wait le porcess
            waitpid(minis->cmd[i].res_fork, &res, 0);
        i++;
    }
    return (WEXITSTATUS(res));
}

/*
    fonction qui ferme tous les pipes
*/
void close_all_pipes(t_data *minis, int **fd)
{
    int i;

    i = 0;
    while(i < minis->nb_cmd - 1)
    {
        close(fd[i][0]);
        close(fd[i][1]);
        i++;
    }
}

/*
    fonction qui recherche le chemin d'acces de la commande pour execve
*/
int find_path_struct(t_data *minis)
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
            {
                printf("command not found: %s\n", minis->cmd[i].tab[0]);
                return (127);
            }
        }
        i++;
    }
    return(0);
}

/*
    fonction qui alloue une double tableau de pipe
*/
int **malloc_pipes(t_data *minis)
{
    int **fd;
    int i;

    fd = malloc(sizeof(int*) * (minis->nb_cmd - 1));
    if(!fd)
        exit(1);//il faudra quitter proprement
    i = 0;
    while(i < minis->nb_cmd - 1)
    {
        fd[i] = malloc(sizeof(int) * 2);
        if(!fd[i])
            exit(1);//il faudra quitter prorpement
        if (pipe(fd[i]) == -1)
            exit(1);//il faudra quitter prorpement
        i++;
    }
    return(fd);
}

/*
    fonction principale du pipe
*/
int ft_pipe(t_data *minis, char **envp)
{   
    int **fd;
    int res;

    if(find_path_struct(minis) == 127)
        return(127);
    if(minis->nb_cmd == 1)//si il n'y a qu'un seule commande
    {
        res = just_one_cmd(minis, &minis->cmd[0], envp);
        return (res);
    }
    fd = malloc_pipes(minis);
    ft_execute(minis, fd, envp);
    //close_all_pipes(minis, fd);
    //res = wait_all_pids(minis);
    res = 0;
    return(res);//il faudra chopper la variable
}