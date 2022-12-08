#include "../includes/minishell.h"

int ft_strlen_var(char *str, int j)//fonction qui calcule le nombre de charcateres de la variable d'environnement
{
    int i;

    i = 1;
    j++;

    while(str[j] && (ft_isalnum(str[j]) || str[j] == '_'))//peut-etre seulement alnum et _??
    {
        i++;
        j++;
    }
    return(i);
}

char  *search_env_var(char *str, int i)//renvoie la variable qui se trouve dans la commande
{
    char *new;
    int k;
    int j;

    j = i + 1;
    while(str[j] && (ft_isalnum(str[j]) || str[j] == '_'))//peut-etre seulement alnum et _??
        j++;
    new = malloc(sizeof(char) * (j + 1));
    if(!new)
        exit(1);//il faudra quitter proprement
    j = i + 1;
    k = 0;
    while(str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
    {
        new[k] = str[j];
        k++;
        j++;
    }
    new[k] = '\0';
    return(new);
}

char *ft_cpy_new_line(char *cmd, char *var_env, int i)//malloc new et copie le debut de la commande
{
    int j;
    char *new;

    j = ft_strlen(cmd) - ft_strlen_var(cmd, i);
    if(var_env)
        j += ft_strlen(var_env);
    new = malloc(sizeof(char) * (j + 1));
    if(!new)
        exit(1);//il faudra quitter proprement
    j = 0;
    while(j < i && cmd)
    {

        new[j] = cmd[j];
        j++;
    }
    new[j] = '\0';
    new = ft_cpy_new_line_bis(cmd, var_env, new, i);
    return(new);
}

char *get_envp_var(t_data *minis, char *cmd)//retourne une commande avec la variable d'envrionnement remplacée par son contenu
{
    char *var_env;
    char *res_env;
    int i;
    int j;

    i = 0;
    while(cmd[i])//lire lettre par lettre la commande
    {
        if(cmd[i] == '$' && is_no_open_single_quote(cmd, i) && cmd[i + 1] && (ft_isalnum(cmd[i + 1]) || cmd[i + 1] == '_'))//si la string contient le dollar et qu'il n'y a pas de single quote ouverte
        {
            var_env = search_env_var(cmd, i);//fonction qui recherche la variable d'environnement dans la commande
            res_env = list_chr(minis->env, var_env);//fonction autorisée retourne la contenu de la variable env res_env ne doit pas etre free!!!
            //supprimer
            free(var_env);//on en aura plus besoin
            var_env = ft_cpy_new_line(cmd, res_env, i);//fonction qui copie les resultats sur la ligne finale et free l'ancienne cmd
            j = 0;
            while(var_env[j] && var_env[j] != '$')
                j++;
            if((size_t)j != ft_strlen(var_env))
                var_env = get_envp_var(minis, var_env);
            return(var_env);                           //si la variable existe pas elle est supprimée echo "yo $salut bjr" = echo "yo  bjr"
        }
        i++;
    }
    return(cmd);
    //est-ce qu'il faut gerer les "é è ç à ù" ??

}

void    put_env_var(t_data *minis)
{
    int i;

    i = 0;
    while(i < minis->nb_cmd)//boucle des structure de commandes
    {
        minis->cmd[i].line_cmd = get_envp_var(minis, minis->cmd[i].line_cmd);//la $variable d'environnement remplacée par son contenu pour chaque commandes
        i++;
    }
}