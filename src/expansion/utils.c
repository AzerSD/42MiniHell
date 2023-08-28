/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 19:45:51 by asioud            #+#    #+#             */
/*   Updated: 2023/08/28 01:42:54 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_buffer_bounds(t_shell *g_shell, int *count, int *len, char ***buf)
{
	int		newlen;
	char	**hn2;

	if (*count >= *len)
	{
		if (!(*buf))
		{
			*buf = my_malloc(&g_shell->memory, 32 * sizeof(char **));
			if (!(*buf))
				return (0);
			*len = 32;
		}
		else
		{
			newlen = (*len) * 2;
			hn2 = my_realloc(&g_shell->memory, *buf, newlen * sizeof(char **));
			if (!hn2)
				return (0);
			*buf = hn2;
			*len = newlen;
		}
	}
	return (1);
}

void	free_buffer(int len, char **buf)
{
	if (!len)
		return ;
	while (len--)
		free(buf[len]);
	free(buf);
}

void	search_colon(t_shell *g_shell, char *orig_var_name,
		struct s_var_expand *var)
{
	var->sub = ft_strchr(orig_var_name, ':');
	if (!var->sub)
		var->sub = strchr_any(orig_var_name, "-=?+%#");
	if (var->sub)
		var->len = (size_t)(var->sub - orig_var_name);
	else
		ft_strlen(orig_var_name);
	if (var->sub && *var->sub == ':')
		var->sub++;
	var->var_name = my_malloc(&g_shell->memory, var->len + 1);
	ft_strncpy(var->var_name, orig_var_name, var->len);
	var->var_name[var->len] = '\0';
	var->empty_val = "";
	var->tmp = NULL;
	var->setme = 0;
	var->entry = get_symtab_entry(g_shell, var->var_name);
	if (var->entry && var->entry->val && var->entry->val[0])
		var->tmp = var->entry->val;
	else
		var->tmp = var->empty_val;
	var->result = NULL;
	var->expanded = 0;
	var->p = NULL;
}

char	*error_inv_var_sub(char *orig_var_name)
{
	ft_printf_fd(2, "error: invalid var substitution: %s\n", \
		orig_var_name);
	return (INVALID_VAR);
}

void	handle_get_length(struct s_var_expand *var)
{
	char	*tmp_str;

	tmp_str = ft_itoa(ft_strlen(var->tmp));
	if (tmp_str)
	{
		ft_strcpy(var->buf, tmp_str);
		free(tmp_str);
	}
}
