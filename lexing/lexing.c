/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:59:28 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/16 17:49:29 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include <stdio.h> // remove later
#include <string.h> // remove later

int is_surrounded_by(char *str, char quote)
{
	size_t len;
	int result;

	if (!str || str[0] != quote)
		return (0); // doesn't start with quote

	len = ft_strlen(str);
	if (len < 2)
		return (0); // too short to have both quotes

	if (str[len - 1] == quote)
		result = 1;
	else
		result = 0;

	return (result);
}

char *strip_quotes(char *str)
{
	size_t	len;
	char	*clean;

	if (!str)
		return (NULL);

	len = ft_strlen(str);
	if (len < 2)
		return (ft_strdup(str)); // nothing to strip

	// remove the first and last character (the quotes)
	clean = ft_substr(str, 1, len - 2);
	if (!clean)
		return (NULL); // memory allocation failed

	return (clean);
}

void    array_free(char **arr)
{
    int i = 0;    if (!arr)
        return;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}

void    print_token_list(t_token *head)
{
    int i;
    const char *token_type_names[] =
    {
    "WORD",
    "PIPE",
    "REDIR_IN",
    "REDIR_OUT",
    "APPEND",
    "HEREDOC",
	"END_OF_FILE",
	"FLAG",
	"SINGLE_QUOTED_STRING",
	"DOUBLE_QUOTED_STRING",
	"COMMAND",
	"VARIABLE",
	"AND_IF",
	"OR_IF",
	"PAREN_LEFT",
	"PAREN_RIGHT"
    };    
	i = 1;
    printf("\n< < < < Token List > > > >\n\n");
    while (head)
    {
        printf("Node : %d\n", i);
        printf("Type : %s\nValue : %s\nPath : %s\n\n", token_type_names[head->type], head->value, head->path);
        head = (head->next);
        i++;
    }
    printf("\n");
}

t_token_type identify_type(char *token, t_op *operators) //include? change strcmp to ft_strcmp
{
	int i;

	i = 0;
	if (strcmp(token, "&&") == 0)
		return (AND_IF);
	if (strcmp(token, "||") == 0)
		return (OR_IF);
	if (strcmp(token, "(") == 0)
		return (PAREN_LEFT);
	if (strcmp(token, ")") == 0)
		return (PAREN_RIGHT);
	if (token[0] == '$')
		return (VARIABLE);
	if (token[0] == '-')
		return (FLAG);
    while (operators[i].symbol)
    {
        if (strcmp(token, operators[i].symbol) == 0)
            return (operators[i].type);
        i++;
    }
    return (WORD);
}

void    print_raw_tokens(char **raw_tokens) //include?
{
    int i;    i = 0;
    printf("\n\n< < < < Raw Tokens > > > >\n\n"); // replace
    while (raw_tokens[i])
            printf("%s\n", raw_tokens[i++]); // replace
    printf("\n");  // replace
}

 char    *find_path_variable(char **envp)
 {
	char    **ptr;
	char    *path_variable;
 	ptr = envp;
     while (*ptr)
     {
         if ((ft_strnstr(*ptr, "PATH", ft_strlen(*ptr)) && **ptr == 'P'))
             break ;
         ptr++;
     }
     if (*ptr == NULL)
         return (NULL);
     path_variable = *ptr;
     path_variable += ft_strlen("PATH=");
     return (path_variable);
 }

 char    *get_path(char *str, char **envp)
 {
     char    *path_variable;
     char    *temp1;
     char    *temp2;
     char    **arr;
     int     i;
 	i = -1;
     path_variable = find_path_variable(envp);
     if (!path_variable)
         return (NULL);
     arr = ft_split(path_variable, ':');
     while (arr[++i])
     {
         temp1 = ft_strjoin(arr[i], "/");
         temp2 = ft_strjoin(temp1, str);
         free(temp1);
         if (access(temp2, F_OK | X_OK) == 0)
         {
             array_free(arr);
             return (temp2);
         }
         free(temp2);
     }
     array_free(arr);
     return (NULL);
 }

t_token     *lexing(char *line, char **envp)
{
    char    **raw_tokens;
    t_op    operators[7];
    t_token *head = NULL;
    t_token *last;
    t_token *new_node;
	operators[0] = (t_op){"|", PIPE};
    operators[1] = (t_op){">", REDIR_OUT};
    operators[2] = (t_op){"<", REDIR_IN};
    operators[3] = (t_op){">>", APPEND};
    operators[4] = (t_op){"<<", HEREDOC};
    operators[5] = (t_op){NULL, WORD};
	operators[6] = (t_op){NULL, END_OF_FILE};
    if (!line)
        return (NULL);
    raw_tokens = split_line(line);
    print_raw_tokens(raw_tokens);
    while (*raw_tokens)
    {
        new_node = malloc(sizeof(t_token));
        if (!new_node)
            return (NULL);
        if (is_surrounded_by(*raw_tokens, '\''))
		{
			new_node->value = strip_quotes(*raw_tokens);
			new_node->type = SINGLE_QUOTED_STRING;
		}
		else if (is_surrounded_by(*raw_tokens, '"'))
		{
			new_node->value = strip_quotes(*raw_tokens);
			new_node->type = DOUBLE_QUOTED_STRING;
		}
		else
		{
			new_node->value = ft_strdup(*raw_tokens);
			new_node->type = identify_type(*raw_tokens, operators);
		}
        new_node->next = NULL;
        new_node->path = NULL;
        // if (new_node->type == WORD && (!last || last->type == PIPE))
        if (new_node->type == WORD)
        {
            if (access(new_node->value, F_OK | X_OK) == 0)
                new_node->path = ft_strdup(new_node->value);
            else
                new_node->path = get_path(new_node->value, envp);
        }
        if (!head)
            head = new_node;
        else
            last->next = new_node;
        last = new_node;
        raw_tokens++;
    }
    new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->value = NULL;
	new_node->type = END_OF_FILE;
	new_node->next = NULL;
	new_node->path = NULL;
	last->next = new_node;
	last = new_node;
    print_token_list(head);
    return (head);
}
