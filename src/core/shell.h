/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 01:55:30 by asioud            #+#    #+#             */
/*   Updated: 2023/08/27 04:46:16 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

void	prompt_display_ps1(void);
void	prompt_display_ps2(void);
int		parse_and_execute(t_parsing *prs, t_cli *cli);
// void	print_ast(t_node *node, int indent);

#endif
