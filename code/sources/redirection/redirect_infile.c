#include "../../includes/minishell.h"

t_redi *find_new_heredoc(t_redi *redi, int z)
{
    t_redi *ptr;

    if(!redi)
        return(NULL);
    if(z == 1 && !redi->next)
        return(NULL);
    if(z == 1)
        ptr = ptr->next;
    else
        ptr = redi;
    ptr = ptr->next;
    while(ptr->next)
    {
        if(ptr->type == D_OUTFILE)
            return(ptr);
        ptr = ptr->next;
    }
    if(ptr->type == D_OUTFILE)
    {
        printf("cc\n\n");
        return(ptr);
    }
    return(NULL);
}

void    d_infile_to_pipe(t_redi *redi, int redi_pipe[2])
{
    char *str;
    t_redi *ptr;
    int i;
    
    if(!redi)
        return;
    i = 0;
    ptr = redi;
    while(1)
    {
        str = readline("heredoc>");
        if(str && *str && ft_strcmp(str, ptr->file) == 0)
        {
            if(!ptr->next)
                break;
            ptr = ptr->next;
            continue;
        }
        write(redi_pipe[1], str, ft_strlen(str));
        write(redi_pipe[1], "\n", 1);
        str = NULL;
        //free read line?????
    }
    dup2(redi_pipe[0], 0);
}

/*
    Fonction qui ecrit dans le pipes des redirections les contenu des fichiers
*/
void    infile_to_pipe(t_redi *ptr, int redi_pipe[2])
{
    int fd;
    char *buf;
    int len;

    fd = open(ptr->file, O_RDONLY);
    if(fd == -1)
    {
        printf("Erreur d'ouverture du fichier %s\n", ptr->file);
        exit(1);//il faudra quitter proprement
    }
    while(1)
    {
        buf = get_next_line(fd);//si get_next_line fail son malloc????
        if(buf == NULL)
            break ;
        len = ft_strlen(buf);
        write(redi_pipe[1], buf, len);//verifier le write?
        free(buf);
    }
    dup2(redi_pipe[0], 0);
    close(fd);
}

/*
    Fonction qui regarde s'il y a un fichier d'entrée en redirection
*/
void redirect_infile(t_board *cmd, int redi_pipe[2])
{
    t_redi *ptr;

    if(!cmd->redi)
        return;
    ptr = cmd->redi;
    while(ptr->next != NULL)
    {
        if(ptr->type == INFILE)
            infile_to_pipe(ptr, redi_pipe);
        ptr = ptr->next;
    }
    if(ptr->type == INFILE)
        infile_to_pipe(ptr, redi_pipe);
    d_infile_to_pipe(cmd->redi, redi_pipe);
        
}