#include "../inc/minishell.h"
t_lst_env *var_exist(t_lst_env *env, char *var);



int update_var(t_lst_env *env, char *var,int status)
{
    char *value;
    t_lst_env *to_update;

    ft_printf("%d\n", status);
    if (status == VALID)
    {
        value = strdup(ft_strchr(var, '=') + 1);
        to_update = var_exist(env, var);
        if (to_update->value)
            free(to_update->value);
        to_update->value = value;
    }
    else 
    {
        to_update = var_exist(env, var);
        if (to_update->value)
            free(to_update->value);
        to_update->value = ft_strdup("\'\'");
    }
    to_update->export_only = false;
    return (EXIT_SUCCESS);
}

char * ft_get_key(char *var)
{
    int i; 
    char *key;

    i = 0;
    while (var[i] && var[i] != '=')
        i++;
    key = malloc(sizeof(char *) * i + 1);
    if (!key)
        return (NULL);
    i = 0;
    while (var[i] &&var[i] != '=')
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
    if (ft_isalpha(var[0]) == 0 && var[0] != '_' || !ft_strcmp(var, "_"))
        return (UNVALID);
    while (var[i] && (ft_isalnum(var[i]) || var[i] == '_'))
        i++;
    if (!var[i])
        return (EMPTY);
    if (var[i] != '=')
        return (UNVALID);
    i++;
    while (var[i] && ft_isprint(var[i]))
        i++;
    if (!var[i])
        return (VALID);
    return (UNVALID);
}


int add_var(t_lst_env *env, char *var, int status, t_shell *shell)
{
    char *value;
    char *key;
    t_lst_env *new;

    key = ft_get_key(var);
    value = NULL;
    if (status == VALID)
    {
        value = strdup(ft_strchr(var, '=') + 1);
        new = env_new_node(key, value, false, shell);
    }
    else
    {
        value = strdup("\'\'");
        new = env_new_node(key, value, true, shell);
    }
    env_append(&env, new);
}

int export_var(t_process *process, char *var)
{
    int input_status;

    input_status = var_is_valid(var);
    if (input_status == UNVALID)
        return (EXIT_FAILURE);
    else if (var_exist(process->shell->env, var))
        return (update_var(process->shell->env, var, input_status));
    else
        return (add_var(process->shell->env, var, input_status, process->shell));
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

t_lst_env *ft_env_dup(t_lst_env *env, t_shell *shell)
{
    t_lst_env *dup;
    t_lst_env *new;

    dup = NULL;
    while (env)
    {
        new = env_new_node(env->key, env->value, env->export_only, shell);
        env_append(&dup, new);
        env = env->next;
    }
    return(dup);
}

int ft_print_sorted_env(t_lst_env *env, t_shell *shell)
{
    int len = 0;
    t_lst_env *current;
    t_lst_env *new_env = ft_env_dup(env, shell);

    current = new_env;
    while (current != NULL) {
        len++;
        current = current->next;
    }
    for (int i = 0; i < len - 1; i++) {
        current = new_env;
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
    current = new_env;
    while (current != NULL)
    {
        if (strcmp(current->key, "_"))
            ft_printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
    ft_free_env(new_env);
    return EXIT_SUCCESS;
}

int ft_export(t_process *process)
{
    if (process->argc == 1)
        return(ft_print_sorted_env(process->shell->env, process->shell));
    else
        return(export_vars(process));
    return (EXIT_SUCCESS);
}