/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:32:39 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/21 15:50:55 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include <signal.h>

// SIGINT
// SIGSTOP
// SIGQUIT

//  use CTRL + D to exit the shell
/*
	if CTRL + D is pressed (which sends an EOF — End Of File to *line)
	essentialy setting it to NULL which ends loop and shell terminates
	but prompt needs to be empty for CTRL + D to work (for now) .
	You may need to compile with readline lib "cc read_line.c -lreadline"
	but that may be because im using mbp, the school computers probaly
	have the libraries installed and you dont neet to include the lib.
*/ 
// typedef struct s_proc
// {
// 	int num_inf;
// 	int num_outf;
// 	int *infiles;
// 	int *outfiles;
// 	char **cmd_and_args;
// }           t_proc;

// typedef struct s_main
// {
// 	char *prompt;
// 	char **envp;
// 	int	num_of_proc;
// 	t_proc *proc_array;	
// }           t_main;

// void    print_main_stuff1(t_main *main)
// {
//     char **envp = main->envp;
//     char *prompt = main->prompt;
//     char **curr = envp;
//     ft_printf(1, "\n");
//     ft_printf(1, "Prompt : \n");
//     ft_printf(1, "\n");
//     ft_printf(1, "%s\n", prompt);
//     ft_printf(1, "\n");   
//     ft_printf(1, "Environment Variables : \n");
//     ft_printf(1, "\n");
//     while (*curr)
//     {
//         ft_printf(1, "%s\n", *curr);
//         curr++;
//     }
//     return ;
// }

void	print_processes_and_their_contents(t_proc *process_array, int number_of_processes)
{
	int i = 0;
	int k = 0;
	while (i < number_of_processes)
	{
		ft_printf(1, "For process %d\n", i + 1);
		ft_printf(1, "\n");
		ft_printf(1, "The number of legal infiles is: \n");
		ft_printf(1, "\n");
		ft_printf(1, "%d\n", (process_array[i]).num_inf);
		ft_printf(1, "\n");
		ft_printf(1, "The number of legal outfiles is: \n");
		ft_printf(1, "\n");
		ft_printf(1, "%d\n", (process_array[i]).num_outf);
		ft_printf(1, "\n");
		ft_printf(1, "The number of commands and arguments is: \n");
		ft_printf(1, "\n");
		ft_printf(1, "%d\n", ft_array_len((process_array[i]).cmd_and_args));
		ft_printf(1, "\n");
		if (((process_array[i]).cmd_and_args))
		{
			while (k < ft_array_len((process_array[i]).cmd_and_args))
			{
				if (k == 0)
				{
					ft_printf(1, "The command is:\n");
					ft_printf(1, "%s\n", (process_array[i]).cmd_and_args[k]);
					ft_printf(1, "\n");		
				}
				else
				{
					ft_printf(1, "Argument %d is:\n", k);
					ft_printf(1, "%s\n", (process_array[i]).cmd_and_args[k]);
					ft_printf(1, "\n");						
				}
				k++;
			}
			k = 0;
		}
		i++;
	}
}
	
void    print_cshell_stuff2(t_cshell *cshell, int exit_code)
{
	if (exit_code != 0)
	{
		ft_printf(1, "Syntax error detected\n");
		return ;
	}
	int number_of_processes = cshell->num_of_proc;
	t_proc *process_array = cshell->proc_array;
	ft_printf(1, "\n");
	ft_printf(1, "The number of processes is: \n");
	ft_printf(1, "\n");
	ft_printf(1, "%d\n", number_of_processes);
	ft_printf(1, "\n");
	print_processes_and_their_contents(process_array, number_of_processes);

	return ;
}

int	main(int argc, char **argv, char **envp)
{
	((void)argc, (void)argv);
	char *line;
	int exit_code;
	t_cshell cshell;
	
	exit_code = 0;
	init_cshell(&cshell, envp);
	line = readline(cshell.prompt);
	while (line != NULL)
	{
		if (*line) // if there's something in the line 
		{
			add_history(line);
			lexing(&cshell, line);
			// expansions(&cshell, exit_code);
			exit_code = init_processes(&cshell);
			evaluate_and_execute(&cshell, &exit_code);
		}
		free(line);
		init_cshell(&cshell, envp);
		line = readline(cshell.prompt);
	}
}

