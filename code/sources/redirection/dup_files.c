#include "../../includes/minishell.h"

void close_redi_pipe(int redi_pipe[2][2])
{
    close(redi_pipe[0][0]);
    close(redi_pipe[0][1]);
    close(redi_pipe[1][0]);
    close(redi_pipe[1][1]);
}

void    dup_inflie(t_redi *ptr, int redi_pipe[2])
{
    int fd;
    char *buf;
    //char *res;

    fd = open(ptr->file, O_RDONLY);
    if(fd == -1)
    {
        printf("Erreur d'ouverture du fichier %s\n", ptr->file);
        exit(1);//il faudra quitter proprement
    }
    while(1)
    {
        buf = get_next_line(fd);
        if(buf == NULL)
            break ;
        write(redi_pipe[1], buf, ft_strlen(buf));
        free(buf);
    }
    dup2(redi_pipe[0], 0);
    close(fd);
}

void dup_outfile(t_redi *ptr, int redi_pipe[2])
{
    int fd;
    char *buf;

    fd = open(ptr->file, O_TRUNC | O_WRONLY | O_CREAT, 0644);
    if(fd == -1)
    {
        printf("Erreur d'ouverture du fichier %s\n", ptr->file);
        exit(1);//il faudra quitter proprement
    }
    write(redi_pipe[1], &buf, 1); 
    dup2(fd, 1);
    close(fd);
}

void dup_files_in(t_board *cmd, int redi_pipe[2][2])
{
    t_redi *ptr;

    if(!cmd->redi)
        return;
    ptr = cmd->redi;
    while(ptr->next != NULL)
    {
        if(ptr->type == INFILE)
            dup_inflie(ptr, redi_pipe[0]);
        if(ptr->type == OUTFILE)
            dup_outfile(ptr, redi_pipe[1]);
        ptr = ptr->next;
    }
    if(ptr->type == INFILE)
        dup_inflie(ptr, redi_pipe[0]);
    if(ptr->type == OUTFILE)
        dup_outfile(ptr, redi_pipe[1]);
}