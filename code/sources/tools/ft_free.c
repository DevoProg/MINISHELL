#include "../../includes/minishell.h"

void	free_struct_cmd(t_data *minis)
{
	int	i;

	i = 0;
	while (i < minis->nb_cmd)
	{
		if (minis->cmd[i].line_cmd)
			free(minis->cmd[i].line_cmd);
		if (minis->cmd[i].tab)
			free_tab(minis->cmd[i].tab, minis->cmd[i].nb_words);
		if (minis->cmd[i].cmd_path)
			free(minis->cmd[i].cmd_path);
		i++;
	}
	free(minis->cmd);
}

void	free_tab(char **tab, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if(tab[j])
			free(tab[j]);
		j++;
	}
	free(tab);
}

void	free_list(t_var *env)
{
	if(!env)
		return ;
	while (env->next)
	{
		env = ft_delete_first_node(env);
	}
	ft_delete_first_node(env);
}