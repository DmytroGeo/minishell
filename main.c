/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:32:39 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/06/27 15:25:04 by dgeorgiy         ###   ########.fr       */
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
// void    print_tokens(t_token *token_chain)
// {
//     t_token *current = token_chain;
//     int i = 0;
//     while (current)
//     {
//         ft_printf("%d \n", i);
//         i++;
//         current = current->next;
//     }
// }   
  
int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    char *prompt = get_prompt();
    char *line;
    int *exit_status = malloc(sizeof(int *));
    t_token *token_chain;
    t_simple_command *simple_command;
	char **env_copy;

	env_copy = copy_envp(envp);
    while ((line = readline(prompt)) != NULL)
    {
        if (*line)
        {
            // if cd is the first word, then we change directory
            // same with exit (apart from exit | ...). If exit is in a pipe process, say < infile cat | exit | wc > out, then it exits the child process but doesn't kill main process.
            // with $? always print exit_code.
            add_history(line);
            token_chain = lexing(line, envp);
			if (token_chain->type == EXPORT)
			{
				t_token *arg = token_chain->next;
				while (arg && arg->type != END_OF_FILE)
				{
					if (is_valid_variable_assignment(arg->value))
						export_variable(&env_copy, arg->value);
					else
						ft_printf("Invalid export format: %s\n", arg->value);
					arg = arg->next;
				}
				// print_env(env_copy);
			}
			else if (token_chain->type == UNSET)
			{
				t_token *arg = token_chain->next;
				while (arg && arg->type != END_OF_FILE)
				{
					unset_variable(&env_copy, arg->value);
					arg = arg->next;
				}
				// print_env(env_copy);
			}
            else
            {
                // expand_variables(&token_chain);
                simple_command = parse(token_chain);
                // evaluate_built_ins(token_chain, exit_status, &prompt);
                // free(&token_chain);
                if (simple_command)
                {
                    *exit_status = execution(ft_array_len(simple_command->commands), simple_command, envp);
                }
                else
                {
                    ft_printf("Program was exited\n");
                }
            }
        }
        free(line);             
    }
    return (0);
}
