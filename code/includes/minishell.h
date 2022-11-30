#ifndef MINISHELL_H
# define MINISHELL_H

// DECLARATIONS LIB
# include "../libft/libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

// DECLARATION VARIABLES
# define RDLINE_BUF_SIZE  1024

// DECLARATION STRUCT

// -- PARSING --
typedef struct	s_tokens_list
{
	void					*content;
	struct s_tokens_list	*prev;
	struct s_tokens_list	*next;
}	t_tokens_list;


typedef struct	s_token
{
	char		**sep_elements;
	char		*spaces;
	char		*quotes;
}	t_token;

enum	table_cst			// Table enum sert a def variables globales
{							// A default de ne pas mettre de précision,
	cst_AND,				// les cst deviennent respectivement = 0, 1, 2, ... 
	cst_OR,					// servira a comparer les cas rencontrés.
	cst_PIPE,
	cst_NONE
};

// -- COMMANDES --
typedef struct s_commande
{	
	enum table_cst	contenu;  // Definit séprateur rencontré.
	t_tokens_list	*args;
	char			*infile;
	t_tokens_list	*outfiles;
}	t_commande;

// DECLARATION FONCTIONS

// -- PARSING --
// [TOKEN_LIST_UTILS]
t_tokens_list	*create_token_list(void *contenu);
void	fct_elem_token_list(t_tokens_list *noeud, void (*fct)(void*));
void	suppr_elem_token_list(t_tokens_list **tlist, t_tokens_list *noeud, void (*fct)(void*));
void	clear_token_list(t_tokens_list **tlist, void (*fct)(void*));

//[TOKEN_LIST_ELEM]
t_tokens_list *last_token(t_tokens_list *tlist);
size_t	token_list_size(t_tokens_list *tlist);
t_tokens_list	*add_top_token_list(t_tokens_list **tlist, t_tokens_list *n_noeud);
t_tokens_list	*add_btm_token_list(t_tokens_list **tlist, t_tokens_list *n_noeud);
void	add_list_token_list(t_tokens_list **tlist, t_tokens_list *n_tlist);

//[SPLIT]
char	**ft_split(char const *str, char c);
int		words_counting(char const *str, char c);
char	*get_word(const char *str, char c, int index);

//[COMMANDES]
void	init_commande(t_commande *commande);
t_commande *create_new_commande(t_commande **o_commande);
void	suppr_commande(void *args);

//[ACTUAL PARSING]
t_tokens_list	*parsed_token_lst(char *line);


#endif