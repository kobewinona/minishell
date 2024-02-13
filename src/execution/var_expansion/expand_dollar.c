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



//Naive version
//For now, only supports this case >> echo $VAR1 $VAR2 
// and this case >> echo hello$VAR1 somewords$VAR2
void    expand_dollar(char **arg)
{
    char    *var_value;
    char    *expanded_arg;

    expanded_arg = ft_strjoin(ft_strslice(*arg, 0, ft_ind_char(*arg, '$')),
        getenv((*arg) + ft_ind_char(*arg, '$') + 1));

    *arg = expanded_arg;
        
}


void    replace_dollar_sign(char **argv)
{
    int i;

    i = 1;
    while(argv[i])
    {
        if (is_char_there(argv[i], '$'))
            expand_dollar(&argv[i]);
        i++;
    }
}