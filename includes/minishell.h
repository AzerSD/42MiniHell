/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 03:03:14 by lhasmi            #+#    #+#             */
/*   Updated: 2023/08/27 03:03:14 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <ctype.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <fnmatch.h>
# include <glob.h>
# include <limits.h>
# include <locale.h>
# include <pwd.h>
# include <regex.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include "../libs/garbage_collector/memory.h"
# include "../src/builtins/builtins.h"
# include "../src/core/shell.h"
# include "../src/execution/executor.h"
# include "../src/expansion/expansion.h"
# include "../src/parsing/lexer.h"
# include "../src/parsing/node.h"
# include "../src/parsing/parser.h"
# include "../src/parsing/tokenizer.h"
# include "../src/signals/signals.h"
# include "../src/symbol_table/symtab.h"
# include "libft.h"

# define RESET "\001\033[0m\002"
# define RED "\001\033[31m\002"
# define GRN "\001\033[32m\002"
# define YEL "\001\033[33m\002"
# define BLU "\001\033[34m\002"
# define MAG "\001\033[35m\002"
# define CYN "\001\033[36m\002"
# define WHT "\001\033[37m\002"

typedef unsigned char		t_status;
typedef struct g_shell
{
	t_status				status;
	void					*memory;
	struct s_symtab_stack	s_symtab_stack;
}							t_shell;

#endif
