#include "../includes/minishell.h"

int access_check(char *path)
{
    DIR  *c;

    c = opendir(path);
    if(c == NULL)
        return(ERROR);
    return(SUCCESS);
}

void ft_change_pwd(t_var *env, t_data *minis)
{
    getcwd(minis->path, PATH_LEN);
    if(!*minis->path)
        exit(1);//quitter proprement
    lst_change_value(env, "PWD", minis->path);
}

void ft_cd(t_var *env, t_board *cmd, t_data *minis)
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
    //ft_printf("->>%s\n",list_chr(env, "OLDPWD"));
    //ft_change_pwd(env, minis);
    //ft_printf("->>>%s\n",list_chr(env, "PWD"));

}