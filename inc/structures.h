/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:00:09 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/31 11:51:36 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <linux/limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <string.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <unistd.h>


typedef struct s_lex
{
	char	*next_raw_tok;
	int		i;
	int		start;
	int		in_quotes;
	char	current_quote;
}	t_lex;

typedef struct s_exp
{
	int		i;
	int		expanded_strlen;
	int		varlen;
	char	*expanded_string;
	char	*expanded_var;
	char	*temp;
	char	*cur;
}	t_exp;

typedef enum e_tok_type
{
	word,
	_pipe,
	redir_in,
	redir_out,
	append,
	heredoc,
}	t_tok_type;

typedef struct s_tok_cont
{
	t_tok_type	type;
	char		*value;
}	t_tok_cont;

typedef struct s_token
{
	void			*content;
	struct s_token	*previous;
	struct s_token	*next;
}	t_token;

typedef struct s_op
{
	char		*symbol;
	t_tok_type	type;
}	t_op;

typedef struct s_proc
{
	int		num_inf;
	int		num_outf;
	int		*infiles;
	int		*outfiles;
	char	**cmd_and_args;
}	t_proc;

typedef struct s_cshell
{
	int		num_of_proc;
	int		shell_id;
	int		parse_code;
	int		exec_code;
	int		*pid;
	int		**fd;
	char	*prompt;
	char	**envp;
	t_token	*token_chain;
	t_proc	*proc_array;
}	t_cshell;

#endif