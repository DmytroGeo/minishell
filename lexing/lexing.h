/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:48:55 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/04/04 20:08:34 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include "../libft/libft.h"

typedef struct s_token
{
	int				index; // the index of the token
	char			*type; // the type of token like 'COMMAND'
	char			*value; // the literal value of the token like 'pwd'
	struct s_token	*next;
}			t_token;

int		ft_tokindex(t_token *elem, t_token **head);
int		ft_toksize(t_token *tok);

void	ft_tokadd_front(t_token **tok, t_token *new);
void	ft_tokadd_back(t_token **tok, t_token *new);
void	ft_tokdelone(t_token *tok);
void	ft_tokclear(t_token **tok);


t_token	*ft_toknew(char *type, char *value, int index);
t_token	*ft_toklast(t_token *tok);
t_token	*ft_tokfind(int i, t_token **head);

t_token	**lexing(char *str);

#endif
