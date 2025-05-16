/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:22:58 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/16 13:27:08 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int is_command(t_token *current_token)
{
    if (!current_token)
        return (EXIT_FAILURE);
    return (current_token->path != NULL);
}

int is_redir_in(t_token *current_token)
{
    if (!current_token)
        return (EXIT_FAILURE);
    return (current_token->type == REDIR_IN);
}

int is_redir_out(t_token *current_token)
{
    if (!current_token)
        return (EXIT_FAILURE);
    return (current_token->type == REDIR_OUT);
}

int is_file(t_token *current_token)
{
    if (!current_token)
        return (EXIT_FAILURE);
    return (current_token->type == WORD && current_token->path == NULL);
}

int is_pipe(t_token *current_token)
{
    if (!current_token)
        return (EXIT_FAILURE);
    return (current_token->type == PIPE);
}

int is_EOF(t_token *current_token)
{
    if (!current_token)
        return (EXIT_FAILURE);
    return (current_token->type == END_OF_FILE);
}

int is_flag(t_token *current_token)
{
    if (!current_token)
        return (EXIT_FAILURE);
    return (current_token->type == FLAG);   
}

int find_number_of_commands(t_token *token_chain)
{
    int number_of_commands = 0;
    t_token *current_token = token_chain;
    while (is_EOF(current_token) == EXIT_FAILURE)
    {
        if (is_command(current_token) == EXIT_SUCCESS)
            number_of_commands += 1;
        current_token = current_token->next;
    }
    return (number_of_commands);
}

int pre_parse(t_token *token_chain)
{
    t_token *current_token = token_chain;
    t_token *next_token;
    while (!is_EOF(current_token))
    {
        next_token = current_token->next;
        // parse struct:
        // 1. < (REDIR_IN) should be followed by infile
        if (is_redir_in(current_token) && !is_file(next_token))
        {
            ft_printf("Parse error: < should be followed by infile\n");
            return (EXIT_FAILURE);
        }
        // 2. Infile should be followed by command. Outfile should be followed by EOF. 
        else if (is_file(current_token) && !(is_EOF(next_token) || is_command(next_token)))
        {
            ft_printf("Parse error: file should be followed by EOF or command\n");
            return (EXIT_FAILURE);
        }
        // 3. command should be followed by > or | or a flag
        else if (is_command(current_token) && !(is_flag(next_token) || is_redir_out(next_token) || is_pipe(next_token)))
        {
            ft_printf("Parse error: command should be followed by > or | or a flag\n");
            return (EXIT_FAILURE);
        }
        // 4. flags should be followed by more flags or | or >
        else if (is_flag(current_token) && !(is_redir_out(next_token) || is_pipe(next_token) || is_flag(next_token)))
        {
            ft_printf("Parse error: flags should be followed by more flags or | or >");
            return (EXIT_FAILURE);
        }
        // 5. pipe should be followed by command
        else if (is_pipe(current_token) && !is_command(next_token))
        {
            ft_printf("Parse error: pipe should be followed by command\n");
            return (EXIT_FAILURE);           
        }
        // 6. > should be followed by an outfile 
        else if (is_redir_out(current_token) && !is_file(next_token))
        {
            ft_printf("Parse error: > should be followed by an outfile\n");
            return (EXIT_FAILURE);         
        }
        else if (!(is_redir_in(current_token) || is_file(current_token) || is_command(current_token) || is_pipe(current_token) || is_redir_out(current_token) || is_flag(current_token)))
        {
            ft_printf("I haven't yet written a test for this.\n");
            return (EXIT_FAILURE);              
        }
        current_token = current_token->next;
    }
    return (EXIT_SUCCESS);
}

void    find_infile_and_outfile(t_simple_command **simple_command, t_token *token_chain)
{
    int infile_found = 0;
    t_token *current_token = token_chain;
    // look for infile
    while (is_file(current_token) == EXIT_FAILURE && is_EOF(current_token) == EXIT_FAILURE)
        current_token = current_token->next;
    if (is_file(current_token) == EXIT_SUCCESS)
    {
        (*simple_command)->infile = ft_strdup(current_token->value);
        infile_found = 1;  
        current_token = current_token->next;             
    }
    else
    {
        ft_printf("infile not found");
        return;
    }
    // look for outfile:
    while (is_file(current_token) == EXIT_FAILURE && is_EOF(current_token) == EXIT_FAILURE)
        current_token = current_token->next;
    if (is_file(current_token) == EXIT_SUCCESS && infile_found == 1)
        (*simple_command)->outfile = ft_strdup(current_token->value);              
    else
        ft_printf("outfile not found");
    return;    
}  

void    find_commands_and_flags(t_simple_command **simple_command, t_token *token_chain)
{
    // int number_of_commands = find_number_of_commands(token_chain);
    t_token *current_token = token_chain;
    char *temp = NULL;
    
    int counter = 0;
    while (is_EOF(current_token) == EXIT_FAILURE)
    {
        if (is_command(current_token) == EXIT_SUCCESS)
        {
            ((*simple_command)->commands)[counter] = ft_strdup(current_token->value);
            current_token = current_token->next;
            while (is_flag(current_token) == EXIT_SUCCESS)
            {
                temp = ft_strjoin(((*simple_command)->commands)[counter], " ");
                free(((*simple_command)->commands)[counter]);
                ((*simple_command)->commands)[counter] = temp;
                temp = ft_strjoin(((*simple_command)->commands)[counter], current_token->value);
                free(((*simple_command)->commands)[counter]);
                ((*simple_command)->commands)[counter] = temp;
                current_token = current_token->next;               
            }
            counter++;          
        }
        else
            current_token = current_token->next;
    }
    
}

t_simple_command *create_simple_command(t_token *token_chain)
{
    t_simple_command *simple_command = malloc(sizeof(t_simple_command));
    int number_of_commands = find_number_of_commands(token_chain);
    simple_command->infile = malloc(sizeof(char *));
    simple_command->infile = NULL;
    simple_command->outfile = malloc(sizeof(char *));
    simple_command->outfile = NULL;
    find_infile_and_outfile(&simple_command, token_chain);
    simple_command->commands = malloc(number_of_commands * sizeof(char *));
    find_commands_and_flags(&simple_command, token_chain);
    return(simple_command);   
}

t_simple_command    *parse_struct_2(t_token *token_chain)
{
    t_simple_command *simple_command = NULL;

    if (!pre_parse(token_chain))
        ft_printf("Parsing returned an error.\n");
    else
    {
        ft_printf("Parsing is fine.\n");     
        simple_command = create_simple_command(token_chain);
    }
    return (simple_command);

}

// t_simple_command    *parse_struct_1(t_token *token_chain)
// {
//     // cmd1 infile > ....
//     t_simple_command *simple_command = malloc(sizeof(simple_command));
//     t_token *current_token = token_chain;
//     t_token *next_token = current_token->next;
//     t_list *commands = NULL;
//     // the first command of the simple command is command.
//     // the infile is the second thing.
//     // go through the token string - If we find a pipe we should expect a command after it.
//     // if we find a redir_out we should see an outfile after it.
//     // error should free.
// }

t_simple_command  *parse(t_token *token_chain)
{
    t_simple_command  *simple_command = NULL;
    if (!token_chain)
    {
        ft_printf("Something wrong with token chain\n");
        return (NULL);        
    }
    if (is_redir_in(token_chain))
    {
        // < infile cmd1 | cmd2 | ... | cmdn > outfile
        ft_printf("type2\n");
        simple_command = parse_struct_2(token_chain);     
    }
    else
    {
        ft_printf("Cannot parse this structure\n");
    }
    // else if (is_command(token_chain))
    //     ft_printf("type1\n");
        // simple_command = parse_struct_1(token_chain); // cmd1 infile > ....
    

    return (simple_command); // returns NULL is command is not of the type we want.
}