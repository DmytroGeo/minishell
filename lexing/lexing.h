/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:48:55 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/04/05 13:02:30 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include "libft.h"
// We can do this instead of hardcoding the path (say for example "../libft/libft.h")
// We can do this because of the -I stuff in the Makefile 
// The -I flag tells the compiler where to look for the .h file
// We should do this instead of the hardcoding because if 
// we were to move the relative folders around in the future, "../libft/libft.h" would no longer apply.
// and it makes the header location-dependant.

typedef enum e_token_type 
{
    WORD,
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    APPEND,
    HEREDOC
}	t_token_type;

typedef struct s_token
{
	int				index; // the index of the token
	t_token_type	type; // the type of token like 'COMMAND'
	char			*value; // the literal value of the token like 'pwd'
	char			*path;
	struct s_token	*next;
}			t_token;

typedef struct s_op 
{
    char *symbol;
    t_token_type type;
}	t_op;

int		ft_tokindex(t_token *elem, t_token **head);
int		ft_toksize(t_token *tok);

void	ft_tokadd_front(t_token **tok, t_token *new);
void	ft_tokadd_back(t_token **tok, t_token *new);
void	ft_tokdelone(t_token *tok);
void	ft_tokclear(t_token **tok);

t_token	*ft_toknew(t_token_type *type, char *value, int index);
t_token	*ft_toklast(t_token *tok);
t_token	*ft_tokfind(int i, t_token **head);

t_token	*lexing(char *line, char **envp);

char **split_line(char *line);
int is_operator_start(char *line, int i);
int operator_length(char *line);

#endif
