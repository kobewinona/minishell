/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_linked_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliashko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:44:53 by sliashko          #+#    #+#             */
/*   Updated: 2024/02/14 16:45:06 by sliashko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var_node  *create_var_node(char *key_val_str)
{
    t_var_node *new_element;
    char       **splitted_arr;


    new_element = (t_var_node *) malloc(sizeof(t_var_node));
    if (new_element == NULL)
        return (NULL);
    splitted_arr = ft_split(key_val_str, '=');
    new_element->name = ft_strdup(splitted_arr[0]);
    if (splitted_arr[1])
        new_element->value = ft_strdup(splitted_arr[1]);
    else
        new_element->value = NULL;
    new_element->is_numeric = false;
    new_element->deleted = false;
    new_element->next = NULL;
    free_array(splitted_arr);
    return (new_element);
}

void    append_var_node(t_var_node **head, char *key_val_str)
{
    t_var_node *new_node;
    t_var_node *current;

    new_node = create_var_node(key_val_str);
    if (key_val_str == NULL || new_node == NULL)
        return ;
    if (*head == NULL)
        *head = new_node;
    else
    {
        current = *head;
        while (current->next)
            current = current->next;
        current->next = new_node;
        
    }
}

char    *get_env_var(t_var_node **env_vars, char *varname)
{
    t_var_node  *curr_var;

    curr_var = *env_vars;
    while (curr_var)
    {
        if (!ft_strncmp(varname, curr_var->name, ft_strlen(varname))
                && !curr_var->deleted)
            return (curr_var->value);
        curr_var = curr_var->next;
    }
    return (NULL);
}


//Doesnt work properly for some reasons: need to adjust
void    set_var_deleted(t_var_node **env_vars, char *varname)
{
    t_var_node  *curr_var;

    curr_var = *env_vars;
    while (curr_var)
    {
        if (!ft_strncmp(varname, curr_var->name, ft_strlen(varname)))
        {
            curr_var->value = NULL;
            curr_var->deleted = true;
            return ;
        }
        curr_var = curr_var->next;
    }
}