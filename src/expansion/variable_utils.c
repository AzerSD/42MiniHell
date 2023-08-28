/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 23:27:27 by asioud            #+#    #+#             */
/*   Updated: 2023/08/28 01:44:29 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_svar_expand(struct s_var_expand *v)
{
	v->entry = NULL;
	v->len = 0;
	v->get_length = 0;
	v->sub = NULL;
	v->var_name = NULL;
	v->empty_val = NULL;
	v->tmp = NULL;
	v->setme = 0;
	v->p = NULL;
	v->longest = 0;
	v->p2 = NULL;
	v->expanded = 0;
	ft_memset(v->buf, 0, sizeof(v->buf));
}

char	*setup_var(char *orig_var_name, struct s_var_expand *var)
{
	if (!orig_var_name)
		return (NULL);
	orig_var_name++;
	var->len = ft_strlen(orig_var_name);
	if (*orig_var_name == '{')
	{
		orig_var_name[var->len - 1] = '\0';
		orig_var_name++;
	}
	if (!*orig_var_name)
		return (NULL);
	var->get_length = 0;
	if (*orig_var_name == '#')
	{
		if (ft_strchr(orig_var_name, ':'))
			return (error_inv_var_sub(orig_var_name));
		var->get_length = 1;
		orig_var_name++;
	}
	return (orig_var_name);
}

char	*exit_code_to_str(unsigned char status)
{
	static char	str[4];
	char		*status_str;

	status_str = ft_itoa(status);
	if (status_str != NULL)
	{
		ft_strcpy(str, status_str);
		free(status_str);
	}
	else
		str[0] = '\0';
	return (str);
}

char	*exit_code_expansion(t_shell *g_shell, char *orig_var_name)
{
	char	*exit_code_str;
	char	*exit_code_copy;

	(void)orig_var_name;
	exit_code_str = exit_code_to_str(g_shell->status);
	exit_code_copy = ft_strdup(exit_code_str);
	if (exit_code_copy == NULL)
	{
		ft_printf_fd(STDERR_FILENO,
			"error: failed to allocate memory for exit code\n");
		return (INVALID_VAR);
	}
	return (exit_code_copy);
}

void	check_result(t_shell *g_shell, struct s_var_expand *var)
{
	if (var->setme)
	{
		if (!var->entry)
			var->entry = add_to_symtab(g_shell, var->var_name);
		if (var->entry)
			symtab_entry_setval(g_shell, var->entry, var->tmp);
	}
	if (var->get_length)
	{
		if (!var->tmp)
			ft_strcpy(var->buf, "0");
		else
			handle_get_length(var);
		var->p = malloc(ft_strlen(var->buf) + 1);
		if (var->p)
			ft_strcpy(var->p, var->buf);
	}
	else
	{
		var->p = malloc(ft_strlen(var->tmp) + 1);
		if (var->p)
			ft_strcpy(var->p, var->tmp);
	}
}
