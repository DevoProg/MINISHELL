#include "../../includes/minishell.h"

/*
    Fonction qui ecrit le resultat de la commande dans les fichiers de redirection de sorite ou le print
*/
void write_in_all_file(char *buf, t_board *cmd)
{
    t_redi *ptr;

    if(!cmd->redi)
    {
        ft_printf("%s", buf);
        return;
    }
    ptr = cmd->redi;
    while(ptr->next != NULL)
    {
        if(ptr->type == OUTFILE)
            write(ptr->file_fd, buf, 1);
        ptr = ptr->next;
    }
    if(ptr->type == OUTFILE)
        write(ptr->file_fd, buf, 1);
}

/*
    Fonction qui lit le resultat de la commande(pipe redi)
*/
void redirect_outfile(t_board *cmd, int redi_pipe[2])
{
    char *buf;
    int res_read;

    open_all_redi_files(cmd);
    while(1)
    {
        buf = malloc(sizeof(char) * 2);
        if(!buf)
            exit(1);//il faudra quitter proprement
        res_read = read(redi_pipe[0], buf, 1);
        if(res_read == -1 || res_read == 0)
            return;
        buf[1] = '\0';
        write_in_all_file(buf, cmd);
        free(buf);
    }
    close_all_redi_files(cmd);
}