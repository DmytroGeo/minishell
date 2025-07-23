/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:48:55 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/23 16:22:48 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include "../libft/libft.h"

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
	char	*prompt;
	char	**envp;
	int		*pid;
	int		**fd;
	t_token	*token_chain;
	t_proc	*proc_array;	
}	t_cshell;

void		lexing(t_cshell *cshell, char *line);
void		ft_dlstadd_back(t_token **tok, t_token *new);
void		ft_dlstadd_front(t_token **tok, t_token *new);
void		print_raw_tokens(char **raw_tokens);
void		print_token_list(t_token *head);
void		populate_operators(t_op *operators);
void		ft_perror(char *str, char c);
void		del_tok_cont(void *content);
void		free_tok_chain(t_token **start, void (*del)(void*));
void		free_cshell(t_cshell *cshell);
void		free_whole_cshell(t_cshell *cshell);
void		free_proc_array(t_proc *proc_array, int len);

int			is_surrounded_by(char *str, char quote);
int			is_operator_start(char *line, int i);
int			operator_length(char *line);
int			ft_tokindex(t_token *elem, t_token **head);
int			ft_toksize(t_token *tok);

t_token		*ft_toklast(t_token *tok);
t_token		*ft_dlstnew(void *content);

t_tok_type	identify_type(char *token, t_op *operators);

t_tok_cont	*init_tok_cont(char *raw_token, t_op *operators);

char		*find_variable_in_envp(char **envp, char *variable);
char		**split_line(char *line);
char		*strip_quotes(char *str);
char		*get_path(char *str, char **envp);

#endif
