#include "../../includes/minishell.h"

void    fork_one_cmd(t_data *minis, char **envp, int redi_pipe[2][2], t_board *cmd)
{
    redirect_infile(cmd, redi_pipe[0]);
    if(is_redi_outfile(cmd))
        dup2(redi_pipe[1][1], STDOUT_FILENO);
    if(is_redi_infile(cmd))
        dup2(redi_pipe[0][0], STDIN_FILENO);
    close_redi_pipe(redi_pipe);
    if (!ft_is_builtins(cmd))
        execve(cmd->cmd_path, cmd->tab, envp);
    ft_check_builtins(minis, cmd);
    exit(1);
}

void fork_first_cmd(t_data *minis, char **envp, int redi_pipe[2][2], int i)
{
    redirect_infile(&minis->cmd[0], redi_pipe[0]);
    if(is_redi_infile(&minis->cmd[i]))
        dup2(redi_pipe[0][0], STDIN_FILENO);
    dup2(redi_pipe[1][1], STDOUT_FILENO);
    close_all_pipes(minis);
    close_redi_pipe(redi_pipe);
    if(!ft_is_builtins(&minis->cmd[0]))
        execve(minis->cmd[0].cmd_path, minis->cmd[0].tab, envp);
    ft_check_builtins(minis, &minis->cmd[0]);
    exit(1);
}

void fork_middle_cmd(t_data *minis, char **envp, int redi_pipe[2][2], int i)
{
    res_cmd_to_pipe(minis->cmd[i - 1].pipe_fd, redi_pipe[0], &minis->cmd[i], 0);
    redirect_infile(&minis->cmd[i], redi_pipe[0]);
    dup2(redi_pipe[0][0], STDIN_FILENO);
    dup2(redi_pipe[1][1], STDOUT_FILENO);
    close_all_pipes(minis);
    close_redi_pipe(redi_pipe);
    if(!ft_is_builtins(&minis->cmd[i]))
        execve(minis->cmd[i].cmd_path, minis->cmd[i].tab, envp);
    ft_check_builtins(minis, &minis->cmd[i]);
    exit(1);
}

void fork_last_cmd(t_data *minis, char **envp, int redi_pipe[2][2], int i)
{
    res_cmd_to_pipe(minis->cmd[i - 1].pipe_fd, redi_pipe[0], &minis->cmd[i], 0);
    redirect_infile(&minis->cmd[i], redi_pipe[0]);
    dup2(redi_pipe[0][0], STDIN_FILENO);
    if(is_redi_outfile(&minis->cmd[i]))
        dup2(redi_pipe[1][1], STDOUT_FILENO);
    close_all_pipes(minis);
    close_redi_pipe(redi_pipe);
    if(!ft_is_builtins(&minis->cmd[i]))
        execve(minis->cmd[i].cmd_path, minis->cmd[i].tab, envp);
    ft_check_builtins(minis, &minis->cmd[i]);
    exit(1);
}