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
    char    **splitted_arr;
    char    *expanded_str;
    char    *value;
    int     i;

    splitted_arr = ft_split(*arg, '$');
    expanded_str = "";
    i = 0;
    if (**arg != '$')
    {
        expanded_str = splitted_arr[0];
        i++;
    }
    while (splitted_arr[i])
    {
        value = getenv(splitted_arr[i]);
        if (value)
            expanded_str = ft_strjoin(expanded_str, value);
        i++;
    }
    *arg = expanded_str;
    free_array(splitted_arr);
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