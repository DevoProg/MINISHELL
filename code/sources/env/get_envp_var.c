/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 00:53:06 by alondot           #+#    #+#             */
/*   Updated: 2023/01/17 01:26:02 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Fonction servant a calcule nombre de characteres de la var d'environnement.
*/
int	ft_strlen_var(char *str, int j)
{
	int	i;

	i = 1;
	j++;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_' || str[j] == '?'))
	{
		i++;
		j++;
	}
	return (i);
}

/*
	Fonction servant a recupérer la variable se trouvant dans la commande.
*/
char	*search_env_var(char *str, int i, t_data *minis)
{
	char	*new;
	int		k;
	int		j;

	j = i + 1;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_' || str[j] == '?'))
		j++;
	new = malloc(sizeof(char) * (j + 1));
	if (!new)
		ft_error("Malloc", minis, 3, 1);
	j = i + 1;
	k = 0;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_' || str[j] == '?'))
	{
		new[k] = str[j];
		k++;
		j++;
	}
	new[k] = '\0';
	return (new);
}

/*
	Fonction servant a reservé adresse mémoire et copier le debut de la commande. 
*/
char	*ft_cpy_new_line(char *cmd, char *var_env, int i, t_data *minis)
{
	int		j;
	char	*new;

	j = ft_strlen(cmd) - ft_strlen_var(cmd, i);
	if (var_env)
		j += ft_strlen(var_env);
	new = malloc(sizeof(char) * (j + 1));
	if (!new)
		ft_error("Malloc", minis, 3, 1);
	j = 0;
	while (j < i && cmd)
	{
		new[j] = cmd[j];
		j++;
	}
	new[j] = '\0';
	new = ft_cpy_new_line_bis(cmd, var_env, new, i);
	return (new);
}

/*
	Fonction servant a recupérer toutes les variables d'environnement.
	Retourne une commande avec la variable d'environnement 
	remplacée par son contenu.
*/
char	*get_envp_var(t_data *minis, char *cmd)
{
	char	*var_env;
	char	*res_env;
	int		i;
	int		j;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$' && is_no_open_single_quote(cmd, i) && cmd[i + 1]
			&& (ft_isalnum(cmd[i + 1])
				|| cmd[i + 1] == '_' || cmd[i + 1] == '?'))
		{
			var_env = search_env_var(cmd, i, minis);
			res_env = list_chr(minis->env, var_env);
			free(var_env);
			var_env = ft_cpy_new_line(cmd, res_env, i, minis);
			j = 0;
			while (var_env[j] && var_env[j] != '$')
				j++;
			if ((size_t)j != ft_strlen(var_env))
				var_env = get_envp_var(minis, var_env);
			return (var_env);
		}
		i++;
	}
	return (cmd);
}

/*
	Fonction servant a ecrire les variables d'environnements
	dans "minis->cmd[n].line_cmd". 
*/
void	put_env_var(t_data *minis)
{
	int	i;

	i = 0;
	while (i < minis->nb_cmd)
	{
		minis->cmd[i].line_cmd = get_envp_var(minis, minis->cmd[i].line_cmd);
		i++;
	}
}
