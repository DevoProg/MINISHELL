#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <dirent.h>
#include "../libft/includes/libft.h"
#include "../libft/includes/ft_printf.h"//pas oublier de retirer

#define PATH_LEN 1024

#define SUCCESS 1
#define ERROR 0

typedef struct s_var    // structure pour les variable d'env
{
	char *name;           // nom variable d'environnement.
	char *value;					// valeur de la variable d'environnement.
	int is_export;				// Si la var = '_'.
	struct s_var *next;   // Noeud suivant
}				t_var;


typedef struct s_board
{
	char *line_cmd;			//toute la commande qui a ete split du |
	char **tab;					//split la commande en tableau des espaces
	int nb_words;				//le nombre de cases dans le tableau
}				t_board;			//structure pour chaque commande

typedef struct s_data
{
	char *line;//la ligne lue
	int nb_cmd;//le nombre de commande lue sur la ligne lue
	char **tab_cmd;//tableau avec les commandes (il est free dans init_struct)
	t_var *env;
	t_board *cmd;//tableau de structure pour chaque commande cmd[0]->structure de la premiere commande
															//cmd[1]->de la deuxieme ect
}			t_data;//structure du programme minishell


//main.c
void minishell_loop(char **envp);
void control_c();

//ft_split_line.c
void line_to_cmd(t_data *minis);
char *str_cpy_cmd(char *line, int *i, t_data *minis);
int ft_count_command(char *line);

//innit_struct.c
void init_struct(t_data *minis);
void free_struct(t_data *minis);
t_var *lst_last(t_var *lst);
void lst_add(t_var **lst, t_var *new);
void ft_get_name(char *str, t_var *ptr);
void ft_get_value(char *str, t_var *ptr);
void ft_create_env(t_data *minis, char **envp);
t_var *lst_name_finding(t_var *lst, char *name);
void lst_change_value(t_var *lst, char *name, char* changing_value);

//ft_envp_var.c
char *get_envp_var(t_data *minis, char *cmd);//remplace la string cmd par sa variable d'environnement
char *ft_cpy_new_line(char *cmd, char *var_env, int i);
char  *search_env_var(char *str, int i);
int 	ft_strlen_var(char *str, int j);
void    put_env_var(t_data *minis);

//ft_split_cmd.c
void    ft_split_cmd(t_data *minis);

//ft_check_builtins.c
void ft_check_builtins(t_data *minis);
int  ft_pwd(void);
void ft_cd(t_data *minis, t_board *cmd);
void ft_export(t_data *minis, t_board *cmd);
void    ft_unset(t_data *minis, t_board *cmd);

//utils.c
int is_no_open_single_quote(char *line, int i);
int ft_len_cmd(char *line);
int is_no_open_quote(char *line, int i);
char *ft_cpy_new_line_bis(char *cmd, char *var_env, char *new, int i);
int	ft_strcmp(char *s1, char *s2);
char *list_chr(t_var *exp, char *str_name);
void print_list(t_var *exp, int i);

//ft_error.c
void ft_error(char *message, t_data *minis, int z);
void free_tab(char **tab, int i);


#endif
