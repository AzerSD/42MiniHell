/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 14:11:50 by lhasmi            #+#    #+#             */
/*   Updated: 2023/08/25 14:17:32 by lhasmi           ###   ########.fr       */
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

static char	*build_path(char *start, char *end, char *file, int plen)
{
	char	*path;

	path = my_malloc(&shell_instance.memory, plen + 1 + ft_strlen(file) + 1);
	if (!path)
		return (NULL);
	ft_strncpy(path, start, plen);
	path[plen] = '\0';
	if (end[-1] != '/')
		ft_strcat(path, "/");
	ft_strcat(path, file);
	return (path);
}

char	*build_path_and_check_existence(char *p, char *p2, char *file, int plen)
{
	char	*path;

	path = build_path(p, p2, file, plen);
	if (!path)
		return (NULL);
	if (file_exists(path))
		return (path);
	else
		free(path);
	return (NULL);
}
