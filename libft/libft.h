/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 14:48:09 by yoelguer          #+#    #+#             */
/*   Updated: 2020/01/30 22:14:37 by yoelguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# define BUFF_SIZE 50000
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);
void				ft_putendl(char const *s);
void				ft_strdel(char **as);
void				ft_putnbr(int n);
void				ft_strclr(char *s);
void				ft_putchar(char c);
void				ft_memdel(void **ap);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putstr(char const *s);
void				ft_putchar_fd(char c, int fd);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_bzero(void *s, size_t n_bytes);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_striter(char *s, void (*f)(char *));
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *str1, const void *str2, size_t n);
void				*ft_memset(void *p, int c, size_t n_bytes);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strtrim(char const *s);
char				*ft_strdup(const char *s1);
char				*ft_itoa(int n);
char				*ft_strnew(size_t size);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strmapi(char const *s, char(*f)(unsigned int, char));
char				*ft_strncat(char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				**ft_strsplit(char const *s, char c);
char				*ft_strnstr(const char *haystack,
							const char *needle, size_t len);
int					**ft_tabnew_two(size_t x, size_t y);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
int					ft_strequ(char const *s1, char const *s2);
int					ft_count_words_sep(char const *s, char c);
int					ft_max(int *tab, unsigned int len);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					get_next_line(const int fd, char **line);

#endif
