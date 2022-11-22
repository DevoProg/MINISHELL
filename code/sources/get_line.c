#include "../includes/minishell.h"

int		str_length(char *str)
{
	while(str && *str)
		return (1 + str_len(str+1));
	return (0);
}

ssize_t	getline(char **lineptr, size_t *n, FILE *stream)
{
	ssize_t		readed_char;
	char		*tampon;
	int			i;
	
	if(*lineptr == NULL)
	{
		tampon = malloc(sizeof(char) * )	
	}
	
	i = n;
	readed_char = 0;
	while()
	{
		
	}
}