/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:54:09 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/16 13:16:00 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "libft.h"
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <limits.h>
# include <stdio.h>
# include <stdarg.h>

typedef struct s_exec_list
{
	int				ac;
	int				index;
	char			*path;
	char			**flags;
	char			**av;
	char			**envp;
	struct s_exec_list	*next;
}	t_exec_list;

t_exec_list	*ft_exec_lstnew(char *pa, char **fl, int ac, char **envp);
t_exec_list	*ft_find_node(int i, t_exec_list **head);
void	ft_exec_lstadd_front(t_exec_list **lst, t_exec_list *new);
void	ft_intarr_free(int **fd, int len);
void	ft_perror(char *str, char c);
void	ft_exec_lstclear(t_exec_list **lst);
int		ft_exec_lstsize(t_exec_list *lst);

void	close_fds(int **fd, int len);
int		proc_call(int i, char c);
char	*get_path(char *str, char **envp);
char	**get_flags(char **arr);
void	init_list(int ac, char **av, char **envp, t_exec_list **head);
void	init_setup(int **pid, int ***fd, int ac, t_exec_list **head);
int		proc_call(int i, char c);
void	process_loop(t_exec_list **head, int *pid, int **fd);
void	execute(int i, int **fd, int *pid, t_exec_list **head);
int		wait_for_processes(int *pid, int ac);
void	dup_read_side(int i, int **fd, int *pid, t_exec_list **head);
void	dup_write_side(int i, int **fd, int *pid, t_exec_list **head);
void	free_and_exit(int *pid, int **fd, t_exec_list **head);
int		execution(int n, char **processed_command, char **envp);

#endif