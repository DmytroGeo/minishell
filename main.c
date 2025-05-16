/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:32:39 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/16 17:36:41 by dgeorgiy         ###   ########.fr       */
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

char **evaluate(t_simple_command *simple_command)
{
    char    **processed_command = NULL;
    int     number_of_commands = ft_array_len(simple_command->commands);
    int     i = 1;
    processed_command = malloc((number_of_commands + 4) * sizeof(char *)); // number_of_commands + 2 (for infile and outfile) + 1 (standin for executable) + 1 (for NULL termination)
    processed_command[0] = "exec";
    processed_command[1] = ft_strdup(simple_command->infile);
    processed_command[number_of_commands + 2] = ft_strdup(simple_command->outfile);
    processed_command[number_of_commands + 3] = NULL;   
    while (++i < number_of_commands + 2)
        processed_command[i] = ft_strdup((simple_command->commands)[i - 2]);
    return(processed_command);
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
            // int i = 0;
            // if (simple_command)
            // {
            //     ft_printf("infile : %s \n", simple_command->infile);
            //     ft_printf("outfile: %s \n", simple_command->outfile);
            //     int number_of_commands = ft_array_len(simple_command->commands);
            //     ft_printf("number of commands: %d \n", number_of_commands);
            //     while (i < number_of_commands)
            //     {
            //         ft_printf("Command %d is %s \n", i + 1, (simple_command->commands)[i]);
            //         i++;
            //     }               
            // }
            // else
            //     ft_printf("try again \n");
            
            // need to free token_chain
            
            char    **processed_command;
            processed_command = evaluate(simple_command);
            
            // char **temp;
            // temp = processed_command;
            // while (*temp)
            // {
            //     ft_printf("%s \n", *temp);
            //     temp++;
            // }
            
            // need to free simple_command
            
            execution(ft_array_len(processed_command), processed_command, envp);
        }
        free(line);
    }
    return 0;
}