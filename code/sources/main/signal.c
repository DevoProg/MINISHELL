# include "../../includes/minishell.h"

int error;

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		//Si jamais donne error : 130
		write (STDERR_FILENO, "\n", 1);
		//rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

/*
	Fonction interceptant les signaux.
	Le premier appel de signal sert a ignorer les appels de ctrl+\.
	Le second exec le signal_handler qui s'occupera de reprompt.	
*/
void	init_signals()
{
	signal(SIGQUIT, SIG_IGN); 			// Ignore le signal ctrl+\ (SIGQUIT)
	signal(SIGINT, signal_handler);		// Execute le signal_handler
}

/*
	Free tout les elements de minis->env, afin de preparer le exit().
*/
void	free_env(t_data *minis)
{
	int 	i;
	t_var	*tmp;
	
	i = 0;
	while(minis->env->next != NULL)
	{
		tmp = minis->env;

		minis->env = minis->env->next;
		if(tmp->name)
			free(tmp->name);
		if(tmp->value)
			free(tmp->value);
		if(tmp)
			free(tmp);
		i++;
	}
	free(minis->env->name);
	free(minis->env->value);
	free(minis->env);
}

/*
	Fonction servant a gerer le cas d'un signal ctrl+d. Free le minishell avant le exit.
*/
void	line_empty(t_data *minis)
{
	free_env(minis);
	if (errno == ENOMEM)
	{
		perror("error");
		exit(EXIT_FAILURE);
	}
	printf("CTRL+D : exit le shell...\n");
	exit(EXIT_SUCCESS);
}

// IDEE DE GETTER POUR LE PROMPT, POSSIBLE QU IL FAILLE FAIRE CETTE VERIFICATION A DISCUTER

// static char	*get_input(void)
// {
// 	char	*input;
// 	char	prompt[PROMPT_MAX];

// 	if (isatty(STDIN_FILENO))
// 		input = readline(get_prompt(prompt));
// 	else
// 		input = get_next_line(STDIN_FILENO);
// 	return (input);
// }