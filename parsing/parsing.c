/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:22:58 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/06/26 11:03:10 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int is_command(t_token *current_token)
{
    if (!current_token)
        return (EXIT_FAILURE);
    // consider also putting in commands that don't have paths: export, cd, unset, 
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

int is_append(t_token *current_token)
{
    if (!current_token)
        return (EXIT_FAILURE);
    return (current_token->type == APPEND);
}

int is_heredoc(t_token *current_token)
{
    if (!current_token)
        return (EXIT_FAILURE);
    return (current_token->type == HEREDOC);
}

int find_number_of_commands(t_token *token_chain)
{
    int number_of_commands = 0;
    t_token *current_token = token_chain;
    while (!is_EOF(current_token))
    {
        if (is_command(current_token))
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
        // 2. Infile should be followed by command.
        // else if (is_redir_in(current_token) && is_file(next_token) && !is_command(next_token->next))
        // {
        //     ft_printf("Parse error: infile should be followed by a command\n");
        //     return (EXIT_FAILURE);
        // }         
        // 3. Command should be followed by < or << (heredoc) or > or | or a flag or a file (this includes commands) or an EOF
        else if (is_command(current_token) && !(is_heredoc(next_token) || is_redir_in(next_token) || is_flag(next_token) || is_command(next_token) || is_redir_out(next_token) || is_pipe(next_token) || is_file(next_token) || is_EOF(next_token)))
        {
            ft_printf("Parse error: command should be followed by < or << > or | or a flag or a file\n");
            return (EXIT_FAILURE);
        }
        // 4. flags should be followed by more flags or | or > or EOF
        else if (is_flag(current_token) && !(is_redir_out(next_token) || is_pipe(next_token) || is_flag(next_token) || is_EOF(next_token)))
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
        // 6. > and >> should be followed by an outfile 
        else if ((is_redir_out(current_token) || is_append(current_token)) && !is_file(next_token))
        {
            ft_printf("Parse error: > or >> should be followed by an outfile\n");
            return (EXIT_FAILURE);         
        }
        // 7. Outfile should be followed by EOF or >. 
        else if ((is_redir_out(current_token) || is_append(current_token)) && is_file(next_token) && !(is_EOF(next_token->next) || is_redir_out(current_token)))
        {
            ft_printf("Parse error: outfile should be followed by EOF\n");
            return (EXIT_FAILURE);
        }
        // 8. << should be followed by limiter (which can be any string)
        else if (is_heredoc(current_token) && is_EOF(next_token))
        {
            ft_printf("bash: syntax error near unexpected token `newline'\n");
            return (EXIT_FAILURE);
        }
        // else if (!(is_redir_in(current_token) || is_file(current_token) || is_command(current_token) || is_pipe(current_token) || is_redir_out(current_token) || is_flag(current_token)))
        // {
        //     ft_printf("I haven't yet written a test for this.\n");
        //     return (EXIT_FAILURE);              
        // }
        current_token = current_token->next;
    }
    return (EXIT_SUCCESS);
}

void    find_infile(t_simple_command *simple_command, t_token *token_chain)
{
    t_token *current_token = token_chain;
    simple_command->infile = malloc(sizeof(int *));
    // simple_command->heredoc_flag = malloc(sizeof(int *));
    // *(simple_command->heredoc_flag) = 0;
    while (!is_redir_in(current_token) && !is_heredoc(current_token) && !is_EOF(current_token))
        current_token = current_token->next;
    if (is_heredoc(current_token))
    {
        char *limiter = current_token->next->value;
        int *fd = malloc(2 * sizeof(int));
        pipe(fd);
        while (1)
        {
            write(1, "> ", 2);
            char *line_read = get_next_line(0);
            if (ft_strncmp(line_read, limiter, ft_strlen(limiter)) == 0 && ft_strncmp(line_read, limiter, ft_strlen(line_read) - 1) == 0)
            {
                *(simple_command->infile) = fd[0];
                close(fd[1]);               
                break;               
            }
            else
                write(fd[1], line_read, ft_strlen(line_read));
        }
        return; 
    }
    if (is_redir_in(current_token) && is_file(current_token->next))
    {
        current_token = current_token->next;
        if (access(current_token->value, F_OK) == 0)
			proc_call(access(current_token->value, R_OK), 'a');
        else
            perror(NULL);
        *(simple_command->infile) = open(current_token->value, O_RDONLY);
        return;      
    }
    simple_command->infile = NULL;
    return;   
}

int find_number_of_outfiles(t_token *token_chain)
{
    int number_of_outfiles = 0;
    t_token *current_token = token_chain;
    
    while (!is_EOF(current_token))
    {
        if (is_redir_out(current_token))
            number_of_outfiles++;
        current_token = current_token->next;
    }
    return (number_of_outfiles);
}

void    find_outfiles(t_simple_command *simple_command, t_token *token_chain)
{
    t_token *current_token = token_chain;
    int number_of_outfiles = find_number_of_outfiles(token_chain);
    int i = 0;
    simple_command->outfile = malloc((number_of_outfiles + 1) * sizeof(int *));
    if (number_of_outfiles == 0)
    {
        simple_command->outfile = NULL;
        return ;       
    }
    while (!is_EOF(current_token))
    {
        if (is_redir_out(current_token) && is_file(current_token->next))
        {
            current_token = current_token->next;
            (simple_command->outfile)[i] = malloc(sizeof(int *));
            *((simple_command->outfile)[i]) = open(current_token->value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
            i++;        
        }
        else if (is_append(current_token) && is_file(current_token->next))
        {
            current_token = current_token->next;
            (simple_command->outfile)[i] = malloc(sizeof(int *));
            *((simple_command->outfile)[i]) = open(current_token->value, O_CREAT | O_APPEND | O_WRONLY, 0644);
            i++;              
        }     
        current_token = current_token->next;
    }
    (simple_command->outfile)[number_of_outfiles] = NULL;
    return;   
}

 
void    collect_arguments(t_token **current_token, t_simple_command **simple_command, int counter)
{
    char *temp = NULL;
    while (is_flag(*current_token) || is_file(*current_token) || is_command(*current_token))
    {
        temp = ft_strjoin(((*simple_command)->commands)[counter], " ");
        free(((*simple_command)->commands)[counter]);
        ((*simple_command)->commands)[counter] = temp;
        temp = ft_strjoin(((*simple_command)->commands)[counter], (*current_token)->value);
        free(((*simple_command)->commands)[counter]);
        ((*simple_command)->commands)[counter] = temp;
        (*current_token) = (*current_token)->next;               
    }   
}

void    find_commands_and_arguments(t_simple_command **simple_command, t_token *token_chain)
{
    t_token *current_token = token_chain;
    
    int counter = 0;
    while (!is_EOF(current_token))
    {
        if (is_command(current_token))
        {
            ((*simple_command)->commands)[counter] = ft_strdup(current_token->value);
            current_token = current_token->next;
            if (is_flag(current_token) || is_file(current_token) || is_command(current_token))
                collect_arguments(&current_token, simple_command, counter);
            counter++;          
        }
        else
            current_token = current_token->next;
    }
    ((*simple_command)->commands)[counter] = NULL;
    return ;
}

t_simple_command *create_simple_command(t_token *token_chain)
{
    t_simple_command *simple_command = malloc(sizeof(t_simple_command));
    int number_of_commands = find_number_of_commands(token_chain);
    find_infile(simple_command, token_chain);
    find_outfiles(simple_command, token_chain);
// /////////
//     int **temp = simple_command->outfile;
//     while (*temp)
//     {
//         ft_printf("%d\n", *temp);
//         temp++;
//     }
// /////////
    simple_command->commands = malloc((number_of_commands + 1) * sizeof(char *));
    find_commands_and_arguments(&simple_command, token_chain);
    return(simple_command);
}

t_simple_command  *parse(t_token *token_chain)
{
    t_simple_command  *simple_command = NULL;
    if (!token_chain)
    {
        ft_printf("Something wrong with token chain\n");
        return (NULL);        
    }
    if (pre_parse(token_chain) == EXIT_FAILURE)
        ft_printf("Parsing returned an error.\n");
    else
        simple_command = create_simple_command(token_chain);   
    return (simple_command); 
}