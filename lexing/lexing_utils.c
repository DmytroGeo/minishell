/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:37:13 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/03 11:14:58 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

char	*find_path_variable(char **envp)
{
	char	**ptr;
	char	*path_variable;

	ptr = envp;
	while (*ptr)
	{
		if ((ft_strncmp(*ptr, "PATH=", 5)) == 0)
			break ;
		ptr++;
	}
	if (*ptr == NULL)
	{
		ft_perror("", 'p');
		return (NULL);
	}
	path_variable = *ptr;
	path_variable += ft_strlen("PATH=");
	return (path_variable);
}

char	*find_home_variable(char **envp)
{
	char	**ptr;
	char	*home_variable;

	ptr = envp;
	while (*ptr)
	{
		if ((ft_strncmp(*ptr, "HOME=", 5)) == 0)
			break ;
		ptr++;
	}
	if (*ptr == NULL)
	{
		ft_perror("", 'p');
		return (NULL);
	}
	home_variable = *ptr;
	home_variable += ft_strlen("HOME=");
	return (home_variable);
}

char	*get_path(char *str, char **envp)
{
	char	*path_variable;
	char	*temp1;
	char	*temp2;
	char	**arr;
	int		i;

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

	i = 0;
	if (ft_strncmp(token, "&&", 3) == 0)
		return (AND_IF);
	if (ft_strncmp(token, "||", 3) == 0)
		return (OR_IF);
	if (ft_strncmp(token, "(", 2) == 0)
		return (PAREN_LEFT);
	if (ft_strncmp(token, ")", 2) == 0)
		return (PAREN_RIGHT);
	if (token[0] == '$')
		return (VARIABLE);
	if (token[0] == '-')
		return (FLAG);	
	// if (ft_strncmp(token, "cd", 3) == 0)
	// 	return (CD);
	// if (ft_strncmp(token, "export", 7) == 0)
	// 	return (EXPORT);
	// if (ft_strncmp(token, "unset", 6) == 0)
	// 	return (UNSET);
	// if (ft_strncmp(token, "exit", 5) == 0)
	// 	return (EXIT);
	while (operators[i].symbol)
	{
		if (ft_strncmp(token, operators[i].symbol, ft_strlen(token) + 1) == 0 && ft_strncmp(token, operators[i].symbol, ft_strlen(operators[i].symbol) + 1) == 0)
			return (operators[i].type);
		i++;
	}
	return (WORD);
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
	"PAREN_RIGHT",
	"CD",
	// "EXPORT",
	// "UNSET",
	// "EXIT"
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

void    print_raw_tokens(char **raw_tokens) //include?
{
	int i;    i = 0;
	printf("\n\n< < < < Raw Tokens > > > >\n\n"); // replace
	while (raw_tokens[i])
			printf("%s\n", raw_tokens[i++]); // replace
	printf("\n");  // replace
}