/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliashko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:04:50 by sliashko          #+#    #+#             */
/*   Updated: 2024/02/12 18:04:51 by sliashko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool    is_dollar_there(char *arg)
{
    while (*arg)
    {
        if (*arg == '$')
            return (true);
        arg++;
    }
    return (false);
}


//Naive version
void    expand_dollar(char **arg)
{
    char    *dol_begin;
    char    *var_value;

    dol_begin = ft_strchr(*arg, '$');
    var_value = getenv(dol_begin);
}


t_exec    *replace_dollar_sign(t_exec *cmd)
{
    int i;

    i = 1;
    while(cmd->argv[i])
    {
        if (is_dollar_there(cmd->argv[i]))
            expand_dollar(cmd->argv[i]);
        i++;
    }
    return (cmd);
}