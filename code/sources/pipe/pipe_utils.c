#include "../../includes/minishell.h"


void close_for_cmd_pipe(t_data *minis, int z, int i)
{
	if(z == 1)
		close(minis->cmd[0].pipe_fd[1]);
	if(z == 2)
	{
		close(minis->cmd[i - 1].pipe_fd[0]);
		close(minis->cmd[i].pipe_fd[1]);
	}
	if(z == 3)
		close(minis->cmd[i - 1].pipe_fd[0]);
}

int error_or_not_fork(t_data *minis, t_board *cmd, int z, int i)
{

	if (!infile_error_message(minis, &minis->cmd[i], 1))
	{	
		close_for_cmd_pipe(minis, z, i);
		return (1);
	}
	if (ft_is_not_fork(cmd))
	{
		close_for_cmd_pipe(minis, z, i);
		butiltins_without_fork(minis, cmd, i);
		return (1);
	}
	return (0);
}

int	command_error_message(t_data *minis, t_board *cmd, int print)
{
	if (!cmd->cmd_path && !ft_is_builtins(cmd))
	{
		if (print == 1)
		{
			ft_putstr_fd("Command not found :", 2);
			ft_putstr_fd(cmd->tab[0], 2);
			ft_putchar_fd('\n', 2);
		}
		return (0);
	}
	return (1);
}

int check_acces_read(t_redi *ptr, int print)
{
	if (access(ptr->file, R_OK) != 0)
	{
		if (print == 1)		
		{
			ft_putstr_fd("Error to open file :", 2);
			ft_putstr_fd(ptr->file, 2);
			ft_putchar_fd('\n', 2);
		}
		return (0);
	}
	return(1);
}

int	infile_error_message(t_data *minis, t_board *cmd, int print)
{
	t_redi	*ptr;

	ptr = cmd->redi;
	if (!ptr)
		return (command_error_message(minis, cmd, print));
	while (ptr->next != NULL)
	{
		if (ptr->type == INFILE)
			if (!check_acces_read(ptr, print))
				return (0);
		ptr = ptr->next;
	}
	if (ptr->type == INFILE)
		if (!check_acces_read(ptr, print))
			return (0);
	return (command_error_message(minis, cmd, print));
}
