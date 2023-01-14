#include "../../includes/minishell.h"

/*
    Fonction servant a check les acces au chemin ciblé.
*/
int access_check(char *path)
{
    DIR  *c;

    c = opendir(path);
    if(c == NULL)
        return(ERROR);
    return(SUCCESS);
}

/*
    Fonction servant a changer l'ancien chemin d'acces actuel.
    Modifie la valeur de la var d'environnement
*/
void ft_change_oldpwd(t_var *env, t_data *minis)
{
    char *path;
    t_var *ptr;

    path = list_chr(env, "PWD");
    if(!path)
        ft_error("Cd failed\n", minis, 2, 0);//quitter avec perror?
    ptr = lst_name_finding(env, "OLDPWD");
    free(ptr->value);
    ptr->value = ft_strdup(path);
    ptr = NULL;
}

/*
    Fonction servant a changer le chemin d'acces actuel.
    Modifie la valeur de la var d'environnement
*/
void ft_change_pwd(t_var *env, t_data *minis)
{
    char path[PATH_LEN];
    t_var *ptr;

    getcwd(path, PATH_LEN);
    if(!*path)
        ft_error("Getcwd", minis, 2, 1);//quitter avec perror?
    ptr = lst_name_finding(env, "PWD");
    free(ptr->value);
    ptr->value = ft_strdup(path);
    ptr = NULL;
}

/*
    Cas commande : CD.
*/
void ft_cd(t_data *minis, t_board *cmd)
{
    char *home_dir;
    t_var *ptr;

    if(cmd->nb_words == 2)
    {
        ptr = lst_name_finding(minis->env, "HOME");
        home_dir = ptr->value;
    }
    else 
        home_dir = cmd->tab[1];
    if(access_check(home_dir) == ERROR)
    {
        ft_printf("%s\n", "wrong path or not authorized");
        put_res_pipe(minis, 1);
        return ;
    }
    if(chdir(home_dir) == -1)
    {
        ft_printf("%s\n", "ERROR CHANGING DIR");
        put_res_pipe(minis, 1);
        return ;
    }
    ft_change_oldpwd(minis->env, minis);
    ft_change_pwd(minis->env, minis);
    put_res_pipe(minis, 0);

}