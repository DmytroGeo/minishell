/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:32:39 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/06/26 15:38:00 by dgeorgiy         ###   ########.fr       */
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

// char **evaluate(t_simple_command *simple_command)
// {
//     char    **processed_command = NULL;
//     int     number_of_commands = ft_array_len(simple_command->commands);
//     int     i = 1;
//     processed_command = malloc((number_of_commands + 4) * sizeof(char *)); // number_of_commands + 2 (for infile and outfile) + 1 (standin for executable) + 1 (for NULL termination)
//     processed_command[0] = "exec";
//     processed_command[1] = ft_strdup(simple_command->infile);
//     processed_command[number_of_commands + 2] = ft_strdup(simple_command->outfile);
//     processed_command[number_of_commands + 3] = NULL;   
//     while (++i < number_of_commands + 2)
//         processed_command[i] = ft_strdup((simple_command->commands)[i - 2]);
//     return(processed_command);
// }

char	*get_cwd(void)
{
	char	buffer[PATH_MAX];
	char	*str;
	str = getcwd(buffer, PATH_MAX);
	return (str);
}

char *get_prompt(void)
{
    char *cwd = get_cwd();
    char *temp = ft_strjoin("minishell:", cwd);
    char *prompt = ft_strjoin(temp, "$ ");
    free(temp);
    return(prompt);
}

void    change_directory(t_token *token_chain, char **prompt)
{
    if (chdir(token_chain->next->value) != 0)
    {
        ft_printf("Directory doesn't exist \n");
        return ;        
    }
    *prompt = get_prompt();
    return;         
}   
  
int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    char *prompt = get_prompt();
    char *line;
    int *exit_status = malloc(sizeof(int *));
    t_token *token_chain;
    t_simple_command *simple_command;
    while ((line = readline(prompt)) != NULL)
    {
        if (*line)
        {
            add_history(line);
            token_chain = lexing(line, envp);
            if (ft_strncmp(token_chain->value, "cd", 3) == 0 && !is_EOF(token_chain->next)) // this doesn't work for smth like cd | > outfile
                change_directory(token_chain, &prompt);
            else if (ft_strncmp(token_chain->value, "$?", 3) == 0)
                ft_printf("%d\n", *exit_status);
            else
            {
                simple_command = parse(token_chain);
                if (simple_command)
                {
                    int number_of_commands = ft_array_len(simple_command->commands);
                    *exit_status = execution(number_of_commands, simple_command, envp);
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
