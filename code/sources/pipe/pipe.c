#include "../../includes/minishell.h"

void first_cmd(t_data *minis, t_board *cmd, char **envp, int fd[3][2])
{
    cmd->res_fork = fork();
    if (cmd->res_fork < 0) {
        return ;
    }
    
    if (cmd->res_fork == 0) {
        // Child process 1 (ping)
        dup2(fd[0][1], STDOUT_FILENO);
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

void middle_cmd(t_data *minis, t_board *cmd, char **envp, int fd[3][2])
{
    cmd->res_fork = fork();
    if (cmd->res_fork < 0) {
        return ;
    }

    if (cmd->res_fork == 0) {
        // Child process 2 (grep)
        dup2(fd[0][0], STDIN_FILENO);
        dup2(fd[1][1], STDOUT_FILENO);
        close(fd[0][0]);
        close(fd[0][1]);
        close(fd[1][0]);
        close(fd[1][1]);
        close(fd[2][0]);
        close(fd[2][1]);
        if(!ft_is_builtins(minis, &minis->cmd[1]))
            execve(minis->cmd[1].cmd_path, minis->cmd[1].tab, envp);
        ft_check_builtins(minis,  &minis->cmd[1]);
        exit(1);
    }
}

void last_cmd(t_data *minis, t_board *cmd, char **envp, int fd[3][2])
{
    cmd->res_fork = fork();
    if (cmd->res_fork < 0) {
        return ;
    }

    if (cmd->res_fork == 0) {
        // Child process 2 (grep)
        dup2(fd[1][0], STDIN_FILENO);
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
    int fd[3][2];
//     // fd = malloc(sizeof(int*));
//     // fd[0] = malloc(sizeof(int) * 2);
//     // fd[1] = malloc(sizeof(int) * 2);
    if (pipe(fd[0]) == -1) {
        return;
    }
    if (pipe(fd[1]) == -1) {
        return;
    }
    if (pipe(fd[2]) == -1) {
        return;
    }

    first_cmd(minis, &minis->cmd[0], envp, fd);
    middle_cmd(minis, &minis->cmd[1], envp ,fd);
    middle_cmd(minis, &minis->cmd[2], envp ,fd);
    last_cmd(minis, &minis->cmd[3], envp, fd);
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