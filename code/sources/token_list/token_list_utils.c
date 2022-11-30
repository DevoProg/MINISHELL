#include "../../includes/minishell.h"

/*
Fonction servant a créer une token list avec un contenu.	
*/
t_tokens_list	*create_token_list(void *contenu)
{
	t_tokens_list	*noeud;
	
	noeud = malloc(sizeof(t_tokens_list));
	if(!noeud)
		return (NULL);
	noeud->content = contenu;
	noeud->prev = NULL;
	noeud->next = NULL;
	return (noeud);
}

/*
Fonction servant a appliquer une fct a un element unique (utile pour free).
*/
void	fct_elem_token_list(t_tokens_list *noeud, void (*fct)(void*))
{
	if(noeud)
	{
		if(fct)
		{
			fct(noeud->content);
		}
		free(noeud);
	}
}


/*
Fonction servant a retirer un element de la token list.	
*/
void	suppr_elem_token_list(t_tokens_list **tlist, t_tokens_list *noeud, void (*fct)(void*))
{
	if(fct && noeud)
	{
		if(noeud->prev)
			noeud->prev->next = noeud->next;
		if(!noeud->next)
			*tlist = noeud->next;
		if(noeud->next)
			noeud->next->prev = noeud->prev;
		fct_elem_token_list(noeud, fct);
	}
}

/*
Fonction servant a liberer l intégralité d'un token list.	
*/
void	clear_token_list(t_tokens_list **tlist, void (*fct)(void*))
{
	t_tokens_list	*tmp;
	t_tokens_list	*noeud;
	
	if(!tlist)
		return ;
	noeud = *tlist;
	while(noeud)
	{
		tmp = noeud->next;
		fct_elem_token_list(noeud, fct);
		noeud = tmp;
	}
	*tlist = NULL;
}
