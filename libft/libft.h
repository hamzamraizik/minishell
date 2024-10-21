/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochangli <ochangli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:01:41 by hmraizik          #+#    #+#             */
/*   Updated: 2024/10/18 03:33:59 by ochangli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

int		ft_isalpha(int c);
int		ft_isdigit(int n);
int		ft_isalnum(int x);
int		ft_isascii(int c);
int		ft_isprint(int p);
size_t	ft_strlen( char *str);
void	*ft_memset(void *s, int value, size_t num);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, void *src, size_t n);
void	*ft_memccpy(void *dst, void *src, int c, size_t n);
void	*ft_memmove(void *dest, void *src, size_t n);
size_t	ft_strlcpy(char *dst, char *src, size_t size);
size_t	ft_strlcat(char *dst, char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr( char *s, int c);
char	*ft_strrchr( char *s, int c);
int		ft_strncmp( char *s1, char *s2, size_t n);
void	*ft_memchr( void *s, int c, size_t n);
int		ft_memcmp( void *s1, void *s2, size_t n);
char	*ft_strnstr( char *haystack, char *needle, size_t len);
int		ft_atoi( char *str);
void	*ft_calloc(size_t n_elements, size_t s_elements);
char	*ft_strdup( char *s1);
char	*ft_strndup(char *s1, int n);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char *s1, char *set);
char	**ft_split(char *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
#endif