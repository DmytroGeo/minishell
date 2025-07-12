/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:32:39 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/12 10:22:14 by dgeorgiy         ###   ########.fr       */
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
    t_token *token_chain; // var 3
    t_big_struct *big_struct; // var 4
    
    big_struct = malloc(sizeof(t_big_struct));
    if (!big_struct)
        exit (1);
    init_envp_and_prompt(big_struct, envp);
    while ((line = readline(big_struct->prompt)) != NULL)
    {
        if (*line) // if there's something in the line 
        {
            add_history(line);
            token_chain = lexing(line, big_struct->envp);
            // init_processes(big_struct, token_chain);
            // // free token chain
            // exit_status = execution(big_struct);
        }
        free(line);             
    }
    return (0);
}
