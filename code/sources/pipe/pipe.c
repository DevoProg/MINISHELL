#include "../../includes/minishell.h"

void wait_all_pids(t_data *minis)
{
    int i;

    i = 0;
    while(i < minis->nb_cmd)
    {
        waitpid(minis->cmd[i].res_fork, NULL, 0);
        i++;
    }
}

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

void just_one_cmd(t_data *minis, t_board *cmd, char **envp)
{
    cmd->res_fork = fork();
    if (cmd->res_fork < 0)
        exit(1);//il faudra exit prorpement
    
    if (cmd->res_fork == 0) 
    {
        if (!ft_is_builtins(minis, cmd))
            execve(cmd->cmd_path, cmd->tab, envp);
        ft_check_builtins(minis, cmd);
        exit(1);
    }
}

void first_cmd(t_data *minis, t_board *cmd, char **envp, int **fd, int i)
{
    cmd->res_fork = fork();
    if (cmd->res_fork < 0)
        exit(1);//il faudra quitter prorement
    if (cmd->res_fork == 0) 
    {
        dup2(fd[i][1], STDOUT_FILENO);
        close_all_pipes(minis, fd);
        if(!ft_is_builtins(minis, cmd))
            execve(cmd->cmd_path, cmd->tab, envp);
        ft_check_builtins(minis, cmd);
        exit(1);
    }
}

void middle_cmd(t_data *minis, t_board *cmd, char **envp, int **fd, int i)
{
    cmd->res_fork = fork();
    if (cmd->res_fork < 0)
        exit(1);//il faudra quitter prormeent
    if (cmd->res_fork == 0)
    {
        dup2(fd[i - 1][0], STDIN_FILENO);
        dup2(fd[i][1], STDOUT_FILENO);
        close_all_pipes(minis, fd);
        if(!ft_is_builtins(minis, cmd))
            execve(cmd->cmd_path, cmd->tab, envp);
        ft_check_builtins(minis,  cmd);
        exit(1);
    }
}

void last_cmd(t_data *minis, t_board *cmd, char **envp, int **fd, int i)
{
    cmd->res_fork = fork();
    if (cmd->res_fork < 0) 
        exit(1);//il faudrda quitter prorpement
    if (cmd->res_fork == 0)
    {
        dup2(fd[i - 1][0], STDIN_FILENO);
        close_all_pipes(minis, fd);
        if(!ft_is_builtins(minis, cmd))
            execve(cmd->cmd_path, cmd->tab, envp);
        ft_check_builtins(minis, cmd);
        exit(1);
    }
}

void find_path_struct(t_data *minis)
{
    char *path;
    int i;

    i = 0;
    path = list_chr(minis->env, "PATH");
    while(i < minis->nb_cmd)
    {
        if(!ft_is_builtins(minis, &minis->cmd[i]))
        {

            minis->cmd[i].cmd_path = ft_try_path(minis, path, &minis->cmd[i]);
            if(!minis->cmd[i].cmd_path)
                printf("command not found: %s\n", minis->cmd[i].tab[0]);
        }

        i++;
    }
}

void ft_execute(t_data *minis, int **fd, char **envp)
{
    int i;

    i = 0;
    while(i < minis->nb_cmd)
    {
        if(i == 0)
            first_cmd(minis, &minis->cmd[i], envp, fd, i);
        else if(i == minis->nb_cmd - 1)
            last_cmd(minis, &minis->cmd[i], envp, fd, i);
        else 
            middle_cmd(minis, &minis->cmd[i], envp ,fd, i);
        i++;
    }
}

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
void ft_pipe(t_data *minis, char **envp)
{   
    int i;
    int **fd;

    find_path_struct(minis);
    if(minis->nb_cmd == 1)//si il n'y a qu'un seule commande
    {
        just_one_cmd(minis, &minis->cmd[0], envp);
        waitpid(minis->cmd[0].res_fork, NULL, 0);
        return;
    }
    fd = malloc_pipes(minis);
    ft_execute(minis, fd, envp);
    close_all_pipes(minis, fd);
    wait_all_pids(minis);
}