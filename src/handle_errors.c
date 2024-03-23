/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 01:19:07 by dklimkin          #+#    #+#             */
/*   Updated: 2024/03/23 16:14:12 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_err_msg(t_err err)
{
	if (err == CMD_NOT_FOUND)
		return (CMD_NOT_FOUND_MSG);
	if (err == NO_FILE_OR_DIR || err == PERM_DENIED || err == CMD_IS_DIR)
		return (strerror(err));
	if (err == UNEXPECTED_TOK)
		return (UNEXPECTED_TOK_MSG);
	if (err == UNEXPECTED_EOF)
		return (UNEXPECTED_EOF_TOK_MSG);
	if (err == TOO_MANY_ARGS || err == CD_TOO_MANY_ARGS)
		return (TOO_MANY_ARGS_MSG);
	if (err == AMBGIGUOUS_R)
		return (AMBIGUOUS_REDIRECT_MSG);
	if (err == CD_PERM_DENIED)
		return (strerror(PERM_DENIED));
	if (err == CD_INVALID_OPTION)
		return (INVALID_OPTION_MSG);
	if (err == CD_NO_FILE_OR_DIR)
		return (strerror(NO_FILE_OR_DIR));
	if (err == CD_NOT_DIR)
		return (NOT_DIR_MSG);
	if (err == EXPORT_INVALID_ID)
		return (INVALID_IDENTIFIER_MSG);
	if (err == EXIT_INVALID_ARG)
		return (INVALID_EXIT_ARG_MSG);
	return ("");
}

static void	print_tok(char *s)
{
	char	*tok;
	char	*temp;

	tok = ft_strdup("`");
	temp = ft_strjoin(tok, s);
	free(tok);
	tok = temp;
	temp = ft_strjoin(tok, "\'");
	free(tok);
	tok = temp;
	ft_putstr_fd(tok, STDERR_FILENO);
	free(tok);
}

static void	print_msg_and_ctx(char *ctx1, char *ctx2, bool is1tok, bool is2tok)
{
	if (ctx1)
	{
		if (is1tok)
			print_tok(ctx1);
		else
			ft_putstr_fd(ctx1, STDERR_FILENO);
	}
	if (ctx2)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		if (is2tok)
			print_tok(ctx2);
		else
			ft_putstr_fd(ctx2, STDERR_FILENO);
	}
}

static void	print_custom_err_msg(t_err err, char *ctx)
{
	ft_putstr_fd(PRG_NAME, STDERR_FILENO);
	if (err > 60)
		ft_putstr_fd("exit: ", STDERR_FILENO);
	else if (err > 50)
		ft_putstr_fd("export: ", STDERR_FILENO);
	else if (err > 40)
	{
		if (ctx)
			ft_putstr_fd("cd: ", STDERR_FILENO);
		else
			ft_putstr_fd("cd", STDERR_FILENO);
	}
	if (err == UNEXPECTED_TOK || err == UNEXPECTED_EOF)
		print_msg_and_ctx(get_err_msg(err), ctx, false, true);
	else if (err == EXPORT_INVALID_ID)
		print_msg_and_ctx(ctx, get_err_msg(err), true, false);
	else
		print_msg_and_ctx(ctx, get_err_msg(err), false, false);
	ft_putstr_fd("\n\0", STDERR_FILENO);
}

void	handle_err(t_msh **msh, t_err err, char *ctx, int exit_code)
{
	if (err == SYSTEM)
	{
		ft_putstr_fd(PRG_NAME, STDERR_FILENO);
		ft_putstr_fd(ctx, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n\0", STDERR_FILENO);
	}
	else
		print_custom_err_msg(err, ctx);
	g_state = IS_IDLE;
	handle_exit(msh, exit_code, true);
}
