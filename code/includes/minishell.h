#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "../libft/libft.h"

typedef struct s_data
{
	char *line;
	char **tab_cmd;
	int nb_tab;
}			t_data;

void line_to_cmd(t_data *minis);
void ft_error(char *message, t_data *minis, int z);

#endif
