/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:48:55 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/16 14:18:19 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #ifndef LEXING_H
// # define LEXING_H

// # include "libft.h"
// # include "../execution/execution.h"

// // We can do this instead of hardcoding the path (say for example "../libft/libft.h")
// // We can do this because of the -I stuff in the Makefile 
// // The -I flag tells the compiler where to look for the .h file
// // We should do this instead of the hardcoding because if 
// // we were to move the relative folders around in the future, "../libft/libft.h" would no longer apply.
// // and it makes the header location-dependant.



// # include "../parsing/parsing.h"

// We can do this instead of hardcoding the path (say for example "../libft/libft.h")
// We can do this because of the -I stuff in the Makefile 
// The -I flag tells the compiler where to look for the .h file
// We should do this instead of the hardcoding because if 
// we were to move the relative folders around in the future, "../libft/libft.h" would no longer apply.
// and it makes the header location-dependant.

// typedef enum e_token_type 
// {
//     word,
//     _pipe,
//     redir_in,
//     redir_out,
//     append,
//     heredoc,
// 	end_of_file,
// }	t_token_type;

// typedef struct s_token
// {
// 	int				index; // the index of the token
// 	t_token_type	type; // the type of token like 'COMMAND'
// 	char			*value; // the literal value of the token like 'pwd'
// 	char			*path;
// 	struct s_token	*next;
// }			t_token;

// typedef struct s_op 
// {
//     char *symbol;
//     t_token_type type;
// }	t_op;

// int		ft_tokindex(t_token *elem, t_token **head);
// int		ft_toksize(t_token *tok);

// void	ft_tokadd_front(t_token **tok, t_token *new);
// void	ft_tokadd_back(t_token **tok, t_token *new);
// void	ft_tokdelone(t_token *tok);
// void	ft_tokclear(t_token **tok);

// t_token	*ft_toknew(t_token_type *type, char *value, int index);
// t_token	*ft_tokfind(int i, t_token **head);
// t_token	*lexing(char *line, char **envp);
// t_token	*ft_toklast(t_token *tok);

// t_token_type identify_type(char *token, t_op *operators);

// void    print_raw_tokens(char **raw_tokens);
// void	print_token_list(t_token *head);
// void    array_free(char **arr);
// char	*find_variable_in_envp(char **envp, char *variable);
// char	**split_line(char *line);
// char	*strip_quotes(char *str);

// int is_surrounded_by(char *str, char quote);
// int	is_operator_start(char *line, int i);
// int	operator_length(char *line);
// void	populate_operators(t_op *operators);
// char	*get_path(char *str, char **envp);
// char	*find_path_variable(char **envp);
// char	*find_home_variable(char **envp);
// void	ft_perror(char *str, char c);

#ifndef LEXING_H
# define LEXING_H

# include "../libft/libft.h"

typedef enum e_token_type
{
	word,
	_pipe,
	redir_in,
	redir_out,
	append,
	heredoc,
}   t_token_type;

typedef struct s_token_content
{
	t_token_type    type; // the type of token like 'PIPE'
	char            *value; // the literal value of the token like '|'   
} t_token_content;

typedef struct s_token
{
	void            *content;
	struct s_token  *previous;
	struct s_token  *next;
}           t_token;

typedef struct s_op
{
	char *symbol;
	t_token_type type;
}   t_op;

void	ft_dlstadd_back(t_token **tok, t_token *new);
void	ft_dlstadd_front(t_token **tok, t_token *new);
void    print_raw_tokens(char **raw_tokens);
void    print_token_list(t_token *head);
void	populate_operators(t_op *operators);
void	ft_perror(char *str, char c);
void  	del_tok_cont(void *content);
void	free_tok_chain(t_token **start, void (*del)(void*));

int		is_surrounded_by(char *str, char quote);
int		is_operator_start(char *line, int i);
int		operator_length(char *line);
int     ft_tokindex(t_token *elem, t_token **head);
int     ft_toksize(t_token *tok);

void	lexing(t_token **tok_chain, char *line);
t_token *ft_toklast(t_token *tok);
t_token	*ft_dlstnew(void *content);

t_token_type identify_type(char *token, t_op *operators);

t_token_content	*init_token_content(char *raw_token, t_op *operators);

char	*find_variable_in_envp(char **envp, char *variable);
char	**split_line(char *line);
char	*strip_quotes(char *str);
char	*get_path(char *str, char **envp);


#endif
