/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:37:13 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/11 15:06:48 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

char    *find_variable_in_envp(char **envp, char *variable)
{
    char    **ptr;
    char    *found_variable;
    char    *variable_with_equal_sign;

    ptr = envp;
    variable_with_equal_sign = ft_strjoin(variable, "=");
    if (!variable_with_equal_sign)
        return (NULL);
    while (*ptr)
    {
        if ((ft_strncmp(*ptr, variable_with_equal_sign, ft_strlen(variable_with_equal_sign))) == 0)
            break ;
        ptr++;
    }
    if (*ptr == NULL)
    {
        ft_perror("", 'p');
        return (NULL);
    }
    found_variable = *ptr;
    found_variable += ft_strlen(variable_with_equal_sign);
    free(variable_with_equal_sign);
    return (found_variable);
}

char    *get_path(char *str, char **envp)
{
    char    *path_variable;
    char    *temp1;
    char    *temp2;
    char    **arr;
    int     i;

	i = -1;
    path_variable = find_variable_in_envp(envp, "PATH");
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
            ft_array_free(arr, ft_array_len(arr));
            return (temp2);
        }
        free(temp2);
    }
    ft_array_free(arr, ft_array_len(arr));
    return (NULL);
}

t_token_type identify_type(char *token, t_op *operators) //include? change strcmp to ft_strcmp
{
    int i;
	int comp1;
	int comp2;
	size_t len1;
	size_t len2;

    i = 0;
    while (operators[i].symbol)
    {
		len1 = ft_strlen(token) + 1;
		len2 = ft_strlen(operators[i].symbol) + 1;
		comp1 = ft_strncmp(token, operators[i].symbol, len1);
		comp2 = ft_strncmp(token, operators[i].symbol, len2);
        if (comp1 == 0 &&  comp2 == 0)
            return (operators[i].type);
        i++;
    }
    return (word);
}

void    print_token_list(t_token *head)
{
    int i;
    const char *token_type_names[] =
    {
    "word",
    "_pipe",
    "redir_in",
    "redir_out",
    "append",
    "heredoc",
    "end_of_file",
    };
    i = 1;
    printf("\n< < < < Token List > > > >\n\n");
    while (head)
    {
        printf("Node : %d\n", i);
        printf("Type : %s\nValue : %s\n\n", token_type_names[((t_token_content *)(head->content))->type], ((t_token_content *)(head->content))->value);
        head = (head->next);
        i++;
    }
    printf("\n");
}

void    print_raw_tokens(char **raw_tokens) //include?
{
    int i;
    i = 0;
    printf("\n\n< < < < Raw Tokens > > > >\n\n"); // replace
    while (raw_tokens[i])
            printf("%s\n", raw_tokens[i++]); // replace
    printf("\n");  // replace
}

