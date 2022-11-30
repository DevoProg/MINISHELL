#include "../../includes/minishell.h" 

/*
Fonction servant a récuperer le dernier token de la token list.	
*/
t_tokens_list *last_token(t_tokens_list *tlist)
{
	if(tlist && tlist->next)
		return (last_token(tlist->next));
	return (tlist);
}

/*
Fonction servant a recuperer la taille de la token list.
*/
size_t	token_list_size(t_tokens_list *tlist)
{
	if(tlist)
		return (1 + token_list_size(tlist->next));
	return (0);
}

/*
Fonction servant a ajouter un elem au dessus de la token list (debut).
*/
t_tokens_list	*add_top_token_list(t_tokens_list **tlist, t_tokens_list *n_noeud)
{
	if(tlist && n_noeud)
	{
		n_noeud->next = *tlist;
		n_noeud->prev = NULL;
		if(*tlist)
			(*tlist)->prev = n_noeud;
		*tlist = n_noeud;
	}
	return (n_noeud);
}

/*
Fonction servant a ajouter un elem en dessous de la token list (fin).	
*/
t_tokens_list	*add_btm_token_list(t_tokens_list **tlist, t_tokens_list *n_noeud)
{
	t_tokens_list	*last_noeud;
	
	if(tlist && n_noeud)
	{
		if(!*tlist)
		{
			n_noeud->next = NULL;
			*tlist = n_noeud;
		}
		else
		{
			last_noeud = last_token(*tlist);
			last_noeud->next = n_noeud;
			n_noeud->prev = last_noeud;
		}
		n_noeud->next = NULL;
	}
	return (n_noeud);
}

/*
Fonction servant a ajouter une token list a la fin d'un token list existante.	
*/
void	add_list_token_list(t_tokens_list **tlist, t_tokens_list *n_tlist)
{
	t_tokens_list	*ajout;
	
	if(n_tlist)
	{
		ajout = n_tlist->next;
		add_btm_token_list(tlist, n_tlist);
		add_list_token_list(tlist, ajout);
	}
}