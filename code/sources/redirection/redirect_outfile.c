#include "../../includes/minishell.h"

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