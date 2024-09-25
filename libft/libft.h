/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:30:22 by njackson          #+#    #+#             */
/*   Updated: 2024/09/14 16:56:49 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_isspace(int c);

// I don't know if size_t is correct
// I also don't know if I have to set const
size_t			ft_strlen(const char *s);
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);

void			*ft_memmove(void *dst, const void *src, size_t len);

size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);

int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			ft_memswap(void *a, void *b, size_t n);

char			*ft_strnstr(const char *haystack,
					const char *needle, size_t len);

int				ft_atoi(const char *str);
int				ft_atoi_base(const char *str, char *base);
int				ft_atoi_strict(const char *str, int *err);
unsigned int	ft_atou_base(const char *str, char *base);
double			ft_atod(const char *str);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strdup(const char *s1);

char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
void			ft_split_free(char **arr, void (*del)(void *));
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));

int				ft_putchar_fd(char c, int fd);
int				ft_putstr_fd(char *s, int fd);
int				ft_putendl_fd(char *s, int fd);
int				ft_putnbr_base_fd(long long n, char *base, int fd);
int				ft_putunbr_base_fd(unsigned long long n, char *base, int fd);
int				ft_putnbr_fd(long long n, int fd);
int				ft_putptr_fd(void *n, int fd);

int				ft_max(int a, int b);
int				ft_min(int a, int b);

// ARRAY STUFF

// these two will give the last occurence of the min/max number
int				ft_arrmax(int *arr, int size);
int				ft_arrmin(int *arr, int size);

// MATH FUNCTIONS

int				ft_abs(int n);
int				ft_log_base_n(int n, int b);

// LISTS

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);

void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));

void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));

// FT_PRINTF THINGS
# define HEX_UPPER "0123456789ABCDEF"
# define HEX_LOWER "0123456789abcdef"
# ifndef DEBUG
#  define DEBUG 0
# endif

int				ft_printf(const char *format, ...);
int				ft_printf_fd(int fd, const char *format, ...);
int				ft_printf_args(int fd, const char *format, va_list args);
int				ft_log(int level, const char *format, ...);

// GET NEXT LINE THINGS
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

# ifndef NUM_FD
#  define NUM_FD 256
// get next line won't be usable if you open more than 253 files
# endif

char			*get_next_line(int fd);

#endif
