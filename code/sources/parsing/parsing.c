#include "../../includes/minishell.h"

static t_commande	*add_new_commande(t_tokens_list **lst)
{
	t_tokens_list	*noeud;
	t_commande		*commande;
	
	commande = malloc(sizeof(t_commande));
	if(!commande)
		return (NULL);
	init_commande(commande);
}

/*
Fonction servant a remplire la token list.
*/
static void			fill_token_lst(t_tokens_list **tlist, t_token *token, char *line)
{
	t_commande	*commande;
	char		*arg;
	char		*contenu;
	
	if(!*tlist)
		add_new_commande(tlist);
	commande = (t_commande *)((last_token(*tlist))->content);
	if(!commande)
		return ;
	arg = get_token_str(); // FONCTION A FAIRE - Séparer les elements presents dans la string (" ", ' ', &&, ||, ...)
	if(arg)
	{
		if(get_contenu_token(contenu)) // FONCTION A FAIRE - Recuperer 
		{
			commande->contenu = get_contenu_token(contenu);
			commande = add_new_commande(tlist);
			if(!commande)
				return ;
		}
		free(arg);
		// EVENTUELLEMENT DES CHECK POUR VOIR SI LE PARSE EST EFFECTIF.
	}
}

/*
Fonction permettant de recuperer, via l'entrée, une liste de token (via séparateurs)
*/
t_tokens_list	*parsed_token_lst(char *line)
{
	t_tokens_list	*token_lst;
	t_token			token;
	
	token_lst = NULL;
	token.sep_elements = ft_split("<<:>>:<:>:&&:||:|:(:)", ':');
	if(!token.sep_elements)
		return (NULL);
	token.spaces = " ";
	token.quotes = "\"\'";
	
	fill_token_lst(&token_lst, &token, line);
	
}