/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 21:51:37 by asioud            #+#    #+#             */
/*   Updated: 2023/08/26 21:46:35 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*var_is_unset(struct s_var_expand *v)
{
	if (v->sub && *v->sub)
	{
		if (v->sub[0] == '-')
			v->tmp = v->sub + 1;
		else if (v->sub[0] == '=')
		{
			v->tmp = v->sub + 1;
			v->setme = 1;
		}
		else if (v->sub[0] == '?')
		{
			if (v->sub[1] == '\0')
				ft_printf_fd(2, "error: %s: parameter not set\n", v->var_name);
			else
				ft_printf_fd(2, "error: %s: %s\n", v->var_name, v->sub + 1);
			return (INVALID_VAR);
		}
		else if (v->sub[0] == '+')
			return (NULL);
		else
			return (INVALID_VAR);
	}
	else
		v->tmp = v->empty_val;
	return (NULL);
}

char	*var_is_set_with_percent(t_shell *g_shell, struct s_var_expand *v)
{
	v->sub++;
	v->p = word_expand_to_str(g_shell, v->tmp);
	if (!v->p)
		return (INVALID_VAR);
	v->longest = 0;
	if (*v->sub == '%')
		v->longest = 1;
	v->sub++;
	v->len = match_suffix(v->sub, v->p, v->longest);
	if (v->len == 0)
		return (v->p);
	v->p2 = my_malloc(&g_shell->memory, v->len + 1);
	if (v->p2)
	{
		ft_strncpy(v->p2, v->p, v->len);
		v->p2[v->len] = '\0';
	}
	free(v->p);
	return (v->p2);
}

char	*var_is_set_with_hash(t_shell *g_shell, struct s_var_expand *v)
{
	v->sub++;
	v->p = word_expand_to_str(g_shell, v->tmp);
	if (!v->p)
		return (INVALID_VAR);
	v->longest = 0;
	if (*v->sub == '#')
		v->longest = 1;
	v->sub++;
	v->len = match_prefix(v->sub, v->p, v->longest);
	if (v->len == 0)
		return (v->p);
	v->p2 = my_malloc(&g_shell->memory, ft_strlen(v->p) - v->len + 1);
	if (v->p2)
		ft_strcpy(v->p2, v->p + v->len);
	free(v->p);
	return (v->p2);
}

char	*var_is_set(t_shell *g_shell, struct s_var_expand *v)
{
	if (v->sub && *v->sub)
	{
		if (v->sub[0] == '+')
			v->tmp = v->sub + 1;
		else if (v->sub[0] == '%')
			return (var_is_set_with_percent(g_shell, v));
		else if (v->sub[0] == '#')
			return (var_is_set_with_hash(g_shell, v));
		else
			return (INVALID_VAR);
	}
	return (NULL);
}

char	*var_expand(t_shell *g_shell, char *orig_var_name)
{
	struct s_var_expand	var;

	init_svar_expand(&var);
	orig_var_name = setup_var(orig_var_name, &var);
	if (!*orig_var_name)
		return (NULL);
	if (ft_strcmp(orig_var_name, "?") == 0)
		return (exit_code_expansion(g_shell, orig_var_name));
	search_colon(g_shell, orig_var_name, &var);
	if (!var.tmp || var.tmp == var.empty_val)
		var.result = var_is_unset(&var);
	else
		var.result = var_is_set(g_shell, &var);
	if (var.result != NULL)
		return (var.result);
	if (var.tmp)
	{
		var.tmp = word_expand_to_str(g_shell, var.tmp);
		if (var.tmp)
			var.expanded = 1;
	}
	check_result(g_shell, &var);
	return (var.p);
}
