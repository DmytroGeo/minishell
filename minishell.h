/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:30:58 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/24 19:49:40 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>
# include <stdio.h>
# include <stdarg.h>

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

// LEXING:

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

// PARSING:

int			is_word(t_token *current_token);
int			is_pipe(t_token *current_token);
int			is_append(t_token *current_token);
int			is_heredoc(t_token *current_token);
int			is_redir_in(t_token *current_token);
int			is_redir_out(t_token *current_token);
int			is_redirect(t_token *current_token);
int			heredoc_fd(char *limiter);
int			is_valid_variable_assignment(char *str);
int			is_valid_variable_name(char *str);
int			find_envp_index(char **envp, const char *key);
int			find_number_of_outfiles(t_token *tok_chain);
int			find_number_of_infiles(t_token *tok_chain);
int			find_infiles(t_proc *proc, t_token *start);
int			find_outfiles(t_proc *proc, t_token *tok_chain);
int			find_cmd_and_args(t_proc *proc, t_token *tok_chain, char **envp);
int			return_heredoc_fd(char *limiter);
int			syntax_check_1(t_token *curr);
int			syntax_check_2(t_token *curr);
int			syntax_check_3(t_token *curr);
int			syntax_check_4(t_token *curr);
int			check_syntax(t_token *tok_chain);
int			init_processes(t_cshell *cshell);
int			export_variable(char ***envp, char *assignment);
int			unset_variable(char ***envp, char *key);
int			get_prompt(char **address_of_prompt);
int			copy_envp(char ***address_of_copy, char **envp);

void		proc_call(int i, char c);
void		init_cshell(t_cshell *cshell, char **envp);
void		expand_all(t_token **tok_chain, int exit_status, char **envp);
void		infile_err2(char *file_name);
void		infile_err3(char *file_name);
void		outfile_err(char *file_name);
void		free_proc_contents(t_proc *proc);

// EXECUTION:

int			execute_built_ins(t_cshell *cshell, int i, int outfile_fd);
int			ft_chdir(char **new_directory, char **prompt, char ***envp);
int			execution(t_cshell *cshell);
int			wait_for_processes(int *pid, int ac);
int			unset_all_vars(char **arguments, char ***envp);
int			ft_echo(int fd, char **arguments);
int			print_envp(int fd, char **envp);
int			ft_exit(char **cmd_and_args, t_cshell *cshell);
int			execute_in_main(t_cshell *cshell);
int			export_all_vars(char **arguments, char ***envp, int fd);
int			is_valid_var_unset(char *str);

void		close_fds(int **fd, int len);
void		ft_perror(char *str, char c);
void		process_loop(t_cshell *cshell);
void		execute_in_child(int i, t_cshell *cshell);
void		free_and_exit(int *pid, int **fd, t_cshell *cshell);
void		dup_infile(int i, t_cshell *cshell);
void		dup_outfile(int i, t_cshell *cshell);
void		init_setup(t_cshell *cshell);
void		evaluate_and_execute(t_cshell *cshell, int *exit_code);
void		ft_pwd(int outfile_fd);
#endif