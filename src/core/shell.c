/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 01:45:52 by asioud            #+#    #+#             */
/*   Updated: 2023/08/27 05:20:56 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd(void)
{
	char	*cmd;

	if (isatty(STDIN_FILENO))
		cmd = readline(MAG "minishell> " RESET);
	else
	{
		cmd = get_next_line(STDIN_FILENO);
		cmd = ft_strtrim(cmd, "\n");
	}
	return (cmd);
}

void	main_loop(t_parsing *prs)
{
	t_cli	cli;
	char	*cmd;
	int		original_stdout;
	int		original_stdin;

	original_stdout = dup(STDOUT_FILENO);
	original_stdin = dup(STDIN_FILENO);
	while (true)
	{
		cmd = get_cmd();
		if (!cmd)
		{
			free_all_mem(&(prs->g_shell->memory));
			exit(prs->g_shell->status);
		}
		if (isatty(STDIN_FILENO))
			add_history(cmd);
		cli.buffer = cmd;
		cli.buff_size = ft_strlen(cmd);
		cli.cur_pos = INIT_SRC_POS;
		prs->g_shell->status = parse_and_execute(prs, &cli);
		dup2(original_stdout, STDOUT_FILENO);
		dup2(original_stdin, STDIN_FILENO);
		unlink("/tmp/heredoc");
	}
}

int	main(int argc, char **argv, char **env)
{
	struct termios	mirror_termios;
	t_shell			*g_shell;
	t_parsing		*prs;

	prs = NULL;
	prs = malloc(sizeof(t_parsing));
	if (prs == NULL)
	{
		ft_putstr_fd("minishell: malloc error\n", 2);
		exit(1);
	}
	g_shell = malloc(sizeof(t_shell));
	g_shell->memory = NULL;
	g_shell->status = 0;
	prs->g_shell = g_shell;
	prs->tok = NULL;
	(void)argc;
	(void)argv;
	init_symtab(g_shell, env);
	signals(&mirror_termios);
	main_loop(prs);
	rl_clear_history();
	free_all_mem(&(prs->g_shell->memory));
	if (prs)
		free(prs);
	return (g_shell->status);
}

int	parse_and_execute(t_parsing *prs, t_cli *cli)
{
	t_node		*ast_cmd;
	t_token		*tok;
	t_curr_tok	*curr;

	curr = my_malloc(&(prs->g_shell->memory), sizeof(t_curr_tok));
	skip_whitespaces(cli);
	tok = get_token(prs->g_shell, cli, curr);
	ast_cmd = parse_cmd(prs, tok, curr);
	if (!ast_cmd)
		return (1);
	return (execc(prs->g_shell, ast_cmd));
}
