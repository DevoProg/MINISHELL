#include "../../includes/minishell.h"
/*
    fonction qui execute une commande car elle est seule dans la ligne lue
*/
int just_one_cmd(t_data *minis, t_board *cmd, char **envp)
{
    int res;
    int redi_pipe[2][2];

    if(pipe(redi_pipe[0]) == -1)
        exit(1);//il faudra quitter prorpement
    if(pipe(redi_pipe[1]) == -1)
        exit(1);//il faudra quitter proprement
    if(ft_is_not_fork(cmd))
    {
        ft_check_builtins(minis, cmd);
        close_redi_pipe(redi_pipe);
        return (0);//il faudra retoruner la bonne valeur pour chaque builtin?
    }
    cmd->res_fork = fork();
    if (cmd->res_fork < 0)
        exit(1);//il faudra exit prorpement
    
    if (cmd->res_fork == 0) 
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
void first_cmd(t_data *minis, char **envp, int **fd, int i)
{
    t_board *cmd;
    int redi_pipe[2][2];

    if(pipe(redi_pipe[0]) == -1)
        exit(1);//il faudra quitter prorpement
    if(pipe(redi_pipe[1]) == -1)
        exit(1);//il faudra quitter proprement

    cmd = &minis->cmd[i];
    if(ft_is_not_fork(cmd))
    {
        ft_check_builtins(minis, cmd);
        close_redi_pipe(redi_pipe);
        return ;
    }
    cmd->res_fork = fork();
    if (cmd->res_fork < 0)
        exit(1);//il faudra quitter prorement
    if (cmd->res_fork == 0) 
    {
        dup2(fd[i][1], STDOUT_FILENO);
        close_all_pipes(minis, fd);
        if(!ft_is_builtins(cmd))
            execve(cmd->cmd_path, cmd->tab, envp);
        ft_check_builtins(minis, cmd);
        exit(1);
    }
}

/*
    fonction qui execute la commande du millieu
*/
void middle_cmd(t_data *minis, char **envp, int **fd, int i)
{
    t_board *cmd;
    int redi_pipe[2][2];

    if(pipe(redi_pipe[0]) == -1)
        exit(1);//il faudra quitter prorpement
    if(pipe(redi_pipe[1]) == -1)
        exit(1);//il faudra quitter proprement

    cmd = &minis->cmd[i];
    if(ft_is_not_fork(cmd))
    {
        ft_check_builtins(minis, cmd);
        close_redi_pipe(redi_pipe);
        return ;
    }
    cmd->res_fork = fork();
    if (cmd->res_fork < 0)
        exit(1);//il faudra quitter prormeent
    if (cmd->res_fork == 0)
    {
        dup2(fd[i - 1][0], STDIN_FILENO);
        dup2(fd[i][1], STDOUT_FILENO);
        close_all_pipes(minis, fd);
        if(!ft_is_builtins(cmd))
            execve(cmd->cmd_path, cmd->tab, envp);
        ft_check_builtins(minis, cmd);
        exit(1);
    }
}

/*
    fonction qui execute la derniere commande
*/
void last_cmd(t_data *minis, char **envp, int **fd, int i)
{
    t_board *cmd;
    int redi_pipe[2][2];

    if(pipe(redi_pipe[0]) == -1)
        exit(1);//il faudra quitter prorpement
    if(pipe(redi_pipe[1]) == -1)
        exit(1);//il faudra quitter proprement

    cmd = &minis->cmd[i];
    if(ft_is_not_fork(cmd))
    {
        ft_check_builtins(minis, cmd);
        close_redi_pipe(redi_pipe);
        return ;
    }
    cmd->res_fork = fork();
    if (cmd->res_fork < 0) 
        exit(1);//il faudrda quitter prorpement
    if (cmd->res_fork == 0)
    {
        if(is_redi_infile(&minis->cmd[i]))
        {
            redirect_infile(cmd, redi_pipe[0]);
            dup2(redi_pipe[0][0], STDIN_FILENO);
        }
        dup2(fd[i - 1][0], STDIN_FILENO);
        close_all_pipes(minis, fd);
        if(!ft_is_builtins(cmd))
            execve(cmd->cmd_path, cmd->tab, envp);
        ft_check_builtins(minis, cmd);
        exit(1);
    }
}

/*
    fonction qui execute toutes les commandes en fonction de leur emplacement dans la ligne lue
*/
void ft_execute(t_data *minis, int **fd, char **envp)
{
    int i;

    i = 0;
    while(i < minis->nb_cmd)
    {
        if(i == 0)
            first_cmd(minis, envp, fd, i);
        else if(i == minis->nb_cmd - 1)
            last_cmd(minis, envp, fd, i);
        else 
            middle_cmd(minis, envp ,fd, i);
        i++;
    }
}
