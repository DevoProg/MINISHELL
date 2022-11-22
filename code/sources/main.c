#include "../includes/minishell.h"
    
int    main(void)
{
    char    *buffer;
    size_t	buf_size;
	
	buf_size = 2048;
	buffer = (char *)malloc(sizeof(char) * buf_size + 1);
	
	if(!buffer)
	{
		perror("Alloc memory failed");
		return (EXIT_FAILURE);
	}
	
	write(1, "$> ", 3);
	
	while()
	
}
