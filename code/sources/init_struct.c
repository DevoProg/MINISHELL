#include "../includes/minishell.h"

void init_struct(t_data *minis)
{
    int i;

    minis->cmd = malloc(sizeof(t_board) * minis->nb_cmd);
    if(!minis->cmd)
        ft_error("Malloc doesn't work", minis, 2);
    i = 0;
    while(i < minis->nb_cmd)
    {
        minis->cmd[i].line_cmd = ft_strdup(minis->tab_cmd[i]);
        if(!minis->cmd[i].line_cmd)
            ft_error("Malloc doesn't work", minis, 3);
        i++;
    }
    free_tab(minis->tab_cmd, minis->nb_cmd + 1);
    i = 0;
    while(i < minis->nb_cmd)
    {
        printf("%s\n", minis->cmd[i].line_cmd);
        // if(i < minis->nb_tab - 1)
        //     printf("--->il faudra pipe le fd\n");
        i++;
    }
}