#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "../libft/libft.h"

typedef struct s_board
{
	char *line_cmd;//la commande
}				t_board;

typedef struct s_data
{
	char *line;//la ligne lue
	char **tab_cmd;
	int nb_cmd;//le nombre de commande lue sur la ligne
	t_board *cmd;//tableau de structure pour chaque commande cmd[0]->structure de la premiere commande
}			t_data;


//main.c
void minishell_loop(void);
void control_c();

//ft_split_cmd.c
void line_to_cmd(t_data *minis);
char *str_cpy_cmd(char *line, int *i, t_data *minis);
int ft_len_cmd(char *line);
int ft_count_command(char *line);
int is_no_open_quote(char *line, int i);

//innit_struct.c
void init_struct(t_data *minis);
void free_struct(t_data *minis);

//ft_error.c
void ft_error(char *message, t_data *minis, int z);
void free_tab(char **tab, int i);

#endif
