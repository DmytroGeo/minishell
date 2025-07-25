/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:32:39 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/25 15:09:24 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "parsing.h"
#include "execution.h"

//  use CTRL + D to exit the shell
/*
	if CTRL + D is pressed (which sends an EOF — End Of File to *line)
	essentialy setting it to NULL which ends loop and shell terminates
	but prompt needs to be empty for CTRL + D to work (for now) .
	You may need to compile with readline lib "cc read_line.c -lreadline"
	but that may be because im using mbp, the school computers probaly
	have the libraries installed and you dont neet to include the lib.
*/
int	main(int argc, char **argv, char **envp)
{
	char		*line;
	int			exit_code;
	t_cshell	cshell;

	((void)argc, (void)argv);
	exit_code = 0;
	init_cshell(&cshell, envp);
	line = readline(cshell.prompt);
	while (line != NULL)
	{
		if (*line)
		{
			add_history(line);
			lexing(&cshell, line);
			exit_code = init_processes(&cshell);
			evaluate_and_execute(&cshell, &exit_code);
		}
		free(line);
		line = readline(cshell.prompt);
	}
}
