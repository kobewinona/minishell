/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliashko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:17:47 by sliashko          #+#    #+#             */
/*   Updated: 2024/02/14 17:17:47 by sliashko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_array(char **array)
{
    char    **temp;

    temp = array;
    while (*temp)
    {
        free(*temp);
        temp++;
    }
    free(array);
}
