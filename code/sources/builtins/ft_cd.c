#include "../includes/minishell.h"

int access_check(char *path)
{
    DIR  *c;

    c = opendir(path);
    if(c == NULL)
        return(ERROR);
    return(SUCCESS);
}

void ft_change_oldpwd(t_var *env, t_data *minis)
{
    char *path;
    t_var *ptr;

    path = list_chr(env, "PWD");
    if(!path)
        exit(1);//quitter proprement
    ptr = lst_name_finding(env, "OLDPWD");
    free(ptr->value);
    ptr->value = ft_strdup(path);
    ptr = NULL;
}

/*
    Fonction servant a changer le chemin d'acces actuel.
    Modifie la valeur de la var "minis->path".
*/
void ft_change_pwd(t_var *env, t_data *minis)
{
    char path[PATH_LEN];
    t_var *ptr;

    getcwd(path, PATH_LEN);
    if(!*path)
        exit(1);                                    //quitter proprement
    ptr = lst_name_finding(env, "PWD");
    free(ptr->value);
    ptr->value = ft_strdup(path);
    ptr = NULL;
}

void ft_cd(t_data *minis, t_board *cmd)
{
    if(access_check(cmd->tab[1]) == ERROR)
    {
        printf("%s\n", "wrong path or not authorized");
        return;
    }
    if(chdir(cmd->tab[1]) == -1)
    {
        printf("%s\n", "ERROR CHANGING DIR");
        return;
    }
    ft_change_oldpwd(minis->env, minis);
    ft_change_pwd(minis->env, minis);
}