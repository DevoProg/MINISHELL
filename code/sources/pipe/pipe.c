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
    if (cmd->res_fork < 0) {
        return ;
    }
    
    if (cmd->res_fork == 0) {
        // Child process 1 (ping)
        if(!ft_is_builtins(minis, cmd))
            execve(cmd->cmd_path, cmd->tab, envp);
        ft_check_builtins(minis, cmd);
        exit(1);
    }
}

void first_cmd(t_data *minis, t_board *cmd, char **envp, int **fd, int i)
{
    cmd->res_fork = fork();
    if (cmd->res_fork < 0) {
        return ;
    }
    
    if (cmd->res_fork == 0) {
        // Child process 1 (ping)
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
    if (cmd->res_fork < 0) {
        return ;
    }

    if (cmd->res_fork == 0) {
        // Child process 2 (grep)
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
    if (cmd->res_fork < 0) {
        return ;
    }

    if (cmd->res_fork == 0) {
        // Child process 2 (grep)
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
        minis->cmd[i].cmd_path = ft_try_path(minis, path, &minis->cmd[i]);
        //printf("%s\n", minis->cmd[i].cmd_path);
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
void ft_pipe(t_data *minis, char **envp)
{
    
    int i;
    int **fd;

    find_path_struct(minis);
    if(minis->nb_cmd == 1)
    {
        just_one_cmd(minis, &minis->cmd[0], envp);
        waitpid(minis->cmd[0].res_fork, NULL, 0);
        return;
    }
    fd = malloc(sizeof(int*) * (minis->nb_cmd - 1));
    i = 0;
    while(i < minis->nb_cmd - 1)
    {
        fd[i] = malloc(sizeof(int) * 2);
        if (pipe(fd[i]) == -1)
            return;
        i++;
    }
    ft_execute(minis, fd, envp);
    close_all_pipes(minis, fd);
    wait_all_pids(minis);
}