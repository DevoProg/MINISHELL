#include "../../includes/minishell.h"
void open_all_redi_files(t_board *cmd)
{
    t_redi *ptr;

    if(!cmd->redi)
        return;
    ptr = cmd->redi;
    while(ptr->next != NULL)
    {
        if(ptr->type == OUTFILE)
        {
            ptr->file_fd = open(ptr->file, O_TRUNC | O_WRONLY | O_CREAT, 0644);
            if(ptr->file_fd == -1)
            {
                printf("Erreur d'ouverture du fichier %s\n", ptr->file);
                exit(1);//il faudra quitter proprement
            }
        }
        ptr = ptr->next;
    }
    if(ptr->type == OUTFILE)
    {
        ptr->file_fd = open(ptr->file, O_TRUNC | O_WRONLY | O_CREAT, 0644);
        if(ptr->file_fd == -1)
        {
            printf("Erreur d'ouverture du fichier %s\n", ptr->file);
            exit(1);//il faudra quitter proprement
        }
    }
}
void close_all_redi_files(t_board *cmd)
{
    t_redi *ptr;

    if(!cmd->redi)
        return;
    ptr = cmd->redi;
    while(ptr->next != NULL)
    {
        if(ptr->type == OUTFILE)
            close(ptr->file_fd);
        ptr = ptr->next;
    }
    if(ptr->type == OUTFILE)
        close(ptr->file_fd);
}
void dup_outfile(t_board *cmd)
{
    open_all_redi_files(cmd);
    close_all_redi_files(cmd);
}
    // int fd;
    // char *buf;

    // fd = open(ptr->file, O_TRUNC | O_WRONLY | O_CREAT, 0644);
    // if(fd == -1)
    // {
    //     printf("Erreur d'ouverture du fichier %s\n", ptr->file);
    //     exit(1);//il faudra quitter proprement
    // }
    // write(redi_pipe[1], &buf, 1); 
    // dup2(fd, 1);
    // close(fd);