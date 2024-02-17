/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliashko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:30:32 by sliashko          #+#    #+#             */
/*   Updated: 2024/02/16 12:30:33 by sliashko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//handle export without args (prints declared vars in ascii order)
//handle declaration without assignment
void    export(char **argv, t_var_node *env_vars)
{
    char    **keyval_arr;
    int     i;

    i = 1;
    while (argv[i])
    {
        keyval_arr = ft_split(argv[i], '=');
        if (keyval_arr == NULL)
            return ;
        update_var(env_vars, keyval_arr[0], keyval_arr[1]);
        i++;
    }
}
