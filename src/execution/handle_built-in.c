/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_built-in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliashko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:22:59 by sliashko          #+#    #+#             */
/*   Updated: 2024/02/16 12:23:00 by sliashko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void    handle_builtin(t_exec *params, t_var_node *env_vars)
{
    if (!ft_strncmp(params->argv[0], ECHO, ft_strlen(ECHO)))
        echo(params->argv);
    if (!ft_strncmp(params->argv[0], PWD, ft_strlen(PWD)))
        pwd();
    if (!ft_strncmp(params->argv[0], EXPORT, ft_strlen(EXPORT)))
        export(params->argv, env_vars) ; //export command here
    if (!ft_strncmp(params->argv[0], UNSET, ft_strlen(UNSET)))
        return ; //unser command here
}