/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:22:58 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/06/27 15:48:57 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_print_envp(char **envp)
{
	int	i;

	i = 0;
	ft_printf("\n\n - - - ENVIRONMENT VARIABLES - - - \n\n");
	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
	ft_printf("\n\n");
}

void print_env(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
		ft_printf("%s\n", envp[i++]);
}

int	find_env_index(char **envp, const char *key)
{
	int		i = 0;
	size_t	len = ft_strlen(key);

	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	unset_variable(char ***envp, const char *key)
{
	int		i = 0;
	int		j = 0;
	int		index = find_env_index(*envp, key);
	char	**new_env;

	if (index < 0)
		return;

	while ((*envp)[i])
		i++;
	new_env = malloc(sizeof(char *) * i); // one less

	i = 0;
	while ((*envp)[i])
	{
		if (i == index)
			free((*envp)[i]);
		else
			new_env[j++] = (*envp)[i];
		i++;
	}
	new_env[j] = NULL;
	free(*envp);
	*envp = new_env;
}

void	export_variable(char ***envp, const char *assignment)
{
	char	**new_env;
	char	*key;
	int		i = 0;
	int		index;

	key = ft_substr(assignment, 0, ft_strchr(assignment, '=') - assignment);
	index = find_env_index(*envp, key);
	free(key);

	if (index >= 0)
	{
		free((*envp)[index]);
		(*envp)[index] = ft_strdup(assignment);
	}
	else
	{
		while ((*envp)[i])
			i++;
		new_env = malloc(sizeof(char *) * (i + 2));
		i = 0;
		while ((*envp)[i])
		{
			new_env[i] = (*envp)[i];
			i++;
		}
		new_env[i] = ft_strdup(assignment);
		new_env[i + 1] = NULL;
		free(*envp);
		*envp = new_env;
	}
}

void copy_envp(char ***envp)
{
	int		i;
	char	**copy;

	if (!*envp)
		return ;
	i = 0;
	while ((*envp)[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return ;
	i = 0;
	while ((*envp)[i])
	{
		copy[i] = ft_strdup((*envp)[i]);
		i++;
	}
	copy[i] = NULL;
	*envp = copy;
	return ;
}

int	is_export(t_token *token)
{
	if (!token)
		return (0);

	if (token->type == EXPORT)
		return (1);

	return (0);
}

int	is_valid_variable_name(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_variable_assignment(char *str)
{
	int		i;
	char	*equal_sign;

	if (!str)
		return (0);

	// Find '=' in the string
	equal_sign = ft_strchr(str, '=');
	if (!equal_sign/* || equals == str || *(equals + 1) == '\0'*/)
		return (0); // no '=' → not a variable assignment

	// Check for space around '='
	if (equal_sign == str || equal_sign[-1] == ' ' || equal_sign[1] == ' ')
		return (0); // starts with '=' or has space around it

	// Check the name before '='
	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (&str[i] < equal_sign)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/////////////////////////////////////////////////////////

int is_EOF(t_token *current_token)
{
    return (current_token->type == END_OF_FILE);
}

int is_command(t_token *current_token)
{
    // consider also putting in commands that don't have paths: export, cd, unset,
    if (!is_EOF(current_token))
    {
        if (ft_strncmp(current_token->value, "cd", 3) == 0)
            return(true);
        else if (ft_strncmp(current_token->value, "exit", 5) == 0)
            return(true);
    }
    return (current_token->path != NULL);
}

int is_redir_in(t_token *current_token)
{
    return (current_token->type == REDIR_IN);
}

int is_redir_out(t_token *current_token)
{
    return (current_token->type == REDIR_OUT);
}

int is_file(t_token *current_token)
{
    return (current_token->type == WORD && current_token->path == NULL);
}

int is_pipe(t_token *current_token)
{
    return (current_token->type == PIPE);
}



int is_flag(t_token *current_token)
{
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
        // 2. Infile should be followed by a command or < or EOF.
        else if (is_redir_in(current_token) && is_file(next_token) && !(is_redir_out(next_token->next) || is_command(next_token->next) || is_redir_in(next_token->next) || is_EOF(next_token->next)))
        {
            ft_printf("Parse error: infile should be followed by a command or < or EOF\n");
            return (EXIT_FAILURE);
        }         
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
        current_token = current_token->next;
    }
    return (EXIT_SUCCESS);
}

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
        if (is_redir_out(current_token) && is_file(current_token->next))
        {
            current_token = current_token->next;
            (simple_command->outfiles)[i] = malloc(sizeof(int *));
            *((simple_command->outfiles)[i]) = open(current_token->value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
            i++;        
        }
        else if (is_append(current_token) && is_file(current_token->next))
        {
            current_token = current_token->next;
            (simple_command->outfiles)[i] = malloc(sizeof(int *));
            *((simple_command->outfiles)[i]) = open(current_token->value, O_CREAT | O_APPEND | O_WRONLY, 0644);
            i++;              
        }     
        current_token = current_token->next;
    }
    (simple_command->outfiles)[number_of_outfiles] = NULL;
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
    find_infiles(simple_command, token_chain);
    find_outfiles(simple_command, token_chain);
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
    {
        ft_printf("Parsing returned an error.\n");
        return (NULL);       
    }
    else
        simple_command = create_simple_command(token_chain);   
    return (simple_command); 
}