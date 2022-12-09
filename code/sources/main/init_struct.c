#include "../../includes/minishell.h"

void free_struct(t_data *minis)//free le tableau de structure
{
    int i;

    i = 0;
    while(i < minis->nb_cmd)
    {
        free(minis->cmd[i].line_cmd);
        free_tab(minis->cmd[i].tab, minis->cmd[i].nb_words);
        //free(&minis->cmd[i]);
        i++;
    }
    free(minis->cmd);
}


t_var *lst_name_finding(t_var *lst, char *name)
{
    while(lst->next != NULL && ft_strcmp(lst->name, name) != 0)
        lst = lst->next;
    if (ft_strcmp(lst->name, name) == 0)
        return(lst);
    else
        return(NULL);
}

void lst_change_value(t_var *lst, char *name, char* changing_value)
{
    t_var *finder;

    finder = lst_name_finding(lst, name);
    if(finder == NULL)
        return; //?
    finder->value = NULL;
    free(finder->value);
    finder->value = changing_value;
    //free(finder);
}

/*
    Fonction servant a récupérer le dernier element t_var de la liste.
*/
t_var	*lst_last(t_var *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*
    Fonction servant a ajouter un ptr de variable complèté dans la liste "minis->env". 
*/
void lst_add(t_var **lst, t_var *newElem)
{
	t_var   *aux_lst;

	if (newElem)
	{
		if (!*lst)
		{
			*lst = newElem;
			return ;
		}
		aux_lst = lst_last(*lst);        // Récuper le dernier element de la liste.
		aux_lst->next = newElem;         // replacer la "fin" avec le nouveau noeud.
    
	}
}

/*
    Fonction servant a recuperer le nom de la variable d'environnement.
    Le nom est stocké dans la structure "t_var ptr".
*/
void ft_get_env_name(char *str, t_var *ptr)
{
    int i;

    i = 0;
    while(str[i] && str[i] != '=')
        i++;
    ptr->name = malloc(sizeof(char) * (i + 1));     // malloc reprenant nom var ($VAR).
    if(!ptr->name)
        exit(1);                                    //il faudra quitter proprement
    i = 0;
    while(str[i] && str[i] != '=')
    {
        ptr->name[i] = str[i];                      // Ecrit le nom de la variable.
        i++;
    }
    ptr->name[i] = '\0';
}

/*
    Fonction servant a récupérer la valeur de la variable d'environnement.
    La valeur est stocké dans la structure "t_var ptr".
*/
void ft_get_env_value(char *str, t_var *ptr)
{
    int i;
    int j;
    int len;

    i = 0;
    while(str[i] && str[i] != '=')
        i++;
    i++;
    len = ft_strlen(str + i);                        // taille de la valeur (total + taille nom = taille valeur).
    ptr->value = malloc(sizeof(char) * (len + 1));
    if(!ptr->value)
        exit(1);//quitter proprement
    j = 0;
    while(str[i])
    {
        ptr->value[j] = str[i];
        j++;
        i++;
    }
    ptr->value[j] = '\0';
}

/*
    Fonction servant a recuperer les variables d'environnement.
*/
void ft_create_env(t_data *minis, char **envp)
{
    t_var *ptr;
    int i;

    i = 0;
    while(envp[i])                          // Parcours toutes les variables d'env
    {
        ptr = malloc(sizeof(t_var));
        if(!ptr)
            exit(1);                        //il faudra exit proprement
        ft_get_env_name(envp[i], ptr);          // recupére le nom
        ft_get_env_value(envp[i], ptr);         // recupére la valeur
        if(ptr->name && ptr->name[0] == '_' && ptr->name[1] == '\0')
            ptr->is_export = 0;
        else
            ptr->is_export = 1;
        i++;
        ptr->next = NULL;                   // Replace la "fin" de la list sur next.
        lst_add(&minis->env, ptr);          // Ajoute le pointeur de variable dans la list "mini->env"
        free(ptr);                          // !!! Free nécessaire dans la loop, obligatoire a faire le mm nbr de fois que les ittérations. 
    }
}

/*
    Fonction servant a init la structure "minis".
*/
void init_struct(t_data *minis, char **envp)    //allocation d'un tableau de strcuture et copier le tableau dans chaque structure
{
    int i;

    minis->cmd = malloc(sizeof(t_board) * minis->nb_cmd);    //allocation d'un tableau de structure
    if(!minis->cmd)
        ft_error("Malloc", minis, 2);
    i = 0;
    while(i < minis->nb_cmd)                                //boucle qui met les commandes dans le tableau de structure
    {
        minis->cmd[i].line_cmd = ft_strdup(minis->tab_cmd[i]);
        if(!minis->cmd[i].line_cmd)
            ft_error("Malloc", minis, 3);
        i++;
    }
    free_tab(minis->tab_cmd, minis->nb_cmd + 1);            //free le tableau du split_cmd car les lignes ont ete copiee dans cmd[i]->cmd_line
}