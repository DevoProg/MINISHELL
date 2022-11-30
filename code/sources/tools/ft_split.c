#include "../../includes/minishell.h"

/*
Fonction servant a free la liste de mots obtenus via le split.
*/
static void	free_word_lst(char **splited)
{
	int		i;
	
	i = 0;
	while(splited[i])
	{
		free(splited[i]);
		i++;
	}
	free(splited);
}

/*
Fonction servant a placer le pointeur sur le debut du mots propre au num d index.
*/
static const char *get_ptr_word(char const *str, char c, int index)
{
	int		w_count;
	
	w_count = 0;
	while(*str)
	{
		while(*str == c)
			str++;
		if(w_count == index)
			return (str);
		while(*str != c)
			str++;
		w_count++;
	}
	return (NULL);
}

/*
Fonction servant a recuperer mot par mot le split (pour lister les elems)
*/
char	*get_word(const char *str, char c, int index)
{
	const char	*pointer;
	char		*word;
	int			length;
	int			i;
	
	pointer = get_ptr_word(str, c, index);
	length = 0;
	while(pointer[length] && pointer[length] != c)
		length++;
	word = malloc(length + 1);
	if(!word)
		return (NULL);
	i = 0;
	while(i < length)
	{
		word[i] = pointer[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

/*
Fonction servant a compter le nombre de mots dans str.	
*/
int		words_counting(char const *str, char c)
{
	int		count;
	
	count = 0;
	if(*str && *str != c)
		count++;
	if(*str)
		str++;
	while(*str)
	{
		if(*(str - 1) == c && *str != c)    // check si nouvel elem précédé d'un separateur.
			count++;                        // si oui, nbr mots ++.
		str++;
	}
	return (count);
}

/*
Fonction split, servant au parsing (séparateur).
str = elem a spliter.
c 	= separateur.
*/
char	**ft_split(char const *str, char c)
{
	char	**splited;
	int		w_count;
	int		index;
	
	if(!str)
		return (NULL);
	w_count = words_counting(str, c);
	splited = malloc(sizeof(char *) * w_count + 1);
	if(!splited)
		return (NULL);
	index = 0;
	while(index < w_count)
	{
		splited[index] = get_word(str, c, index);
		if(!splited[index])
		{
			free_word_lst(splited);
			return (NULL);
		}
		index++;
	}
	splited[index] = NULL;
	return (splited);
}