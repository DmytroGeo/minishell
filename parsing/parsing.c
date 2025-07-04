/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:22:58 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/04 11:42:18 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/// find number of commands, outfiles, infiles

int find_number_of_commands(t_token *token_chain) // this needs to be updated. Currently it's overcounting the commands.
{
    int number_of_commands = 0;
    t_token *current_token = token_chain;
    while (!is_EOF(current_token))
    {
        if (is_command(current_token))
        {
            number_of_commands += 1;
            current_token = current_token->next;
            while (is_flag(current_token) || is_file(current_token) || is_command(current_token))
                current_token = current_token->next;         
        }
        current_token = current_token->next;
    }
    return (number_of_commands);
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

int find_number_of_infiles(t_token *token_chain)
{
    int number_of_infiles = 0;
    t_token *current_token = token_chain;
    
    while (!is_EOF(current_token))
    {
        if (is_redir_in(current_token))
            number_of_infiles++;
        current_token = current_token->next;
    }
    return (number_of_infiles);
}

///////////////////////

///// pre-parse to make sure everything is being followed by the correct thing

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
            ft_printf(2, "Parse error: < should be followed by infile\n");
            return (EXIT_FAILURE);
        }
        // 2. Infile should be followed by a command or < or EOF.
        else if (is_redir_in(current_token) && is_file(next_token) && !(is_redir_out(next_token->next) || is_command(next_token->next) || is_redir_in(next_token->next) || is_EOF(next_token->next)))
        {
            ft_printf(2, "Parse error: infile should be followed by a command or < or EOF\n");
            return (EXIT_FAILURE);
        }         
        // 3. Command should be followed by < or << (heredoc) or > or | or a flag or a file (this includes commands) or an EOF
        else if (is_command(current_token) && !(is_heredoc(next_token) || is_redir_in(next_token) || is_flag(next_token) || is_command(next_token) || is_redir_out(next_token) || is_pipe(next_token) || is_file(next_token) || is_EOF(next_token)))
        {
            ft_printf(2, "Parse error: command should be followed by < or << > or | or a flag or a file\n");
            return (EXIT_FAILURE);
        }
        // 4. flags should be followed by more flags or a file or | or > or EOF
        else if (is_flag(current_token) && !(is_file(next_token) || is_redir_out(next_token) || is_pipe(next_token) || is_flag(next_token) || is_EOF(next_token)))
        {
            ft_printf(2, "Parse error: flags should be followed by more flags or a file or | or >");
            return (EXIT_FAILURE);
        }
        // 5. pipe should be followed by command
        else if (is_pipe(current_token) && !is_command(next_token))
        {
            ft_printf(2, "Parse error: pipe should be followed by command\n");
            return (EXIT_FAILURE);           
        }
        // 6. > and >> should be followed by an outfile 
        else if ((is_redir_out(current_token) || is_append(current_token)) && !is_file(next_token))
        {
            ft_printf(2, "Parse error: > or >> should be followed by an outfile\n");
            return (EXIT_FAILURE);         
        }
        // 7. Outfile should be followed by EOF or >. 
        else if ((is_redir_out(current_token) || is_append(current_token)) && is_file(next_token) && !(is_EOF(next_token->next) || is_redir_out(current_token)))
        {
            ft_printf(2, "Parse error: outfile should be followed by EOF\n");
            return (EXIT_FAILURE);
        }
        // 8. << should be followed by limiter (which can be any string)
        else if (is_heredoc(current_token) && is_EOF(next_token))
        {
            ft_printf(2, "bash: syntax error near unexpected token `newline'\n");
            return (EXIT_FAILURE);
        }
        current_token = current_token->next;
    }
    return (EXIT_SUCCESS);
}

/////////////

////////// initialise infile and outfile fds:
///////// we're counting heredoc as an infile.

void    find_infiles(t_simple_command *simple_command, t_token *token_chain)
{
    t_token *current_token = token_chain;
    int number_of_infiles = find_number_of_infiles(token_chain);
    int i = 0;
    simple_command->infiles = malloc((number_of_infiles + 1) * sizeof(int *));
    if (number_of_infiles == 0)
    {
        simple_command->infiles = NULL;
        return ;       
    }
    while (!is_EOF(current_token))
    {
        if (is_redir_in(current_token) && is_file(current_token->next))
        {
            current_token = current_token->next;
            if (access(current_token->value, F_OK) == 0)
                proc_call(access(current_token->value, R_OK), 'a');
            else
                perror(NULL);
            (simple_command->infiles)[i] = malloc(sizeof(int *));
            *((simple_command->infiles)[i]) = open(current_token->value, O_RDONLY);
            i++;
        }
        else if (is_heredoc(current_token))
        ///////////////////////
        // dgeorgiy@c1r4s5:~/42_cursus_personal/minishell$ <<
        // bash: syntax error near unexpected token `newline'
        // dgeorgiy@c1r4s5:~/42_cursus_personal/minishell$ cat <<hello
        // > hii
        // > $USER
        // > hello
        // hii
        // dgeorgiy
        // dgeorgiy@c1r4s5:~/42_cursus_personal/minishell$ cat << 'hello'
        // > hiiui
        // > $USER
        // > 'hello'
        // > hello
        // hiiui
        // $USER
        // 'hello'
        // dgeorgiy@c1r4s5:~/42_cursus_personal/minishell$ cat << "hello"
        // > hii
        // > $USER
        // > hello
        // hii
        // $USER
        // dgeorgiy@c1r4s5:~/42_cursus_personal/minishell$ cat << hel"l"o
        // > hi
        // > $USER
        // > hel"l"o
        // > hello
        // hi
        // $USER
        // hel"l"o
        // dgeorgiy@c1r4s5:~/42_cursus_personal/minishell$
        ///////////////////////////
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
                    *((simple_command->infiles)[i]) = fd[0];
                    close(fd[1]);               
                    break;
                }
                else
                    write(fd[1], line_read, ft_strlen(line_read));
            }
            return; 
        }
        current_token = current_token->next;
    }
    (simple_command->infiles)[number_of_infiles] = NULL;
    return;
}

void    find_outfiles(t_simple_command *simple_command, t_token *token_chain)
{
    t_token *current_token = token_chain;
    t_token *previous_token;
    int number_of_outfiles = find_number_of_outfiles(token_chain);
    int i = 0;
    simple_command->outfiles = malloc((number_of_outfiles + 1) * sizeof(int *));
    if (number_of_outfiles == 0)
    {
        simple_command->outfiles = NULL;
        return ;       
    }
    while (!is_EOF(current_token))
    {
        if ((is_redir_out(current_token) || is_append(current_token)) && is_file(current_token->next))
        {
            previous_token = current_token;
            current_token = current_token->next;
            if (access(current_token->value, F_OK) == 0)
            {
                if (access(current_token->value, W_OK) != 0)
                {
                    perror("Access denied");
                    return;                    
                }
            }
            else
            {
                (simple_command->outfiles)[i] = malloc(sizeof(int *));
                if (is_redir_out(previous_token))
                    *((simple_command->outfiles)[i]) = open(current_token->value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
                else if (is_append(previous_token))
                    *((simple_command->outfiles)[i]) = open(current_token->value, O_CREAT | O_APPEND | O_WRONLY, 0644);                
                i++; 
            }
        }   
        current_token = current_token->next;
    }
    (simple_command->outfiles)[number_of_outfiles] = NULL;
    return;   
}

///////////////////

///////////// initialialise commands
 
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
    char *path;
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

t_simple_command *create_simple_command(t_token *token_chain, char **envp)
{
    t_simple_command *simple_command = malloc(sizeof(t_simple_command));
    int number_of_commands = find_number_of_commands(token_chain);
    find_infiles(simple_command, token_chain);
    find_outfiles(simple_command, token_chain);
    simple_command->commands = malloc((number_of_commands + 1) * sizeof(char *));
    find_commands_and_arguments(&simple_command, token_chain);
    return(simple_command);
}

t_simple_command  *parse(t_token *token_chain, char **envp)
{
    t_simple_command  *simple_command = NULL;
    if (!token_chain)
    {
        ft_printf(2, "Something wrong with token chain\n");
        return (NULL);        
    }
    if (pre_parse(token_chain) == EXIT_FAILURE)
    {
        ft_printf(2, "Parsing returned an error.\n");
        return (NULL);       
    }
    else
        simple_command = create_simple_command(token_chain, envp);
    return (simple_command); 
}