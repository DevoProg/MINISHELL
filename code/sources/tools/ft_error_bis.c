#include "../../includes/minishell.h"

void ft_error_pipe(t_data *minis, int redi_pipe[2][2], int y, int z)
{
	if(y == 0 || y == 1)
	{
		close(redi_pipe[0][1]);
		close(redi_pipe[1][1]);
	}
	if(y == 0 || y == 2)
	{
		close(redi_pipe[0][0]);
		close(redi_pipe[1][0]);
	}
	if(z == 1)
		close_all_pipes(minis);
	ft_error("Malloc", minis, 3, 1);
}

void ft_error_in_fork(t_data *minis, int redi_pipe[2][2])
{
	close_all_pipes(minis);
	close_redi_pipe(redi_pipe);
	ft_error("Malloc", minis, 3, 1);
	close_all_pipes(minis);
	close_redi_pipe(redi_pipe);
	ft_error("Malloc", minis, 3, 1);
}

void ft_error_to_pipe(t_data *minis, int i)
{
	int z;
	
	z = 0;
	while(z <  i)
	{
		close(minis->cmd[z].pipe_fd[0]);
		close(minis->cmd[z].pipe_fd[1]);
			z++;
	}
	ft_error("Pipe", minis, 3, 1);
	
}
