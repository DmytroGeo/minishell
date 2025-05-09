/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:21:46 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/09 17:22:02 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
#include "libft.h"
#include "lexing.h"
typedef struct s_simple_command
{
    int infile;
    t_list **commands;
    int outfile;
    // struct s_simple_command *next_command;
}           t_simple_command;

typedef struct s_tree
{
    t_simple_command *command;
}           t_tree;

t_simple_command  *parse(t_token *token_chain);

#endif