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

//Retrieves a value of variable. Return NULL if not found
char    *get_env_var(t_var_node *head, char *varname)
{
    t_var_node  *curr;

    curr = head;
    while (curr)
    {
        if (!((ft_strncmp(varname, curr->name, ft_strlen(varname)))  | curr->deleted))
        {
            return (curr->value);
        }
        curr = curr->next;
    }
    return (NULL);
}


void    set_var_deleted(t_var_node *head, char *varname)
{
    t_var_node  *curr;

    curr = head;
    while (curr)
    {
        if (!(ft_strncmp(varname, curr->name, 5000)))
        {
            
            curr->deleted = true; 
        }
        curr = curr->next;
    }
    
}


//Updates value of env VAR or creates a new one
void update_var(t_var_node *head, char *varname, char *value)
{
    t_var_node  *curr;
    char        *key_val_str;


    key_val_str = NULL;
    curr = head;
    while (curr)
    {
        if (!(ft_strncmp(varname, curr->name, 5000)))
        {
            
            curr->deleted = false;
            curr->value = ft_strdup(value);
            return ;
        }
        curr = curr->next;
    }
    key_val_str = ft_strjoin(varname, "=");
    key_val_str = ft_strjoin(key_val_str, value);
    append_var_node(&head, key_val_str);
}


