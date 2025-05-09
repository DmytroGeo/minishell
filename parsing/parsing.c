/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:22:58 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/09 17:23:19 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int is_command(t_token *token_chain)
{
    return (token_chain->path != NULL);
}

int is_redir_in(t_token *token_chain)
{
    return (token_chain->type == REDIR_IN);
}

t_simple_command    *parse_struct_1(t_token *token_chain)
{
    // cmd1 infile > ....
    t_simple_command *simple_command = malloc(sizeof(simple_command));
    t_token *current_token = token_chain;
    t_token *next_token = current_token->next;
    t_list *commands = NULL;
    // the first command of the simple command is command.
    // the infile is the second thing.
    // go through the token string - If we find a pipe we should expect a command after it.
    // if we find a redir_out we should see an outfile after it.
    // error should free.
}

t_simple_command  *parse(t_token *token_chain)
{
    t_simple_command  *simple_command = NULL;
    if (!token_chain)
        return (NULL);
    if (is_command(token_chain))
        ft_printf("type1\n");
        // simple_command = parse_struct_1(token_chain); // cmd1 infile > ....
    else if (is_redir_in(token_chain))
        ft_printf("type2\n");
        // simple_command = parse_struct_2(token_chain); // < infile cmd1 | cmd2 | ...
    return (simple_command);
}