#include "../../includes/minishell.h"

void    d_infile_to_pipe(t_redi *ptr, int redi_pipe[2])
{
    char *str;
    int i;
    
    if(!ptr)
        return;
    while(1)
    {
        str = readline("heredoc>");
        if(str && *str && ft_strcmp(str, ptr->file) == 0)
        {
            break;
        }
        i = ft_strlen(str);
        write(redi_pipe[1], str, i);
        write(redi_pipe[1], "\n", 1);
        str = NULL;
        //free read line?????
    }
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
    if(fd == -1)//si erreur d'ouverture du fichier quitter le processus en cours le message est affiché a la fin de tous les porcess
    {
        printf("Error to open file : %s\n", ptr->file);
        exit(1);//il faudra quitter proprement
    }
    while(1)
    {
        buf = get_next_line(fd);        //si get_next_line fail son malloc????
        if(buf == NULL)
            break ;
        len = ft_strlen(buf);
        write(redi_pipe[1], buf, len);  //verifier le write?
        free(buf);
    }
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
        if(ptr->type == D_INFILE)
            d_infile_to_pipe(ptr, redi_pipe);
        ptr = ptr->next;
    }
    if(ptr->type == INFILE)
        infile_to_pipe(ptr, redi_pipe);
    if(ptr->type == D_INFILE)
        d_infile_to_pipe(ptr, redi_pipe);        
}