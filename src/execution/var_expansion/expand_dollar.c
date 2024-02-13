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
//For now, only supports this case >> echo $VAR1 $VAR2 
void    expand_dollar(char **arg)
{
    char    *var_value;

    if (**arg == '$')
    {
        var_value = getenv((*arg) + 1);
        *arg = var_value;
    }
        
}


void    replace_dollar_sign(char **argv)
{
    int i;

    i = 1;
    while(argv[i])
    {
        if (is_dollar_there(argv[i]))
            expand_dollar(&argv[i]);
        i++;
    }
}