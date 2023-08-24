/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 01:45:52 by asioud            #+#    #+#             */
/*   Updated: 2023/08/24 21:03:10 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell *get_shell_instance() {
    static t_shell g_shell_instance;
    return &g_shell_instance;
}

char	*get_cmd(void)
{
	char	*cmd;

	if (isatty(fileno(stdin)))
		cmd = readline(MAG "minishell> " RESET);
	else
	{
		cmd = get_next_line(fileno(stdin));
		cmd = ft_strtrim(cmd, "\n");
	}
	return (cmd);
}

void	main_loop(t_shell *g_shell)
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
			free_all_mem(&g_shell->memory);
			exit(g_shell->status);
		}
		if (isatty(STDIN_FILENO))
			add_history(cmd);
		cli.buffer = cmd;
		cli.buff_size = ft_strlen(cmd);
		cli.cur_pos = INIT_SRC_POS;
		g_shell->status = parse_and_execute(g_shell, &cli);
		dup2(original_stdout, STDOUT_FILENO);
		dup2(original_stdin, STDIN_FILENO);
	}
}

int	main(int argc, char **argv, char **env)
{
	struct termios	mirror_termios;
	t_shell			*g_shell;
	g_shell = malloc(sizeof(t_shell));
	g_shell->memory = NULL;
	g_shell->status = 0;
	(void)argc;
	(void)argv;
	init_symtab(g_shell, env);
	signals(&mirror_termios);
	main_loop(g_shell);
	rl_clear_history();
	free_all_mem(&g_shell->memory);
	printf("exit1 %d\n", g_shell->status);
	return (g_shell->status);
}

int	parse_and_execute(t_shell *g_shell, t_cli *cli)
{
	t_node		*ast_cmd;
	t_token		*tok;
	t_curr_tok	*curr;

	curr = my_malloc(&(g_shell->memory), sizeof(t_curr_tok));
	skip_whitespaces(cli);
	tok = get_token(g_shell, cli, curr);
	ast_cmd = parse_cmd(g_shell, tok, curr);
	if (!ast_cmd)
		return (1);
	return (execc(g_shell, ast_cmd));
}

void	print_ast(t_node *node, int indent)
{
	t_node	*child;
	if (node == NULL)
		return ;
	for (int i = 0; i < indent - 1; i++)
		printf("%s  │%s", BLU, RESET);
	if (indent > 0)
		printf("%s  ├─%s", CYN, RESET);
	printf("%sValue: %s%s,%s	%slevel: %s%u%s\n",
			GRN,
			YEL,
			node->val.str,
			RESET,
			RED,
			YEL,
			node->type,
			RESET);
	child = node->first_child;
	while (child != NULL)
	{
		print_ast(child, indent + 1);
		child = child->next_sibling;
	}
}
