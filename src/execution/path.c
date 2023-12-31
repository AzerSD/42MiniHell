/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 05:03:22 by asioud            #+#    #+#             */
/*   Updated: 2023/08/24 18:57:33 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	file_exists(char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISREG(st.st_mode))
		return (1);
	else
	{
		errno = ENOENT;
		return (0);
	}
}

static char	*build_path(t_shell *g_shell, char *start, \
	char *end, char *file, int plen)
{
	char	*path;

	path = my_malloc(&g_shell->memory, plen + 1 + ft_strlen(file) + 1);
	if (!path)
		return (NULL);
	ft_strncpy(path, start, plen);
	path[plen] = '\0';
	if (end[-1] != '/')
		ft_strcat(path, "/");
	ft_strcat(path, file);
	return (path);
}

char	*build_path_and_check_existence(t_shell *g_shell, char *p, char *p2,\
	char *file, int plen)
{
	char	*path;

	path = build_path(g_shell, p, p2, file, plen);
	if (!path)
		return (NULL);
	if (file_exists(path))
		return (path);
	else
		free(path);
	return (NULL);
}

char	*search_path(t_shell *g_shell, char *file)
{
	char	*path;
	char	*p;
	char	*p2;
	int		plen;
	char	*valid_path;
	struct s_symtab_entry			*symtab;

	symtab = get_symtab_entry(g_shell, "PATH");
	if (!symtab)
		return ((errno = ENOENT), NULL);
	path = symtab->val;
	if (!path)
		return ((errno = ENOENT), NULL);
	p = path;
	while (p && *p)
	{
		p2 = ft_strchr(p, ':');
		if (!p2)
			p2 = p + ft_strlen(p);
		plen = p2 - p;
		if (plen == 0)
			plen = 1;
		valid_path = build_path_and_check_existence(g_shell, p, p2, file, plen);
		if (valid_path != NULL)
			return (valid_path);
		if (*p2 == ':')
			p = p2 + 1;
		else
			p = NULL;
	}
	return ((errno = ENOENT), NULL);
}
