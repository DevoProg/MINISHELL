#include "../../includes/minishell.h"

/*
    Fonction qui ouvre tous les files de sortie (redirection)
*/
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

/*
    Fonction qui ferme tous les files de sortie (redirection)
*/
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

/*
    Ferme tous les pipes de redirections
*/
void close_redi_pipe(int redi_pipe[2][2])
{
    close(redi_pipe[0][0]);
    close(redi_pipe[0][1]);
    close(redi_pipe[1][0]);
    close(redi_pipe[1][1]);
}
