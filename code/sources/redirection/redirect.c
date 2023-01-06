#include "../../includes/minishell.h"

int ft_is_redi(char *str, size_t i)
{
    if(ft_strncmp("<<", str + i, 2) == 0 && is_no_open_quote(str, i))
        return(D_INFILE);
    else if(ft_strncmp("<", str + i, 1) == 0 && is_no_open_quote(str, i))
        return(INFILE);
    else if(ft_strncmp(">>", str + i, 2) == 0 && is_no_open_quote(str, i))
        return(D_OUTFILE);
    else if(ft_strncmp(">", str + i, 1) == 0 && is_no_open_quote(str, i))
        return(OUTFILE);
    return (0);
}

char *get_file_redi(char *str)
{
    char *new;
    int i;

    i = 0;
    while(*str && *str == ' ')
        str++;
    while(str[i] && str[i] != ' '  && str[i] != '<' && str[i] != '>')
        i++;
    new = malloc(sizeof(char) * (i + 1));
    if(!new)
        exit(1);//quitter prorprement
    i = 0;
    while(str[i] && str[i] != ' '  && str[i] != '<' && str[i] != '>')
    {
        new[i] = str[i];
        i++;
    }
    new[i] = '\0';
    return(new);
}

t_redi	*lst_last_redi(t_redi *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void lst_add_redi(t_redi **lst, t_redi *new)
{
	t_redi   *aux_lst;

	if (new)
	{
		if (!*lst)
		{
			*lst = new;
			return ;
		}
		aux_lst = lst_last_redi(*lst);
		aux_lst->next = new;
	}
}

void stock_redi(t_board *cmd, char *str, int res)
{
    t_redi *redi;
    int j;

    if(res == INFILE || res == OUTFILE)
        j = 1;
    else if(res == D_INFILE || res == D_OUTFILE)
        j = 2;
    redi = malloc(sizeof(t_redi));
    if(!redi)
        exit(1);// QUITTER
    redi->type = res;
    redi->file = get_file_redi(str + j);
    redi->next = NULL;
    lst_add_redi(&cmd->redi, redi);
    //cmd->redi = NULL;
}

void clean_this_redi(char *str, int j, int res)
{
    str[j] = ' ';
    if(res == D_INFILE || res == D_OUTFILE)
    {
        j++;
        str[j] = ' ';
    }
    while(str[j] && str[j] == ' ')
        j++;
    while(str[j] && str[j] != ' '  && str[j] != '<' && str[j] != '>')
    {
        str[j] = ' ';
        j++;
    }
}

void redirection(t_data *minis)
{
    int i;
    size_t j;
    int res;

    i = 0;
    while(i < minis->nb_cmd)
    {
        j = 0;
        minis->cmd[i].redi = NULL;
        while(j < ft_strlen(minis->cmd[i].line_cmd))
        {
            res = ft_is_redi(minis->cmd[i].line_cmd, j);
            if(res != 0)
            {
                stock_redi(&minis->cmd[i], minis->cmd[i].line_cmd + j, res);
                //creer une focnrion qui clean les redirecitons
                clean_this_redi(minis->cmd[i].line_cmd, j, res);
                if(res == D_INFILE || res == D_OUTFILE)
                    j++;
            }
            j++;
        }
        // t_board *cmd = &minis->cmd[i];
        // if(cmd->redi)
        // {
        //     t_redi *tmp = minis->cmd[i].redi;
        //     printf("commande ->%d\n", i);
        //     while(tmp->next != NULL)
        //     {
        //         printf("%s\n", tmp->file);
        //         printf("%d\n", tmp->type);
        //         tmp = tmp->next;
        //     }
        //     printf("%s\n", tmp->file);
        //     printf("%d\n\n", tmp->type);
        // }
        i++;
    }
}