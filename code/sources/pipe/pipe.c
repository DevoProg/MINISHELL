#include "../../includes/minishell.h"

void first_cmd(t_data *minis, t_board *cmd, char **envp, int **fd, int i)
{
    cmd->res_fork = fork();
    if (cmd->res_fork < 0) {
        return ;
    }
    
    if (cmd->res_fork == 0) {
        // Child process 1 (ping)
        dup2(fd[i][1], STDOUT_FILENO);
        close(fd[0][0]);
        close(fd[0][1]);
        close(fd[1][0]);
        close(fd[1][1]);
        close(fd[2][0]);
        close(fd[2][1]);
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
        close(fd[0][0]);
        close(fd[0][1]);
        close(fd[1][0]);
        close(fd[1][1]);
        close(fd[2][0]);
        close(fd[2][1]);
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
        close(fd[0][0]);
        close(fd[0][1]);
        close(fd[1][0]);
        close(fd[1][1]);
        close(fd[2][0]);
        close(fd[2][1]);
        if(!ft_is_builtins(minis, cmd))
            execve(cmd->cmd_path, cmd->tab, envp);
        ft_check_builtins(minis, cmd);
        exit(1);
    }
}

void ft_pipe(t_data *minis, char **envp)
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
//     // ////////////////////////////////////////////////////////////////////
    int **fd;
    fd = malloc(sizeof(int*) * (minis->nb_cmd - 1));
    i = 0;
    while(i < minis->nb_cmd - 1)
    {
        fd[i] = malloc(sizeof(int) * 2);
        i++;
    }

    if (pipe(fd[0]) == -1) {
        return;
    }
    if (pipe(fd[1]) == -1) {
        return;
    }
    if (pipe(fd[2]) == -1) {
        return;
     }
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
    close(fd[0][0]);
    close(fd[0][1]);
    close(fd[1][0]);
    close(fd[1][1]);
    close(fd[2][0]);
    close(fd[2][1]);
    //if(!ft_is_builtins(minis, &minis->cmd[0]))
    waitpid(minis->cmd[0].res_fork, NULL, 0);
    // if(!ft_is_builtins(minis, &minis->cmd[1]))
    waitpid(minis->cmd[1].res_fork, NULL, 0);
    // if(!ft_is_builtins(minis, &minis->cmd[2]))
    waitpid(minis->cmd[2].res_fork, NULL, 0);

    waitpid(minis->cmd[3].res_fork, NULL, 0);

}