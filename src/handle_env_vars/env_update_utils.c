/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:37:43 by sliashko          #+#    #+#             */
/*   Updated: 2024/03/25 11:39:50 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void update_var_value(t_env *head, t_evar evar) {
  t_env *curr;
  char *temp;

  curr = head;
  while (curr) {
    if (!(ft_strncmp(evar.name, curr->name, 5000))) {
      if (evar.value) {
        if (evar.is_to_append)
          temp = ft_strjoin(curr->value, evar.value);
        else
          temp = ft_strdup(evar.value);
        free(curr->value);
        curr->value = temp;
      }
      return;
    }
    curr = curr->next;
  }
}

bool is_in_env(t_env *head, char *varname) {
  t_env *curr;

  curr = head;
  while (curr) {
    if (!(ft_strncmp(varname, curr->name, 5000)))
      return (true);
    curr = curr->next;
  }
  return (false);
}
