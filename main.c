/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:32:39 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/09 17:16:38 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  use CTRL + D to exit the shell
/*
    if CTRL + D is pressed (which sends an EOF — End Of File to *line)
    essentialy setting it to NULL which ends loop and shell terminates
    but prompt needs to be empty for CTRL + D to work (for now) .
    You may need to compile with readline lib "cc read_line.c -lreadline"
    but that may be because im using mbp, the school computers probaly
    have the libraries installed and you dont neet to include the lib.
*/
void    print_tokens(t_token *token_chain)
{
    t_token *current = token_chain;
    int i = 0;
    while (current)
    {
        ft_printf("%d \n", i);
        i++;
        current = current->next;
    }
}
int main(int argc, char **argv, char **envp)
{
    char *line;
    (void)argc;
    (void)argv;
    t_token *token_chain;
    t_simple_command *simple_command;
    while ((line = readline("minishell$ ")) != NULL)
    {
        if (*line)
        {
            add_history(line);
            token_chain = lexing(line, envp);
            simple_command = parse(token_chain);
            // execute(simple_command);
        }
        free(line);
    }
    return 0;
}