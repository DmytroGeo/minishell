/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_infiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:12:29 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/05 15:20:40 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int is_redir_in(t_token *current_token)
{
    return (current_token->type == REDIR_IN);
}

int is_heredoc(t_token *current_token)
{
    return (current_token->type == HEREDOC);
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