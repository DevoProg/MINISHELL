#include "../includes/minishell.h"

int is_no_open_single_quote(char *line, int i)//verifier qu'il n'y ait pas de single quote ouvert
{//il faudra quand meme verifier cette maniere de faire  /!\'
    int single_quote;
    int j;

    j = 0;
    single_quote = 0;
    while(j < i)
    {
        if(line[j] == 39)// 39 == '
            single_quote++;
        j++;
    }
    if(single_quote % 2 != 0)
        return(0);//si ouverte return 0
    return(1);//si fermée ou pas de quote return 1
}


int ft_strlen_var(char *str, int j)//fonction qui calcule le nombre de charcateres de la variable d'environnement
{
    int i;

    i = 1;
    j++;

    while(str[j] && (ft_isalnum(str[j]) || str[j] == '_'))//peut-etre seulement alpha et _??
    {
        i++;
        j++;
    }
    return(i);
}




char  *search_env_var(char *str, int i)//renvoie la variable dans la commande
{
    char *new;
    int k;
    int j;

    j = i + 1;
    while(str[j] && (ft_isalnum(str[j]) || str[j] == '_'))//peut-etre seulement alpha?
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
    //*i = j - 1;
    return(new);
}

char *ft_cpy_new_line_bis(char *cmd, char *var_env, char *new, int i)
{
    int k;
    int j;

    k = 0;
    j = 0;
    while(new[j])
        j++;
    while(var_env && var_env[k])
    {
        new[j] = var_env[k];
        j++;
        k++;
    }
    k = i + ft_strlen_var(cmd, i);
    while(cmd[k] && cmd)
    {
        new[j] = cmd[k];
        j++;
        k++;
    }
    new[j] = '\0';
    free(cmd);
    return(new);
}

char *ft_cpy_new_line(char *cmd, char *var_env, int i)
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

char *get_envp_var(char *cmd)//retourne une commande avec la variable d'envrionnement remplacée par son contenu
{
    char *var_env;
    char *res_env;
    int i;

    i = 0;
    while(cmd[i])//lire lettre par lettre la commande
    {
        //printf("j = %c\n", cmd[i]);
        if(cmd[i] == '$' && is_no_open_single_quote(cmd, i) && cmd[i + 1] && ft_isalnum(cmd[i + 1]))//si la string contient le dollar et qu'il n'y a pas de single quote ouverte
        {
            var_env = search_env_var(cmd, i);//fonction qui recherche la variable d'environnement dans la commande
            res_env = getenv(var_env);//fonction autorisée retourne la contenu de la variable env res_env ne doit pas etre free!!!
            free(var_env);//on en aura plus besoin
            var_env = ft_cpy_new_line(cmd, res_env, i);//fonction qui copie les resultats sur la ligne finale et free l'ancienne cmd
            return(var_env);                           //si la variable existe pas elle est supprimée echo "yo $salut bjr" = echo "yo  bjr"
        }
        i++;
    }
    return(cmd);
    //est-ce qu'il faut gerer les é è ç à ù ? 
}