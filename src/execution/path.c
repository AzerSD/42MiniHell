/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 05:03:22 by asioud            #+#    #+#             */
/*   Updated: 2023/08/25 14:17:26 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sp	*init_search_path_struct(char **path)
{
	t_sp	*sp;

	sp = (t_sp *)malloc(sizeof(t_sp));
	if (!sp)
		return (NULL);
	sp->symtab = get_symtab_entry("PATH");
	if (!sp->symtab || !(sp->symtab->val))
		return (free(sp), (errno = ENOENT), NULL);
	*path = sp->symtab->val;
	sp->p = *path;
	sp->p2 = NULL;
	sp->plen = 0;
	sp->valid_path = NULL;
	return (sp);
}

static char	*return_result_and_free(t_sp *sp, char *result)
{
	free(sp);
	return (result);
}

char	*search_path(char *file)
{
	char	*path;
	t_sp	*sp;

	sp = init_search_path_struct(&path);
	if (!sp)
		return (NULL);
	while (sp->p && *(sp->p))
	{
		sp->p2 = ft_strchr(sp->p, ':');
		if (!sp->p2)
			sp->p2 = sp->p + ft_strlen(sp->p);
		sp->plen = sp->p2 - sp->p;
		if (sp->plen == 0)
			sp->plen = 1;
		sp->valid_path = build_path_and_check_existence(sp->p, sp->p2, file,
				sp->plen);
		if (sp->valid_path != NULL)
			return (return_result_and_free(sp, sp->valid_path));
		if (*(sp->p2) == ':')
			sp->p = sp->p2 + 1;
		else
			sp->p = NULL;
	}
	return (return_result_and_free(sp, (errno = ENOENT, NULL)));
}

// char	*search_path(char *file)
// {
// 	char					*path;
// 	char					*p;
// 	char					*p2;
// 	int						plen;
// 	char					*valid_path;
// 	struct s_symtab_entry	*symtab;

// 	symtab = get_symtab_entry("PATH");
// 	if (!symtab)
// 		return ((errno = ENOENT), NULL);
// 	path = symtab->val;
// 	if (!path)
// 		return ((errno = ENOENT), NULL);
// 	p = path;
// 	while (p && *p)
// 	{
// 		p2 = ft_strchr(p, ':');
// 		if (!p2)
// 			p2 = p + ft_strlen(p);
// 		plen = p2 - p;
// 		if (plen == 0)
// 			plen = 1;
// 		valid_path = build_path_and_check_existence(p, p2, file, plen);
// 		if (valid_path != NULL)
// 			return (valid_path);
// 		if (*p2 == ':')
// 			p = p2 + 1;
// 		else
// 			p = NULL;
// 	}
// 	return ((errno = ENOENT), NULL);
// }
