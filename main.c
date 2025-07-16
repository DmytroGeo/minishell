/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:32:39 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/16 14:21:24 by dgeorgiy         ###   ########.fr       */
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
  
int main(int argc, char **argv, char **envp)
{
    // test yes | head -n 1
    (void)argc;
    (void)argv;
    char *line; // var 1
    int exit_status; // var 2
    t_token *tok_chain; // var 3
    t_main *main; // var 4
    
    exit_status = 0;
    tok_chain = NULL;
    main = malloc(sizeof(t_main));
    if (!main)
        exit (1);
    init_envp_and_prompt(main, envp);
    while ((line = readline(main->prompt)) != NULL)
    {
        if (*line) // if there's something in the line 
        {
            add_history(line);
            lexing(&tok_chain, line);
            print_token_list(tok_chain);
            // expansions(&tok_chain);
            // init_processes(main, tok_chain);
            free_tok_chain(&tok_chain, del_tok_cont);
            // exit_status = execution(main);
        }
        free(line);
    }
    return (0);
}
