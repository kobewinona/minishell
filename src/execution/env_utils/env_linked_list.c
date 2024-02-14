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

char    *get_env_var(t_var_node **head, char *varname)
{
    t_var_node  *curr;

    curr = *head;
    while (curr)
    {
        if (!((ft_strncmp(varname, curr->name, ft_strlen(varname)))  | curr->deleted))
        {
            printf("deleted = %d\n", curr->deleted);
            return (curr->value);
        }
        curr = curr->next;
    }
    return (NULL);
}

void    set_var_deleted(t_var_node **head, char *varname)
{
    t_var_node  *curr;

    curr = *head;
    while (curr)
    {
        if (!(ft_strncmp(varname, curr->name, ft_strlen(varname))))
        {
            
            curr->deleted = true;

            printf("var = %s; deleted = %d\n", curr->value, curr->deleted);
            return ;
        }
        curr = curr->next;
    }
    
}

t_var_node  *copy_env_vars(char **envp)
{
    int             i;
    t_var_node      *head;

    i = 1;
    head = create_var_node(envp[i]);
    head = NULL;
    while (envp[i])
    {
        append_var_node(&head, envp[i]);
        i++;
    }
    return (head);
}