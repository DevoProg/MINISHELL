#include "../includes/minishell.h"

void ft_pwd(t_data *minis)
{
    ft_putendl_fd(minis->path, 1);
}