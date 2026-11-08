/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:09:12 by tat-nguy          #+#    #+#             */
/*   Updated: 2026/10/23 12:00:24 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/*
** :::::::::::::::::::::::::::::::::* HEADERS *:::::::::::::::::::::::::::::: **
*/

# include <unistd.h>
# include <stdlib.h>
# include "ft_printf.h"
# include "get_next_line.h"

/*
** :::::::::::::::::::::::::::* STRUCT DECLARATION *::::::::::::::::::::::::: **
*/

typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}					t_list;

/*
** ::::::::::::::::::::::::::* FUNCTION PROTOTYPES *::::::::::::::::::::::::: **
*/

/*
**	is
*/

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
int		ft_isdigit_s(char *s);

/*
**	lst
*/

t_list	*ft_create_elem(void *data);
t_list	*ft_list_at(t_list *begin_list, unsigned int nbr);
void	ft_list_clear_fct(t_list *begin_list, void (*free_fct)(void *));
void	ft_list_clear(t_list *begin_list);
t_list	*ft_list_find(t_list *begin_list, void *data_ref,
			int (*cmp)(void *, void *));
void	ft_list_foreach_if(t_list *begin_list, void (*f)(void *),
			void *data_ref, int (*cmp)(void *, void *));
void	ft_list_foreach(t_list *begin_list, void (*f)(void *));
t_list	*ft_list_last(t_list *begin_list);
void	ft_list_merge(t_list **begin_list1, t_list *begin_list2);
void	ft_list_push_back(t_list **begin_list, void *data);
void	ft_list_push_front(t_list **begin_list, void *data);
t_list	*ft_list_push_strs(int size, char **strs);
void	ft_list_remove_if(t_list **begin_list, void *data_ref,
			int (*cmp)(void *, void *));
void	ft_list_reverse_fun(t_list *begin_list);
void	ft_list_reverse(t_list **begin_list);
int		ft_list_size(t_list	*begin_list);
void	ft_list_sort(t_list **begin_list, int (*cmp)(void *, void *));
void	ft_sorted_list_insert(t_list **begin_list, void *data, int (*cmp)());
void	ft_sorted_list_merge(t_list **begin_list1,
			t_list *begin_list2, int (*cmp)());

void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *data);
int		ft_lstsize(t_list *lst);

/*
**	mem
*/

void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);

/*
**	put
*/

void	ft_putchar_fd(char c, int fd);
void	ft_putchar(int c);
void	ft_putendl_fd(char *s, int fd);
void	ft_putendl(char *s);
void	ft_putnbr_fd(int n, int fd);
void	ft_putnbr(int n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putstr(char *s);

/*
**	str
*/

size_t	ft_countwords(const char *str, char *charset);
void	ft_split_free(char **arrs);
char	**ft_split(char const *s, char c);
char	**ft_split_charset(char const *s, char *charset);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strchr(const char *str, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strdup(const char *s);
char	**ft_tabdup(char **tab);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_sep(char **strs, char *sep);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);
int		ft_tablen(char **tab);
size_t	ft_strlen_egal(const char *str);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *str, int c);
char	*ft_strstr(char *str, char *to_find);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);

/*
** to
*/

int		ft_atoi(const char *nptr);
long	ft_atol(const char *s);
char	*ft_itoa(int n);
int		ft_tolower(int c);
int		ft_toupper(int c);

/*
**	math
*/
double ft_pow_int(double base, int power);
double ft_sqrt(double x);

#endif
