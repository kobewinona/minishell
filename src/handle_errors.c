/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 01:19:07 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/22 02:15:26 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_custom_err_msg(t_err err, char *ctx)
{
	if (err == CMD_NOT_FOUND)
		printf("%s: '%s': %s\n", PRG_NAME, ctx, CMD_NOT_FOUND_MSG);
	if (err == PERM_DENIED || err == CMD_IS_DIR)
		printf("%s: %s: %s\n", PRG_NAME, ctx, strerror(err));
	if (err == CD_PERM_DENIED)
		printf("%s: cd: %s: %s\n", PRG_NAME, ctx, strerror(PERM_DENIED));
	if (err == UNEXPECTED_TOK)
		printf("%s: %s: `%s'\n", PRG_NAME, UNEXPECTED_TOK_MSG, ctx);
	if (err == UNEXPECTED_EOF)
		printf("%s: %s: `%s'\n", PRG_NAME, UNEXPECTED_EOF_TOK_MSG, ctx);
	if (err == NO_FILE_OR_DIR)
		printf("%s: %s: %s\n", PRG_NAME, ctx, strerror(NO_FILE_OR_DIR));
	if (err == CD_NO_FILE_OR_DIR)
		printf("%s: cd: %s: %s\n", PRG_NAME, ctx, strerror(NO_FILE_OR_DIR));
	if (err == EXPORT_INVALID_ARG)
		printf("%s: export: `%s': %s\n", PRG_NAME, ctx, INVALID_EXPORT_ARG_MSG);
	if (err == EXIT_INVALID_ARG)
		printf("%s: exit: %s: %s\n", PRG_NAME, ctx, INVALID_EXIT_ARG_MSG);
	if (err == TOO_MANY_ARGS)
		printf("%s: %s: %s\n", PRG_NAME, ctx, TOO_MANY_ARGS_MSG);
}

void	handle_err(t_msh **msh, t_err err, char *ctx, int exit_code)
{
	int	org_fd;

	org_fd = dup(STDOUT_FILENO);
	if (org_fd == ERROR)
		handle_exit(msh, exit_code, true);
	if (dup2(STDERR_FILENO, STDOUT_FILENO) == ERROR)
		handle_exit(msh, exit_code, true);
	if (err == SYSTEM)
	{
		dup2(STDOUT_FILENO, STDERR_FILENO);
		close(org_fd);
		printf("%s: %s: %s\n", PRG_NAME, ctx, strerror(errno));
	}
	else
		print_custom_err_msg(err, ctx);
	dup2(STDOUT_FILENO, STDERR_FILENO);
	close(org_fd);
	g_state = IS_IDLE;
	handle_exit(msh, exit_code, true);
}
