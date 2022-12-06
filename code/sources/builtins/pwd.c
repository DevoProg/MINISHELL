#include "../includes/minishell.h"

int	ft_pwd(void)
{
	char	cwd[PATH_LEN];

	if (getcwd(cwd, PATH_LEN))
	{
		ft_putendl_fd(cwd, 1);
		return (SUCCESS);
	}
	else
		return (ERROR);
}