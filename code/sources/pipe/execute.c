#include "../../includes/minishell.h"
/*
    fonction qui execute une commande car elle est seule dans la ligne lue
*/
void just_one_cmd(t_data *minis, t_board *cmd, char **envp)
{
    int redi_pipe[2][2];

    if(pipe(redi_pipe[0]) == -1)
        exit(1);
    if(pipe(redi_pipe[1]) == -1)
        exit(1);
    if(ft_is_not_fork(cmd))
    {
        ft_check_builtins(minis, cmd);
        return ;
    }
    cmd->res_fork = fork();
    if (cmd->res_fork < 0)
        exit(1);//il faudra exit prorpement
    
    if (cmd->res_fork == 0) 
    {
        dup_files_in(cmd, redi_pipe);
        close_redi_pipe(redi_pipe);
        if (!ft_is_builtins(cmd))
            execve(cmd->cmd_path, cmd->tab, envp);
        ft_check_builtins(minis, cmd);
        exit(1);
    }
    close_redi_pipe(redi_pipe);
    //printf("%s", get_next_line(redi_pipe[1][0]));
    
}

/*
    fonction qui execute la premiere commande
*/
void first_cmd(t_data *minis, char **envp, int **fd, int i)
{
    t_board *cmd;

    cmd = &minis->cmd[i];
    if(ft_is_not_fork(cmd))
    {
        ft_check_builtins(minis, cmd);
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

    cmd = &minis->cmd[i];
    if(ft_is_not_fork(cmd))
    {
        ft_check_builtins(minis, cmd);
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

    cmd = &minis->cmd[i];
    if(ft_is_not_fork(cmd))
    {
        ft_check_builtins(minis, cmd);
        return ;
    }
    cmd->res_fork = fork();
    if (cmd->res_fork < 0) 
        exit(1);//il faudrda quitter prorpement
    if (cmd->res_fork == 0)
    {
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
