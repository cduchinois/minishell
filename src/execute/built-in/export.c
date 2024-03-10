// #include "../inc/minishell.h"

// char *split_var(char *var, int mode)
// {
//     int index;
//     char *content;
//     char *equal_sub;

//     equal_sub = ft_strchr(var, '=');
//     if (equal_sub == NULL)
//         return (NULL);
//     index = equal_sub - var;
//     if (mode == 0)
//     {
//         content = malloc(sizeof(char) * index + 1);
//         if (!content)
//             return (NULL);
//         ft_strncpy(content, var, index);
//         content[index] = '\0';
//     }
//     else
//         content = strdup(equal_sub + 1);
//     if (!content)
//         return (NULL);
//     return (content);
// }

// int update_var(t_process *process, char *var)
// {
//     char *name;
//     char *env_name;
//     int i;
//     ft_printf("test\n");
//     i = 0;
//     name = split_var(var, 0);
//     if (name == NULL)
//         return (EXIT_FAILURE);
//     while (process->shell->env)
//     {
//         env_name = split_var(process->shell->env, 0);
//         if (ft_strcmp(env_name, name) == 0)
//         {
//             free(process->shell->env);
//             process->shell->env = ft_strdup(var);
//         }
//         free(env_name);
//         i++;
//     }
//     i = 0;
//     free(name);
//     return (EXIT_FAILURE);
// }

// int var_exist(char **env, char *var)
// {
//     char *name;
//     char *env_name;
//     int i;

//     i = 0;
//     name = split_var(var, 0);
//     if (name == NULL)
//         return (EXIT_FAILURE);
//     while (env[i])
//     {
//         env_name = split_var(env[i], 0);
//         if (ft_strcmp(env_name, name) == 0)
//             return (free(name), free(env_name), EXIT_SUCCESS);
//         free(env_name);
//         i++;
//     }
//     free(name);
//     return (EXIT_FAILURE);
// }

// int var_is_valid(char *var)
// {
//     int i;

//     i = 1;
//     if (ft_isalpha(var[0]) == 0 && var[0] != '_')
//         return (UNVALID);
//     while (ft_isalnum(var[i]) || var[i] == '_')
//         i++;
//     if (!var[i])
//         return (EMPTY);
//     if (var[i] != '=')
//         return (UNVALID);
//     i++;
//     while (ft_isprint(var[i]))
//         i++;
//     if (!var[i])
//         return (VALID);
//     return (UNVALID);
// }

// int export_var(t_process *process, char *var)
// {
//     int input_status;

//     input_status = var_is_valid(var);
//     ft_printf("status = %d", input_status);
//     if (input_status == UNVALID)
//         return (EXIT_FAILURE);
//     else if (var_exist(process->shell->env_export, var))
//         return (update_var(process, var));
//     else
//         //return (add_var(process, var, input_status));
//     return (EXIT_FAILURE);
// }

// int export_vars(t_process *process)
// {
//     int i;
//     bool error;
//     i = 1;
//     error = false;
//     while (process->args[i])
//     {
//         error += export_var(process, process->args[i]);
//         i++;
//     }
//     if (error == true)
//         return (EXIT_FAILURE);
//     return (EXIT_SUCCESS);
// }

// int ft_print_sorted_env(char **env_export)
// {
//     int i;
//     int len;
//     int j;
//     char *tmp;

//     i = 0;
//     len = 0;
//     while (env_export[len])
//         len++;
//     while (i < len - 1)
//     {
//         j = 0;
//         while (j < len - i -1)
//         {
//             if(ft_strcmp(env_export[j], env_export[j + 1]) > 0)
//             {
//                 tmp = env_export[j];
//                 env_export[j] = env_export[j + 1];
//                 env_export[j + 1] = tmp;
//             }
//             j++;
//         }
//         i++;
//     }
//     i = 0;
//     while (env_export[i])
//         ft_printf("%s\n", env_export[i++]);
//     return (EXIT_SUCCESS);
// }

// int ft_export(t_process *process)
// {
//     if (process->argc == 1)
//         return(ft_print_sorted_env(process->shell->env_export));
//     else
//         return(export_vars(process));
//     return (EXIT_SUCCESS);
// }