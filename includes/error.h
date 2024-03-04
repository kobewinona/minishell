/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:26:47 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/04 15:01:52 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# include "minishell.h"

typedef struct s_ret_err_val
{
	int		t_int;
	void	*t_null;
}	t_ret_err_val;

typedef struct s_err
{
	t_types	type;
	char	*ctx1;
	char	*ctx2;
}	t_err;

t_ret_err_val	print_err(t_msh **msh, t_err err, bool is_on_exit);

#endif
