#include "../../includes/minishell.h"

void ft_pipe(t_data *minis, char **envp)
{
    char *path;
    int i;

    i = 0;
    path = list_chr(minis->env, "PATH");
    while(i < minis->nb_cmd)
    {
        minis->cmd[i].cmd_path = ft_try_path(minis, path, &minis->cmd[i]);
        printf("%s\n", minis->cmd[i].cmd_path);
        i++;
    }
}