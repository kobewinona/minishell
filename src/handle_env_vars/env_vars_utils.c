/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <dklimkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:44:53 by sliashko          #+#    #+#             */
/*   Updated: 2024/03/25 11:41:19 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// retrieves a value of variable. Return NULL if not found
char *get_env_var(t_env *head, char *varname) {
  t_env *curr;

  curr = head;
  while (curr) {
    if (!(ft_strncmp(varname, curr->name, 1000)) && curr->is_value_assigned &&
        curr->value) {
      return (curr->value);
    }
    curr = curr->next;
  }
  return ("");
}

void set_var_deleted(t_env *head, char *varname) {
  t_env *curr;
  t_env *temp;
  t_env *prev;

  prev = head;
  curr = head->next;
  while (curr) {
    if (!(ft_strncmp(varname, curr->name, 5000))) {
      temp = curr->next;
      curr = prev;
      free(curr->next->name);
      free(curr->next->value);
      free(curr->next);
      curr->next = temp;
      return;
    }
    prev = curr;
    curr = curr->next;
  }
}

// updates value of env VAR or creates a new one
void update_var(t_env *head, t_evar evar) {
  if (is_in_env(head, evar.name))
    return (update_var_value(head, evar));
  append_var_node(&head, evar.name, evar.value);
}

void increment_shlvl(t_msh **msh, t_env *env_vars) {
  t_evar evar;

  ft_memset(&evar, 0, sizeof(t_evar));
  if (get_env_var(env_vars, "SHLVL")) {
    evar.name = "SHLVL";
    evar.value = ft_itoa(ft_atoi(get_env_var(env_vars, "SHLVL")) + 1);
    if (!evar.value)
      return (handle_err(msh, SYSTEM, MALLOC, 1));
    update_var(env_vars, evar);
    return (free(evar.value));
  } else
    update_var(env_vars, (t_evar){"SHLVL", "1", false});
}
