#include "../../includes/minishell.h"

/*
    Fonction qui ecrit dans le pipes des redirections les contenu des fichiers
*/
void    dup_inflie(t_redi *ptr, int redi_pipe[2])
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
            dup_inflie(ptr, redi_pipe);
        ptr = ptr->next;
    }
    if(ptr->type == INFILE)
        dup_inflie(ptr, redi_pipe);
}