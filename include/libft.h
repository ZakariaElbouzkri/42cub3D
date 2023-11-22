/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 02:26:09 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/11/22 09:37:35 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <stdint.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

void	*ft_memset(void *b, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strchr(const char *s, char c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(const char *src);
char	*ft_strtrim(const char *str, const char *set);
char	**ft_split(char const *s, char c);
int		ft_strcmp(char *s1, char *s2);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *str);
int		ft_max(int a, int b);
bool	ft_empty(const char *str);
void	ft_puterror(int n, ...);
char	*get_next_line(int fd);

#endif
