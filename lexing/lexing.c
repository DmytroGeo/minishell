/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:59:28 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/04/04 20:09:58 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

// A snippet of an initialisation function from my pipex in the three functions below.
// I recommend you adapt the below code to your lexer/tokenizer when you wantto check if a given string is a command name.
// The expected input for pipex was:
// ./pipex infile "command1 flag1 ..." "command2 flag1 ..." ... "command_n flag1 ..." outfile

// void	init_list(int argc, char **argv, char **envp)
// {
// 	// In this function we have a loop that goes from argv[2] ("command1 flag1 ...")
// 	// to argv[ac - 2] ("command_n flag1 ...") splits each string to get the commangs by themselves without the flags
// 	// and uses access() to check whether we've been given the full path of a command (like "/usr/bin/cat")
// 	// If not then we may have been given the shortended version "cat" and we go to the get_path (next funct on this page).
	
// 	int		i;
// 	char	**array;
// 	char	*path;

// 	i = 2;
// 	while (i < argc - 1)
// 	{
// 		array = ft_split(argv[i], ' ');
// 		if (access(array[0], F_OK | X_OK) == 0)
// 			path = ft_strdup(array[0]);
// 		else
// 			path = get_path(array[0], envp);
// 		if (!path)
// 			perror(array[0]);
// 		i++;
// 	}
// 	// ...
// }

// // Also from my pipex:

// char	*get_path(char *str, char **envp)
// {
// 	// This function ft_splits the string returned from find_path_variable (funct below this one) using ':' as a delimiter,
// 	// Then, if the command name is the short-hand one (like 'cat' instead of '/usr/bin/cat'),
// 	// It takes the each of the arrays we got from the split (like /home/linuxbrew/.linuxbrew/bin),
// 	// sticks cat on the end (/home/linuxbrew/.linuxbrew/bin -> /home/linuxbrew/.linuxbrew/bin/cat) and
// 	// uses the function access() to check that full path (and hence the command) exists. 
// 	// If the user input a valid command and the PATH variable is set on our system, 
// 	// eventually we'll find the proper full path, which is what this function will return.
// 	char	*path_variable;
// 	char	*temp1;
// 	char	*temp2;
// 	char	**arr;
// 	int		i;

// 	i = -1;
// 	path_variable = find_path_variable(envp);
// 	if (!path_variable)
// 		return (NULL);
// 	arr = ft_split(path_variable, ':');
// 	while (arr[++i])
// 	{
// 		temp1 = ft_strjoin(arr[i], "/");
// 		temp2 = ft_strjoin(temp1, str);
// 		free(temp1);
// 		if (access(temp2, F_OK | X_OK) == 0)
// 		{
// 			ft_array_free(arr);
// 			return (temp2);
// 		}
// 		free(temp2);
// 	}
// 	ft_array_free(arr);
// 	return (NULL);
// }

// char	*find_path_variable(char **envp)
// {
// 	// This functions finds the PATH variable from your environment variables:
// 	// PATH=/home/linuxbrew/.linuxbrew/bin:/home/linuxbrew/.linuxbrew/sbin:...
// 	// and returns the string starting at the first slash:
// 	// /home/linuxbrew/.linuxbrew/bin:/home/linuxbrew/.linuxbrew/sbin:...
// 	char	**ptr;
// 	char	*path_variable;

// 	ptr = envp;
// 	while (*ptr)
// 	{
// 		if ((ft_strnstr(*ptr, "PATH", ft_strlen(*ptr)) && **ptr == 'P'))
// 			break ;
// 		ptr++;
// 	}
// 	if (*ptr == NULL)
// 	{
// 		ft_perror("", 'p');
// 		return (NULL);
// 	}
// 	path_variable = *ptr;
// 	path_variable += ft_strlen("PATH=");
// 	return (path_variable);
// }

t_token		**lexing(char *str)
{
	if (!str)
		return (NULL);
	// From what I saw this should have similar logic to printf:
	// While we haven't yet reached '/0', keep iterating through the string.
	// If we encounter an ascii char, go into a function with lots of if statements.
	// keep going through the 'word', char by char till we hit whitespace again.
	// save that word and see if it's a command, symbol or file.
	// create a token node based on the word parsed (see token structure in lexing.h).
	// add to the list and move onto the next char.
	//
	// Some things I noted about whilst thinking about lexing:
	// 1) What token types do we want?
	// Some commands you can find in PATH, like: echo, pwd, env, cat, ls, etc which should be a type.
	// Some functions you can't find in PATH, like: cd, export, unset, exit. These should have their own type.
	// Wildcards like *.c
	// Operators like && and || and brackets ().
	// Single quotes '' and double quotes "".
	// pipes |, 
	// flags like -la
	// redirections < ,>
	// << and >> 
	// forward slashes and path names (relative, absolute, etc, look into this - perhaps use the access() function).
	// Variables like $abc
	// Dollar sign operators like $? for error codes (and others, look into this).
	// Once you got everything above and anything else I am missing from the subject,
	// I think it'd be best to put anything that doesn't already have a type under the type FILENAME,
	// as files can be given any name (also check if there's anything you can't name your file)
	//
	// 2) How should whitespaces be treated? 
	// Most of the time whitespaces aren't important but in the case of single/double quotation marks they are.
	// As such I think there's two solutions:
	// A) Have a token with the WHITESPACE type and just count all whitespaces. The con of this approach is you'll be leaving more work to the parser.
	// B) Find some way (perhaps using a flag when you hit a quotation mark) to discern which whitespaces are important.
	// I recommend A as the lexing is meant to be simple as possible.

	
	return (NULL); // this line is just a placeholder. 
}