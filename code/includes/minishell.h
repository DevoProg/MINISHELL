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
	char *value;   		  // valeur de la variable d'environnement.
	int is_export;		  // Si la var = '_'.
	struct s_var *next;   // Noeud suivant
}				t_var;


typedef struct s_board
{
	char *line_cmd;			//toute la commande qui a ete split du |
	char **tab;				//split la commande en tableau des espaces
	int nb_words;			//le nombre de cases dans le tableau
	char *cmd_path;			//pour execve(path dans la variable d'environneemnt)
	int res_fork;			//int qui sert a wait le resultat du pipe
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


//MAIN
//main.c
void minishell_loop(char **envp);
void control_c();
//init_struct.c
void init_struct(t_data *minis);
void ft_create_env(t_data *minis, char **envp);
void ft_get_value(char *str, t_var *ptr);
void ft_get_name(char *str, t_var *ptr);
void lst_add(t_var **lst, t_var *new);
t_var *lst_last(t_var *lst);
t_var *lst_name_finding(t_var *lst, char *name);
void free_struct(t_data *minis);

//PARSING
//ft_split_cmd.c
void    ft_split_cmd(t_data *minis);
char **ft_split_each_cmd(char *str, t_board *cmd, t_data *minis);
char *str_cpy_words(char *line, int *i, t_data *minis);
int ft_count_split(char *line);
int ft_len_words(char *line);
//ft_split_line.c
void line_to_cmd(t_data *minis);
char *str_cpy_cmd(char *line, int *i, t_data *minis);
int ft_count_command(char *line);

//ENV
//ft_envp_var.c
void    put_env_var(t_data *minis);
char *get_envp_var(t_data *minis, char *cmd);//remplace la string cmd par sa variable d'environnement
char *ft_cpy_new_line(char *cmd, char *var_env, int i, t_data *minis);
char  *search_env_var(char *str, int i, t_data *minis);
int 	ft_strlen_var(char *str, int j);

//BUILTINS
//export.c
void ft_export(t_data *minis, t_board *cmd);
void ft_create_variable(t_data *minis, char *str);
void ft_assign_new_value(t_data *minis, char *str, char *name);
char *get_name(char *str, t_data *minis);
//ft_cd.c
void ft_cd(t_data *minis, t_board *cmd);
void ft_change_pwd(t_var *env, t_data *minis);
void ft_change_oldpwd(t_var *env, t_data *minis);
int access_check(char *path);
//ft_check_builtins.c
void ft_check_builtins(t_data *minis, t_board *cmd);
void ft_exit(t_data *minis);
void ft_echo(t_board *cmd);
void ft_envp(t_data *minis);
int  ft_pwd(void);
//unset.c
void    ft_unset(t_data *minis, t_board *cmd);
t_var    *ft_delete_node(char *str, t_var *env);
t_var    *ft_delete_first_node(t_var *env);
void    ft_delete_last_node(t_var *env);
void    ft_delete_middle_node(t_var *env);

//TOOLS
//utils.c
int ft_is_not_fork(t_data *minis, t_board *cmd);
int ft_is_builtins(t_data *minis, t_board *cmd);
char *ft_cpy_new_line_bis(char *cmd, char *var_env, char *new, int i);
int is_no_open_quote(char *line, int i);
int ft_len_cmd(char *line);
int is_no_open_single_quote(char *line, int i);
int	ft_strcmp(char *s1, char *s2);
char *list_chr(t_var *exp, char *str_name);
void print_list(t_var *exp, int i);
//ft_error.c
void ft_error(char *message, t_data *minis, int z, int is_perror);
void free_list(t_var *env);
void free_tab(char **tab, int i);
void free_struct_cmd(t_data *minis);

//PIPE
//pipe.c
void ft_pipe(t_data *minis, char **envp);
int **malloc_pipes(t_data *minis);
void find_path_struct(t_data *minis);
void close_all_pipes(t_data *minis, int **fd);
void wait_all_pids(t_data *minis);
//path.c
char *ft_try_path(t_data *minis, char *path, t_board *cmd);
char *cpy_path(t_board *cmd, char *path, int *path_len);
void cpy_cmd(t_board *cmd, char *poss, int i);
//execute.c
void ft_execute(t_data *minis, int **fd, char **envp);
void last_cmd(t_data *minis, t_board *cmd, char **envp, int **fd, int i);
void middle_cmd(t_data *minis, t_board *cmd, char **envp, int **fd, int i);
void first_cmd(t_data *minis, t_board *cmd, char **envp, int **fd, int i);
void just_one_cmd(t_data *minis, t_board *cmd, char **envp);

//si unset ne trouve pas d'id il doit dire `x': not a valid identifier

#endif
