/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:03:25 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/05/13 18:43:09 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTS_H
# define LISTS_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <limits.h>
# include <stdio.h>
# include <stdarg.h>

typedef struct s_list
{
	int				ac;
	int				index;
	char			*path;
	char			**flags;
	char			**av;
	char			**envp;
	struct s_list	*next;
}	t_list;

void	ft_putchar_fd(char c, int fd, int *count);
void	ft_putchex_fd(unsigned int n, int fd, int *count);
void	ft_puthex_fd(unsigned int n, int fd, int *count);
void	ft_putnbr_fd(int n, int fd, int *count);
void	ft_putptr_fd(void *ptr, int fd, int *count);
void	ft_putstr_fd(char *s, int fd, int *count);
void	ft_putuns_fd(unsigned int n, int fd, int *count);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
int		ft_printf(const char *str, ...);
size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_array_free(char **array);
int		ft_array_len(char **array);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst);
t_list	*ft_lstnew(char *pa, char **fl, int ac, char **envp);
int		ft_lstsize(t_list *lst);
char	*ft_strdup(const char *s);
t_list	*ft_find_node(int i, t_list **head);
void	ft_intarr_free(int **fd, int len);
char	**ft_free(char **ptr, size_t k);
void	ft_perror(char *str, char c);

#endif