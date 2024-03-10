#include "../inc/minishell.h"
t_lst_env *var_exist(t_lst_env *env, char *var);

int update_var(t_lst_env *env, char *var)
{
    char *value;
    t_lst_env *to_update;
    value = strdup(ft_strchr(var, '=') + 1);
    to_update = var_exist(env, var);
    free(to_update->value);
    to_update->value = value;
    to_update->export_only = false;
    return (EXIT_SUCCESS);
}

char * ft_get_key(char *var)
{
    int i; 
    char *key;

    i = 0;
    while (var[i] != '=' && var[i])
        i++;
    key = malloc(sizeof(char *) * i + 1);
    if (!key)
        return (NULL);
    i = 0;
    while (var[i] != '=' && var[i])
    {
        key[i] = var[i];
        i++;
    }
    key[i] = '\0';
    return (key);
}

t_lst_env *var_exist(t_lst_env *env, char *var)
{
    char *key;
    int i;

    i = 0;
    key = ft_get_key(var);
    if (!key)
        return (NULL);
    while (env)
    {
        if (ft_strcmp(env->key, key) == 0)
            return (free(key), env);
        i++;
        env = env->next;
    }
    free(key);
    return (NULL);
}

int var_is_valid(char *var)
{
    int i;

    i = 1;
    if (ft_isalpha(var[0]) == 0 && var[0] != '_')
        return (UNVALID);
    while (ft_isalnum(var[i]) || var[i] == '_')
        i++;
    if (!var[i])
        return (EMPTY);
    if (var[i] != '=')
        return (UNVALID);
    i++;
    while (ft_isprint(var[i]))
        i++;
    if (!var[i])
        return (VALID);
    return (UNVALID);
}

int export_var(t_process *process, char *var)
{
    int input_status;

    input_status = var_is_valid(var);
    if (input_status == UNVALID)
        return (EXIT_FAILURE);
    else if (var_exist(process->shell->env, var))
        return (update_var(process->shell->env, var));
    else
        //return (add_var(process, var, input_status));
    return (EXIT_FAILURE);
}

int export_vars(t_process *process)
{
    int i;
    bool error;
    i = 1;
    error = false;
    while (process->args[i])
    {
        error += export_var(process, process->args[i]);
        i++;
    }
    if (error == true)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

int ft_print_sorted_env(t_lst_env *env) {
    int len = 0;
    t_lst_env *current = env;
    
    while (current != NULL) {
        len++;
        current = current->next;
    }
    for (int i = 0; i < len - 1; i++) {
        current = env;
        for (int j = 0; j < len - i - 1; j++) {
            if (ft_strcmp(current->key, current->next->key) > 0) {
                char *tmp_key = current->key;
                char *tmp_value = current->value;
                current->key = current->next->key;
                current->value = current->next->value;
                current->next->key = tmp_key;
                current->next->value = tmp_value;
            }
            current = current->next;
        }
    }
    current = env;
    while (current != NULL) {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
    return EXIT_SUCCESS;
}

int ft_export(t_process *process)
{
    if (process->argc == 1)
        return(ft_print_sorted_env(process->shell->env));
    else
        return(export_vars(process));
    return (EXIT_SUCCESS);
}