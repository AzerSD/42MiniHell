/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 05:03:22 by asioud            #+#    #+#             */
/*   Updated: 2023/08/27 22:46:26 by lhasmi           ###   ########.fr       */
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

static char	*build_path(t_shell *g_shell, char **range, int plen)
{
	char	*path;

	path = my_malloc(&g_shell->memory, plen + 1 + ft_strlen(range[2]) + 1);
	if (!path)
		return (NULL);
	ft_strncpy(path, range[0], plen);
	path[plen] = '\0';
	if (range[1][-1] != '/')
		ft_strcat(path, "/");
	ft_strcat(path, range[2]);
	return (path);
}

char	*build_path_and_check_existence(t_shell *g_shell, char **pfile, \
		int plen)
{
	char	*path;

	path = build_path(g_shell, pfile, plen);
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
	char					*poop_path[3];
	int						plen;
	char					*valid_path;
	struct s_symtab_entry	*symtab;

	symtab = get_symtab_entry(g_shell, "PATH");
	poop_path[0] = symtab->val;
	if (!symtab || !poop_path[0])
		return ((errno = ENOENT), NULL);
	poop_path[1] = poop_path[0];
	while (poop_path[1] && *poop_path[1])
	{
		poop_path[2] = ft_strchr(poop_path[1], ':');
		if (!poop_path[2])
			poop_path[2] = poop_path[1] + ft_strlen(poop_path[1]);
		plen = poop_path[2] - poop_path[1];
		if (plen == 0)
			plen = 1;
		valid_path = build_path_and_check_existence(g_shell, \
			(char *[]){poop_path[1], poop_path[2], file}, plen);
		if (valid_path != NULL)
			return (valid_path);
		if (*poop_path[2] == ':')
			poop_path[1] = poop_path[2] + 1;
		else
			poop_path[1] = NULL;
	}
	return ((errno = ENOENT), NULL);
}
