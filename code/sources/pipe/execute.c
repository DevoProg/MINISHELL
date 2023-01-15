#include "../../includes/minishell.h"
/*
    fonction qui execute une commande car elle est seule dans la ligne lue
*/
int just_one_cmd(t_data *minis, t_board *cmd, char **envp)
{
    int redi_pipe[2][2];
    int res;

    if(!infile_error_message(minis, &minis->cmd[0], 1))
    {
        return (1);
    }
    if(ft_is_not_fork(cmd))
    {
        butiltins_without_fork(minis, cmd, 0);
        return (0);//il faudra retoruner la bonne valeur pour chaque builtin?
    }
    ft_pipe_redi(redi_pipe);
    cmd->res_fork = fork();
    if (cmd->res_fork < 0)
        exit(1);//il faudra exit prorpement
    if (cmd->res_fork == 0)
        fork_one_cmd(minis, envp, redi_pipe, cmd);
    close(redi_pipe[1][1]);
    close(redi_pipe[0][1]);
    waitpid(minis->cmd[0].res_fork, &res, 0);
    if(is_redi_outfile(cmd))
        redirect_outfile(cmd, redi_pipe[1]);
    close(redi_pipe[0][0]);
    close(redi_pipe[1][0]);
    return(WEXITSTATUS(res));
}

/*
    fonction qui execute la premiere commande
*/
void first_cmd(t_data *minis, char **envp, int i)
{
    t_board *cmd;
    int redi_pipe[2][2];

    cmd = &minis->cmd[i];
    if(!infile_error_message(minis, &minis->cmd[i], 1))
    {
        close(minis->cmd[0].pipe_fd[1]);
        return;
    }
    if(ft_is_not_fork(cmd))
    {
        butiltins_without_fork(minis, cmd, i);
        return ;//il faudra retoruner la bonne valeur pour chaque builtin?
    }
    ft_pipe_redi(redi_pipe);
    cmd->res_fork = fork();
    if (cmd->res_fork < 0)
        exit(1);//il faudra quitter prorement
    if (cmd->res_fork == 0)
        fork_first_cmd(minis, envp, redi_pipe, i);
    close(redi_pipe[1][1]);
    close(redi_pipe[0][1]);
    res_cmd_to_pipe(redi_pipe[1], minis->cmd[0].pipe_fd, cmd, 1);
    close(redi_pipe[0][0]);
    close(redi_pipe[1][0]);
    close(minis->cmd[0].pipe_fd[1]);
}

/*
    fonction qui execute la commande du millieu
*/
void middle_cmd(t_data *minis, char **envp, int i)
{
    t_board *cmd;
    int redi_pipe[2][2];

    if(!infile_error_message(minis, &minis->cmd[i], 1))
    {
        close(minis->cmd[i - 1].pipe_fd[0]);
        close(minis->cmd[i].pipe_fd[1]);
        return;
    }
    cmd = &minis->cmd[i];
    if(ft_is_not_fork(cmd))
    {
        butiltins_without_fork(minis, cmd, i);
        return ;//il faudra retoruner la bonne valeur pour chaque builtin?
    }
    ft_pipe_redi(redi_pipe);
    cmd->res_fork = fork();
    if (cmd->res_fork < 0)
        exit(1);//il faudra quitter prormeent
    if (cmd->res_fork == 0)
        fork_middle_cmd(minis, envp, redi_pipe, i);
    close(redi_pipe[1][1]);
    close(redi_pipe[0][1]);
    res_cmd_to_pipe(redi_pipe[1], minis->cmd[i].pipe_fd, cmd, 1);
    close(redi_pipe[0][0]);
    close(redi_pipe[1][0]);
    close(minis->cmd[i - 1].pipe_fd[0]);
    close(minis->cmd[i].pipe_fd[1]);
}

/*
    fonction qui execute la derniere commande
*/
void last_cmd(t_data *minis, char **envp, int i)
{
    t_board *cmd;
    int res;
    int redi_pipe[2][2];

    if(!infile_error_message(minis, &minis->cmd[i], 1))
    {
        close(minis->cmd[i - 1].pipe_fd[0]);
        return;
    }
    cmd = &minis->cmd[i];
    if(ft_is_not_fork(cmd))
    {
        butiltins_without_fork(minis, cmd, i);
        return ;//il faudra retoruner la bonne valeur pour chaque builtin?
    }
    ft_pipe_redi(redi_pipe);
    cmd->res_fork = fork();
    if (cmd->res_fork < 0) 
        exit(1);//il faudrda quitter prorpement
    if (cmd->res_fork == 0)
        fork_last_cmd(minis, envp, redi_pipe, i);
    close(redi_pipe[1][1]);
    close(redi_pipe[0][1]);
    if(is_redi_outfile(cmd))
        redirect_outfile(cmd, redi_pipe[1]);
    close(redi_pipe[0][0]);
    close(redi_pipe[1][0]);
    close_redi_pipe(redi_pipe);
    close(minis->cmd[i - 1].pipe_fd[0]);
}

/*
    fonction qui execute toutes les commandes en fonction de leur emplacement dans la ligne lue
*/
int ft_execute(t_data *minis, char **envp)
{
    int i;
    int res;

    i = 0;
    while(i < minis->nb_cmd)
    {
        if(i == 0)
        {
            first_cmd(minis, envp, i);
            if(!ft_is_not_fork(&minis->cmd[i]) && infile_error_message(minis, &minis->cmd[i], 0))
                waitpid(minis->cmd[i].res_fork, &res, 0);
        }
        else if(i == minis->nb_cmd - 1)
        {
            last_cmd(minis, envp, i);
            if(!ft_is_not_fork(&minis->cmd[i]) && infile_error_message(minis, &minis->cmd[i], 0))
                waitpid(minis->cmd[i].res_fork, &res, 0);
            if(!minis->cmd[i].cmd_path && !ft_is_builtins(&minis->cmd[i]))
                return(127);
        }
        else
        {
            middle_cmd(minis, envp, i);
            if(!ft_is_not_fork(&minis->cmd[i]) && infile_error_message(minis, &minis->cmd[i], 0))
                waitpid(minis->cmd[i].res_fork, &res, 0);
        }
        i++;
    }
    return (WEXITSTATUS(res));
}
