#include "../../includes/minishell.h"

/*
    fonction qui copie le reste de la commande apres le chemin d'acces
*/
void cpy_cmd(t_board *cmd, char *poss, int i)
{
    int j;

    j = 0;
    while(cmd->tab[0][j])
    {
        poss[i] = cmd->tab[0][j];
        i++;
        j++;
    }
    poss[i] = '\0';
}

/*
    fonction qui copie un chemin d'acces dans une string
*/
char *cpy_path(t_board *cmd, char *path, int *path_len)
{
    int i;
    int j;
    char *poss;

    *path_len = 0;
    while(path[*path_len] && path[*path_len] != ':')
        (*path_len)++;
    i = *path_len;
    i += ft_strlen(cmd->tab[0]);
    poss = malloc(sizeof(char) * (i + 2));//pas oublier de free
    if(!poss)
        exit(1);//il faudra exit proprement
    i = 0;
    while(path[i] && path[i] != ':')
    {
        poss[i] = path[i];
        i++;
    }
    poss[i] = '/';
    i++;
    cpy_cmd(cmd, poss, i);
    return(poss);
}

/*
    fonction qui teste les chemin d'access pour les commandes et qui le retourne si il est trouvé
*/
char *ft_try_path(t_data *minis, char *path, t_board *cmd)
{
    char *poss;
    char *res;
    int path_len;

    if(!path || !*path)
        return (0);
    if (access(cmd->tab[0], X_OK) == 0)
        return(cmd->tab[0]);
    path_len = 0;
    if(path[path_len] == ':')
        path++;
    poss = cpy_path(cmd, path, &path_len);
    if (access(poss, X_OK) == 0)
        return(poss);
    if (path[path_len])
    {
        res = ft_try_path(minis, path + path_len, cmd);
        if(res)
            return(res);
    }
    free(poss);
    return(NULL);
}
