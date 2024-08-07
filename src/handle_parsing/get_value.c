/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:06:00 by dklimkin          #+#    #+#             */
/*   Updated: 2024/02/29 19:06:01 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool process_quotes(t_val *ctx, char *c, int i) {
  if (!ctx->is_in_quotes) {
    (ctx->is_in_quotes) = (*c) == T_DOUBLE_QUOTE || (*c) == T_SINGLE_QUOTE;
    if (ctx->is_in_quotes) {
      (*ctx) = (t_val){ctx->s, ctx->len, ctx->offset, true, (*c)};
      return (ft_memmove(c, c + 1, ((ctx->len--) - i)), true);
    }
  }
  if (ctx->is_in_quotes && (*c) == ctx->end_char) {
    if (ctx->is_in_quotes)
      (*ctx) = (t_val){ctx->s, ctx->len, ctx->offset, false, T_SPACE};
    return (ft_memmove(c, c + 1, ((ctx->len--) - i)), true);
  }
  return (false);
}

static size_t extract_value(t_val *ctx) {
  int i;

  i = 0;
  while ((*ctx->s)[i]) {
    if (process_quotes(ctx, &(*ctx->s)[i], i))
      continue;
    if ((*ctx->s)[i] && (*ctx->s)[i] == ctx->end_char)
      break;
    ctx->offset++;
    i++;
  }
  return (ctx->len = i, i);
}

char *get_value(t_msh **msh, char **s) {
  t_val ctx;
  char *value;
  int len;

  if (!(*s) || is_emptystr(*s))
    return (NULL);
  while (ft_isspace((**s)))
    (*s)++;
  ctx = (t_val){s, ft_strlen((*s)), 0, false, T_SPACE};
  len = extract_value(&ctx);
  if (len == ERROR)
    return (NULL);
  if (ctx.is_in_quotes)
    return (handle_err(msh, UNEXPECTED_EOF, tokstr(ctx.end_char), 2), NULL);
  value = (*s);
  (*s) += ctx.offset + (value[ctx.len] != '\0');
  value[ctx.len] = '\0';
  return (value);
}
