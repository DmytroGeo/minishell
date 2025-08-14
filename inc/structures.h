/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:00:09 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/14 19:31:12 by dgeorgiy         ###   ########.fr       */
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
# include <sys/types.h>
# include <dirent.h>

typedef struct s_qts
{
	int	num_squotes;
	int	num_dquotes;
	int	in_dquotes;
	int	in_squotes;
}	t_qts;

typedef struct s_hd_exp
{
	char	*str;
	char	*var;
	char	*exp_var;
	char	*og_string;
	char	*temp;
	char	*next_dollar_sign;
	char	*current;
	char	*non_var_str;
	int		i;
	int		varlen;
	int		exp_varlen;
	int		strlen;
	int		non_var_len;
}	t_hd_exp;

typedef struct s_qts_remov
{
	char	*str;
	char	*exp_str;
	char	*current;
	char	*og_string;
	char	*next_quote;
	char	*temp;
	char	type;
	int		i;
	int		len;
	int		strlen;
}	t_qts_remov;

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
	int		strlen;
	int		exp_strlen;
	int		varlen;
	int		exp_varlen;
	char	*exp_var;
	char	*exp_str;
	char	*exp_start;
	char	*exp_end;
	char	*str;
	char	*og_str;
	char	*temp;
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
	int				exp_needed;
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
	int		num_heredocs;
	int		shell_id;
	int		parse_code;
	int		exit_code;
	int		*pid;
	int		**fd;
	char	*prompt;
	char	*line_read;
	char	**envp;
	t_token	*token_chain;
	t_proc	*proc_array;
}	t_cshell;

#endif