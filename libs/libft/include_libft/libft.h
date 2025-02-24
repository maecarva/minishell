/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:16:18 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/23 18:37:25 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <stdbool.h>
# include <limits.h>
# include "../src_binary_tree_libft/ft_btree.h"


// lists
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;

typedef struct s_dlist
{
	void		*content;
	struct s_dlist	*prev;
	struct s_dlist	*next;
}	t_dlist;

void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **head, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);

// file descriptors
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);

// chars
int		ft_isascii(int c);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);

// strings
char	**ft_split(char const *s, char c);
char	**ft_split_charset(char *str, char *charset);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *src);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t size);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_count_char_in_str(char *str, char c);
int		ft_count_char_in_str_rev(char *str, char c, int index);
bool	ft_is_in_charset(char c, char *charset);
char	ft_first_char_in_charset_rev(char *s, char *charset, int index);
char	ft_first_char_in_charset(char *s, char *charset);
bool	ft_str_is_only_charset(char *str, char *charset);

// memory
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memchr(const void *memoryBlock, int searchedChar, size_t size);
int		ft_memcmp(const void *pointer1, const void *pointer2, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t count);
void	*ft_memmove(void *dest, const void *src, size_t count);
void	*ft_memset(void *dest, int c, size_t count);

// int
int		ft_atoi(const char *str);
char	*ft_itoa(int n);

//extra
int		ft_abs(int nb);
void	ft_close(int *fd);
void	ft_error(char *str, int exit_status);
void	ft_free_double_ptr(char ***split);
void	ft_free_simple_ptr(char **ptr);
int		ft_issign(int c);
int		ft_isspace(int c);
int		ft_max(int nb1, int nb2);
int		ft_min(int nb1, int nb2);
int		ft_only_space(char *str);
void	ft_perror(char *str, int exit_status);
void	ft_skip_spaces(char *str, int *i);
char	*ft_str_three_join(char const *s1, char const *s2, char const *s3);
int		ft_strcmp(char *src1, char *src2);
void	ft_swap(int *a, int *b);
bool	ft_only_whitespaces_after(char *str);
long	ft_atol(const char *str);
bool	ft_strisnumber(char *str);
bool	ft_islong(char *str);
size_t	ft_strcpy(char *dest, const char *src);

// double linked list
void	dll_clear(t_dlist **dlist);
t_dlist	*dll_add_back(t_dlist **dlist, t_dlist *new_elem);
t_dlist	*dll_new(void *content);
int		dll_size(t_dlist **dlist);
int		dll_size_between(t_dlist *start, t_dlist *end);
void	dll_insert(t_dlist *l1, t_dlist *l2);

#endif
