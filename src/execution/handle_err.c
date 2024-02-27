/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 01:19:07 by dklimkin          #+#    #+#             */
/*   Updated: 2024/02/27 17:08:11 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_exit(t_msh **msh, bool is_on_exit)
{
	free((*msh)->err);
	(*msh)->err = NULL;
	printf("\n\nexit code: %d\n\n", (*msh)->exit_code);
	if (is_on_exit)
		exit((*msh)->exit_code);
}

static void	process_parsing_err(t_msh **msh, bool is_on_exit)
{
	int	org_fd;

	if (!(*msh)->err)
		return ;
	org_fd = dup(STDOUT_FILENO);
	if (org_fd < 0)
		handle_exit(msh, is_on_exit);
	if (dup2(STDERR_FILENO, STDOUT_FILENO) == ERROR)
		handle_exit(msh, is_on_exit);
	if ((*msh)->err->type == T_SYNTAX_ERR)
		printf("%s: %s `%s'\n", PRG_NAME, (*msh)->err->ctx1, (*msh)->err->ctx2);
	if ((*msh)->err->type == T_CMD_NOT_FOUND)
		printf("%s: %s: %s\n", PRG_NAME, (*msh)->err->ctx1, CMD_NOT_FOUND_MSG);
	if ((*msh)->err->type == T_CMD_FOUND_NO_EXEC)
		printf("%s: %s: %s\n", PRG_NAME, (*msh)->err->ctx1, CMD_FOUND_NOT_EXEC_MSG);
	dup2(STDOUT_FILENO, STDERR_FILENO);
	close(org_fd);
	handle_exit(msh, is_on_exit);
}

void	process_err(t_msh **msh, bool is_on_exit)
{
	if (!(*msh)->err)
		return ;
	if ((*msh)->err->type == T_SYS_ERR)
	{
		perror((*msh)->err->ctx1);
		handle_exit(msh, is_on_exit);
	}
	process_parsing_err(msh, is_on_exit);
}

void	log_err(t_msh **msh, t_types err_type, char *ctx1, char *ctx2)
{
	if (!(*msh)->err)
	{
		(*msh)->err = (t_err *)malloc(sizeof(t_err));
		memset((*msh)->err, 0, sizeof(t_err));
	}
	if (err_type != T_SYS_ERR)
		(*msh)->exit_code = err_type;
	else
		(*msh)->exit_code = errno;
	(*msh)->err->type = err_type;
	(*msh)->err->ctx1 = ctx1;
	(*msh)->err->ctx2 = ctx2;
}

int	handle_err(int ret_val, t_msh **msh,
		t_types err_type, char *ctx1, char *ctx2)
{
	if (ret_val == ERROR)
		log_err(msh, err_type, ctx1, ctx2);
	return (ret_val);
}
