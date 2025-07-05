/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:32:39 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/05 15:23:03 by dgeorgiy         ###   ########.fr       */
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
    (void)argc;
    (void)argv;
    char *prompt = get_prompt();
    char *line;
    int exit_status;
    t_token *token_chain;
    t_simple_command *simple_command;
	copy_envp(&envp);
    exit_status = 0;
    simple_command = NULL;
    while ((line = readline(prompt)) != NULL)
    {
        if (*line)
        {
            add_history(line);
            token_chain = lexing(line, envp);
            if (!token_chain)
            {
                ft_array_free(envp, ft_array_len(envp));
            }
            // do_all_expansions(&token_chain, exit_status, envp); /* make sure to expand $? into the last error code. Also ~ expands to home*/
            simple_command = init_exec_struct(prompt, envp);
            if (simple_command)
            {
                init_exec_struct_2(simple_command, token_chain);
                if (simple_command && ft_array_len(simple_command->commands) > 0)
                {
                    exit_status = execution(simple_command);
                }
                else
                {
                    ft_printf(2, "Program was exited\n");
                }                
            }

        }
        free(line);             
    }
    return (0);
}
