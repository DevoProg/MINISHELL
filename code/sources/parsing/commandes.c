#include "../../includes/minishell.h"

/*
Fonction servant a créer une nouvelle commande "vide".
*/
void	init_commande(t_commande *commande)
{
	if(commande)
	{
		commande->contenu = cst_NONE;
		commande->args = NULL;
		commande->infile = NULL;
		commande->outfiles = NULL;
	}
}

/*
Fonction servant a mettre en place la nouvelle commande "vide".
*/
t_commande *create_new_commande(t_commande **o_commande)
{
	t_commande	*n_commande;
	
	n_commande = malloc(sizeof(t_commande));
	init_commande(n_commande);
	if(*o_commande)
		*o_commande = n_commande;
	return (n_commande);
}

/*
Fonction servant a libérer une commande (Bien pense a tt les free necessaire).
*/
void	suppr_commande(void *args)
{
	t_commande	*commande;
	
	commande = (t_commande *) args;
	if(commande)
	{
		clear_token_list(&commande->args, free);
		clear_token_list(&commande->outfiles, free);
		free(commande->infile);
		free(commande);
	}
}